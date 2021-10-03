
#include "Errors.h"

const char *errorCodeToString(ErrorType errorCode)
{
    switch (errorCode)
    {
    case SUCCESS:
        return "Success";
    case BAD_FILE:
        return "Cannot open file";
    case BAD_SIZE_OF_MATRIX:
        return "Bad size of matrix";
    case BAD_DIMESIONS_OF_MATRICES:
        return "Bad dimensions of matrices";
    case BAD_PRECISION:
        return "Bad precision";
    case BAD_COUNT_OF_ARGS:
        return "Bad count of args";
    case BAD_ARGUMENT:
        return "Bad argument";
    default:
        return "Unknown error";
    }
}