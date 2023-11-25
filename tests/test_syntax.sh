#!/usr/bin/env bash

# for FILE in /home/apostolis/Shmmy/compilers/grace/ntua_compilers/grace/syntax_gen/progs/*;
for FILE in /home/gkosm/Documents/ECE/semester_10/compiler_project/yet-another-grace-compiler/tests/type_checking/*;
do 
    if ! ./gracec < $FILE > /dev/null; then echo "$FILE Failed"
    # else echo "Success"
    fi
done
