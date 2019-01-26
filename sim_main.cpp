#include "verilated.h"          // Defines common routines
#include <iostream>             // Need std::cout
#include "VTLSimpleL2Cache.h"               // From Verilating "top.v"
#define TOP VTLSimpleL2Cache
#define RESET_TIME 10000
#define TEST_END 100000
#define TLMESSAGE_GET 0x4
#define TLMESSAGE_PUTFULLDATA 0x0
#define MEM_SIZE 0xffff

typedef int u32;
typedef long u64;
typedef char u8;

TOP* top;                     // Instantiation of module
vluint64_t main_time = 0;       // Current simulation time
int state = 0;					// simulator state
int test_case;
int test_case_type = 0; //0: read case; 1: write case;
u64 test_case_addr = 0x0;
u8 mem[MEM_SIZE];

int readCntFromMemToCache = -1;
int readCntFromCacheToCPU = -1;
int writeCntFromCPUToCache = -1;
int writeCntFromCacheToMem = -1;
u64 cache_reply_buf[8];
u64 to_mem_paddr; 
u64 to_mem_vaddr;
//0 <--> nop; 1 <--> request read/write addr; 2 <--> cache reply 1; 6 <--> cpu reply data
//4 <--> cache request read data from mem(8 beats total);
//5 <--> transmit consistent wdata (8 beats total)
//Trace: 
//read hit: 0 nop -> 1 req read addr -> 2 cache reply read req -> 6 cache reply rdata
//read miss: 0 nop -> 1 req read addr -> 2 cache reply read req -> 4 cache request read data from mem -> 6 cache reply rdata
//write hit: 0 nop -> 5 transmit consistent wdata -> 7 cache reply 'bresp' -> 8 cache state turn 'idle'(cache real finished)
//write miss:
//read miss writeback: 0 nop -> 1 req read addr -> 2 cache reply read req -> 9 cache wdata to ram -> 2 -> 4 cache request read data from mem -> 6 cache reply rdata
//write miss writeback: 0 nop -> 5 transmit consistent wdata -> 7 cache reply 'bresp' -> 8 cache state turn 'idle'(cache real finished) -> 9 cache wdata to ram -> 8

int ValidateReply() {
	printf("test_case: %d PASSED!\n", test_case);
	//TODO: compare diff of mem and StandardMem, diff of cache_reply_buf and StandardCacheReplyBuf
	return 0;
}

u64 PAddrToVAddr(u64 paddr) {
	return (paddr & 0x000000000000ffff);
}

void printInfo(const char* str) {
	cout << "-------" << str << endl;
	cout << "main_time: " << main_time << endl;
	printf("DEBUG simulator_state %x\n", state);
	printf("DEBUG cache_state %x\n", top->TLSimpleL2Cache__DOT___T_267); //T_267 is the state machine

	//printf("io_deq_bits: %d\n", top->io_deq_bits);
	//printf("DEBUG TLSimpleL2Cache__DOT___T_6887_456 %x\n", top->TLSimpleL2Cache__DOT___T_6887_456); //T_267 is the state machine
	//printf("io_deq_ready: %d\n", top->io_deq_ready);
	//printf("io_deq_valid: %d\n", top->io_deq_valid);
}

void printOutA() {
	cout << "-------cache request read data from mem:" << endl;
	cout << "main_time: " << main_time << endl;
	//printf("out.a.opcode: %x\n", top->auto_out_a_bits_opcode);
	printf("out.a.address: %lx\n", top->auto_out_a_bits_address);
	printf("out.a.data: %lx\n", top->auto_out_a_bits_data);
}

void printInD() {
	cout << "-------cache reply read data to processor:" << endl;
	cout << "main_time: " << main_time << endl;
	printf("in.d.opcode: %x\n", top->auto_in_d_bits_opcode);
	//printf("in.d.size: %x\n", top->auto_in_d_bits_size);
	//printf("in.d.source: %x\n", top->auto_in_d_bits_source);
	printf("in.d.data: %lx\n", top->auto_in_d_bits_data);
}

void op_sendDataFromMemToCache(u64 val) {
	top->auto_out_d_valid = 0x1;
	top->auto_out_d_bits_data = val;
}

