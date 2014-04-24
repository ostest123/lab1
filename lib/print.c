#include "print.h"

#define IsDigit(x) (((x)>='0') && ((x)<='9'))
#define Ctod(x)    ((x)-'0')

extern int PrintChar(char *, char, int, int);
extern int PrintString(char *, char *, int, int);
extern int PrintNum(char *, unsigned long, int, int, int, int, char, int);

static const char theFatalMsg[] = "fatal error in lp_Print!";

void lp_Print(void (*output)(void *, char *, int), 
	      void * arg,
	      char *fmt, 
	      va_list ap)
{
  
#define 	OUTPUT(arg, s, l)					\
  { if (((l) < 0) || ((l) > LP_MAX_BUF)) {				\
      (*output)(arg, (char*)theFatalMsg, sizeof(theFatalMsg)-1); for(;;); \
    } else {								\
      (*output)(arg, s, l);						\
    }									\
  }
  
  char buf[LP_MAX_BUF];
  
  char c;
  char *s;
  long int num;
  
  int longFlag;  // %ld
  int negFlag;
  int width;
  //int prec;      // precision
  int ladjust;   // left adjust
  char padc;     // padding char
  
  int length;
  
  /* your code here. My solution is about 160 lines. Use the three helper functions to calculate length and buffer of output. Then call OUTPUT macro to output */
 
    /////////////////////////////////////////////////////////////
    //                                                         //
    // a possible solution (cannot parse .x precision prefix)  //
    //                                                         //
    // main code from gxemul version code                      //
    //                                                         //
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    
    //for test
    //OUTPUT(arg, "a", 1);
    
    
    for(;;) {
        {
            /* scan for the next '%' */
            while ((*fmt != '%') && (*fmt != '\0'))
            {
                /* flush the string found so far */
	    		//flush means print and move to next?
	    		OUTPUT(arg, fmt, 1);
                fmt++;
            }
            
            /* are we hitting the end? */
            if (*fmt == '\0')
                break;
			
        }
        
        /* we found a '%' */
        
        //move to next: prefixes
    	//ATTENTION:
        //process prefixes below ONLY
        //
        //  	l: long num
        //  	0: use 0 as padding char
        //  	-: prefix - for left align)
        //      width: output width
        //
        //        eg. %-20d %12u
        //
        
        fmt++;
        
        //clear old prefixes
        //clear the old longFlag
        longFlag = 0;
        //clear padding char
        padc = ' ';
        //clear ladjust
        ladjust = 0;
        //clear width (in fact it will be cleared in the following codes again)
        width = 0;
        
        while (1)
        {
            /* check for long */
            if (*fmt == 'l')
            {
                longFlag = 1;
                fmt++;
            }
            /* check for other prefixes */
            //padding char prefix
            else if (*fmt == '0')
            {
                padc = '0';
                fmt++;
            }
            //left prefix
            else if (*fmt == '-')
            {
                ladjust = 1;
                fmt++;
            }
            //width prefix ('0' has been checked)
            else if (IsDigit(*fmt))
            {
                //need to check the size of variable width for security
                //eg %123456789012d
                //omit it here
                
                //clear width to make sure to get the latest num
                width = 0;
                while (IsDigit(*fmt))
                {
                    width = 10 * width + Ctod(*fmt);
                    fmt++;
                }
            }
            else
                break;
        }
        
        /* check format flag */
        negFlag = 0;
        switch (*fmt) {
            case 'b':
                if (longFlag) {
                    num = va_arg(ap, long int);
                } else {
                    num = va_arg(ap, int);
                }
                length = PrintNum(buf, num, 2, 0, width, ladjust, padc, 0);
                OUTPUT(arg, buf, length);
                break;
                
            case 'd':
            case 'D':
                if (longFlag) {
                    num = va_arg(ap, long int);
                } else {
                    num = va_arg(ap, int);
                }
                if (num < 0) {
                    num = - num;
                    negFlag = 1;
                }
                length = PrintNum(buf, num, 10, negFlag, width, ladjust, padc, 0);
                OUTPUT(arg, buf, length);
                break;
                
            case 'o':
            case 'O':
                if (longFlag) {
                    num = va_arg(ap, long int);
                } else {
                    num = va_arg(ap, int);
                }
                length = PrintNum(buf, num, 8, 0, width, ladjust, padc, 0);
                OUTPUT(arg, buf, length);
                break;
                
            case 'u':
            case 'U':
                if (longFlag) {
                    num = va_arg(ap, long int);
                } else { 
                    num = va_arg(ap, int); 
                }
                length = PrintNum(buf, num, 10, 0, width, ladjust, padc, 0);
                OUTPUT(arg, buf, length);
                break;
                
            case 'x':
                if (longFlag) { 
                    num = va_arg(ap, long int);
                } else { 
                    num = va_arg(ap, int); 
                }
                length = PrintNum(buf, num, 16, 0, width, ladjust, padc, 0);
                OUTPUT(arg, buf, length);
                break;
                
            case 'X':
                if (longFlag) { 
                    num = va_arg(ap, long int);
                } else { 
                    num = va_arg(ap, int); 
                }
                length = PrintNum(buf, num, 16, 0, width, ladjust, padc, 1);
                OUTPUT(arg, buf, length);
                break;
                
            case 'c':
                c = (char)va_arg(ap, int);
                length = PrintChar(buf, c, width, ladjust);
                OUTPUT(arg, buf, length);
                break;
                
            case 's':
                s = (char*)va_arg(ap, char *);
                length = PrintString(buf, s, width, ladjust);
                OUTPUT(arg, buf, length);
                break;
                
            case '\0':
                fmt --;
                break;
                
            default:
                /* output this char as it is */
                OUTPUT(arg, fmt, 1);
        }	/* switch (*fmt) */
        
        fmt ++;
    }		/* for(;;) */
    
    /* special termination call */
    OUTPUT(arg, "\0", 1);

    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////

}


