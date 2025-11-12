# CJson Examples

[日本語はこちら](README.ja.md)

`EspHelper::CJsonDocument` wraps the ESP-IDF `cJSON` library with RAII semantics and Arduino-flavored helpers.

## Key Concepts
- **Creation helpers** – `CJsonDocument::NewObject()` / `NewArray()` build empty containers, while `CJsonDocument::Parse()` converts JSON text into a tree.
- **Ownership** – The destructor automatically calls `cJSON_Delete`, but you can transfer ownership via `release()` if another API needs the raw pointer.
- **Strings** – To avoid guessing buffer sizes, you can read into `String` directly; fixed buffers are still supported via the explicit overloads.

## API Reference
- Lifetime: `bool valid()`, `void reset(cJSON *replacement = nullptr)`, `cJSON *release()`
- Serialization: `String toString(bool pretty = false)`
- Object mutation: `addString`, `addNumber`, `addBool`, `addNull`, `addObject`, `addArray`
- Array mutation: `arrayAddNumber`, `arrayAddString`, `arrayAddBool`, `arrayAddNull`, `arrayAdd(CJsonDocument&&)`
- Access: `getString`, `getNumber`, `getBool`, `arraySize`, `arrayItem`

## Example Overview
- `BuildAndParse/BuildAndParse.ino` – builds a nested object, prints both compact and pretty strings, then parses them back to retrieve values.
