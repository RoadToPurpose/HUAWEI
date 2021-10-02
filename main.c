
#include "Matrix.c"
#include <string.h>

/*
    Arguments:
        the first argument (without taking into account the program name) is the mode of the program Values:
            file - if the source data should be read from files
            random - if the source data should be generated
        
        if the first argument is file
            the second argument is the path to the file with matrix A
            the third argument is the path to the file with matrix B
            the fourth argument is the number of decimal places when displaying matrices

        if the first argument is random
            the second argument is the count of rows in matrix A
            the third argument is the count of cols in matrix A
            the fourth argument is the count of rows in matrix B
            the fifth argument is the count of cols in matrix B
            the sixth argument is the number of decimal places when displaying matrices

    File format:
        the first row is the number of rows of the matrix
        the second row is the number of cols of the matrix
        Next, there are rows_count rows (each with cols_count elements), which contain the elements of the matrix
        
        Example:
        A matrix that contains 3 rows and 2 columns, with elements 1 2 3 4 5 6, respectively:
        3
        2
        1 2
        3 4
        5 6
    
    Return value:
        error code (an explanatory line is displayed in the console): 
            0 - success
            1 - non-existent file
            2 - incorrect parameters of the matrix size (for example, if it was indicated that the matrix should have -10 rows)
            3 - if matrices do not match in size
            4 - incorrect precision value (less than or equal to zero)
            5 - wrong number of arguments
            6 - invalid argument value

    Results of the program:
        if the random mode is specified, then matrix A is output to the file matrixA.txt, 
        and matrix B is output to the file matrixB.txt

        the result of the sequential algorithm is output to the sequential.txt file
        the result of the parallel algorithm is output to the parallel.txt file

    Examples: 
        Launching the program with reading initial data from files A.txt and B.txt 
        and with outputting matrices with precision up to three decimal places:
        ./main file A.txt B.txt 3

        Launching the program with the generation of initial data (matrix A has a size of 5x10, matrix B has a size of 10x3) 
        and with the output of matrices with an accuracy of four decimal places
        ./main random 5 10 10 3 4
        
*/
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