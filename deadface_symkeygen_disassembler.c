#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

char stack[36] = "";
int prog[] = { 0x91000, 0x92000, 0x93000, 0x91000, 0x92000, 0x50204, 0x0A0000, 0x32305, 0x0A1000, 0x6100F, 0x6300D, 0x0A2000, 0x22103, 0x91000, 0x23102, 0x0A3000, 0x92000, 0x0A2000, 0x91000, 0x91000, 0x63005, 0x22103, 0x0A2000, 0x0A1000, 0x93000, 0x61005, 0x42103, 0x53200, 0x0A3000, 0x91000, 0x92000, 0x93000, 0x91000, 0x92000, 0x50204, 0x0A0000, 0x32305, 0x0A1000, 0x6100F, 0x6300D, 0x0A2000, 0x22103, 0x91000, 0x23102, 0x0A3000, 0x92000, 0x0A2000, 0x91000, 0x91000, 0x63005, 0x22103, 0x0A2000, 0x0A1000, 0x93000, 0x61005, 0x42103, 0x53200, 0x0A3000 };

int regs[15];
int pc = 0, ins = 0, reg1 = 0, reg2 = 0, reg3 = 0, imm = 0, fl = 0, sp = 0;
int running = 1;

int fetch();
void run();
void decode(int opcode);
void eval();

int main() {
    unsigned int v3;
    time_t v4;
    time_t timer;

    v3 = time(&timer);
    srand(v3);
    v4 = timer;
    printf("Beginning key generation at %lu\n", timer);
    run();
    printf("Key: %s\n", stack);
}

void eval() {
    switch (ins) {
        case 0: {
            running = 0;
            break;
        }
        case 2: {
            regs[reg1] = regs[reg2] - regs[reg3];
            printf("SUB R%d, R%d\n", reg1, regs[reg1]);
            fl = regs[reg1];
            printf("SET FLAG TO R%d VALUE 0x%x\n\n",  reg1, regs[reg1]);
            break;
        }
        case 3: {
            regs[reg1] = regs[reg2] - imm;
            printf("\nSUBI R%d, 0x%x\n", reg1, regs[reg1]);
            fl = regs[reg1];
            printf("SET FLAG VALUE TO R%d\n\n", reg1);
            break;
        }
        case 4: {
            regs[reg1] = regs[reg2] + regs[reg3];
            printf("ADD R%d, 0x%x\n", reg2, regs[reg2]);
            fl = 0;
            printf("SET FLAG ZERO\n\n");
            break;
        }
        case 5: {
            regs[reg1] = regs[reg2] + imm;
            printf("\nADD R%d, 0x%x\n", reg1, regs[reg1]);
            fl = 0;
            printf("SET FLAG ZERO\n\n");
            break;
        }
        case 6: {
            regs[reg1] = imm;
            printf("MOVI R%d, %x\n", reg1, imm);
            fl = 0;
            printf("SET FLAG TO ZERO\n\n");
            break;
        }
        case 9: {
            printf("PUSH R%d\n", reg1);
            u_int32_t eax = rand();
            u_int32_t edx = (eax > 0) - (eax < 0);
            regs[reg1] = ((eax + (edx >> 0x1C)) & 0xF) + 0x46;
            printf("MOVI R%d, 0x%x\n\n", reg1, regs[reg1]);
            break;
        }
        case 0x0A: {
            stack[sp++] = (char)regs[reg1];
            printf("MOV stack[%d], R%d \n", sp, reg1);
            fl = 0;
            printf("SET FLAG ZERO\n\n");
            break;
        }
        default:
        break;
    }
}


void decode(int opcode) {
    ins = (opcode >> 16) & 0xF;
    reg1 = (opcode >> 12) & 0xF;
    reg2 = (opcode >> 8) & 0xF;
    reg3 = opcode & 0xF;
    imm = (int)opcode;
}

int fetch() {
    return prog[pc++];
}

void run() {
    while (running) {
        int opcode = fetch();
        decode(opcode);
        eval();
    }
}
