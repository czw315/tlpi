#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char* format, ...);

#ifdef __GNUC__

/**
 * 解决由于下列函数终止main()或者其他有返回值的函数而导致的'gcc -Wall'
 * 报出的'control reaches end of non-void function'错误
 */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char* format, ...) NORETURN;
void err_exit(const char* format, ...) NORETURN;
void errExitEN(int errnum, const char* format, ...) NORETURN;
void fatal(const char* format, ...) NORETURN;
void usageErr(const char* format, ...) NORETURN;
void cmdLineErr(const char* format, ...) NORETURN;
 
#endif
