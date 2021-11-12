/*
 * Riscy 0.0.1
 * Copyright 2021 Leap of Azzam.
 *
 * To set up Riscy in your project, define RISCY_IMPLEMENTATION macro:
 *
 *     ...
 *     #define RISCY_IMPLEMENTATION
 *     #include "riscy.h"
 *     ...
 *
 * and then add these functions in your code:
 *
 *     uint8_t rv_read_mem(uint64_t mem);
 *     void rv_write_mem(uint64_t mem);
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#define RISCY_IMPLEMENTATION
#include "riscy.h"

#ifdef __cplusplus
extern "C" {
#endif

void rv_cpu_reset(riscv_t *cpu, int ram_size) {
    cpu->pc = 0;
    cpu->regs = malloc(sizeof(uint32_t));
    cpu->regs[0] = 0;
    cpu->regs[1] = 32;
    cpu->regs[2] = ram_size;
} // rv_cpu_reset

uint32_t rv_fetch(riscv_t *cpu) {
    uint64_t index = cpu->pc;
    return rv_read_mem(index) |
           rv_read_mem(index + 1) << 8 |
           rv_read_mem(index + 2) << 16 |
           rv_read_mem(index + 3) << 24;
} // rv_fetch

void rv_execute(riscv_t *cpu, uint32_t inst) {
    uint32_t opcode = inst & 0x7f;
    size_t rd = ((inst >> 7) & 0x1f);
    size_t rs1 = ((inst >> 15) & 0x1f);
    size_t rs2 = ((inst >> 20) & 0x1f);
    printf("%x %x\n", inst, opcode);

    switch (opcode) {
        case 0x13: { // addi
            uint64_t imm = ((int64_t)(int32_t)(inst & 0xfff00000) >> 20);
            cpu->regs[rd] = cpu->regs[rs1] + imm;
            return;
        }
        case 0x33: { // add
            cpu->regs[rd] = cpu->regs[rs1] + cpu->regs[rs2];
            return;
        }
        default: printf("warning: instruction not implemented: 0x%02x\n", opcode);
    }
} // rv_execute

void rv_dump(riscv_t *cpu) {
    for (int i = 0; i < cpu->pc; i += 4) {
        printf(
            "x%02d=0x%01x x%02d=0x%01x x%02d=0x%01x x%02d=0x%01x\n",
            i,
            cpu->regs[i],
            i + 1,
            cpu->regs[i + 1],
            i + 2,
            cpu->regs[i + 2],
            i + 3,
            cpu->regs[i + 3]
        );
    }
} // rv_dump

#ifdef __cplusplus
} // extern "C"
#endif