void op_sendBrespFromMemToCache() {
	top->auto_out_d_valid = 0x1;
}

void op_reqCacheReadData(u64 addr) {
	top->auto_in_a_bits_opcode = TLMESSAGE_GET;
	top->auto_in_a_bits_address = addr;
	top->auto_in_a_valid = 0x1; //weird problem happens if put valid & request singals in same cycle
}

void op_reqCacheWriteData(u64 addr, u64 first_data_beat) {
	writeCntFromCPUToCache = 0;
	top->auto_in_a_bits_address = addr;
	top->auto_in_a_bits_data = first_data_beat;
	top->auto_in_a_valid = 0x1;
}

void op_reqCacheWriteData1(u64 next_data_beat) {
	top->auto_in_a_bits_data = next_data_beat;
}

double sc_time_stamp () {       // Called by $time in Verilog
	return main_time;           // converts to double, to match
								// what SystemC does
}

u64 getMemData(u64 start_addr, int len_byte) {
	if (len_byte != 8) return 0x0;
	u64 result;
	memcpy(&result, (u8 *)(mem + start_addr), len_byte);
	//printf("get***%lx: %lx\n", start_addr, result);
	return result;
}

void writeMemData(u64 start_addr, u64 wdata, int len_byte) {
	if (len_byte != 8) return;
	u64 data = wdata;
	//printf("write***%lx: %lx\n", start_addr, data);
	memcpy((u8 *)(mem + start_addr), &data, len_byte);
}

void initMainMemory () {
	for (int i = 0x1100; i < 0xff00; i = i + 8) {
		writeMemData(i, i, 8);
	}
/*	mem[0x000000100 + 0] = 0xdeadbeef2040406f;
	mem[0x000000100 + 1] = 0xdeadbeefaaaaaaaa;
	mem[0x000000100 + 2] = 0xdeadbeefbbbbbbbb;
	mem[0x000000100 + 3] = 0xdeadbeefcccccccc;
	mem[0x000000100 + 4] = 0xdeadbeefdddddddd;
	mem[0x000000100 + 5] = 0xdeadbeefeeeeeeee;
	mem[0x000000100 + 6] = 0xdeadbeefffffffff;
	mem[0x000000100 + 7] = 0xdeadbeefdeadbeef;*/

/*	mem[0x000001100 + 0] = 0xbeefdead00000000;
	mem[0x000001100 + 1] = 0xbeefdead11111111;
	mem[0x000001100 + 2] = 0xbeefdead22222222;
	mem[0x000001100 + 3] = 0xbeefdead33333333;
	mem[0x000001100 + 4] = 0xbeefdead44444444;
	mem[0x000001100 + 5] = 0xbeefdead55555555;
	mem[0x000001100 + 6] = 0xbeefdead66666666;
	mem[0x000001100 + 7] = 0xbeefdead77777777;*/
}

