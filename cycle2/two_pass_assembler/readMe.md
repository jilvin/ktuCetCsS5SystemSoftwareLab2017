# Two Pass Assembler for SIC Architecture

## Command for Compiling

#### First Pass
gcc src/1_first_pass/first_pass.c src/common/optab/optab.c src/common/systab/systab.c src/common/intermediate/intermediate.c -o build/first_pass

#### Second Pass
gcc src/2_second_pass/second_pass.c src/common/optab/optab.c src/common/systab/systab.c src/common/intermediate/intermediate.c -o build/second_pass

## Execution

#### First Pass
./build/first_pass test_file

#### Second Pass
./build/second_pass

#### Two Pass Assembler (First Pass + Second Pass)

## Current Issues

#### First Pass
locCtr is considered as a decimal integer. It should be in hexadecimal representation.
