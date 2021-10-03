#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "../Errors/Errors.h"

#define MatrixType float
#define MatrixDimensions unsigned long long int
#define PrecisionType unsigned int
#define TOP_RANDOM 100
#define BOT_RANDOM -100

struct Matrix
{
    MatrixDimensions rowsCount;
    MatrixDimensions colsCount;

    MatrixType **matrix;
};

long long int mtime();

void freeMatrix(struct Matrix matrix);

struct Matrix readMatrixFromFile(char *fileName, ErrorType *errorCode);

void writeMatrixToFile(char *fileName, struct Matrix matrix, PrecisionType precision, ErrorType *errorCode);

void showMatrix(struct Matrix matrix, PrecisionType precision, ErrorType *errorCode);

struct Matrix matrixMultiplication(struct Matrix A, struct Matrix B, ErrorType *errorCode);

struct Matrix matrixMultiplicationParallel(struct Matrix A, struct Matrix B, ErrorType *errorCode);

struct Matrix generateRandomMatrix(MatrixDimensions rowsCount, MatrixDimensions colsCount, ErrorType *errorCode);

int compareMatrices(struct Matrix matrix1, struct Matrix matrix2);