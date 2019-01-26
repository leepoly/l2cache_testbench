module L2_data_array(
  input  [13:0] RW0_addr,
  input         RW0_en,
  input         RW0_clk,
  input         RW0_wmode,
  input  [63:0] RW0_wdata_0,
  input  [63:0] RW0_wdata_1,
  input  [63:0] RW0_wdata_2,
  input  [63:0] RW0_wdata_3,
  input  [63:0] RW0_wdata_4,
  input  [63:0] RW0_wdata_5,
  input  [63:0] RW0_wdata_6,
  input  [63:0] RW0_wdata_7,
  input  [63:0] RW0_wdata_8,
  input  [63:0] RW0_wdata_9,
  input  [63:0] RW0_wdata_10,
  input  [63:0] RW0_wdata_11,
  input  [63:0] RW0_wdata_12,
  input  [63:0] RW0_wdata_13,
  input  [63:0] RW0_wdata_14,
  input  [63:0] RW0_wdata_15,
  output [63:0] RW0_rdata_0,
  output [63:0] RW0_rdata_1,
  output [63:0] RW0_rdata_2,
  output [63:0] RW0_rdata_3,
  output [63:0] RW0_rdata_4,
  output [63:0] RW0_rdata_5,
  output [63:0] RW0_rdata_6,
  output [63:0] RW0_rdata_7,
  output [63:0] RW0_rdata_8,
  output [63:0] RW0_rdata_9,
  output [63:0] RW0_rdata_10,
  output [63:0] RW0_rdata_11,
  output [63:0] RW0_rdata_12,
  output [63:0] RW0_rdata_13,
  output [63:0] RW0_rdata_14,
  output [63:0] RW0_rdata_15,
  input         RW0_wmask_0,
  input         RW0_wmask_1,
  input         RW0_wmask_2,
  input         RW0_wmask_3,
  input         RW0_wmask_4,
  input         RW0_wmask_5,
  input         RW0_wmask_6,
  input         RW0_wmask_7,
  input         RW0_wmask_8,
  input         RW0_wmask_9,
  input         RW0_wmask_10,
  input         RW0_wmask_11,
  input         RW0_wmask_12,
  input         RW0_wmask_13,
  input         RW0_wmask_14,
  input         RW0_wmask_15
);
  wire [13:0] L2_data_array_ext_RW0_addr;
  wire  L2_data_array_ext_RW0_en;
  wire  L2_data_array_ext_RW0_clk;
  wire  L2_data_array_ext_RW0_wmode;
  wire [1023:0] L2_data_array_ext_RW0_wdata;
  wire [1023:0] L2_data_array_ext_RW0_rdata;
  wire [15:0] L2_data_array_ext_RW0_wmask;
  wire [63:0] _GEN_0;
  wire [63:0] _GEN_1;
  wire [63:0] _GEN_2;
  wire [63:0] _GEN_3;
  wire [63:0] _GEN_4;
  wire [63:0] _GEN_5;
  wire [63:0] _GEN_6;
  wire [63:0] _GEN_7;
  wire [63:0] _GEN_8;
  wire [63:0] _GEN_9;
  wire [63:0] _GEN_10;
  wire [63:0] _GEN_11;
  wire [63:0] _GEN_12;
  wire [63:0] _GEN_13;
  wire [63:0] _GEN_14;
  wire [63:0] _GEN_15;
  wire [63:0] _GEN_16;
  wire [63:0] _GEN_17;
  wire [63:0] _GEN_18;
  wire [63:0] _GEN_19;
  wire [127:0] _GEN_20;
  wire [127:0] _GEN_21;
  wire [63:0] _GEN_22;
  wire [63:0] _GEN_23;
  wire [63:0] _GEN_24;
  wire [63:0] _GEN_25;
  wire [127:0] _GEN_26;
  wire [127:0] _GEN_27;
  wire [255:0] _GEN_28;
  wire [255:0] _GEN_29;
  wire [63:0] _GEN_30;
  wire [63:0] _GEN_31;
  wire [63:0] _GEN_32;
  wire [63:0] _GEN_33;
  wire [127:0] _GEN_34;
  wire [127:0] _GEN_35;
  wire [63:0] _GEN_36;
  wire [63:0] _GEN_37;
  wire [63:0] _GEN_38;
  wire [63:0] _GEN_39;
  wire [127:0] _GEN_40;
  wire [127:0] _GEN_41;
  wire [255:0] _GEN_42;
  wire [255:0] _GEN_43;
  wire [511:0] _GEN_44;
  wire [511:0] _GEN_45;
  wire  _GEN_46;
  wire  _GEN_47;
  wire  _GEN_48;
  wire  _GEN_49;
  wire [1:0] _GEN_50;
  wire [1:0] _GEN_51;
  wire  _GEN_52;
  wire  _GEN_53;
  wire  _GEN_54;
  wire  _GEN_55;
  wire [1:0] _GEN_56;
  wire [1:0] _GEN_57;
  wire [3:0] _GEN_58;
  wire [3:0] _GEN_59;
  wire  _GEN_60;
  wire  _GEN_61;
  wire  _GEN_62;
  wire  _GEN_63;
  wire [1:0] _GEN_64;
  wire [1:0] _GEN_65;
  wire  _GEN_66;
  wire  _GEN_67;
  wire  _GEN_68;
  wire  _GEN_69;
  wire [1:0] _GEN_70;
  wire [1:0] _GEN_71;
  wire [3:0] _GEN_72;
  wire [3:0] _GEN_73;
  wire [7:0] _GEN_74;
  wire [7:0] _GEN_75;
  L2_data_array_ext L2_data_array_ext (
    .RW0_addr(L2_data_array_ext_RW0_addr),
    .RW0_en(L2_data_array_ext_RW0_en),
    .RW0_clk(L2_data_array_ext_RW0_clk),
    .RW0_wmode(L2_data_array_ext_RW0_wmode),
    .RW0_wdata(L2_data_array_ext_RW0_wdata),
    .RW0_rdata(L2_data_array_ext_RW0_rdata),
    .RW0_wmask(L2_data_array_ext_RW0_wmask)
  );
  assign L2_data_array_ext_RW0_clk = RW0_clk;
  assign L2_data_array_ext_RW0_en = RW0_en;
  assign L2_data_array_ext_RW0_addr = RW0_addr;
  assign _GEN_0 = L2_data_array_ext_RW0_rdata[63:0];
  assign RW0_rdata_0 = $unsigned(_GEN_0);
  assign _GEN_1 = L2_data_array_ext_RW0_rdata[127:64];
  assign RW0_rdata_1 = $unsigned(_GEN_1);
  assign _GEN_2 = L2_data_array_ext_RW0_rdata[191:128];
  assign RW0_rdata_2 = $unsigned(_GEN_2);
  assign _GEN_3 = L2_data_array_ext_RW0_rdata[255:192];
  assign RW0_rdata_3 = $unsigned(_GEN_3);
  assign _GEN_4 = L2_data_array_ext_RW0_rdata[319:256];
  assign RW0_rdata_4 = $unsigned(_GEN_4);
  assign _GEN_5 = L2_data_array_ext_RW0_rdata[383:320];
  assign RW0_rdata_5 = $unsigned(_GEN_5);
  assign _GEN_6 = L2_data_array_ext_RW0_rdata[447:384];
  assign RW0_rdata_6 = $unsigned(_GEN_6);
  assign _GEN_7 = L2_data_array_ext_RW0_rdata[511:448];
  assign RW0_rdata_7 = $unsigned(_GEN_7);
  assign _GEN_8 = L2_data_array_ext_RW0_rdata[575:512];
  assign RW0_rdata_8 = $unsigned(_GEN_8);
  assign _GEN_9 = L2_data_array_ext_RW0_rdata[639:576];
  assign RW0_rdata_9 = $unsigned(_GEN_9);
  assign _GEN_10 = L2_data_array_ext_RW0_rdata[703:640];
  assign RW0_rdata_10 = $unsigned(_GEN_10);
  assign _GEN_11 = L2_data_array_ext_RW0_rdata[767:704];
  assign RW0_rdata_11 = $unsigned(_GEN_11);
  assign _GEN_12 = L2_data_array_ext_RW0_rdata[831:768];
  assign RW0_rdata_12 = $unsigned(_GEN_12);
  assign _GEN_13 = L2_data_array_ext_RW0_rdata[895:832];
  assign RW0_rdata_13 = $unsigned(_GEN_13);
  assign _GEN_14 = L2_data_array_ext_RW0_rdata[959:896];
  assign RW0_rdata_14 = $unsigned(_GEN_14);
  assign _GEN_15 = L2_data_array_ext_RW0_rdata[1023:960];
  assign RW0_rdata_15 = $unsigned(_GEN_15);
  assign L2_data_array_ext_RW0_wmode = RW0_wmode;
  assign _GEN_16 = $unsigned(RW0_wdata_15);
  assign _GEN_17 = $unsigned(RW0_wdata_14);
  assign _GEN_18 = $unsigned(RW0_wdata_13);
  assign _GEN_19 = $unsigned(RW0_wdata_12);
  assign _GEN_20 = {_GEN_16,_GEN_17};
  assign _GEN_21 = {_GEN_18,_GEN_19};
  assign _GEN_22 = $unsigned(RW0_wdata_11);
  assign _GEN_23 = $unsigned(RW0_wdata_10);
  assign _GEN_24 = $unsigned(RW0_wdata_9);
  assign _GEN_25 = $unsigned(RW0_wdata_8);
  assign _GEN_26 = {_GEN_22,_GEN_23};
  assign _GEN_27 = {_GEN_24,_GEN_25};
  assign _GEN_28 = {_GEN_20,_GEN_21};
  assign _GEN_29 = {_GEN_26,_GEN_27};
  assign _GEN_30 = $unsigned(RW0_wdata_7);
  assign _GEN_31 = $unsigned(RW0_wdata_6);
  assign _GEN_32 = $unsigned(RW0_wdata_5);
  assign _GEN_33 = $unsigned(RW0_wdata_4);
  assign _GEN_34 = {_GEN_30,_GEN_31};
  assign _GEN_35 = {_GEN_32,_GEN_33};
  assign _GEN_36 = $unsigned(RW0_wdata_3);
  assign _GEN_37 = $unsigned(RW0_wdata_2);
  assign _GEN_38 = $unsigned(RW0_wdata_1);
  assign _GEN_39 = $unsigned(RW0_wdata_0);
  assign _GEN_40 = {_GEN_36,_GEN_37};
  assign _GEN_41 = {_GEN_38,_GEN_39};
  assign _GEN_42 = {_GEN_34,_GEN_35};
  assign _GEN_43 = {_GEN_40,_GEN_41};
  assign _GEN_44 = {_GEN_28,_GEN_29};
  assign _GEN_45 = {_GEN_42,_GEN_43};
  assign L2_data_array_ext_RW0_wdata = {_GEN_44,_GEN_45};
  assign _GEN_46 = $unsigned(RW0_wmask_15);
  assign _GEN_47 = $unsigned(RW0_wmask_14);
  assign _GEN_48 = $unsigned(RW0_wmask_13);
  assign _GEN_49 = $unsigned(RW0_wmask_12);
  assign _GEN_50 = {_GEN_46,_GEN_47};
  assign _GEN_51 = {_GEN_48,_GEN_49};
  assign _GEN_52 = $unsigned(RW0_wmask_11);
  assign _GEN_53 = $unsigned(RW0_wmask_10);
  assign _GEN_54 = $unsigned(RW0_wmask_9);
  assign _GEN_55 = $unsigned(RW0_wmask_8);
  assign _GEN_56 = {_GEN_52,_GEN_53};
  assign _GEN_57 = {_GEN_54,_GEN_55};
  assign _GEN_58 = {_GEN_50,_GEN_51};
  assign _GEN_59 = {_GEN_56,_GEN_57};
  assign _GEN_60 = $unsigned(RW0_wmask_7);
  assign _GEN_61 = $unsigned(RW0_wmask_6);
  assign _GEN_62 = $unsigned(RW0_wmask_5);
  assign _GEN_63 = $unsigned(RW0_wmask_4);
  assign _GEN_64 = {_GEN_60,_GEN_61};
  assign _GEN_65 = {_GEN_62,_GEN_63};
  assign _GEN_66 = $unsigned(RW0_wmask_3);
  assign _GEN_67 = $unsigned(RW0_wmask_2);
  assign _GEN_68 = $unsigned(RW0_wmask_1);
  assign _GEN_69 = $unsigned(RW0_wmask_0);
  assign _GEN_70 = {_GEN_66,_GEN_67};
  assign _GEN_71 = {_GEN_68,_GEN_69};
  assign _GEN_72 = {_GEN_64,_GEN_65};
  assign _GEN_73 = {_GEN_70,_GEN_71};
  assign _GEN_74 = {_GEN_58,_GEN_59};
  assign _GEN_75 = {_GEN_72,_GEN_73};
  assign L2_data_array_ext_RW0_wmask = {_GEN_74,_GEN_75};
endmodule
