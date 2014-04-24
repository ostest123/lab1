#include "regdef.h"
#include "cp0regdef.h"

#define LEAF(symbol)        \
  .globl symbol;            \
  .align 2;                 \
  .type  symbol, @function; \
  .ent   symbol, 0;         \
symbol:  .frame sp, 0, ra

#define NESTED(symbol, framesize, rpc) \
  .globl symbol;                       \
  .align 2;                            \
  .type  symbol, @function;            \
  .ent   symbol, 0;                    \
symbol: .frame sp, framesize, rpc

#define END(function)       \
  .end  function;           \
  .size funcion, .-function
