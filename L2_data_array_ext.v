module L2_data_array_ext(
input RW0_clk,
input [13:0] RW0_addr,
input RW0_en,
input RW0_wmode,
input [15:0] RW0_wmask,
input [1023:0] RW0_wdata,
output [1023:0] RW0_rdata
);

reg reg_RW0_ren;
reg [13:0] reg_RW0_addr;
reg [1023:0] ram [16383:0];
`ifdef RANDOMIZE_MEM_INIT
integer initvar;
initial begin
#`RANDOMIZE_DELAY begin end
for (initvar = 0; initvar < 16384; initvar = initvar+1)
ram[initvar] = {32 {$random}};
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
if (RW0_wmask[0]) ram[RW0_addr][63:0] <= RW0_wdata[63:0];
if (RW0_wmask[1]) ram[RW0_addr][127:64] <= RW0_wdata[127:64];
if (RW0_wmask[2]) ram[RW0_addr][191:128] <= RW0_wdata[191:128];
if (RW0_wmask[3]) ram[RW0_addr][255:192] <= RW0_wdata[255:192];
if (RW0_wmask[4]) ram[RW0_addr][319:256] <= RW0_wdata[319:256];
if (RW0_wmask[5]) ram[RW0_addr][383:320] <= RW0_wdata[383:320];
if (RW0_wmask[6]) ram[RW0_addr][447:384] <= RW0_wdata[447:384];
if (RW0_wmask[7]) ram[RW0_addr][511:448] <= RW0_wdata[511:448];
if (RW0_wmask[8]) ram[RW0_addr][575:512] <= RW0_wdata[575:512];
if (RW0_wmask[9]) ram[RW0_addr][639:576] <= RW0_wdata[639:576];
if (RW0_wmask[10]) ram[RW0_addr][703:640] <= RW0_wdata[703:640];
if (RW0_wmask[11]) ram[RW0_addr][767:704] <= RW0_wdata[767:704];
if (RW0_wmask[12]) ram[RW0_addr][831:768] <= RW0_wdata[831:768];
if (RW0_wmask[13]) ram[RW0_addr][895:832] <= RW0_wdata[895:832];
if (RW0_wmask[14]) ram[RW0_addr][959:896] <= RW0_wdata[959:896];
if (RW0_wmask[15]) ram[RW0_addr][1023:960] <= RW0_wdata[1023:960];
end
`ifdef RANDOMIZE_GARBAGE_ASSIGN
reg [1023:0] RW0_random;
`ifdef RANDOMIZE_MEM_INIT
initial begin
#`RANDOMIZE_DELAY begin end
RW0_random = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
reg_RW0_ren = RW0_random[0];
end
`endif
always @(posedge RW0_clk) RW0_random <= {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
assign RW0_rdata = reg_RW0_ren ? ram[reg_RW0_addr] : RW0_random[1023:0];
`else
assign RW0_rdata = ram[reg_RW0_addr];
`endif

endmodule
