# CJson Examples

[日本語はこちら](README.ja.md)

`EspHelper::CJsonDocument` wraps the ESP-IDF `cJSON` library with RAII semantics and Arduino-flavored helpers. Use it when you want the rich feature set of cJSON (parsing arbitrary JSON, duplicating nodes, pretty printing) but prefer not to manage lifetime manually.

## Highlights
- Create objects/arrays with `NewObject()` / `NewArray()` and add primitive values or nested documents.
- Parse existing text via `CJsonDocument::Parse()` and extract data with `getString` / `getNumber` / `getBool`.
- `toString(true)` produces pretty output for debugging; `toString(false)` keeps it compact for transport.

## Example overview
- `BuildAndParse/BuildAndParse.ino` – builds a nested JSON payload, prints both compact and pretty versions, then parses it back to read key values.
