#include <mips/regdef.h>
#include <mips/cp0regdef.h>
#include <mips/asm.h>
	
LEAF(_start)
	mtc0	zero, CP0_STATUS
	mtc0	zero, CP0_WATCHLO
	mtc0	zero, CP0_WATCHHI

	mfc0	t0, CP0_CONFIG
	and	t0, ~0x7
	ori	t0, 0x2
	mtc0	t0, CP0_CONFIG
	//goto main
	
	/* code here */
    lui t1, 0x00008040
	ori sp, t1, 0
    //can it be right?
    jal main

loop:
	j	loop
	nop
END(_start)
