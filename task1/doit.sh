#!/bin/sh 

# cleanup
rm -rf obj_dir
rm -f counter.vcd

# run verilator to translate verilog to c++ 
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

# built c++ project automated by verilator
make -j -C obj_dir/ -f Vcounter.mk Vcounter

#run executable
obj_dir/Vcounter
