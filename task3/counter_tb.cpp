#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

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

    //innit Vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("ALLAHU AKBAR");
    vbdSetMode(1);

    //set init variables
    top->clk = 1;
    top->rst = 0;
    top->ld = 1;
    top->v = 0;

    // run the simulation over 300 clk cycles
    for (i = 0; i<1000; i++) {

        //dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk++){
            tfp->dump (2*i+clk); //unit in ps
            top->clk = !top->clk;
            top->eval ();
        }

        //Send count value to Vbuddy
        ///*
        vbdHex(4, (int(top->count) >> 12) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        //*/
        //Plot on TFT
        //vbdPlot(int(top->count), 0 , 255);

        vbdCycle(i+1);
        
        //change input stimuli
        top->v = vbdValue();
        top->ld = vbdFlag();
        if(Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}   
