// including design file
`include "design.sv"
`timescale 1ns/1ns;

 module fasystemTest;

    //list of input ports..
    reg clk;
    //add other input ports that you will need. For example the following is for
    //flight attendant system.
    reg Call;
    reg Cancel;
    // add the required input ports for the module you are testing.

    //list of output ports..
    wire Light; //add output ports as required to test your module

    //instantiate your module to be tested here and connect ports appropriately
    //your_module_name uut (.port_name_in_module(port_name_in_testbench),...)
    //As an example module instantiation to test flight attendant call system is given below:

    fasystem_bh uut(.call_button(Call), .cancel_button(Cancel), .light_state(Light), .clk(clk));

    always #1 clk=~clk; // this will create a clock signal with fr equency of(1/2ns=500MZ)

    initial begin

        $dumpfile("fasystemOut.vcd");
        $dumpvars;

        clk=0; //this will initialize clk to logic 0 at time 0ns

        //Start giving stimulation to input ports as required to test your module here.
        //A sample stimulus set to test flight attendant call system
        // is given below as an example:

        Call=0; Cancel=0;
        #17;  //wait for appropriate amount of time so that you can see
        //some impact of input to output (i.e all the clocks in your module at least
        //completes one cycle. This includes the slow_clk as well if used. )
        Call=0; Cancel=1;
        #13;
        Call=1; Cancel=0;
        #19;
        Call=1; Cancel=1;
        #33;
        Call=0; Cancel=1;
        #13;
        Call=1; Cancel=1;
        #27;
        Call=0; Cancel=1;
        #29;

        $finish; //this is very important. Otherwise your test will
        //never stop as clock will keep running infinitely according to line 23.

    end
endmodule

module edgedectectorTest;

    //list of input ports..
    reg clk;
    //add other input ports that you will need. For example the following is for
    //flight attendant system.
    reg signal;
    // add the required input ports for the module you are testing.

    //list of output ports..
    wire outedge; //add output ports as required to test your module

    //instantiate your module to be tested here and connect ports appropriately
    //your_module_name uut (.port_name_in_module(port_name_in_testbench),...)
    //As an example module instantiation to test flight attendant call system is given below:

    edgedetector_bh uut(.clk(clk), .signal(signal), .outedge(outedge));

    always #1 clk=~clk; // this will create a clock signal with fr equency of(1/2ns=500MZ)

    initial begin

        $dumpfile("edgeDetectorOut.vcd");
        $dumpvars;

        clk=0; //this will initialize clk to logic 0 at time 0ns

        //Start giving stimulation to input ports as required to test your module here.
        //A sample stimulus set to test flight attendant call system
        // is given below as an example:

        signal = 0;
        #559;

        signal = 1;
        #559;

        signal = 0;
        #559;

        signal = 1;
        #559;

        signal = 0;
        #559;

        signal = 1;
        #559;

        signal = 0;
        #179;

        signal = 1;
        #99;

        signal = 0;
        #559;

        signal = 1;
        #559;

        signal = 0;
        #559;

        $finish; //this is very important. Otherwise your test will
        //never stop as clock will keep running infinitely according to line 23.

    end
endmodule
