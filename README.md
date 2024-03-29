# Yet-Another-Grace-Compiler

| Authors                                                                |
|------------------------------------------------------------------------|
| Giorgos Kosmas  ([@gkosm314](https://github.com/gkosm314)) |
| Apostolis Stamatis ([@apostolis1](https://github.com/apostolis1))      |

## Prerequisites

The project was developed using `llvm-12`.

## Building

`make` builds the `gracec` executable and the `libgrc.a` file. 

`make clean` deletes all automatically generated files except the `gracec` executable.

`make distclean` same as `make clean` but also deletes the `gracec` executable.

## Testing

An extensive testing suite is developed to assure  

Tests are available in the `/tests` directory and are organized in the following way:

- `lexical`: testing lexer
- `optimizations`: testing optimization passes
- `parser`: testing parser
- `scope`: testing scopes
- `type_checking`: testing types
- `runtime`: testing code generation
- `runtime/leetcode`: leetcode problems solved in `grace`
- `runtime/repo`: tests from the [NTUA compilers repo](https://github.com/kostis/ntua_compilers/tree/master)
- `runtime/unit`: unit tests

The convention used in the naming of tests is that if a filename begins with `err` (e.g. `/tests/parser/err_arr_def_expr.grc`) the compilation should not be successfull.

A utility script is provided in `tests/run_tests.sh` to automatically run the test suite (make sure you change the directory path at the beginning of a file)

## Using the gracec compiler

The `gracec` executable can be used to produce intermediate and final code

The following flags are supported:

`-o`: Make optimizations

`-i` Read input from stdin and dump intermediate code to stdout

`-f` Read input from stdin and dump final code to stdout

If neither `-i` nor `-f` are set, the source code is read from a file, the path of which is the only argument passed to `gracec`. In that case, the intermediate code is place to a `.imm` file in the same path as the source code file. Same goes about the final code which is placed in a `.asm` file. For example, running `./gracec /tmp/buy_and_sell_stock.grc` will produce the files: `/tmp/buy_and_sell_stock.imm` and `/tmp/buy_and_sell_stock.asm`

Setting both the `-i` and `-f` flags is not supported, since the output would consist of both intermediate and final code, making it confusing to read.

The final code can then be compiled to an executable by a compiler like `clang`. Note that in this case a file containing the library calls should be linked, eg `libgrc.a`.

Additionally, the intermediate code can be compiled to final code using llc. This is useful in case additional passes or params are to be added to llvm via llc.

An example workflow as provided in `do.sh` (invoked as `./do.sh PATH/TO/GRC/FILE`):

```
./gracec -i -o < $1 > a.imm
llc-12 -regalloc=pbqp a.imm -o a.asm
clang a.asm libgrc.a -no-pie -o a.out
```

## Optimizations

The following optimizations are applied:

- Local optimizations
- Intermediate code optimizations with data and control flow analysis
- Register allocation and final code optimizations

## Library functions

The library function file `libgrc.a` is generated using code from [this repo](https://github.com/avtzis/ntua-grace-runtime-lib)