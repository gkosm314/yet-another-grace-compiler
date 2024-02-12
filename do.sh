#!/bin/bash

./gracec -i -o < $1 > a.imm
llc-12 -regalloc=pbqp a.imm -o a.asm
clang a.asm libgrc.a -no-pie -o a.out