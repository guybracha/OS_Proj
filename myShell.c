#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<myShell.h>
#include<functionShell.h>

int main(){
    wellcome();

    while(1){
        char str[40]="hello1 hello2 hello3";
        puts("SubStr");
        puts(str);
        char* subStr = strtok(str, " ");
        while ((subStr=strtok(NULL," "))!=NULL)
        {
            puts(subStr);
            puts(str);
        }
    }
    char* pArr[10];

    return 0;
}