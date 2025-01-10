#ifndef _Data_Type_h_
#define _Data_Type_h_



#define seg_a   0x01
#define seg_b   0x02
#define seg_c   0x04
#define seg_d   0x08
#define seg_e   0x10
#define seg_f   0x20
#define seg_g   0x40
#define seg_h   0x80

#define bit0    0x01
#define bit1    0x02
#define bit2    0x04
#define bit3    0x08
#define bit4    0x10
#define bit5    0x20
#define bit6    0x40
#define bit7    0x80





#define bit00    0x00000001
#define bit01    0x00000002
#define bit02    0x00000004
#define bit03    0x00000008
#define bit04    0x00000010
#define bit05    0x00000020
#define bit06    0x00000040
#define bit07    0x00000080
#define bit08    0x00000100
#define bit09    0x00000200
#define bit10    0x00000400
#define bit11    0x00000800
#define bit12    0x00001000
#define bit13    0x00002000
#define bit14    0x00004000
#define bit15    0x00008000
#define bit16    0x00010000
#define bit17    0x00020000
#define bit18    0x00040000
#define bit19    0x00080000
#define bit20    0x00100000
#define bit21    0x00200000
#define bit22    0x00400000
#define bit23    0x00800000
#define bit24    0x01000000
#define bit25    0x02000000
#define bit26    0x04000000
#define bit27    0x08000000
#define bit28    0x10000000
#define bit29    0x20000000
#define bit30    0x40000000
#define bit31    0x80000000

#define GETBIT_VAL(var,bit) 		(var&(1<<bit))
#define SETBIT_VAL(var,bit) 		(var|=(1<<bit))
#define CLRBIT_VAL(var,bit) 		(var&=(~(0x01<<(bit))))

#define     BYTEMAX                 255
#define     WORDMAX                 65500

#endif
