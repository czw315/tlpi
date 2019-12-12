#include<stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif
static void terminate(Boolean useExit3)
{
    char* s;
    /* 假如环境变量EF_DUMPCORE被定义且不是空字符串那么产生core文件；*/

    s=getenv("EF_DUMPCORE");
    if(s!=NULL&&*s!='\0')
        abort();
    else if(useExit3)
        exit(EXIT_FAILURE);
    else 
        _exit(EXIT_FAILURE);
}

static void
outputError(Boolean useErr, int err, Boolean flushStdout,
        const char* format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE],userMsg[BUF_SIZE],errText[BUF_SIZE];

    vsnprintf(userMsg,BUF_SIZE,format,vp);

    if(useErr)
        snprintf(errText,BUF_SIZE," [%s %s]",
                (err>0&&err<MAX_ENAME)?
                ename[err]:"?UNKONWN?",strerror(err));
    else
        snprintf(errText,BUF_SIZE,":");
    
    snprintf(buf,BUF_SIZE,"ERROR%s %s\n",errText,userMsg);

    if(flushStdout)
        fflush(stdout);
    fputs(buf,stderr);
    fflush(stderr);
}
/**
 * 打印到标准错误输出，除了追加一个终止换行符和printf一样，打印出errno对应的错误文本，包括
 * 错误名以及strerror返回的错误描述，同时外加参数列表指定的格式化输出
 */
void
errMsg(const char* format, ...)
{
    va_list argList;
    int savedErrno;

    savedErrno = errno;                 //防止修改errno
    va_start(argList,format);
    outputError(TRUE,errno,TRUE,format,argList);
    va_end(argList);

    errno = savedErrno;
}
/**
 * 除了打印信息与errMsg一样，还会用abort或者exit退出程序
 */
void
errExit(const char* format, ...)
{
    va_list argList;

    va_start(argList,format);
    outputError(TRUE,errno,TRUE,format,argList);
    va_end(argList);

    terminate(TRUE);
}
/**
 * 与errExit不同的是不会在打印错误消息前刷新stdout，调用的是_exit(),不会对stdio缓冲区
 * 刷新以及调用exit handler,假如在多进程中，子进程若因发生错误而需要终止时err_exit就显得有用
 */
void
err_exit(cosnt char* format, ...)
{
    va_list argList;

    va_start(argList,format);
    outputError(TRUE,errno,FALSE,format,argList);
    va_end(argList);

    terminate(FALSE);
}
/**
 * 在POSIX线程函数中，返回0表示成功，错误返回错误号(errno)，并不设置errno,
 * 在线程程序中errno已被定义为宏，展开后是一个函数调用，主要使用errExitEN
 */
void
errExitEN(int errnum,const char* format, ...)
{
    va_list argList;

    va_start(argList,format);
    outputError(TRUE,errnum,TRUE,format,argList);
    va_end(argList);

    terminate(TRUE);
}
/**
 * 来诊断一般性错误，并终止程序
 */
void
fatal(const char* format, ...)
{
    va_list argList;
    
    va_start(argList,format);
    outputError(FALSE,0,TRUE,format,argList);
    va_end(argList);

    terminate(TRUE);
}
/**
 * 命令行参数错误
 */
void
usageErr(const char* format, ...)
{
    va_list argList;

    fflush(stdout);
    fprintf(stderr,"Usage: ");
    va_start(argList,format);
    vfprintf(stderr,format,argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE)；
}

void
cmdLineErr(const char* format, ...)
{
    va_list argList;

    fflush(stdout);
    fprintf(stderr,"Command-line usage error: ");
    va_start(argList,format);
    vfprintf(stderr,format,argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE)；
}