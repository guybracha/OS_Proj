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

void **splitArgument(char* str){
    char *subStr;
    int size = 2;
    int index = 0;
    subStr = strtok(str, " ");
    char **arguments = (char **)malloc(size * sizeof(char *));
    *(arguments + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        size++;
        index++;
        *(arguments + index) = subStr;
        arguments = (char **)realloc(arguments, size * sizeof(char *));
    }
    *(arguments + (index + 1)) = NULL;

    return arguments;
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

void move(char **args) {
    if (args[1] == NULL || args[2] == NULL) {
        printf("Error: insufficient arguments\n");
        return;
    }

    FILE *original_file, *destination_file;
    char *original_path = args[1];
    char *destination_path = args[2];

    original_file = fopen(original_path, "r");
    if (original_file == NULL) {
        printf("Error: unable to open the original file.\n");
        return;
    }

    destination_file = fopen(destination_path, "w");
    if (destination_file == NULL) {
        fclose(original_file); // Close the original file stream before returning
        printf("Error: unable to create/open the destination file.\n");
        return;
    }

    int ch;
    while ((ch = fgetc(original_file)) != EOF) {
        if (fputc(ch, destination_file) == EOF) {
            fclose(original_file); // Close the file streams
            fclose(destination_file);
            printf("Error: writing to destination file failed.\n");
            return;
        }
    }

    // Close the file streams
    fclose(original_file);
    fclose(destination_file);

    // Remove the original file
    if (remove(original_path) != 0) {
        printf("Error: unable to remove the original file.\n");
    } else {
        printf("File moved successfully.\n");
    }
}


void echoppned(char **args){
    int i = 1;
    FILE *output_file = NULL;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], ">>") == 0)
        {
            if (args[i+1] != NULL)
            {
                output_file = fopen(args[i+1],"a");
                if (output_file == NULL)
                {
                    output_file = fopen(args[i+1], "w");
                    if (output_file ==NULL)
                    {
                        perror("error creaing file");
                        return;
                    }
                }
            } else {
                printf("No filename specified agter '>>'\n");
                return;
            }
            break;
        }
        i++;
    }
    i = 1;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], ">>") != 0)
        {
            if (output_file != NULL)
            {
                fprintf(output_file, "%s", args[i]);
            }
            else {
                printf("%s ", args[i]);
            }
        }
        i++;
    } if (output_file != NULL)
    {
        fclose(output_file);
    }
}

void echorite(char **args){
    char *username = args[1];
    char *filepath = args[3];
    char *content = args[2];

    FILE *file = fopen(filepath,"w");
    if(file == NULL){
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s", content);

    fclose(file);

    printf("Content written to file %s bt user %s\n", filepath, username);
}

void myRead(char **args){
    if(args[1] == NULL){
        printf("Usage: %s <filepath>\n",args[0]);
        return;
    }

    char *filePath = args[1];
    FILE *file = fopen(filePath, "r");
    if(file == NULL){
        perror("error opening file");
        return;
    }

    char buffer[1024];

    printf("File content:\n");
    while (fgets(buffer, sizeof(buffer),file) != NULL)
    {
        printf("%s",buffer);
    }
    fclose(file);
}

void wordCount(char **args){
    if(args[1] == NULL || args[2] ==NULL){
        printf("Usage: %s <-w or -l> <filepath>\n", args[0]);
        return;
    }
    char *option = args[1];
    char *filePath = args[2];

    FILE *file = fopen(filePath, "r");
    if(file == NULL){
        perror("error opening file");
        return;
    }

    int wordCount = 0;
    int lineCount = 0;
    char buffer[1024];

    while(fgets(buffer, sizeof(buffer),file) != NULL){
        lineCount++;
        char *token = strtok(buffer, " \t\n");
        while(token != NULL){
            wordCount++;
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(file);

    if(strcmp(option, "-w") == 0){
        printf("word count: %d\n", wordCount);
    } else if(strcmp(option, "-l") == 0){
        printf("Line count: %d\n", lineCount);
    } else{
        printf("Invalid option\n");
    }
}