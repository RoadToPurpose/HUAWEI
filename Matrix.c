#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "Errors.c"

#define MatrixType float
#define MatrixDimensions unsigned long long int
#define PrecisionType unsigned int
#define TOP_RANDOM 100
#define BOT_RANDOM -100

// getting the running time of the program in milliseconds
long long int mtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);

    return (long long int)t.tv_sec * 1000 + t.tv_usec / 1000;
}

struct Matrix
{
    MatrixDimensions rowsCount;
    MatrixDimensions colsCount;

    MatrixType **matrix;
};

void freeMatrix(struct Matrix matrix)
{

    MatrixDimensions i;
#pragma omp parallel for default(none) shared(matrix) private(i)
    for (i = 0; i < matrix.rowsCount; i++)
    {
        free(matrix.matrix[i]);
    }
    free(matrix.matrix);
}

struct Matrix readMatrixFromFile(char *fileName, ErrorType *errorCode)
{
    FILE *file = fopen(fileName, "r");

    struct Matrix matrix;
    if (!file)
    {
        (*errorCode) = BAD_FILE;
        return matrix;
    }

    fscanf(file, "%llu", &matrix.rowsCount);
    fscanf(file, "%llu", &matrix.colsCount);

    if ((matrix.rowsCount <= 0) || (matrix.colsCount <= 0))
    {
        (*errorCode) = BAD_SIZE_OF_MATRIX;
        return matrix;
    }

    matrix.matrix = (MatrixType **)malloc(matrix.rowsCount * sizeof(MatrixType *));
    for (MatrixDimensions i = 0; i < matrix.rowsCount; i++)
    {
        matrix.matrix[i] = (MatrixType *)malloc(matrix.colsCount * sizeof(MatrixType));
        for (MatrixDimensions j = 0; j < matrix.colsCount; j++)
        {
            fscanf(file, "%f", &matrix.matrix[i][j]);
        }
    }

    fclose(file);
    (*errorCode) = SUCCESS;

    return matrix;
}

void writeMatrixToFile(char *fileName, struct Matrix matrix, PrecisionType precision, ErrorType *errorCode)
{

    FILE *file = fopen(fileName, "w");

    if (!file)
    {
        (*errorCode) = BAD_FILE;
        return;
    }

    if (precision <= 0)
    {
        (*errorCode) = BAD_PRECISION;
        return;
    }

    char precisionStr[20];
    sprintf(precisionStr, "%%.%uf ", precision);

    fprintf(file, "%llu\n", matrix.rowsCount);
    fprintf(file, "%llu\n", matrix.colsCount);
    for (MatrixDimensions i = 0; i < matrix.rowsCount; i++)
    {
        for (MatrixDimensions j = 0; j < matrix.colsCount; j++)
        {
            fprintf(file, precisionStr, matrix.matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    (*errorCode) = SUCCESS;
}

void showMatrix(struct Matrix matrix, PrecisionType precision, ErrorType *errorCode)
{

    if (precision <= 0)
    {
        (*errorCode) = BAD_PRECISION;
        return;
    }

    char precisionStr[20];
    sprintf(precisionStr, "%%.%uf ", precision);

    for (MatrixDimensions i = 0; i < matrix.rowsCount; i++)
    {
        for (MatrixDimensions j = 0; j < matrix.colsCount; j++)
        {
            printf(precisionStr, matrix.matrix[i][j]);
        }
        printf("\n");
    }
}

struct Matrix matrixMultiplication(struct Matrix A, struct Matrix B, ErrorType *errorCode)
{

    struct Matrix result;
    if (A.colsCount != B.rowsCount)
    {
        (*errorCode) = BAD_DIMESIONS_OF_MATRICES;
        return result;
    }

    result.rowsCount = A.rowsCount;
    result.colsCount = B.colsCount;

    MatrixDimensions i;
    MatrixDimensions j;
    MatrixDimensions r;

    result.matrix = (MatrixType **)malloc(result.rowsCount * sizeof(MatrixType *));

    for (i = 0; i < result.rowsCount; i++)
    {
        result.matrix[i] = (MatrixType *)malloc(result.colsCount * sizeof(MatrixType));
        for (j = 0; j < result.colsCount; j++)
        {
            result.matrix[i][j] = 0;
            for (r = 0; r < A.colsCount; r++)
            {
                result.matrix[i][j] += A.matrix[i][r] * B.matrix[r][j];
            }
        }
    }

    (*errorCode) = SUCCESS;

    return result;
}

struct Matrix matrixMultiplicationParallel(struct Matrix A, struct Matrix B, ErrorType *errorCode)
{

    struct Matrix result;
    if (A.colsCount != B.rowsCount)
    {
        (*errorCode) = BAD_DIMESIONS_OF_MATRICES;
        return result;
    }

    result.rowsCount = A.rowsCount;
    result.colsCount = B.colsCount;

    MatrixDimensions i;
    MatrixDimensions j;
    MatrixDimensions r;

    result.matrix = (MatrixType **)malloc(result.rowsCount * sizeof(MatrixType *));

#pragma omp parallel for default(none) shared(A, B, result) private(i, j, r)
    for (i = 0; i < result.rowsCount; i++)
    {
        result.matrix[i] = (MatrixType *)malloc(result.colsCount * sizeof(MatrixType));
        for (j = 0; j < result.colsCount; j++)
        {
            result.matrix[i][j] = 0;
            for (r = 0; r < A.colsCount; r++)
            {
                result.matrix[i][j] += A.matrix[i][r] * B.matrix[r][j];
            }
        }
    }

    (*errorCode) = SUCCESS;

    return result;
}

struct Matrix generateRandomMatrix(MatrixDimensions rowsCount, MatrixDimensions colsCount, ErrorType *errorCode)
{

    srand(mtime());

    struct Matrix matrix;
    if ((rowsCount <= 0) || (colsCount <= 0))
    {
        (*errorCode) = BAD_DIMESIONS_OF_MATRICES;
        return matrix;
    }

    matrix.rowsCount = rowsCount;
    matrix.colsCount = colsCount;
    matrix.matrix = (MatrixType **)malloc(matrix.rowsCount * sizeof(MatrixType *));

    MatrixDimensions i;
    MatrixDimensions j;
#pragma omp parallel for default(none) shared(matrix) private(i, j)
    for (i = 0; i < matrix.rowsCount; i++)
    {
        matrix.matrix[i] = (MatrixType *)malloc(matrix.colsCount * sizeof(MatrixType));
        for (j = 0; j < matrix.colsCount; j++)
        {
            matrix.matrix[i][j] = rand() % (abs(TOP_RANDOM) + abs(BOT_RANDOM)) + BOT_RANDOM + 1;
        }
    }

    return matrix;
}

int compareMatrices(struct Matrix matrix1, struct Matrix matrix2)
{

    if (matrix1.colsCount != matrix2.colsCount)
    {
        return 0;
    }

    if (matrix1.rowsCount != matrix2.rowsCount)
    {
        return 0;
    }

    int flag = 1;

    MatrixDimensions i;
    MatrixDimensions j;
#pragma omp parallel for default(none) shared(matrix1, matrix2) private(i, j) reduction(&& \
                                                                                        : flag)
    for (i = 0; i < matrix1.rowsCount; i++)
    {
        for (j = 0; j < matrix1.colsCount; j++)
        {
            if (matrix1.matrix[i][j] != matrix2.matrix[i][j])
            {
                flag = 0;
            }
        }
    }

    return flag;
}