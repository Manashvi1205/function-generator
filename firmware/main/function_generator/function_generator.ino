#include <WebServer.h>
#include <WiFi.h>

enum WaveformType { WAVE_SINE, WAVE_SQUARE, WAVE_TRIANGLE };

struct ChannelState {
  float frequency;
  float amplitude;
  WaveformType waveform;
  bool enabled;
};

struct AppState {
  int active_channel;
  ChannelState channels[2];
};

AppState state = {
  0,
  {{10000.0f, 5.0f, WAVE_SINE, true}, {1000.0f, 3.5f, WAVE_SINE, true}}
};

const char *SSID = "ESP32-Generator";
const char *PASSWORD = "password123";
WebServer server(80);

// The supplied backend listing embedded a second copy of its UI. This compact page keeps
// the reconstructed sketch self-contained; web/index.html preserves the fuller Listing 9 UI.
const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html><html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Function Generator</title><style>
body{font:16px system-ui;max-width:32rem;margin:2rem auto;padding:0 1rem;background:#080b10;color:#e6eef8}
section{background:#0e1319;border:1px solid #263241;border-radius:1rem;padding:1rem;margin:1rem 0}
button,input,select{font:inherit;margin:.25rem;padding:.5rem;background:#131920;color:inherit;border:1px solid #3a4858;border-radius:.4rem}
</style></head><body><h1>Function Generator</h1><p>ESP32 state demonstrator</p>
<section><label>Channel <select id="ch"><option>1</option><option>2</option></select></label>
<label>Frequency <input id="freq" type="number" min="10" max="1000000"> Hz</label>
<label>Amplitude <input id="amp" type="number" min="0" max="10" step=".1"> V</label>
<select id="wave"><option>sine</option><option>square</option><option>triangular</option></select>
<button id="power">Toggle output</button></section><pre id="status"></pre><script>
const $=id=>document.getElementById(id),send=(p,q)=>fetch(p+"?"+new URLSearchParams(q));
freq.onchange=()=>send("/setFreq",{ch:ch.value,val:freq.value});
amp.onchange=()=>send("/setAmp",{ch:ch.value,val:amp.value});
wave.onchange=()=>send("/setWave",{ch:ch.value,type:wave.value});
power.onclick=()=>send("/setEnable",{ch:ch.value,val:power.dataset.on==="true"?0:1});
ch.onchange=()=>send("/setActiveChannel",{ch:ch.value});
async function sync(){let s=await(await fetch("/getStatus")).json(),c=s.channels[ch.value];
freq.value=c.frequency;amp.value=c.amplitude;wave.value=c.waveType;power.dataset.on=c.enabled;
status.textContent=JSON.stringify(s,null,2)}setInterval(sync,1000);sync();
</script></body></html>
)HTML";

bool readChannel(int &channel) {
  channel = server.arg("ch").toInt() - 1;
  return channel >= 0 && channel < 2;
}

void reply(bool valid) {
  server.send(valid ? 200 : 400, "text/plain", valid ? "OK" : "Invalid parameter");
}

void handleSetFrequency() {
  int channel;
  float value = server.arg("val").toFloat();
  bool valid = readChannel(channel) && value >= 10.0f && value <= 1000000.0f;
  if (valid) {
    state.channels[channel].frequency = value;
    Serial.printf("[STATE] CH%d frequency: %.2f Hz\n", channel + 1, value);
  }
  reply(valid);
}

void handleSetAmplitude() {
  int channel;
  float value = server.arg("val").toFloat();
  bool valid = readChannel(channel) && value >= 0.0f && value <= 10.0f;
  if (valid) {
    state.channels[channel].amplitude = value;
    Serial.printf("[STATE] CH%d amplitude: %.2f V\n", channel + 1, value);
  }
  reply(valid);
}

void handleSetWaveform() {
  int channel;
  String value = server.arg("type");
  bool valid = readChannel(channel) &&
               (value == "sine" || value == "square" || value == "triangular");
  if (valid) {
    state.channels[channel].waveform =
      value == "square" ? WAVE_SQUARE : value == "triangular" ? WAVE_TRIANGLE : WAVE_SINE;
    Serial.printf("[STATE] CH%d waveform: %s\n", channel + 1, value.c_str());
  }
  reply(valid);
}

void handleSetEnable() {
  int channel;
  String value = server.arg("val");
  bool valid = readChannel(channel) && (value == "0" || value == "1");
  if (valid) state.channels[channel].enabled = value == "1";
  reply(valid);
}

void handleSetActiveChannel() {
  int channel;
  bool valid = readChannel(channel);
  if (valid) state.active_channel = channel;
  reply(valid);
}

const char *waveformName(WaveformType waveform) {
  if (waveform == WAVE_SQUARE) return "square";
  if (waveform == WAVE_TRIANGLE) return "triangular";
  return "sine";
}

void handleGetStatus() {
  String json = "{\"activeChannel\":" + String(state.active_channel + 1) + ",\"channels\":{";
  for (int i = 0; i < 2; ++i) {
    if (i) json += ',';
    json += "\"" + String(i + 1) + "\":{\"frequency\":" +
            String(state.channels[i].frequency, 2) + ",\"amplitude\":" +
            String(state.channels[i].amplitude, 2) + ",\"enabled\":" +
            (state.channels[i].enabled ? "true" : "false") + ",\"waveType\":\"" +
            waveformName(state.channels[i].waveform) + "\"}";
  }
  server.send(200, "application/json", json + "}}");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(SSID, PASSWORD);
  Serial.print("Access point: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", [] { server.send_P(200, "text/html", INDEX_HTML); });
  server.on("/setFreq", handleSetFrequency);
  server.on("/setAmp", handleSetAmplitude);
  server.on("/setWave", handleSetWaveform);
  server.on("/setEnable", handleSetEnable);
  server.on("/setActiveChannel", handleSetActiveChannel);
  server.on("/getStatus", handleGetStatus);
  server.onNotFound([] { server.send(404, "text/plain", "Not found"); });
  server.begin();
}

void loop() {
  server.handleClient();
}
