#!/bin/bash

verilator -cc TLSimpleL2Cache.v TLMonitor_54.v plusarg_reader.v L2_meta_array.v L2_data_array.v --exe sim_main.cpp
make -C obj_dir/ -f VTLSimpleL2Cache.mk
