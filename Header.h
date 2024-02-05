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
#define MAX_COMMIT_HASH_LENGTH 20
#define MAX_COMMIT_MESSAGE_LENGTH 73
#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100
#define MAX_FILE_COUNT 100
#define MAX_USER_NAME_LENGTH 50
#define MAX_USER_EMAIL_LENGTH 100
#define MAX_ALIAS_LENGHT 21
#define MAX_ALIAS_COMMAND_LENGHT 100
#define MAX_SETTING_COUNT 100
#define MAX_COMMIT_COUNT 100
#define MAX_TAG_NAME_LENGTH 100
#define MAX_TAG_MASSAGE_LENGTH 100
#define MAX_TAG_COUNT 100
#define MAX_LINE_COUNT 100
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
#define LACK_OF_ADD puts("You haven't added any file yet!");
#define BRANCH_ALREADY_EXIST puts("A branch with this name has already been made , so you need to choose another name for the new branch!");
#define LACK_OF_CONFIGURATION puts("You haven't set sufficient configuration!");
#define MASSAGE_IS_TOO_LONG puts("Massage for every commit shouldn't be longer than 72 character!");
#define SHORTCUT_IS_TOO_LONG puts("Shortcut shouldn't be longer than 20 character!");
#define LACK_OF_SETTING puts("You haven't set sufficient setting!");
#define SHORTCUT_EXISTENCE_ERROR puts("You have entered a shortcut that does not exist!");
#define LACK_OF_COMMIT puts("You haven't committed anything yet!");
#define BRANCH_EXISTENCE_ERROR puts("You have entered a branch that does not exist!");
#define STAGE_IS_NOT_EMPTY_ERROR puts("Stagging area is not empty!");
#define READ_ONLY_ERROR puts("You have checked out to a commit , so you cann't add or commit!");
#define COMMIT_EXISTENCE_ERROR puts("You have entered a commit that does not exist!");
#define TAG_EXISTENCE_ERROR puts("You have entered a tag that does not exist!");
#define LINES_ARE_NOT_EQUAL puts("The count of line to diff are not equal!");

//Massages:
#define SUCCESS_MASSAGE(word) printf("%s is done successfully!\n", word);
#define FAIL_MASSAGE(word) printf("%s failed!\n", word);
#define EXISTENCE_ERROR_MASSAGE(word) printf("%s does not exist in the current directory!\n", word);
#define STAGE_EXISTENCE_ERROR_MASSAGE(word) printf("%s does not exist in the stagging area!\n", word);

//Colors:
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
    char commit_branch[MAX_BRANCH_NAME];
    int commit_number;
};
struct HEAD_information
{
    int HEAD;
    char branch_name[MAX_BRANCH_NAME];
    int read_only;
};
struct massage_information
{
    char massage[MAX_COMMIT_MESSAGE_LENGTH];
    char shortcut[MAX_ALIAS_LENGHT];
};
struct tag
{
    time_t commit_time;
    int commit_hash;
    char commit_massage[MAX_COMMIT_MESSAGE_LENGTH];
    char commit_user_name[MAX_USER_NAME_LENGTH];
    char commit_user_email[MAX_USER_EMAIL_LENGTH];
    char commit_branch[MAX_BRANCH_NAME];
    int commit_number;
    char tag_name[MAX_TAG_NAME_LENGTH];
    char tag_massage[MAX_TAG_MASSAGE_LENGTH];
};

//Typedefs:
typedef struct dirent dirent;
typedef struct tm tm;
typedef struct commit_information commit_information;
typedef struct user user;
typedef struct alias alias;
typedef struct HEAD_information HEAD_information;
typedef struct massage_information massage_information;
typedef struct tag tag;

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
void reverse(char* , int);
char* citoa(int , char* , int);
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
int branch_maker(char* , int , char* , char*);
int branch_shower();
//Commit:
int add_commit(char* , char* , int*);
int set(char* , char*);
int replace(char* , char*);
int remove_shortcut(char*);
//Log:
int log_show();
int log_number(int);
int log_branch(char*);
int log_author(char*);
int log_time_since(time_t);// YYYY/MM/DD
int log_time_before(time_t);// YYYY/MM/DD
int log_word(char*);
//Checkout:
int checkout(char* , HEAD_information*);
int checkout_commit_hash(HEAD_information*);
//Revert:
//no new function is needed
//Tag:
int tag_maker(commit_information , char* , char*);
int tag_remaker(commit_information , char* , char*);
int tag_organizer();
int all_tag_shower();
int tag_shower(char*);
//Diff:
int diff_file(char* , char* , int , int , int , int);
int diff_commit(commit_information , commit_information);
//Merge:
int merge(char* , char*);