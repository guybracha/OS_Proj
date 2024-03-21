# include "myFunction.h"

int main(){
    wellcome();
    getLocation();
   
    char input[] = "bdika ka ko ki";
    char **ans = splitArguement(input);
    for (int i = 0; ans[i] != NULL; i++)
    {
        printf("Argument %d: %s\n", i, ans[i]);
    }
    free(ans);
    char exit_buf[] ="exit";
    logout(exit_buf);
    
    
    return 0;
}