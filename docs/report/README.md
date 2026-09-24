# Report provenance

The repository was reconstructed from the files actually delivered in
`function_generator_source/`.

## Present

- `LATEST_INDEXED_REPORT_FULL_TEXT.txt` — complete parsed text of the latest indexed
  109-page report, identified by the handoff as `ELP305_2__1___2_(1).pdf`
- `extracted_code/` — ten PDF-extracted listings plus a manifest
- `AGENT_INSTRUCTIONS.md` — reconstruction requirements
- `EXTRACTION_NOTES.md` — extraction history
- `LINKS_AND_EXTERNAL_RESOURCES.md` — the one explicit external product URL found
- `assets/MEDIA_MANIFEST.md` — names and page locations of extracted media
- `assets/embedded_images/` — raster images extracted from the earlier report
- `assets/report_pages/` — selected rendered pages from the earlier report
- `source_reports/ELP305_2__4_accessible_raw.pdf` — earlier 105-page report PDF

## Referenced but absent

- the raw 109-page latest PDF
- original standalone firmware, CAD, PCB, Gerber, or video files

The absent files were not recreated as placeholders. The earlier PDF, extracted media,
full latest-report text, and original damaged listings remain unmodified for auditability;
cleaned files elsewhere in the repository make only syntax-level repairs or clearly
documented packaging changes.

## Reconstruction policy

- Preserve conflicting report specifications rather than select unsupported values.
- Do not imply that declarations have implementations.
- Do not turn proposed features into completed features.
- Distinguish the report's web-state demonstrator from real waveform hardware control.
- Do not assert a license that the source package did not supply.
