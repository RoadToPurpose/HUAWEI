#! bin/bash
gcc -fopenmp main.c -o main
./main $*