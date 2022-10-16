#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

char stack[36];
u_int32_t prog[58] = { 0x91000, 0x92000, 0x93000, 0x91000, 0x92000, 0x50204, 0x0A0000, 0x32305, 0x0A1000, 0x6100F, 0x6300D, 0x0A2000, 0x22103, 0x91000, 0x23102, 0x0A3000, 0x92000, 0x0A2000, 0x91000, 0x91000, 0x63005, 0x22103, 0x0A2000, 0x0A1000, 0x93000, 0x61005, 0x42103, 0x53200, 0x0A3000, 0x91000, 0x92000, 0x93000, 0x91000, 0x92000, 0x50204, 0x0A0000, 0x32305, 0x0A1000, 0x6100F, 0x6300D, 0x0A2000, 0x22103, 0x91000, 0x23102, 0x0A3000, 0x92000, 0x0A2000, 0x91000, 0x91000, 0x63005, 0x22103, 0x0A2000, 0x0A1000, 0x93000, 0x61005, 0x42103, 0x53200, 0x0A3000 };
u_int32_t regs[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
u_int32_t pc, ins, reg1, reg2, reg3, imm, fl;
u_int32_t sp = 0;
u_int32_t running = 1;

u_int32_t fetch();
u_int64_t run();
u_int64_t decode(u_int32_t opcode);
u_int64_t eval();

int main() {
    unsigned int v3;
    time_t v4;
    time_t timer;

    v3 = time(&timer);
    srand(v3);
    v4 = timer;
    printf("Beginning key generation at %lu\n", timer);
    run();
    for (int i = 0; i < (sizeof(stack) / sizeof(stack[36])); i++) {
        printf("%c", stack[i]);
    }
}

u_int64_t eval() {
    if (ins <= 0x0A) {
        switch (ins) {
            case 0: {
                running = 0;
                break;
            }
            case 9: {
                u_int32_t rand_num = rand();
                u_int32_t rand_num_t = rand_num;
                rand_num_t = rand_num_t >> 0x1C;
                rand_num += rand_num_t;
                rand_num &= 0x0F;
                rand_num -= rand_num_t;
                rand_num_t = (rand_num + 0x46);
                printf("PUSH R%d\n", *(&reg1) * 4);
                regs[*(&reg1) * 4] = rand_num_t;
                printf("MOVI R%d, 0x%x\n\n", *(&reg1) * 4, rand_num_t);
                break;
            }
            case 0x0A: {
                u_int32_t tmp = sp;
                printf("PUSH R%d\n", *(&reg1) * 4);
                printf("PUSH SP\n");
                sp += 1;
                printf("INC SP\n");
                stack[tmp] = regs[*(&reg1) * 4];
                printf("MOV SP[%d], R%d \n", tmp, *(&reg1) * 4);
                fl = 0;
                printf("SET FLAG ZERO\n\n");
                break;
            }
            case 5: {
                u_int32_t idx = *(&reg2) * 4;
                u_int32_t reg_val_2 = regs[*(&reg2) * 4];
                imm += reg_val;
                printf("\nADD R%d, 0x%x\n", idx, imm);
                regs[*(&reg1) * 4] = imm;
                printf("MOV R%d, 0x%x\n", *(&reg1) * 4, imm);
                fl = 0;
                printf("SET FLAG ZERO\n\n");
                break;
            }
            case 3: {
                u_int32_t idx = *(&reg2) * 4;
                u_int32_t reg_val = regs[idx];
                reg_val -= imm;
                printf("\nSUBI R%d, 0x%x\n", idx, imm);
                regs[*(&reg1) * 4] = reg_val;
                printf("MOV R%d, R%d\n", (*(&reg1) * 4), (*(&reg2) * 4));
                fl = regs[*(&reg1) * 4];
                printf("SET FLAG VALUE TO R%d\n\n", *(&reg1) * 4);
                break;
            }
            case 6: {
                regs[*(&reg1) * 4] = imm;
                printf("MOVI R%d, %x\n", *(&reg1) * 4, imm);
                fl = 0;
                printf("SET FLAG TO ZERO\n\n");
                if (fl != 0) {
                    pc = imm;
                    printf("=======================UPDATING PC=======================\n\n\n");
                    fl = 0;
                }
                break;
            }
            case 2: {
                u_int32_t reg_val_1 = regs[*(&reg1) * 4];
                printf("PUSH R%d\n", *(&reg1) * 4);
                u_int32_t reg_val_2 = regs[*(&reg2) * 4];
                printf("PUSH R%d\n", *(&reg2) * 4);
                u_int32_t reg_val_3 = regs[*(&reg3) * 4];
                printf("PUSH R%d\n", *(&reg3) * 4);
                reg_val_2 -= reg_val_3;
                printf("SUB R%d, R%d\n", *(&reg2) * 4, *(&reg3) * 4);
                reg_val_1 = reg_val_2;
                printf("MOV R%d, R%d\n", *(&reg1) * 4, *(&reg2) * 4);
                fl = reg_val_1;
                printf("SET FLAG TO R%d VALUE 0x%x\n\n",  *(&reg1) * 4, reg_val_1);
                break;
            }
            case 4: {
                u_int32_t reg_val_1 = regs[*(&reg1) * 4];
                printf("PUSH R%d\n", *(&reg1) * 4);
                u_int32_t reg_val_2 = regs[*(&reg2) * 4];
                printf("PUSH R%d\n", *(&reg2) * 4);
                u_int32_t reg_val_3 = regs[*(&reg3) * 4];
                printf("PUSH R%d\n", *(&reg3) * 4);
                reg_val_2 += reg_val_3;
                printf("ADD R%d, R%d\n", *(&reg2) * 4, *(&reg3) * 4);
                reg_val_1 = reg_val_2;
                printf("MOV R%d, R%d\n", *(&reg1) * 4, *(&reg2) * 4);
                fl = 0;
                printf("SET FLAG ZERO\n\n");
                break;
            }
            default:
            break;
        }
    }
}


u_int64_t decode(u_int32_t opcode) {
    ins = (opcode >> 16) & 0xF;
    reg1 = (opcode >> 12) & 0xF;
    reg2 = (opcode >> 8) & 0xF;
    reg3 = opcode & 0xF;
    imm = (u_int8_t)opcode;
    return (u_int8_t)opcode;
}

u_int32_t fetch() {
    u_int32_t tmp = pc++;
    return prog[tmp];
}

u_int64_t run() {
    u_int32_t opcode;

    while (running) {
        opcode = fetch();
        decode(opcode);
        eval();
    }

    return imm;
}
