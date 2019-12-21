#include<stdio.h>
#include<unistd.h>
int main(){
    freopen("test.txt","w",stdout);
    printf("stdout redirected to test.txt");
    fclose(stdout);
    //linux
    freopen("/dev/tty","w",stdout);
    //windows
    //freopen("CON","w",stdout);
    getchar();
    return 0;
}