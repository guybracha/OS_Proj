#include "myFunction.h"
#include <math.h>

void printPattern(int radius){
    printf("circle here - 0 \n\n\n");
}

void welcome(){
    printPattern(10);
    printf("\nWellcome to guyShell\n this is shelly\n");
    printf("\n more projects by guy bracha - https://github.com/guybracha?tab=repositories\n");
}

void getLocation(){
    char location[BUFF_SIZE];
    char *buf;
    buf = (char *)malloc(10*sizeof(char));
    buf=getlogin();
    printf("\n%s\n",buf);
    if(getcwd(location, BUFF_SIZE) == NULL){
        printf("error");
    } else {
        green();
        bold();
        printf("%s",location);
        resetColor();
        printf("$ ");
    }
}

void **splitArguement(char* str){
    
}