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
 *     uint8_t rv_read_mem(uint64_t address);
 *     void rv_write_mem(uint64_t address, uint8_t value);
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
#include <errno.h>
#define RISCY_IMPLEMENTATION
#define RISCY_DEBUG
#include "riscy.h"

// Set the RAM size to 128M
#define RAM_SIZE (1024 * 1024 * 128)
uint64_t ram[RAM_SIZE];

uint8_t rv_read_mem(uint64_t address) {
    return ram[address];
}

void rv_write_mem(uint64_t address, uint8_t value) {
    ram[address] = value;
}

int main(int argc, char **argv) {
    printf("%d\n", argc);
    for (int i = 0; i < argc; i++)
        printf("%d %s\n", i, argv[i]);

    if (argc < 2) {
        printf("usage: emu <filename>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        fprintf(stderr, "Couldn't open %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

    riscv_t cpu;

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);
    rv_cpu_reset(&cpu, RAM_SIZE);
    fread(ram, sizeof(uint8_t), fsize, f);
    fclose(f);

    while (cpu.pc < fsize) {
        uint32_t inst = rv_fetch(&cpu);
        cpu.pc += 4;
        rv_execute(&cpu, inst);
    }
    rv_dump(&cpu);

    return 0;
}
