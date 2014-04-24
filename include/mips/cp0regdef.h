#ifndef _mips_cp0regdef_h
#define _mips_cp0regdef_h

#define CP0_INDEX $0
#define CP0_RANDOM $1
#define CP0_ENTRYLO0 $2
#define CP0_ENTRYLO1 $3
#define CP0_CONTEXT $4
#define CP0_PAGEMASK $5
#define CP0_WIRED $6
#define CP0_BADVADDR $8
#define CP0_COUNT $9
#define CP0_ENTRYHI $10
#define CP0_COMPARE $11
#define CP0_STATUS $12
#define CP0_CAUSE $13
#define CP0_EPC $14
#define CP0_PRID $15
#define CP0_CONFIG $16
#define CP0_LLADDR $17
#define CP0_WATCHLO $18
#define CP0_WATCHHI $19
#define CP0_XCONTEXT $20
#define CP0_FRAMEMASK $21
#define CP0_DIAGNOSTIC $22
#define CP0_PERFORMANCE $25
#define CP0_ECC $26
#define CP0_CACHEERR $27
#define CP0_TAGLO $28
#define CP0_TAGHI $29
#define CP0_ERROREPC $30

#define STATUSF_IP7 0x8000
#define STATUSF_IP6 0x4000
#define STATUSF_IP5 0x2000
#define STATUSF_IP4 0x1000
#define STATUSF_IP3 0x800
#define STATUSF_IP2 0x400
#define STATUSF_IP1 0x200
#define STATUSF_IP0 0x100

#define STATUSF_TMR 0x40000000

#define STATUS_CU0 0x10000000
#define STATUS_KUC 0x2

#endif
