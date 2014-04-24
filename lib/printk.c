#include <printk.h>
#include <print.h>
#include <mips/uart8250.h>

static void myoutput(void *arg, char *s, int l)
{
    int i;

    // special termination call
    if ((l==1) && (s[0] == '\0')) return;
    
    for (i=0; i< l; i++) {
	Uart8250Put(s[i]);
	if (s[i] == '\n') Uart8250Put('\r');
    }
}

void putchark(char c)
{
  Uart8250Put(c);
}

void printk(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    lp_Print(myoutput, 0, fmt, ap);
    va_end(ap);
}

void _panic(const char *file, int line, const char *fmt,...)
{
  va_list ap;
  va_start(ap, fmt);
  printk("panic at %s:%d: ", file, line);
  lp_Print(myoutput, 0, (char *)fmt, ap);
  printk("\n");
  va_end(ap);
  for(;;);
}
