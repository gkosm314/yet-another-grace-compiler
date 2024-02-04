#!/bin/bash

./gracec < $1 > a.ll
llc-12 -regalloc=pbqp a.ll -o a.s
clang a.s libgrc.a -no-pie -o a.out