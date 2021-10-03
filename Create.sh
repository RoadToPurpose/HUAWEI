#! bin/bash
gcc -fopenmp main.c Matrix/Matrix.h Matrix/Matrix.c Errors/Errors.h Errors/Errors.c -o main
./main $*