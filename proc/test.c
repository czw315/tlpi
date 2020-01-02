#include<unistd.h>
#include<stdio.h>
#define _GNU_SOURCE
#include<errno.h>

extern char* program_invocation_short_name;

int
main()
{
    printf("%s\n",program_invocation_short_name);
    printf("%d\n",sysconf(_SC_PAGESIZE));
    return 0;
}