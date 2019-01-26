// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "VTLSimpleL2Cache__Syms.h"
#include "VTLSimpleL2Cache.h"

// FUNCTIONS
VTLSimpleL2Cache__Syms::VTLSimpleL2Cache__Syms(VTLSimpleL2Cache* topp, const char* namep)
	// Setup locals
	: __Vm_namep(namep)
	, __Vm_activity(false)
	, __Vm_didInit(false)
	// Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    // Setup scope names
    __Vscope_TLSimpleL2Cache.configure(this,name(),"TLSimpleL2Cache");
    __Vscope_TLSimpleL2Cache__TLMonitor.configure(this,name(),"TLSimpleL2Cache.TLMonitor");
}
