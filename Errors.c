
#define ErrorType short

#define SUCCESS 0
#define BAD_FILE 1
#define BAD_SIZE_OF_MATRIX 2
#define BAD_DIMESIONS_OF_MATRICES 3
#define BAD_PRECISION 4
#define BAD_COUNT_OF_ARGS 5
#define BAD_ARGUMENT 6

const char * errorCodeToString(ErrorType errorCode){
    switch(errorCode){
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