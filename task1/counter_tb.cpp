#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;


    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace 
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open("counter.vcd");

    //set init variables
    top->clk = 1;
    top->rst = 0;
    top->en = 1;

    // run the simulation over 300 clk cycles
    for (i = 0; i<300; i++) {
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }
        top->en = (i < 9) | (i >= 11);
        if(Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}   
