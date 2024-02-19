#include<functionShell.h>

char *inputFromUser()
{
    char ch;
    int size = 0;
    char *str = (char *)malloc((size + 1) * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + size) = ch;
        size++;
        str = (char *)realloc(str, size + 1);
    }
    *(str + size) = '\0';
    return str;
}
char **splitString(char *str)
{

    char *subStr;
    subStr = strtok(str, " ");
    int argumentSize = 2;
    int index = 0;
    char **argumentArray = (char **)malloc(argumentSize * sizeof(char *));
    *(argumentArray + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        index++;
        argumentSize++;
        argumentArray = (char **)realloc(argumentArray, argumentSize * sizeof(char *));
        *(argumentArray + index) = subStr;
    }
    *(argumentArray + index + 1) = NULL;

    return argumentArray;
}
void getLocation(){
    char location[256];
    if(getcwd(location, sizeof(location)) == NULL){
        puts("Error");
        return;
    }
    printf("\033[0;34]m");
    printf("%s$ ", location);
    printf("\033[0m");
}
void _exit(){
    puts("logout");
    puts(0);
}

void logout(char* str){
    puts("logout");
    exit(0);
}

void echo(char **arguments){
    int i = 1;
    while (arguments[i] != NULL)
    {
        printf("%s ", arguments[i++]);
        puts("");
    }
    
}

void cd(char *path){
    chdir(path);
}
void cp(){

}
void get_dir(){

}