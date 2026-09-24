# include < WiFi .h >
# include < WebServer .h >
/*
APP LOGIC & STATE
*/
enum WaveformType { WAVE_SINE , WAVE_SQUARE , WAVE_TRIANGLE };
struct ChannelState {
float frequency ;
float amplitude ;
WaveformType waveform ;
bool enabled ;
};
struct AppState {
int active_channel ;
ChannelState ch [2];
};
AppState globalState = {
0 ,
{
{10000.00 , 5.00 , WAVE_SINE , true } ,
{1000.00 , 3.50 , WAVE_SINE , true }
}
};
// Hardware control functions ( Updates serial monitor )
void app_set_frequency (int ch , float freq ) {
globalState . ch [ ch ]. frequency = freq ;
Serial . printf ( " [ HARDWARE ] ␣ CH % d ␣ Frequency ␣ set ␣ to : ␣ %.2 f ␣ Hz \ n " , ch +1 ,
freq ) ;
}
void app_set_amplitude (int ch , float amp ) {
globalState . ch [ ch ]. amplitude = amp ;
Serial . printf ( " [ HARDWARE ] ␣ CH % d ␣ Amplitude ␣ set ␣ to : ␣ %.2 f ␣ V \ n " , ch +1 ,
amp ) ;
}
void app_set_waveform (int ch , WaveformType w ) {
globalState . ch [ ch ]. waveform = w ;
const char * names [] = { " SINE " , " SQUARE " , " TRIANGLE " };
Serial . printf ( " [ HARDWARE ] ␣ CH % d ␣ Waveform ␣ set ␣ to : ␣ % s \ n " , ch +1 , names [
w ]) ;
}
void app_set_enable (int ch , bool en ) {
globalState . ch [ ch ]. enabled = en ;
Serial . printf ( " [ HARDWARE ] ␣ CH % d ␣ State : ␣ % s \ n " , ch +1 , en ? " ENABLED " :
" DISABLED " ) ;
}
void app_set_active_channel (int ch ) {
globalState . active_channel = ch ;
Serial . printf ( " [ UI ] ␣ Switched ␣ to ␣ Channel ␣ % d \ n " , ch +1) ;
}
const AppState * app_get_state () { return & globalState ; }
/*
WEB SERVER & UI CONTENT
*/
const char * ssid = " ESP32 - Generator " ;
const char * password = " password123 " ;
WebServer server (80) ;
const char INDEX_HTML [] PROGMEM = R " rawliteral (
<! DOCTYPE ␣ html >
< html ␣ lang = " en " >
< head >
␣ ␣ < meta ␣ charset = " UTF -8 " ␣ / >
␣ ␣ < meta ␣ name = " viewport " ␣ content = " width = device - width , initial - scale =1.0 "
/ >
␣ ␣ < title > Dual ␣ Channel ␣ Function ␣ Generator </ title >
␣ ␣ < link ␣ href = " https :// fonts . googleapis .com / css2 ? family = Space + Mono :
wght@400 ;700& family = Syne : wght@400 ;600;700;800& display = swap " rel ="
stylesheet "/ >
< style >
* , *:: before , *:: after { box - sizing : border - box ; margin : 0; padding
: 0; }
: root {
-- radius - md : 10 px ; -- radius - xl : 22 px ;
-- bg : #080 b10 ; -- surface : #0 e1319 ; -- surface -2: #131920; -- border
: #1 c2330 ; -- border - light : #2 a3545 ;
-- ch1 : #00 ffaa ; -- ch1 - dim : #00 ffaa22 ; -- ch1 - glow : #00 ffaa55 ;
-- ch2 : # ff6b35 ; -- ch2 - dim : # ff6b3522 ; -- ch2 - glow : # ff6b3555 ;
-- text - primary : # dde8f5 ; -- text - sec : #6 b7f99 ; -- text - muted :
#384556;
-- font - ui : ’ Syne ’ , sans - serif ; -- font - mono : ’ Space ␣ Mono ’ ,
monospace ;
-- active : var ( - - ch1 ) ; -- active - dim : var ( - - ch1 - dim ) ; -- active - glow
: var ( - - ch1 - glow ) ;
}
body { background : var ( - - bg ) ; font - family : var ( - - font - ui ) ; color :
var ( - - text - primary ) ; padding : 20 px 16 px ; background - image :
linear - gradient ( rgba (0 ,255 ,170 ,.01) 1 px , transparent 1 px ) ,
linear - gradient (90 deg , rgba (0 ,255 ,170 ,.01) 1 px , transparent 1 px )
; background - size : 40 px 40 px ; }
. app { width : 100%; max - width : 500 px ; margin : 0 auto ; }
. header { display : flex ; align - items : center ; gap : 16 px ; padding :
px ; background : var ( - - surface ) ; border : 1 px solid var ( - - border
) ; border - radius : var ( - - radius - xl ) ; margin - bottom : 14 px ; }
. header - icon { width : 40 px ; height : 40 px ; border - radius : 8 px ;
background : var ( - - ch1 ) ; display : flex ; align - items : center ;
justify - content : center ; font - size : 20 px ; box - shadow : 0 0 20 px
var ( - - ch1 - glow ) ; }
. tab - bar { display : grid ; grid - template - columns : 1 fr 1 fr ; gap : 8 px ;
margin - bottom : 14 px ; }
. tab - btn { padding : 14 px ; border - radius : var ( - - radius - md ) ; border :
px solid var ( - - border - light ) ; background : var ( - - surface ) ; color
: var ( - - text - sec ) ; font - weight : 800; cursor : pointer ; display :
flex ; align - items : center ; justify - content : center ; gap : 8 px ;
transition : 0.2 s ; }
. tab - btn . active - ch1 { background : var ( - - ch1 - dim ) ; color : var ( - - ch1 )
; border - color : var ( - - ch1 ) ; }
. tab - btn . active - ch2 { background : var ( - - ch2 - dim ) ; color : var ( - - ch2 )
; border - color : var ( - - ch2 ) ; }
. tab - dot { width : 8 px ; height : 8 px ; border - radius : 50%; background :
currentColor ; }
. ch - panel { background : var ( - - surface ) ; border : 1 px solid var ( - -
border ) ; border - radius : var ( - - radius - xl ) ; overflow : hidden ; }
. ch - panel - header { display : flex ; align - items : center ; justify -
content : space - between ; padding : 14 px 20 px ; background : var ( - -
surface -2) ; border - bottom : 1 px solid var ( - - border ) ; }
. pwr - btn { padding : 6 px 12 px ; border - radius : 99 px ; border : 1 px
solid var ( - - border - light ) ; background : var ( - - bg ) ; color : var ( - -
text - sec ) ; font - family : var ( - - font - mono ) ; font - size : 10 px ;
cursor : pointer ; }
. pwr - btn . on { background : var ( - - active - dim ) ; color : var ( - - active ) ;
border - color : var ( - - active - glow ) ; }
. canvas - wrap { padding : 10 px ; background : #05070 a ; position :
relative ; }
. canvas - corner { position : absolute ; font - family : var ( - - font - mono ) ;
font - size : 9 px ; color : var ( - - text - muted ) ; padding : 10 px ; z -
index : 2; }
. tr { right : 0; top : 0; } . tl { left : 0; top : 0; }
canvas { width : 100%; height : 160 px ; display : block ; }
. stats - grid { display : grid ; grid - template - columns : 1 fr 1 fr ; border
- bottom : 1 px solid var ( - - border ) ; }
. stat - cell { padding : 16 px 20 px ; border - right : 1 px solid var ( - -
border ) ; }
. stat - label { font - family : var ( - - font - mono ) ; font - size : 10 px ; color
: var ( - - text - sec ) ; text - transform : uppercase ; margin - bottom : 4 px
; }
. stat - value { display : flex ; align - items : baseline ; font - family :
var ( - - font - mono ) ; font - size : 22 px ; font - weight : 700; color : var
( - - active ) ; }
. stat - input { background : transparent ; border : none ; color : inherit
; font : inherit ; width : 100%; outline : none ; }
. stat - select { background : transparent ; border : none ; color :
inherit ; font : inherit ; font - size : 12 px ; cursor : pointer ;
outline : none ; padding - left : 4 px ; }
. controls - section { padding : 20 px ; display : flex ; flex - direction :
column ; gap : 20 px ; }
. wave - btns { display : grid ; grid - template - columns : repeat (3 , 1 fr ) ;
gap : 8 px ; }
. wave - btn { padding : 12 px ; border - radius : var ( - - radius - md ) ; border :
px solid var ( - - border - light ) ; background : var ( - - bg ) ; color :
var ( - - text - sec ) ; cursor : pointer ; display : flex ; flex - direction :
column ; align - items : center ; gap : 8 px ; font - size : 11 px ; font -
weight : 700; }
. wave - btn svg { width : 30 px ; height : 18 px ; stroke : currentColor ;
fill : none ; stroke - width : 2; }
. wave - btn . active - ch1 { background : var ( - - ch1 - dim ) ; color : var ( - - ch1
) ; border - color : var ( - - ch1 ) ; }
. wave - btn . active - ch2 { background : var ( - - ch2 - dim ) ; color : var ( - - ch2
) ; border - color : var ( - - ch2 ) ; }
input [ type = range ] { - webkit - appearance : none ; width : 100%; height :
px ; border - radius : 2 px ; outline : none ; margin : 15 px 0;
background : var ( - - border - light ) ; }
input [ type = range ]:: - webkit - slider - thumb { - webkit - appearance : none ;
width : 18 px ; height : 18 px ; border - radius : 50%; background : var
( - - bg ) ; border : 2 px solid var ( - - active ) ; box - shadow : 0 0 10 px
var ( - - active - glow ) ; cursor : pointer ; }
. slider - current { float : right ; font - family : var ( - - font - mono ) ; font
- size : 11 px ; color : var ( - - active ) ; }
. summary - bar { display : grid ; grid - template - columns : 1 fr 1 fr ; gap :
px ; margin - top : 14 px ; }
. summary - chip { background : var ( - - surface ) ; border : 1 px solid var
( - - border ) ; border - radius : var ( - - radius - md ) ; padding : 12 px ;
display : flex ; align - items : center ; gap : 8 px ; font - size : 10 px ; }
. disabled { opacity : 0.25; pointer - events : none ; }
</ style >
</ head >
< body >
< div class = " app " >
< div class = " header " >
< div class = " header - icon " > </ div >
<div > < h1 style = " font - size :16 px " > FUNCTION GENERATOR </ h1 > < p style = "
font - size :10 px ; ␣ color : var ( - - text - sec ) " >10 Hz - 1 MHz DUAL CHANNEL
</ p > </ div >
</ div >
< div class = " tab - bar " >
< button id = " tab1 " class = " tab - btn " onclick = " UI . switchChannel (1) " ><
span class = " tab - dot " > </ span > CH 1 </ button >
< button id = " tab2 " class = " tab - btn " onclick = " UI . switchChannel (2) " ><
span class = " tab - dot " > </ span > CH 2 </ button >
</ div >
< div class = " ch - panel " >
< div class = " ch - panel - header " >
< div style = " font - weight :800; ␣ font - size :13 px " id = " chTitle " > CHANNEL
</ div >
< button class = " pwr - btn " id = " pwrBtn " onclick = " UI . togglePower () " >
POWER : ON </ button >
</ div >
< div class = " canvas - wrap " >
< div class = " canvas - corner ␣ tl " id = " cornerTL " >CH1 </ div > < div class = "
canvas - corner ␣ tr " id = " cornerTR " > SINE </ div >
< canvas id = " waveCanvas " > </ canvas >
</ div >
< div id = " mainControls " >
< div class = " stats - grid " >
< div class = " stat - cell " >
< div class = " stat - label " > Frequency </ div >
< div class = " stat - value " >< input type = " number " id = " freqInput "
step = " 0.01 " class = " stat - input " onchange = " UI . onFreqInput (
this . value ) " / > < select id = " freqUnit " class = " stat - select "
onchange = " UI . onFreqUnitChange () " >< option > Hz </ option > <
option > kHz </ option > < option > MHz </ option > </ select > </ div >
</ div >
< div class = " stat - cell " >
< div class = " stat - label " > Amplitude </ div >
< div class = " stat - value " >< input type = " number " id = " ampInput "
step = " 0.01 " class = " stat - input " onchange = " UI . onAmpInput (
this . value ) " / > < select id = " ampUnit " class = " stat - select "
onchange = " UI . onAmpUnitChange () " >< option >V </ option > < option >
mV </ option > </ select > </ div >
</ div >
</ div >
< div class = " controls - section " >
< div class = " wave - btns " >
< button class = " wave - btn " id = " btn - sine " onclick = " UI . setWave ( ’
sine ’) " >< svg viewBox = " 0 ␣ 0 ␣ 36 ␣ 20 " >< path d = " M2 ␣ 10 ␣ C6 ␣ 2 , ␣ 10 ␣
, ␣ 13 ␣ 10 ␣ C16 ␣ 18 , ␣ 20 ␣ 18 , ␣ 23 ␣ 10 ␣ C26 ␣ 2 , ␣ 30 ␣ 2 , ␣ 34 ␣ 10 " / > </ svg >
SINE </ button >
< button class = " wave - btn " id = " btn - square " onclick = " UI . setWave
( ’ square ’) " >< svg viewBox = " 0 ␣ 0 ␣ 36 ␣ 20 " >< path d = " M2 ␣ 15 ␣ L2 ␣ 5 ␣
L12 ␣ 5 ␣ L12 ␣ 15 ␣ L22 ␣ 15 ␣ L22 ␣ 5 ␣ L32 ␣ 5 ␣ L32 ␣ 15 ␣ L34 ␣ 15 " / > </ svg >
SQUARE </ button >
< button class = " wave - btn " id = " btn - triangular " onclick = " UI .
setWave ( ’ triangular ’) " >< svg viewBox = " 0 ␣ 0 ␣ 36 ␣ 20 " >< path d = "
M2 ␣ 15 ␣ L9 ␣ 5 ␣ L18 ␣ 15 ␣ L27 ␣ 5 ␣ L34 ␣ 15 " / > </ svg > TRI </ button >
</ div >
<div >
< div class = " stat - label " > Frequency < span class = " slider - current
" id = " curFreq " > </ span > </ div >
< input type = " range " id = " freqSlider " min = " 10 " max = " 1000000 "
oninput = " UI . onFreqChange ( this . value ) " / >
</ div >
<div >
< div class = " stat - label " > Amplitude < span class = " slider - current
" id = " curAmp " > </ span > </ div >
< input type = " range " id = " ampSlider " min = " 0 " max = " 1000 " oninput
= " UI . onAmpChange ( this . value ) " / >
</ div >
</ div >
</ div >
</ div >
< div class = " summary - bar " >
< div class = " summary - chip " id = " sum1 " > CH1 : - - </ div >
< div class = " summary - chip " id = " sum2 " > CH2 : - - </ div >
</ div >
</ div >
< script >
const Network = {
send ( ep , p ={}) { fetch ( ‘/${ ep }?${ new URLSearchParams ( p ) } ‘) . catch ( e = >
console . error ( e ) ) ; } ,
async getStatus () { try { const r = await fetch ( ’/ getStatus ’) ; return
await r . json () ; } catch ( e ) { return null ; } }
};
const State = {
active : 1 , maxF : 1000000 , minF : 10 , maxA : 10 ,
ch : { 1: { f : 10000.00 , a : 5.00 , w : ’ sine ’ , c : ’ #00 ffaa ’ , en : true } ,
: { f : 1000.00 , a : 3.50 , w : ’ sine ’ , c : ’# ff6b35 ’ , en : true } }
};
const UI = {
update () {
const c = State . ch [ State . active ];
const root = document . documentElement ;
root . style . setProperty ( ’ -- active ’ , State . active === 1 ? ’ var ( - - ch1 )
’ : ’ var ( - - ch2 ) ’) ;
root . style . setProperty ( ’ -- active - dim ’ , State . active === 1 ? ’ var ( - -
ch1 - dim ) ’ : ’ var ( - - ch2 - dim ) ’) ;
root . style . setProperty ( ’ -- active - glow ’ , State . active === 1 ? ’ var
( - - ch1 - glow ) ’ : ’ var ( - - ch2 - glow ) ’) ;
document . getElementById ( ’ tab1 ’) . className = ’tab - btn ’ + ( State .
active === 1 ? ’␣ active - ch1 ’ : ’ ’) ;
document . getElementById ( ’ tab2 ’) . className = ’tab - btn ’ + ( State .
active === 2 ? ’␣ active - ch2 ’ : ’ ’) ;
document . getElementById ( ’ chTitle ’) . textContent = " CHANNEL ␣ " + State
. active ;
document . getElementById ( ’ cornerTL ’) . textContent = " CH " + State .
active ;
document . getElementById ( ’ cornerTR ’) . textContent = c . w . toUpperCase ()
;
document . getElementById ( ’ pwrBtn ’) . textContent = " POWER : ␣ " + ( c . en ?
" ON " : " OFF " ) ;
document . getElementById ( ’ pwrBtn ’) . className = " pwr - btn " + ( c . en ? "
␣ on " : " " ) ;
document . getElementById ( ’ mainControls ’) . className = c . en ? " " : "
disabled " ;
// Freq Format
let fv = c . f ; let fu = " Hz " ;
if( fv >= 1 e6 ) { fv /= 1 e6 ; fu = " MHz " ; } else if( fv >= 1 e3 ) { fv /=
e3 ; fu = " kHz " ; }
document . getElementById ( ’ freqInput ’) . value = fv . toFixed (2) ;
document . getElementById ( ’ freqUnit ’) . value = fu ;
document . getElementById ( ’ curFreq ’) . textContent = c . f . toFixed (2) + "
␣ Hz " ;
// Amp Format
let av = c . a ; let au = document . getElementById ( ’ ampUnit ’) . value ;
if( au === ’ mV ’) av *= 1000;
document . getElementById ( ’ ampInput ’) . value = av . toFixed (2) ;
document . getElementById ( ’ curAmp ’) . textContent = c . a . toFixed (2) + " ␣
V " ;
document . getElementById ( ’ freqSlider ’) . value = c . f ;
document . getElementById ( ’ ampSlider ’) . value = ( c . a / State . maxA ) *
;
[ ’ sine ’ , ’ square ’ , ’ triangular ’ ]. forEach ( w = > {
document . getElementById ( ’btn - ’+ w ) . className = ’ wave - btn ’ + ( c . w
=== w ? ‘ active - ch${ State . active } ‘ : ’ ’) ;
}) ;
for ( let i =1; i <=2; i ++) {
const s = State . ch [ i ];
document . getElementById ( ’ sum ’+ i ) . textContent = ‘ CH$ { i }: ${ s . en ?
s . f . toFixed (2) + ’ Hz ’ : ’ OFF ’} ‘;
document . getElementById ( ’ sum ’+ i ) . style . color = s . en ? State . ch [ i
]. c : ’ var ( - - text - muted ) ’;
}
} ,
switchChannel ( ch ) { State . active = ch ; Network . send ( ’ setActiveChannel
’ , { ch }) ; this . update () ; } ,
togglePower () { const c = State . ch [ State . active ]; c . en = ! c . en ;
Network . send ( ’ setEnable ’ , { ch : State . active , val : c . en ?1:0}) ; this
. update () ; } ,
onFreqChange ( v ) { let hz = Math . max ( State . minF , Math . min ( State . maxF ,
Number ( v ) ) ) ; State . ch [ State . active ]. f = hz ; Network . send ( ’ setFreq ’
, { ch : State . active , val : hz . toFixed (2) }) ; this . update () ; } ,
onFreqInput ( v ) { let hz = parseFloat ( v ) ; let u = document .
getElementById ( ’ freqUnit ’) . value ; if( u === ’ kHz ’) hz *= 1000; else
if( u === ’ MHz ’) hz *= 1000000; this . onFreqChange ( hz ) ; } ,
onFreqUnitChange () { this . onFreqInput ( document . getElementById ( ’
freqInput ’) . value ) ; } ,
onAmpChange ( v ) { let amp = ( v /1000) * State . maxA ; State . ch [ State .
active ]. a = amp ; Network . send ( ’ setAmp ’ , { ch : State . active , val :
amp . toFixed (2) }) ; this . update () ; } ,
onAmpInput ( v ) { let val = parseFloat ( v ) ; if( document . getElementById ( ’
ampUnit ’) . value === ’ mV ’) val /= 1000; this . onAmpChange (( val / State
. maxA ) *1000) ; } ,
onAmpUnitChange () { this . onAmpInput ( document . getElementById ( ’ ampInput
’) . value ) ; } ,
setWave ( type ) { State . ch [ State . active ]. w = type ; Network . send ( ’
setWave ’ , { ch : State . active , type }) ; this . update () ; }
};
const Oscilloscope = {
canvas : document . getElementById ( ’ waveCanvas ’) , phase : 0 ,
start () { this . ctx = this . canvas . getContext ( ’2 d ’) ; window . onresize =
() = > this . resize () ; this . resize () ; this . draw () ; } ,
resize () { this . canvas . width = this . canvas . offsetWidth ; this . canvas .
height = this . canvas . offsetHeight ; } ,
draw () {
const { ctx , canvas : v } = this ; const { width :w , height : h } = v ; const
c = State . ch [ State . active ];
ctx . clearRect (0 ,0 ,w , h ) ;
ctx . strokeStyle = ’ #1 c2330 ’; ctx . lineWidth = 1;
for ( let i =0; i <=8; i ++) { ctx . beginPath () ; ctx . moveTo ( i * w /8 , 0) ;
ctx . lineTo ( i * w /8 , h ) ; ctx . stroke () ; }
for ( let i =0; i <=4; i ++) { ctx . beginPath () ; ctx . moveTo (0 , i * h /4) ;
ctx . lineTo (w , i * h /4) ; ctx . stroke () ; }
if( c . en ) {
ctx . beginPath () ; ctx . strokeStyle = c . c ; ctx . lineWidth = 3; ctx .
shadowBlur = 10; ctx . shadowColor = c . c ;
// Cycles based on frequency ( wavelength changes )
let visibleCycles = 1 + ( Math . log10 ( c . f ) - 1) * 2;
for ( let x =0; x < w ; x ++) {
let t = ( x / w ) * Math . PI * 2 * visibleCycles + this . phase ;
let y =0;
if( c . w === ’ sine ’) y = Math . sin ( t ) ;
else if( c . w === ’ square ’) y = Math . sin ( t ) >= 0 ? 0.7 : -0.7;
else y = ( Math . abs (( t % ( Math . PI *2) ) - Math . PI ) / Math . PI ) * 2
- 1;
const py = h /2 - y *( h /3) *( c . a / State . maxA ) ;
x ===0 ? ctx . moveTo (x , py ) : ctx . lineTo (x , py ) ;
}
ctx . stroke () ; ctx . shadowBlur = 0;
this . phase += 0.05; // Fixed animation speed
}
requestAnimationFrame (() = > this . draw () ) ;
}
};
Oscilloscope . start () ;
setInterval ( async () = > {
const s = await Network . getStatus () ;
if( s && document . activeElement . tagName !== ’ INPUT ’) {
State . active = s . activeChannel ;
for ( let i =1; i <=2; i ++) {
State . ch [ i ]. f = s . channels [ i ]. frequency ;
State . ch [ i ]. a = s . channels [ i ]. amplitude ;
State . ch [ i ]. w = s . channels [ i ]. waveType ;
State . ch [ i ]. en = s . channels [ i ]. enabled ;
}
UI . update () ;
}
} , 2000) ;
UI . update () ;
</ script >
</ body >
</ html >
) rawliteral " ;
/* ␣
␣ ␣ ␣ SERVER ␣ HANDLERS ␣ ( With ␣ Serial ␣ Output )
␣ ␣ ␣
␣ */
void ␣ handleRoot () ␣ { ␣ server . send (200 , ␣ " text / html " ,␣ INDEX_HTML ) ; ␣ }
void ␣ handleSetFreq () ␣ {
␣ ␣ int ␣ ch ␣ = ␣ server . arg ( " ch " ) . toInt () ␣ -␣ 1;
␣ ␣ float ␣ val ␣ = ␣ server . arg ( " val " ) . toFloat () ;
␣ ␣ if ( ch >=0 ␣ && ␣ ch <2) ␣ app_set_frequency ( ch , ␣ val ) ;
␣ ␣ server . send (200 , ␣ " text / plain " ,␣ " OK " ) ;
}
void ␣ handleSetAmp () ␣ {
␣ ␣ int ␣ ch ␣ = ␣ server . arg ( " ch " ) . toInt () ␣ -␣ 1;
␣ ␣ float ␣ val ␣ = ␣ server . arg ( " val " ) . toFloat () ;
␣ ␣ if ( ch >=0 ␣ && ␣ ch <2) ␣ app_set_amplitude ( ch , ␣ val ) ;
␣ ␣ server . send (200 , ␣ " text / plain " ,␣ " OK " ) ;
}
void ␣ handleSetEnable () ␣ {
␣ ␣ int ␣ ch ␣ = ␣ server . arg ( " ch " ) . toInt () ␣ -␣ 1;
␣ ␣ bool ␣ val ␣ = ␣ server . arg ( " val " ) . toInt () ␣ == ␣ 1;
␣ ␣ if ( ch >=0 ␣ && ␣ ch <2) ␣ app_set_enable ( ch , ␣ val ) ;
␣ ␣ server . send (200 , ␣ " text / plain " ,␣ " OK " ) ;
}
void ␣ handleSetWave () ␣ {
␣ ␣ int ␣ ch ␣ = ␣ server . arg ( " ch " ) . toInt () ␣ -␣ 1;
␣ ␣ String ␣ t ␣ = ␣ server . arg ( " type " ) ;
␣ ␣ WaveformType ␣ w ␣ = ␣ WAVE_SINE ;
␣ ␣ if ( t == " square " ) ␣ w = WAVE_SQUARE ; ␣ else ␣ if ( t == " triangular " ) ␣ w =
WAVE_TRIANGLE ;
␣ ␣ if ( ch >=0 ␣ && ␣ ch <2) ␣ app_set_waveform ( ch , ␣ w ) ;
␣ ␣ server . send (200 , ␣ " text / plain " ,␣ " OK " ) ;
}
void ␣ handleSetActiveChannel () ␣ {
␣ ␣ int ␣ ch ␣ = ␣ server . arg ( " ch " ) . toInt () ␣ -␣ 1;
␣ ␣ if ( ch >=0 ␣ && ␣ ch <2) ␣ app_set_active_channel ( ch ) ;
␣ ␣ server . send (200 , ␣ " text / plain " ,␣ " OK " ) ;
}
void ␣ handleGetStatus () ␣ {
␣ ␣ const ␣ AppState * ␣ s ␣ = ␣ app_get_state () ;
␣ ␣ String ␣ j ␣ = ␣ " {\ " activeChannel \": " + String (s - > active_channel + 1) + "
,\" channels \":{ " ;
for (int i =0; i <2; i ++) {
j += " \" " + String ( i +1) + " \":{\" frequency \": " + String (s - > ch [ i ].
frequency , 2) + " ,\" amplitude \": " + String (s - > ch [ i ]. amplitude ,
) + " ,\" enabled \": " + String (s - > ch [ i ]. enabled ? " true " : " false " ) +
" ,\" waveType \":\" " ;
if(s - > ch [ i ]. waveform == WAVE_SQUARE ) j += " square " ; else if(s - > ch [ i ].
waveform == WAVE_TRIANGLE ) j += " triangular " ; else j += " sine " ;
j += " \"} " ; if( i ==0) j += " ," ;
}
j += " }} " ;
server . send (200 , " application / json " , j ) ;
}
void setup () {
Serial . begin (115200) ;
WiFi . softAP ( ssid , password ) ;
Serial . print ( " AP ␣ Started . ␣ IP : ␣ " ) ; Serial . println ( WiFi . softAPIP () ) ;
server . on ( " / " , handleRoot ) ;
server . on ( " / setFreq " , handleSetFreq ) ;
server . on ( " / setAmp " , handleSetAmp ) ;
server . on ( " / setWave " , handleSetWave ) ;
server . on ( " / setEnable " , handleSetEnable ) ;
server . on ( " / setActiveChannel " , handleSetActiveChannel ) ;
server . on ( " / getStatus " , handleGetStatus ) ;
server . begin () ;
}
void loop () {
server . handleClient () ;
}