/* --------------- local help functions --------------------- */
int PrintChar(char * buf, char c, int length, int ladjust)
{
  int i;
  
  if (length < 1) length = 1;
  if (ladjust) {
    *buf = c;
    for (i=1; i< length; i++) buf[i] = ' ';
  } else {
    for (i=0; i< length-1; i++) buf[i] = ' ';
    buf[length - 1] = c;
  }
  return length;
}

int PrintString(char * buf, char* s, int length, int ladjust)
{
  int i;
  int len=0;
  char* s1 = s;
  while (*s1++) len++;
  if (length < len) length = len;
  
  if (ladjust) {
    for (i=0; i< len; i++) buf[i] = s[i];
    for (i=len; i< length; i++) buf[i] = ' ';
  } else {
    for (i=0; i< length-len; i++) buf[i] = ' ';
    for (i=length-len; i < length; i++) buf[i] = s[i-length+len];
  }
  return length;
}

int PrintNum(char * buf, unsigned long u, int base, int negFlag, 
	     int length, int ladjust, char padc, int upcase)
{
  
  int actualLength =0;
  char *p = buf;
  int i;
  
  do {
    int tmp = u %base;
    if (tmp <= 9) {
      *p++ = '0' + tmp;
    } else if (upcase) {
      *p++ = 'A' + tmp - 10;
    } else {
      *p++ = 'a' + tmp - 10;
    }
    u /= base;
  } while (u != 0);
  
  if (negFlag) {
    *p++ = '-';
  }
  
  /* figure out actual length and adjust the maximum length */
  actualLength = p - buf;
  if (length < actualLength) length = actualLength;
  
  /* add padding */
  if (ladjust) {
    padc = ' ';
  }
  if (negFlag && !ladjust && (padc == '0')) {
    for (i = actualLength-1; i< length-1; i++) buf[i] = padc;
    buf[length -1] = '-';
  } else {
    for (i = actualLength; i< length; i++) buf[i] = padc;
  }
  
  
  /* prepare to reverse the string */
  {
    int begin = 0;
    int end;
    if (ladjust) {
      end = actualLength - 1;
    } else {
      end = length -1;
    }
    
    while (end > begin) {
      char tmp = buf[begin];
      buf[begin] = buf[end];
      buf[end] = tmp;
      begin ++;
      end --;
    }
  }
  
  /* adjust the string pointer */
  return length;
}
