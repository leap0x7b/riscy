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

#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RISCY_IMPLEMENTATION

typedef struct riscv {
    uint32_t *regs;
    uint64_t pc;
} riscv_t;

void rv_cpu_reset(riscv_t *cpu, int ram_size);
uint32_t rv_fetch(riscv_t *cpu);
void rv_execute(riscv_t *cpu, uint32_t inst);
#ifdef RISCY_DEBUG
void rv_dump(riscv_t *cpu);
#endif

// You need define these yourself.
uint8_t rv_read_mem(uint64_t address);
void rv_write_mem(uint64_t address, uint8_t value);

#endif // #ifdef RISCY_IMPLEMENTATION

#ifdef __cplusplus
} // extern "C"
#endif
