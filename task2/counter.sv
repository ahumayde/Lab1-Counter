module counter #(
    parameter WIDTH = 16
    /*
    1111 1111 1111 1111 1111 >> 16 == 1111   
    */
)(
    input  logic clk,
    input  logic rst,
    input  logic en,
    output logic [WIDTH-1:0] count
);

always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + ( en ? {{WIDTH-1{1'b0}}, 1'b1} : {WIDTH{1'b1}} );

endmodule
