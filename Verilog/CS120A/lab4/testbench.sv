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

// For Part 3:
module bcdto7led_bh(
input wire sw0 ,
input wire sw1 ,
input wire sw2 ,
input wire sw3 ,
output reg a ,
output reg b ,
output reg c ,
output reg d ,
output reg e ,
output reg f ,
output reg g ,
output reg dp
);
// Internal wire
wire [3:0] bundle ;
assign bundle = {sw3,sw2,sw1,sw0 } ;
always @(*) begin
a = 1'b1 ;
b = 1'b1 ;
c = 1'b1 ;
d = 1'b1 ;
e = 1'b1 ;
f = 1'b1 ;
g = 1'b1 ;
dp = 1'b1;
case ( bundle )
4'b0000 : begin // 0
a = 1'b0 ;
b = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
end
4'b0001 : begin // 1
b = 1'b0 ;
c = 1'b0 ;
end
4'b0010 : begin // 2
a = 1'b0 ;
b = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
g = 1'b0 ;
end
4'b0011 : begin // 3
a = 1'b0 ;
b = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
g = 1'b0 ;
end
4'b0100 : begin // 4
b = 1'b0 ;
c = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b0101 : begin // 5
a = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b0110 : begin // 6
a = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b0111 : begin // 7
a = 1'b0 ;
b = 1'b0 ;
c = 1'b0 ;
end
4'b1000 : begin // 8
a = 1'b0 ;
b = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b1001 : begin // 9
a = 1'b0 ;
b = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b1010 : begin // A
a = 1'b0 ;
b = 1'b0 ;
c = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b1011 : begin // B
c = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b1100 : begin // C
a = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
end
4'b1101 : begin // D
b = 1'b0 ;
c = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
g = 1'b0 ;
end
4'b1110 : begin // E
a = 1'b0 ;
d = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
4'b1111 : begin // F
a = 1'b0 ;
e = 1'b0 ;
f = 1'b0 ;
g = 1'b0 ;
end
endcase
end
endmodule
