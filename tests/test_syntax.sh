#!/usr/bin/env bash

for FILE in /home/apostolis/Shmmy/compilers/grace/ntua_compilers/grace/syntax_gen/progs/*;
do 
    if ! ./gracec < $FILE > /dev/null; then echo "$FILE Failed"
    # else echo "Success"
    fi
done
