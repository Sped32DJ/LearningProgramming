module fasystem_bh(
input wire clk,
input wire call_button ,
input wire cancel_button ,
output reg light_state
);
// Internal wire
reg c_state ;
// Combinatorial block
always @(*) begin
    // q = light_state
    // c_state = call
case ({call_button,cancel_button})
2'b00: c_state = light_state ? 'd1 : 'd0 ;
2'b01: c_state = 'd0 ;

// Write the two following states
2'b10: c_state = 'd1;
2'b11: c_state = 'd1;
default : c_state = 'd0 ;
endcase
end
// Sequential block
always @( posedge clk ) begin
    light_state <= c_state ;
end
endmodule

module edgedetector_bh(
input wire clk,
input wire signal,
output reg outedge );

wire slow_clk ;
reg [1:0] c_state ;
reg [1:0] r_state ;
// Define your FSM states
localparam ZERO = 'd0;
localparam CHANGE = 'd1;
localparam ONE = 'd2;
// EECS150 - Digital Design Lecture 17 - Finite State Machines Revisited
// Code for clkdiv module is given below. Create a new Verilog module in the
//same project with the given code.
clkdiv c1(clk, slow_clk );
// Comb. logic.
always @(*) begin
case (r_state)
ZERO : begin
c_state = signal ? CHANGE : ZERO ;
outedge = 'd0 ;
end
CHANGE : begin
    c_state = signal ? ONE : ZERO ;
    outedge = 'd1;
end
ONE : begin
    c_state = signal ? ONE : ZERO ;
    outedge = 'd0;
end
default : begin
c_state = ZERO ;
outedge = 'd0 ;
end
endcase

end
// Seq. logic
always @( posedge slow_clk ) begin
r_state <= c_state ;
end
endmodule

module clkdiv(clk,clk_out);
input clk;
output clk_out;
reg [15:0] COUNT;
initial COUNT = 0;
assign clk_out=COUNT[3];
always @(posedge clk)
begin
COUNT = COUNT + 1;
end
endmodule
