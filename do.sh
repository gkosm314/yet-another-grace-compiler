#!/bin/bash

./gracec < $1 > a.ll
llc-12 a.ll -o a.s
clang a.s libgrc.a -o a.out