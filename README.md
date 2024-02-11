# Yet-Another-Grace-Compiler

| Authors                                                                |
|------------------------------------------------------------------------|
| Giorgos Kosmas  ([@gkosm314](https://github.com/gkosm314)) |
| Apostolis Stamatis ([@apostolis1](https://github.com/apostolis1))      |

## Implementation Decisions

The following are implementation decisions that were not specified by the language specification

## Building

`make` builds the `gracec` executable

`make clean` deletes all automatically generated files except the `gracec` executable

`make distclean` same as `make clean` but also deletes the `gracec` executable

## Using the gracec compiler

The `gracec` executable can be used to produce intermediate and final code

The following flags are supported:

`-o`: Make optimizations

`-i` Read input from stdin and dump intermediate code to stdout

`-f` Read input from stdin and dump final code to stdout

If neither `-i` nor `-f` are set, the source code is read from a file, the path of which is the only argument passed to `gracec`

Setting both the `-i` and `-f` flags is not supported, since the output would consist of both intermediate and final code, making it confusing to read 

The final code can then be compile to an executable by a compiler like `clang`

Additionally, the intermediate code can be compiled to final code using llc. This is useful in case additional passes are to be added to llvm via llc

An example workflow is provided in `do.sh`:

```
./gracec -i < PATH/TO/GRC/FILE > a.imm
llc-12 -regalloc=pbqp a.imm -o a.asm
clang a.asm libgrc.a -no-pie -o a.out
```
