
#include "Matrix/Matrix.h"
#include <string.h>

int main(int argc, char *argv[])
{

    ErrorType errorCode = SUCCESS;
    struct Matrix matrixA;
    struct Matrix matrixB;
    PrecisionType precision;

    if (strcmp(argv[1], "file") == 0)
    {

        if (argc != 5)
        {
            printf("Error: %s\n", errorCodeToString(BAD_COUNT_OF_ARGS));
            return BAD_COUNT_OF_ARGS;
        }

        precision = (PrecisionType)atoi(argv[4]);
        if (precision <= 0)
        {
            printf("Error: %s\n", errorCodeToString(BAD_PRECISION));
            return BAD_PRECISION;
        }

        matrixA = readMatrixFromFile(argv[2], &errorCode);
        if (errorCode != SUCCESS)
        {
            printf("Error: %s\n", errorCodeToString(errorCode));
            return errorCode;
        }

        matrixB = readMatrixFromFile(argv[3], &errorCode);
        if (errorCode != SUCCESS)
        {
            printf("Error: %s\n", errorCodeToString(errorCode));
            return errorCode;
        }
    }
    else
    {
        if (strcmp(argv[1], "random") == 0)
        {

            if (argc != 7)
            {
                printf("Error: %s\n", errorCodeToString(BAD_COUNT_OF_ARGS));
                return BAD_COUNT_OF_ARGS;
            }

            precision = (PrecisionType)atoi(argv[6]);
            if (precision <= 0)
            {
                printf("Error: %s\n", errorCodeToString(BAD_PRECISION));
                return BAD_PRECISION;
            }

            matrixA = generateRandomMatrix(strtoull(argv[2], NULL, 10), strtoull(argv[3], NULL, 10), &errorCode);
            if (errorCode != SUCCESS)
            {
                printf("Error: %s\n", errorCodeToString(errorCode));
                return errorCode;
            }

            char matrixAFileName[] = "matrixA.txt";
            writeMatrixToFile(matrixAFileName, matrixA, precision, &errorCode);
            if (errorCode != SUCCESS)
            {
                printf("Error: %s\n", errorCodeToString(errorCode));
                freeMatrix(matrixA);
                return errorCode;
            }
            printf("Matrix A is written to a file: %s\n", matrixAFileName);

            matrixB = generateRandomMatrix(strtoull(argv[4], NULL, 10), strtoull(argv[5], NULL, 10), &errorCode);
            if (errorCode != SUCCESS)
            {
                printf("Error: %s\n", errorCodeToString(errorCode));
                return errorCode;
            }

            char matrixBFileName[] = "matrixB.txt";
            writeMatrixToFile(matrixBFileName, matrixB, precision, &errorCode);
            if (errorCode != SUCCESS)
            {
                printf("Error: %s\n", errorCodeToString(errorCode));
                freeMatrix(matrixA);
                freeMatrix(matrixB);
                return errorCode;
            }
            printf("Matrix B is written to a file: %s\n", matrixBFileName);
        }
        else
        {

            printf("Error: %s\n", errorCodeToString(BAD_ARGUMENT));

            return BAD_ARGUMENT;
        }
    }

    unsigned long long int beginTime = mtime();
    struct Matrix sequetial = matrixMultiplication(matrixA, matrixB, &errorCode);
    if (errorCode != SUCCESS)
    {
        printf("Error: %s\n", errorCodeToString(errorCode));
        freeMatrix(matrixA);
        freeMatrix(matrixB);
        return errorCode;
    }
    printf("[SEQUENTIAL] Multiplication time in milliseconds: %llu\n", mtime() - beginTime);

    char sequentialFileName[] = "sequential.txt";
    writeMatrixToFile(sequentialFileName, sequetial, precision, &errorCode);
    if (errorCode != SUCCESS)
    {
        printf("Error: %s\n", errorCodeToString(errorCode));
        freeMatrix(matrixA);
        freeMatrix(matrixB);
        freeMatrix(sequetial);
        return errorCode;
    }

    printf("[SEQUENTIAL] Result is written to a file: %s\n", sequentialFileName);

    beginTime = mtime();
    struct Matrix parallel = matrixMultiplicationParallel(matrixA, matrixB, &errorCode);
    if (errorCode != SUCCESS)
    {
        printf("Error: %s\n", errorCodeToString(errorCode));
        freeMatrix(matrixA);
        freeMatrix(matrixB);
        freeMatrix(sequetial);
        return errorCode;
    }
    printf("[PARALLEL] Multiplication time in milliseconds: %llu\n", mtime() - beginTime);

    char parallelFileName[] = "parallel.txt";
    writeMatrixToFile(parallelFileName, sequetial, precision, &errorCode);
    if (errorCode != SUCCESS)
    {
        printf("Error: %s\n", errorCodeToString(errorCode));
        freeMatrix(matrixA);
        freeMatrix(matrixB);
        freeMatrix(sequetial);
        freeMatrix(parallel);
        return errorCode;
    }

    printf("[PARALLEL] Result is written to a file: %s\n", parallelFileName);

    if (compareMatrices(sequetial, parallel))
    {
        printf("The results of the functions are equal\n");
    }
    else
    {
        printf("The results of the functions are not equal\n");
    }

    freeMatrix(matrixA);
    freeMatrix(matrixB);
    freeMatrix(sequetial);
    freeMatrix(parallel);

    return SUCCESS;
}