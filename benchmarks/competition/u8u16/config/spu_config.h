#include "config_defs.h"
/* Compiling for PPC G4 with spu  */

#define DEL_OVERRIDE
#define U8U16_TARGET SPU_TARGET
#define BYTE_ORDER BIG_ENDIAN

#define ALTIVEC_USE_EVEN_INDICES

#define S2P_ALGORITHM S2P_BYTEPACK
#define P2S_ALGORITHM P2S_BYTEMERGE

#ifndef DEL_OVERRIDE 
#define BIT_DELETION NO_BIT_DELETION
#define BYTE_DELETION BYTE_DEL_BY_PERMUTE_TO_LEFT8
#define DOUBLEBYTE_DELETION ALTIVEC_FROM_LEFT8
#endif

#ifdef DEL_OVERRIDE
//#define BIT_DELETION ADDITIVE_SHIFT_TO_LEFT8
#define BIT_DELETION ROTATION_TO_LEFT8
#define BYTE_DELETION NO_BYTE_DELETION
#define DOUBLEBYTE_DELETION ALTIVEC_FROM_LEFT8
#endif

#define INBUF_READ_OVERRIDE
#define OUTBUF_WRITE_OVERRIDE

