#include <printk.h>

int main()
{
  printk("Hello, world!\n");
  printk("%b, %o, %c%-6d%c, %X\n", 9210, 9210, 'Z', 9210, 'Y', 9210);
  printk("%08x\n", 0xbad9210);
  printk("%s %s %s\n%010lx\n", "heihei", "haha", "hoho", 32767);
  printk("\n%012x",255);
    printk("\n%-5-6daaa\n",133);
  panic("Done.\n");
  //_panic("Done.\n");
  return 0;
}
