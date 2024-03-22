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

void cd(char **arg) {
    if (arg[1] == NULL) {
        printf("-myShell: cd: missing directory\n");
        return;
    }
    
    char* path = del_spaces(arg[1]); 
    if (path == NULL) {
        printf("-myShell: cd: invalid directory\n");
        return;
    }

    // Change directory
    if (chdir(path) != 0) {
        printf("-myShell: cd: %s: No such file or directory\n", path);
    }

    free(path);
}


void cp(char **arg) {
    if (arg[1] == NULL || arg[2] == NULL) {
        printf("-myShell: cp: missing source or destination file\n");
        return;
    }

    char *src_file = arg[1]; // Source file argument
    char *des_file = arg[2]; // Destination file argument

    FILE *src, *des;
    char ch;

    // Open source file for reading
    if ((src = fopen(src_file, "r")) == NULL) {
        printf("-myShell: cp: %s: No such file or directory\n", src_file);
        return;
    }

    // Open destination file for writing
    if ((des = fopen(des_file, "w")) == NULL) {
        printf("-myShell: cp: %s: Unable to create destination file\n", des_file);
        fclose(src);
        return;
    }

    // Copy contents from source to destination
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, des);
    }

    fclose(src);
    fclose(des);
}


void delete(char **arg)
{
    char* to_del=del_spaces(arg[1]);
    if (unlink(arg[1]) != 0)
        printf("-myShell: unlink: %s: No such file or directory\n", arg[1]);
    free(to_del);
}

void mypipe(char **argv1, char **argv2)
{
    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(1);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            /* stdout now goes to pipe */
            /* child process does command */
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(0);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
}

char* del_spaces(char* arg) {
    char* path = NULL; 
    size_t len = 0; 

    if (arg == NULL) { 
        return NULL; 
    }

    if (arg[0] == '"') {
        int i = 1;
        while (arg[i] != '\0' && arg[i] != '"') {
            len++; // Increment the length of the string
            i++;
        }
    } else {
        len = strlen(arg); // Get the length of the string
    }

    // Allocate memory for the path string
    path = malloc((len + 1) * sizeof(char)); 
    if (path == NULL) { 
        printf("Error: Memory allocation failed\n");
        return NULL; 
    }

    
    strncpy(path, arg, len);
    path[len] = '\0';

    return path;
}