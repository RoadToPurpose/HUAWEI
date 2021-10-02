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
```
gcc -fopenmp main.c -o main
```

# Launching
To run the program, you need to use the following command (without angle brackets):
```
./main argument_list
```

## Arguments
the first argument (without taking into account the program name) is the mode of the program Values:
- file - if the source data should be read from files
- random - if the source data should be generated
        
if the first argument is file
- the second argument is the path to the file with matrix A (see [File format](https://github.com/RoadToPurpose/HUAWEI#File-format))
- the third argument is the path to the file with matrix B (see [File format](https://github.com/RoadToPurpose/HUAWEI#File-format))
- the fourth argument is the number of decimal places when displaying matrices

if the first argument is random
- the second argument is the count of rows in matrix A
- the third argument is the count of cols in matrix A
- the fourth argument is the count of rows in matrix B
- the fifth argument is the count of cols in matrix B
- the sixth argument is the number of decimal places when displaying matrices

## File format
The program uses the following format for input and output files:
- the first row is the number of rows of the matrix
- the second row is the number of cols of the matrix
- Next, there are rows_count rows (each with cols_count elements), which contain the elements of the matrix

### Example:
A matrix that contains 3 rows and 2 columns, with elements 1 2 3 4 5 6, respectively:
```
3
2
1 2
3 4
5 6
```

## Return value
Return value is an error code (an description line is displayed in the console): 
| Error code | Description |
|:-----------:|:---------------------|
| 0 | success |
| 1 | non-existent file |
| 2 | incorrect parameters of the matrix size (for example, if it was indicated that the matrix should have -10 rows) |
| 3 | if matrices do not match in size |
| 4 | incorrect precision value (less than or equal to zero) |
| 5 | wrong number of arguments |
| 6 | invalid argument value |

## Results of the program
The results of the program are output to text files (see [File format](https://github.com/RoadToPurpose/HUAWEI#File-format)). If the random mode is specified, then matrix A is output to the file "matrixA.txt", and matrix B is output to the file "matrixB.txt".
The result of the sequential algorithm is output to the "sequential.txt" file.
The result of the parallel algorithm is output to the "parallel.txt" file.

## Console output
The program displays the following messages:
- Time of matrix multiplication in milliseconds for the sequential algorithm
- File name with the result of the sequential algorithm
- Time of matrix multiplication in milliseconds for a parallel algorithm
- The name of the file with the result of the parallel algorithm
- The result of comparing the results of the algorithms  
If the "random" mode is selected, the program displays messages about where the generated matrices are stored.  
If an error occurs, the program displays the error text.  

## Examples
### Example matrices
In the folder "Examples" there are files "A.txt" and "B.txt".  
Content of the file "A.txt":
```
4
3
1 2 3
4 5 6
7 8 9
10 11 12
```
Content of the file "B.txt":
```
3
4
13 14 15 16
17 18 19 20
21 22 23 24
```
### With file input
#### Launching
Launching the program with reading initial data from files "A.txt" and "B.txt" and with outputting matrices with precision up to three decimal places :
```
./main file Examples/B.txt Examples/A.txt 3
```
#### Results
Content of the file "sequential.txt":  
```
3
3
334.000 392.000 450.000 
422.000 496.000 570.000 
510.000 600.000 690.000 
```
Content of the file "parallel.txt":  
```
3
3
334.000 392.000 450.000 
422.000 496.000 570.000 
510.000 600.000 690.000 
```
#### Console output:
```
[SEQUENTIAL] Multiplication time in milliseconds: 0
[SEQUENTIAL] Result is written to a file: sequential.txt
[PARALLEL] Multiplication time in milliseconds: 19
[PARALLEL] Result is written to a file: parallel.txt
The results of the functions are equal
```

Launching the program with the generation of initial data (matrix A has a size of 5x10, matrix B has a size of 10x3) and with the output of matrices with an accuracy of four decimal places
```
./main random 5 10 10 3 4
```