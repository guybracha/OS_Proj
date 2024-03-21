#include "myFunction.h"

void wellcome(){
    printf("\n\n------------------\n");
     printf("\nWelcome to myShell!\n\n");
    printf("link to github: https://github.com/guybracha/OS_Proj\n\n");
    printf("\nHave Fun!\n");
    printf(" ----------------- \n\n");
}

void printPattern(int radius){
    printf("circle here - 0 \n\n\n");
}


void getLocation(){
    char location[BUFF_SIZE];
    char *username;
    char hostname[HOST_NAME_MAX];
    char *cwd;

    // get username
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL){
        username = pw->pw_name;
    } else {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }
    
    // get hostname
    if(gethostname(hostname, sizeof(hostname)) != 0){
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    //get current working directory
    cwd = getcwd(location, BUFF_SIZE);
    if(cwd == NULL){
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    char* buf = (char *)malloc(10*sizeof(char));
    buf=getlogin();
    printf("\n%s\n",buf);
    if(getcwd(location, BUFF_SIZE) == NULL){
        printf("error");
    } else {
        GREEN();
        BOLD();
        printf("%s",location);
        RESET_COLOR();
        printf("$ ");
    }
}

void **splitArguement(char* str){
    char *subStr;
    int size = 2;
    int index = 0;
    subStr = strtok(str, " ");
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        size++;
        index++;
        *(argumnts + index) = subStr;
        argumnts = (char **)realloc(argumnts, size * sizeof(char *));
    }
    *(argumnts + (index + 1)) = NULL;

    return argumnts;
}

void logout(char *input){
    free(input);
    puts("log out");
    exit(EXIT_SUCCESS);
}