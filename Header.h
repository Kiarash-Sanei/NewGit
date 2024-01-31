//Headers:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

//Numbers:
#define MAX_FILE_NAME_LENGTH 1000
#define MAX_DIRECTORY_NAME_LENGTH 1000
#define MAX_COMMAND_LENGTH 2000
#define MAX_UNDO_LENGTH 2000
#define MAX_BRANCH_NAME 100
#define MAX_COMMAND_HASH_LENGTH 20
#define MAX_COMMIT_MESSAGE_LENGTH 73
#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100
#define MAX_FILE_COUNT 100
#define MAX_USER_NAME_LENGTH 50
#define MAX_USER_EMAIL_LENGTH 100
#define MAX_ALIAS_LENGHT 20
#define MAX_ALIAS_COMMAND_LENGHT 100
#define ERROR -1
#define SUCCEED 1
#define FAILED 0
#define ACCESS 0777
#define MODIFIED 2

//Errors:
#define DIRECTORY_OPENING_ERROR puts("Opening directory failed!");
#define DIRECTORY_CREATING_ERROR puts("Creating directory failed!");
#define FILE_OPENING_ERROR puts("Opening file failed!");
#define FILE_CREATING_ERROR puts("Creating file failed!");
#define NewGit_EXISTENCE_ERROR puts("You haven't initialized NewGit here!");
#define FILE_EXISTENCE_ERROR puts("You have entered a file name that does not exist in the current directory!");
#define DIRECTORY_EXISTENCE_ERROR puts("You have entered a directory name that does not exist in the current directory!");
#define INVALID_INPUT_ERROR puts("You have entered invalid input!");
#define INVALID_COMMAND_ERROR puts("You have entered invalid command!");
#define NewGit_ALREADY_EXIST_IN_CURRENT_DIRECTORY puts("You have already initialized NewGit in current directory!");
#define NewGit_ALREADY_EXIST_IN_PARENT_DIRECTORY puts("You have already initialized NewGit in one of the parent directories of current directory!");
#define FILE_EXISTENCE_ERROR_IN_STAGE puts("You have entered a file name that does not exist in the stage!");
#define LACK_OF_ADD puts("You haven't add any file yet!");
#define BRANCH_ALREADY_EXIST puts("A branch with this name has already been made , so you need to choose another name for the new branch!");
#define LACK_OF_CONFIGURATION puts("You haven't set sufficient configuration!");
#define MASSAGE_IS_TOO_LONG puts("Massage for every commit shouldn't be longer than 72 character!");

//Massages:
#define SUCCESS_MASSAGE(word) printf("%s is done successfully!\n", word);
#define FAIL_MASSAGE(word) printf("%s failed!\n", word);
#define EXISTENCE_ERROR_MASSAGE(word) printf("%s does not exist in the current directory!\n", word);
//Define Functions:

//Structs:
struct user
{
    char name[MAX_USER_NAME_LENGTH];
    char email[MAX_USER_EMAIL_LENGTH];
};
struct alias
{
    char shortcut[MAX_ALIAS_LENGHT];
    char command[MAX_ALIAS_COMMAND_LENGHT];
};
struct commit_information
{
    time_t commit_time;
    int commit_hash;
    char commit_massage[MAX_COMMIT_MESSAGE_LENGTH];
    char commit_user_name[MAX_USER_NAME_LENGTH];
    char commit_user_email[MAX_USER_EMAIL_LENGTH];
};

//Typedefs:
typedef struct dirent dirent;
typedef struct tm tm;
typedef struct commit_information commit_information;
typedef struct user user;
typedef struct alias alias;

//Prototypes:
//General:
char* NewGit_finder();
int copy_file(char* , char*);
int copy_directory(char* , char*);
int file_content_checker(char* , char*);
int stage_checker_complete(char* , char*);
int stage_checker_name(char*);
int delete_file(char* , char*);
int delete_directory(char* , char*);
//Initializing:
int NewGit_maker();
//Configuration:
int add_configuration_global(char* , char*);
int add_configuration_loacal(char* , char*);
//Add:
int stage_file(char*);
int stage_directory(char*);
int show(int , char*);
int redo();//doesn't work
//Reset:
int reset_file(char*);
int reset_directory(char*);
int undo();
//Status:
int status(char*);
//Branch:
int branch_maker(char* , char* , char* , char*);
int branch_shower();
//Commit:
int add_commit(char* , char*);