int main(int argc, char** argv) {
	Verilated::commandArgs(argc, argv);   // Remember args
	top = new TOP;             // Create instance
	//TODO: need handling write miss

	test_case = 0;
	initMainMemory();

	while (!Verilated::gotFinish()) {
		//init signal
		if (main_time < RESET_TIME) {
			state = 0;
			top->reset = 1;    
			
			top->auto_in_a_valid = 0x0;
			top->auto_in_a_bits_dsid = 0x01;
			top->auto_in_a_bits_param = 0x0;
			top->auto_in_a_bits_size = 0x6;
			top->auto_in_a_bits_source = 0x010;
			top->auto_in_a_bits_address = 0x0;
			top->auto_in_a_bits_mask = 0xff;
			top->auto_in_a_bits_data = 0x0000000000000000;

			top->auto_out_a_ready = 0x1;
			top->auto_in_d_ready = 0x1;
		}
		if (main_time == RESET_TIME + 1) {
			top->reset = 0;
		}
		//clk control
		if ((main_time % 10) == 1) {
			top->clock = 1;       // Toggle clock
		}
		else if ((main_time % 10) == 6) {
			top->clock = 0;
		}
		//state machine
		if ((main_time > RESET_TIME) && (main_time % 10 == 1)) {
			// if (main_time >= 51301 && main_time <= 51301) {
			// 	printInfo(""); //debug
			// }

			if (state == 0) {
				if (test_case == 0) {
					state = 1;
					test_case_type = 0;
					op_reqCacheReadData(0x100001100 + test_case * 64);
					printf("test_case %d START!\n", test_case);
					printInfo("cpu: cpu(read req) ---> cache");
					printf("in.a.addr: %lx\n", top->auto_in_a_bits_address);
					//printf("in.a.size: %x\n", top->auto_in_a_bits_size);
					//printf("in.a.mask: %x\n", top->auto_in_a_bits_mask);
				}
				else if (test_case == 1) {
					state = 5;
					top->auto_in_a_bits_opcode = TLMESSAGE_PUTFULLDATA;
					test_case_type = 1;
					test_case_addr = 0x100000100;
					op_reqCacheWriteData(test_case_addr, 0xdeadbeef00000000);
					printf("test_case %d START!\n", test_case);
					printInfo("cpu: cpu(write req) ---> cache");
					printf("in.a.addr: %lx\n", top->auto_in_a_bits_address);
				}
				else if (test_case == 2) {
					state = 1;
					test_case_type = 0;
					op_reqCacheReadData(0x100000100);
					printf("test_case %d START!\n", test_case);
					printInfo("cpu: cpu(read req) ---> cache");
					printf("in.a.addr: %lx\n", top->auto_in_a_bits_address);
				}
				
			}
			else if (state == 1 && top->auto_in_a_ready == 0x1) {
				printInfo("cache: cpu ---> cache(read req)");
				state = 2;
				top->auto_in_a_valid = 0x0;
			}

			else if (state == 2) {
				if ((top->auto_out_a_valid&top->auto_out_a_ready == 0x1) && (top->auto_out_a_bits_opcode == TLMESSAGE_GET)) {
					printInfo("mem: cache ---> mem(read req1)");
					state = 4;
					top->auto_out_a_ready = 0x0;
					readCntFromMemToCache = 0;
					printOutA();
					to_mem_paddr = top->auto_out_a_bits_address;
					to_mem_vaddr = PAddrToVAddr(to_mem_paddr);
					//printf("DEBUG vaddr:%lx\n", to_mem_vaddr);
					op_sendDataFromMemToCache(getMemData(to_mem_vaddr + readCntFromMemToCache * 8, 8));
					//printInfo("mem: cache <--- mem(data beat)");
					//printf("out.d.data: %lx\n", top->auto_out_d_bits_data);
				}
				else if ((top->auto_in_d_valid&&top->auto_in_d_ready == 0x1)) {
					printInfo("cache: cpu <--- cache(read req)");
					printInD();
					state = 6;
					readCntFromCacheToCPU = 0;
					cache_reply_buf[readCntFromCacheToCPU] = top->auto_in_d_bits_data;
				}
				else if ((top->auto_out_a_valid&top->auto_out_a_ready == 0x1) && (top->auto_out_a_bits_opcode == TLMESSAGE_PUTFULLDATA)) {
					printInfo("mem: cache ---> mem(write req: olddata)");
					state = 9;
					top->auto_out_a_ready = 0x1;
					writeCntFromCacheToMem = 1; //mem have received the first wdata beat
					printOutA();
					to_mem_paddr = top->auto_out_a_bits_address;
					to_mem_vaddr = PAddrToVAddr(to_mem_paddr);
					writeMemData(to_mem_vaddr, top->auto_out_a_bits_data, 8);
				}
			}

			else if (state == 4) {
				//printf("***DEBUG %d\n", to_mem_vaddr + readCntFromMemToCache);
				op_sendDataFromMemToCache(getMemData(to_mem_vaddr + readCntFromMemToCache * 8, 8));
				printInfo("mem: cache <--- mem(data beat)");
				printf("out.d.data: %lx\n", top->auto_out_d_bits_data);

				if (top->auto_out_d_ready == 0x1) {
					readCntFromMemToCache++;
					printInfo("cache: cache(data beat) <--- mem");
					printf("readCntFromMemToCache: %lx\n", readCntFromMemToCache);
					if (readCntFromMemToCache == 8) { 
						
						if (test_case_type == 0)
							state = 2;
						else if (test_case_type == 1)
							state = 8;
						top->auto_out_d_valid = 0x0;
						top->auto_out_a_ready = 0x1;
						readCntFromCacheToCPU = -1;
						//printInfo("cache: has recvd all data beats from mem");
					}
				}
			}

			else if (state == 6) {
				top->auto_in_d_ready = 0x1;
				if (top->auto_in_d_valid == 0x1) {
					readCntFromCacheToCPU++;
					cache_reply_buf[readCntFromCacheToCPU] = top->auto_in_d_bits_data;
					printInfo("cpu: cpu(read req) <--- cache");
					printInD();
					printf("readCntFromCacheToCPU: %lx\n", readCntFromCacheToCPU);
					if (readCntFromCacheToCPU == 7) {
						if (ValidateReply() == 0)
							test_case++;
						state = 0;
						readCntFromCacheToCPU = -1;
						//printInfo("CPU: has recvd all data beats from cache");
					}
				}
			}

			else if (state == 5) {
				op_reqCacheWriteData1(0xdeadbeef00000000 + writeCntFromCPUToCache);
				printInfo("cpu: cpu(wdata beat) ---> cache");
				printf("in.a.data: %lx\n", top->auto_in_a_bits_data);
				if (top->auto_in_a_valid&&top->auto_in_a_ready == 0x1) {
					printInfo("cache: cpu ---> cache(read req)");
					writeCntFromCPUToCache++;
					printf("writeCntFromCPUToCache: %lx\n", writeCntFromCPUToCache);
					if (writeCntFromCPUToCache == 8) {
						state = 7;
						top->auto_in_a_valid = 0x0;
						writeCntFromCPUToCache = -1;
					}
				}
			}

			else if (state == 7) {
				if (top->auto_in_d_ready && top->auto_in_d_valid == 0x1) {
					state = 8;
					printInfo("cache: cpu(bresp) <---- cache");
				}
			}

			else if (state == 8) {
				if (top->TLSimpleL2Cache__DOT___T_267 == 0x0) { //T_267 is cache_state
					state = 0;
					printf("test_case %d: successfully written into cache.\n", test_case);
					printInfo("");
					test_case_addr = 0x0;
					test_case++;
				}
				else if ((top->auto_out_a_valid&top->auto_out_a_ready == 0x1) && (top->auto_out_a_bits_opcode == TLMESSAGE_GET)) {
					printInfo("mem: cache ---> mem(read req')");
					state = 4;
					top->auto_out_a_ready = 0x0;
					readCntFromMemToCache = 0;
					printOutA();
					to_mem_paddr = top->auto_out_a_bits_address;
					to_mem_vaddr = PAddrToVAddr(to_mem_paddr);
					//printf("DEBUG vaddr:%lx\n", to_mem_vaddr);
					op_sendDataFromMemToCache(getMemData(to_mem_vaddr + readCntFromMemToCache * 8, 8));
					printInfo("mem: cache <--- mem(data beat)");
					printf("out.d.data: %lx\n", top->auto_out_d_bits_data);
				}
			}

			else if (state == 9) {
				//writeback
				if ((top->auto_out_a_ready&top->auto_out_a_valid == 0x1) && (top->auto_out_a_bits_opcode == TLMESSAGE_PUTFULLDATA)) {
					printf("out.a.data: %lx\n", top->auto_out_a_bits_data);
					writeMemData(to_mem_vaddr + writeCntFromCacheToMem * 8, top->auto_out_a_bits_data, 8);
					writeCntFromCacheToMem++;
					printf("writeCntFromCacheToMem: %d\n", writeCntFromCacheToMem);
					if (writeCntFromCacheToMem == 8) {
						writeCntFromCacheToMem = -1;
						op_sendBrespFromMemToCache();
						if (test_case_type == 0) 
							state = 2;
						else if (test_case_type == 1)
							state = 8;
					}
				}
			}

			else {
				//printInfo("");
			}
				
		}

		top->eval();            // Evaluate model
		main_time++;            // Time passes...
		if (main_time > TEST_END) {
			printInfo("");
			printf("simulator: Test end.\n");
			break;
		}
	}
	top->final();               // Done simulating
	delete top;
}
