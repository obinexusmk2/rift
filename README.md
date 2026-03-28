# RIFT Is a Flexible Translator

**OBINexus Computing Division** | *Computing From the Heart*
**Technical Lead:** Nnamdi Michael Okpala

> RIFT is not YACC. RIFT listens before it compiles.

---

## What is RIFT?

**RIFT** (RIFT Is a Flexible Translator) is a C/C++ meta-compiler framework that bridges pseudocode and executable C through a Z→Y→X internal reduction:

| Layer | Name | Function |
|-------|------|----------|
| Z | Lexical Pattern Space | Regex automata, token normalization |
| Y | Semantic Transition | Token → Intermediate Representation |
| X | C Binding Layer | IR → C-compatible / hexdump canonical output |

RIFT uses a **Token Triplet** as its fundamental unit:

```c
struct rift_token {
    rift_token_type_t  type;    /* semantic classification */
    rift_token_value_t value;   /* the data */
    rift_memory_span_t memory;  /* memory governance */
};
```

Pattern literals:
- `R""(str)` — static string (compile-time constant)
- `R''(ch)`  — dynamic character (runtime modifiable)

---

## Build

### Requirements

- CMake 3.16+
- GCC / Clang / MSVC (C11 + C++17)
- GNU Make or MinGW Make

### Quick Start

```sh
# Using CMake
cmake -S . -B build
cmake --build build

# Using Make (auto-detects compiler)
make
```

### Build Outputs

| Artifact | Description |
|----------|-------------|
| `build/rift` / `build/rift.exe` | CLI executable |
| `build/librift.a` / `rift.lib` | Static library |
| `build/librift.so` / `librift.dll` | Shared library |

### CMake Options

```sh
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DRIFT_BUILD_TESTS=ON \
    -DRIFT_BUILD_SHARED=ON
```

---

## CLI

```
Usage: rift <command> [options] [files]

Commands:
  bridge       Polyglot interop bridge
  test         Run test suite
  lang         Pattern matching engine
  man          Display manual pages
  doctor       Run diagnostics
  raf          Regulation as firmware
  compile      Compile source file
  tokenize     Tokenize input file
  parse        Parse to AST
  emit         Emit target code

Options:
  --help, -h     Show this help message
  --version, -v  Show version information
```

### Examples

```sh
rift doctor                    # check environment
rift compile example.rf        # compile to C
rift tokenize example.rf       # inspect token stream
rift parse example.rf          # inspect AST
rift emit --target hexdump example.rf  # hexdump canonical
rift bridge --init             # initialize trident topology
rift lang --pattern "^[let]$" example.rf
rift man compile               # manual page
rift raf --validate            # regulation check
```

---

## Project Structure

```
rift/
├── CMakeLists.txt
├── Makefile                   # cross-platform wrapper
├── cmake/
│   ├── platform.cmake
│   └── options.cmake
├── include/rift/
│   ├── rift.h                 # master public header
│   ├── platform.h             # RIFT_API, Win32/POSIX compat
│   ├── token.h                # token triplet
│   ├── memory.h               # memory spans
│   ├── lexer.h                # DFA tokenizer
│   ├── parser.h               # AST
│   ├── semantic.h             # Z->Y->X reduction
│   ├── codegen.h              # IR generation
│   ├── emitter.h              # target emission
│   ├── codec.h                # CIR + two-phase codec
│   ├── bridge.h               # polyglot bridge / trident
│   ├── pattern.h              # pattern matching engine
│   ├── cli.h                  # CLI dispatch
│   └── version.h              # version defines
├── src/
│   ├── cli/                   # subcommand handlers
│   ├── core/                  # rift.c, token.c, memory.c, platform.c
│   ├── lang/                  # lexer, parser, semantic, pattern, emitter
│   ├── codec/                 # CIR linker + emit targets
│   ├── bridge/                # trident, ropen (hex), polyglot
│   └── raf/                   # regulation as firmware
└── tests/
    ├── test_token.c
    ├── test_lexer.c
    ├── test_codec.c
    └── test_cli.c
```

---

## PseudoC Example

```c
// example.rf
let x = R''("input value");    // dynamic runtime string
let y = R""("static value");   // compile-time string literal

fn greet(name) {
    print("Hello, " + name);
    return 0;
}

if (x != "") {
    greet(x);
} else {
    while (true) {
        greet(y);
        break;
    }
}
```

RIFT emits C:

```c
#include <stdio.h>
#include <string.h>

int greet(const char *name) {
    printf("Hello, %s\n", name);
    return 0;
}

int main(void) {
    char x[64]; strcpy(x, "input value");
    const char *y = "static value";
    if (strcmp(x, "") != 0) { greet(x); }
    else { while (1) { greet(y); break; } }
    return 0;
}
```

---

## Testing

```sh
# CMake
cd build && ctest --output-on-failure

# Make
make test
```

---

## Architecture Notes

- **No explicit stages** exposed in API or CLI. Z→Y→X is internal.
- **No YACC**. RIFT is its own pattern-driven reduction engine.
- **Token Triplet** (`type`, `value`, `memory`) — compile-time safety by separation.
- **Two-phase Codec**: LINK (forward pass → CIR) then CODEC (CIR → target). Memory-first ordering: SPAN before ASSIGN.
- **Trident resolution** (bridge): diamond dependency topology with 2/3 consensus (Eze/Uche/Obi polarity system).
- **Regulation as Firmware** (raf): policy enforcement without build lock-in.

---

## License

OBINexus Computing Division. All rights reserved.
*Computing From the Heart.*
