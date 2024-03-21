#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <limits.h>
#include <sys/stat.h>    
#include <sys/types.h>

#define BUFF_SIZE 256
#define BLUE() printf("\033[0;34m")
#define RESET_COLOR() printf("\033[0m")
#define GREEN() printf("\033[0m")
#define BOLD() printf("\e[1m")
#define BOLD_OFF() printf("\e[m")

char *getInputFromUser();
void getLocation();
void wellcome();
void printPattern(int radius);
void **splitArguement(char* str);
void logout(char* str);