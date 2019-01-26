// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _VTLSimpleL2Cache__Syms_H_
#define _VTLSimpleL2Cache__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "VTLSimpleL2Cache.h"

// SYMS CLASS
class VTLSimpleL2Cache__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool	__Vm_activity;		///< Used by trace routines to determine change occurred
    bool	__Vm_didInit;
    //char	__VpadToAlign10[6];
    
    // SUBCELL STATE
    VTLSimpleL2Cache*              TOPp;
    
    // COVERAGE
    
    // SCOPE NAMES
    VerilatedScope __Vscope_TLSimpleL2Cache;
    VerilatedScope __Vscope_TLSimpleL2Cache__TLMonitor;
    
    // CREATORS
    VTLSimpleL2Cache__Syms(VTLSimpleL2Cache* topp, const char* namep);
    ~VTLSimpleL2Cache__Syms() {};
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    inline bool getClearActivity() { bool r=__Vm_activity; __Vm_activity=false; return r;}
    
} VL_ATTR_ALIGNED(64);

#endif  /*guard*/
