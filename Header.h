//Headers:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//Numbers:
#define MAX_FILE_NAME_LENGTH 1000
#define MAX_DIRECTORY_NAME_LENGTH 1000
#define MAX_COMMIT_MESSAGE_LENGTH 2000
#define MAX_LINE_LENGTH 1000
#define ERROR -1
#define SUCCEED 1
#define FAILED 0

//Errors:
#define DIRECTORY_OPENING_ERROR puts("Opening directory failed!");
#define NewGit_EXISTENCE_ERROR puts("You haven't initialized NewGit here!");
#define INVALID_INPUT_ERROR puts("You have entered invalid input!");

//Define Functions

//Structs:

//Typedefs:
typedef struct dirent dirent;

//Prototypes:
//Configuration:
char* NewGit_finder();
int add_configuration_global(char* , char*);
int add_configuration_loacal(char* , char*);
//General:
