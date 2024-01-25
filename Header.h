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
#define ACCESS 0777

//Errors:
#define DIRECTORY_OPENING_ERROR puts("Opening directory failed!");
#define DIRECTORY_CREATING_ERROR puts("Creating directory failed!");
#define NewGit_EXISTENCE_ERROR puts("You haven't initialized NewGit here!");
#define FILE_EXISTENCE_ERROR puts("You have entered a file name that does not exist in the current directory!");
#define DIRECTORY_EXISTENCE_ERROR puts("You have entered a directory name that does not exist in the current directory!");
#define INVALID_INPUT_ERROR puts("You have entered invalid input!");
#define INVALID_COMMAND_ERROR puts("You have entered invalid command!");
#define NewGit_ALREADY_EXIST_IN_CURRENT_DIRECTORY puts("You have already initialized NewGit in current directory!");
#define NewGit_ALREADY_EXIST_IN_PARENT_DIRECTORY puts("You have already initialized NewGit in one of the parent directories of current directory!");

//Massages:
#define SUCCESS_MASSAGE(word) printf("%s is done successfully!\n", word);
#define FAIL_MASSAGE(word) printf("%s failed!\n", word);
//Define Functions:

//Structs:

//Typedefs:
typedef struct dirent dirent;

//Prototypes:
//General:
char* NewGit_finder();
int copy(char* , char*);
//Initializing:
int NewGit_maker();
//Configuration:
int add_configuration_global(char* , char*);
int add_configuration_loacal(char* , char*);
//Add:
int stage_file(char*);//cann't handle same file name
int stage_directory(char*);//cann't handle same file name
