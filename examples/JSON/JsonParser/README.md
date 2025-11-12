# JsonParser Examples

[日本語はこちら](README.ja.md)

These sketches show how to consume JSON documents on ESP32 using `EspHelper::JsonParser`, a header-only wrapper for the ESP-IDF `json_parser` component.

## Key Concepts

- **Token buffer required** – The ESP-IDF parser relies on a token array (from JSMN). Construct `JsonParser` with either an owned size (`JsonParser parser(128);`) or a user-supplied `json_tok_t` buffer. Every JSON primitive/object/array consumes at least one token (objects need one token for themselves plus one per child), so plan roughly 4–5 tokens per JSON field as a safe starting point. Choose a count that comfortably covers the largest document you expect.
- **Parse → Query → End** – Call `parse(json)` to tokenize, use the `get*` helpers or `enterObject/enterArray` to navigate, then call `end()` (or let the destructor do it). Starting a second parse automatically ends the previous one.
- **Object vs array helpers** – `getInt("foo", value)` reads a named field from the current object. To inspect array elements, use `arrayGetInt(index, value)` after entering the array with `enterArray("pins")`. The `enter*` helpers maintain the parser cursor, so remember to call `leave*` when you finish with a container.
- **String helpers** – When reading into `String`, the wrapper first queries the required length so you do not have to guess a buffer size. For fixed-size buffers, use the overload that takes `char *` and `size`.

## API Reference

### Constructors
| Signature | Description |
|-----------|-------------|
| `JsonParser(json_tok_t *tokens, size_t tokenCount)` | Borrow an external token buffer. |
| `JsonParser(json_tok_t (&tokens)[N])` | Stack-array helper. |
| `JsonParser(size_t tokenCount)` | Allocate tokens internally. |

### Lifecycle & Navigation
- `bool parse(const char *json, size_t length = 0)` / `parse(const String&)`
- `void end()` – releases the context (also called automatically by the destructor).
- `bool enterObject(const char *name)`, `bool leaveObject()`
- `bool enterArray(const char *name, int *numElements = nullptr)`, `bool leaveArray()`
- `bool arrayEnter(uint32_t index)`, `bool arrayLeave()` and related `arrayEnterObject/arrayLeaveObject` helpers map directly to ESP-IDF APIs.

### Value Accessors
- Object getters: `getBool`, `getInt`, `getInt64`, `getFloat`, `getString`.
- Array getters: `arrayGetBool`, `arrayGetInt`, `arrayGetFloat`, `arrayGetString`.
- String helpers determine the required length via `json_obj_get_strlen` / `json_arr_get_strlen` before copying.

## Example Overview

- `BasicParse/BasicParse.ino` – Parses a nested JSON document, walks into named objects/arrays, and fetches typed values (bool/int/float/string) while printing them to `Serial`.

All parser examples assume Arduino-ESP32 v2.0.0 or later with the stock ESP-IDF components that ship in the core; no extra setup is needed beyond placing this library in `~/Arduino/libraries/`.
