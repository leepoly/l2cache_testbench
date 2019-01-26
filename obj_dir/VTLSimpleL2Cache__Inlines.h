// Verilated -*- C++ -*-
#ifndef _VTLSimpleL2Cache__Inlines_H_
#define _VTLSimpleL2Cache__Inlines_H_

#include "verilated.h"

//======================

#ifndef VL_HAVE_CONST_W_11X
# define VL_HAVE_CONST_W_11X
static inline WDataOutP VL_CONST_W_11X(int obits, WDataOutP o
    	,IData d10,IData d9,IData d8
    	,IData d7,IData d6,IData d5,IData d4,IData d3,IData d2,IData d1,IData d0) {
        o[10]=d10; o[9]=d9; o[8]=d8;
        o[7]=d7; o[6]=d6; o[5]=d5; o[4]=d4; o[3]=d3; o[2]=d2; o[1]=d1; o[0]=d0;
        for(int i=11;i<VL_WORDS_I(obits);i++) o[i] = (IData)0x0;
        return o;
}
#endif

#ifndef VL_HAVE_CONST_W_12X
# define VL_HAVE_CONST_W_12X
static inline WDataOutP VL_CONST_W_12X(int obits, WDataOutP o
    	,IData d11,IData d10,IData d9,IData d8
    	,IData d7,IData d6,IData d5,IData d4,IData d3,IData d2,IData d1,IData d0) {
        o[11]=d11; o[10]=d10; o[9]=d9; o[8]=d8;
        o[7]=d7; o[6]=d6; o[5]=d5; o[4]=d4; o[3]=d3; o[2]=d2; o[1]=d1; o[0]=d0;
        for(int i=12;i<VL_WORDS_I(obits);i++) o[i] = (IData)0x0;
        return o;
}
#endif

#ifndef VL_HAVE_CONST_W_32X
# define VL_HAVE_CONST_W_32X
static inline WDataOutP VL_CONST_W_32X(int obits, WDataOutP o
    	,IData d31,IData d30,IData d29,IData d28,IData d27,IData d26,IData d25,IData d24
    	,IData d23,IData d22,IData d21,IData d20,IData d19,IData d18,IData d17,IData d16
    	,IData d15,IData d14,IData d13,IData d12,IData d11,IData d10,IData d9,IData d8
    	,IData d7,IData d6,IData d5,IData d4,IData d3,IData d2,IData d1,IData d0) {
        o[31]=d31; o[30]=d30; o[29]=d29; o[28]=d28; o[27]=d27; o[26]=d26; o[25]=d25; o[24]=d24;
        o[23]=d23; o[22]=d22; o[21]=d21; o[20]=d20; o[19]=d19; o[18]=d18; o[17]=d17; o[16]=d16;
        o[15]=d15; o[14]=d14; o[13]=d13; o[12]=d12; o[11]=d11; o[10]=d10; o[9]=d9; o[8]=d8;
        o[7]=d7; o[6]=d6; o[5]=d5; o[4]=d4; o[3]=d3; o[2]=d2; o[1]=d1; o[0]=d0;
        for(int i=32;i<VL_WORDS_I(obits);i++) o[i] = (IData)0x0;
        return o;
}
#endif

//======================

#endif  /*guard*/
