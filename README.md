# Description
Test task for the competition from HUAWEI.

# Task
Implement in the C programming language parallel program and test to it using one or more technologies.
Two real matrices A and B are given. Calculate the matrix C = A ∙ B.

# About the program
The program is written in C using OpenMP.

# Compilation
The program has been successfully compiled and tested with the gcc v9.3.0 compiler on the Ubuntu 20.04 LTS.
To compile, you need to use the following command:
gcc -fopenmp main.c -o main

# Launching
To run the program, you need to use the following command (without angle brackets):
./main argument_list

## Arguments
the first argument (without taking into account the program name) is the mode of the program Values:
- file - if the source data should be read from files
- random - if the source data should be generated
        
if the first argument is file
- the second argument is the path to the file with matrix A
- the third argument is the path to the file with matrix B
- the fourth argument is the number of decimal places when displaying matrices

if the first argument is random
- the second argument is the count of rows in matrix A
- the third argument is the count of cols in matrix A
- the fourth argument is the count of rows in matrix B
- the fifth argument is the count of cols in matrix B
- the sixth argument is the number of decimal places when displaying matrices