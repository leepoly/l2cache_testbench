module L2_meta_array_ext(
input RW0_clk,
input [10:0] RW0_addr,
input RW0_en,
input RW0_wmode,
input [367:0] RW0_wdata,
output [367:0] RW0_rdata
);

reg reg_RW0_ren;
reg [10:0] reg_RW0_addr;
reg [367:0] ram [2047:0];
`ifdef RANDOMIZE_MEM_INIT
integer initvar;
initial begin
#`RANDOMIZE_DELAY begin end
for (initvar = 0; initvar < 2048; initvar = initvar+1)
ram[initvar] = {12 {$random}};
reg_RW0_addr = {1 {$random}};
end
`endif
integer i;
always @(posedge RW0_clk)
reg_RW0_ren <= RW0_en && !RW0_wmode;
always @(posedge RW0_clk)
if (RW0_en && !RW0_wmode) reg_RW0_addr <= RW0_addr;
always @(posedge RW0_clk)
if (RW0_en && RW0_wmode) begin
ram[RW0_addr][367:0] <= RW0_wdata[367:0];
end
`ifdef RANDOMIZE_GARBAGE_ASSIGN
reg [383:0] RW0_random;
`ifdef RANDOMIZE_MEM_INIT
initial begin
#`RANDOMIZE_DELAY begin end
RW0_random = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
reg_RW0_ren = RW0_random[0];
end
`endif
always @(posedge RW0_clk) RW0_random <= {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
assign RW0_rdata = reg_RW0_ren ? ram[reg_RW0_addr] : RW0_random[367:0];
`else
assign RW0_rdata = ram[reg_RW0_addr];
`endif

endmodule
