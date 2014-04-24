#ifndef _printk_h
#define _printk_h

#include <stdarg.h>
void printk(char *fmt, ...);
void putchark(char c);
void _panic(const char *, int, const char *, ...) 
	__attribute__((noreturn));
#define panic(...) _panic(__FILE__, __LINE__, __VA_ARGS__)

#endif

