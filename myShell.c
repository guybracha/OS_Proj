#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<myShell.h>
#include<functionShell.h>

int main(){
    wellcome();

    while(1){
        getLocation();
        char *str = inputFromUser();
        if(strcmp(str, "exit") == 0){
            logout(str);
        }
        char **arguments = splitString(str);
        if(strcmp(str,"echo") == 0){
            echo(arguments);
        }
        free(str);
        free(arguments);
        char str[40] = "hello1 hello2 hello3";
        puts("SubStr");
        puts(str);
        char *subStr = strtok(str, " ");
        if (strcmp(subStr, "exit") == 0)
        {
            puts("logout");
            _exit("");
        }
    }
    char* pArr[10];

    return 0;
}

void wellcome(){
    puts("Hello Shelly Here");
}
