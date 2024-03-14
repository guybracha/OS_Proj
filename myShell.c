int main(){
    welcome();
    getLocation();
    printf("!!!");
    char *bdika = "bdika ka ko ki";
    char** ans = splitArgument(bdika);
    for (int i = 0; i <5 ; i++)
    {
        printf("%d",ans[i]);
    }
    
    return 0;
}