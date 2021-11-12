# Riscy
An embeddable RISC-V emulator, written in C.

Riscy is heavily inspired by [libriscv](https://github.com/fwsGonzo/libriscv), it's doing the same as libriscv, but in C instead of C++, and in a single C file (if you don't count the header file).

As of now, Riscy isn't a very complete RISC-V emulator. It is not recommended to use this in your project.

## Progress
- [X] Write a very basic RISC-V emulator
- [ ] Add most of the RV32IMA and RV64IMA instruction sets.
- [ ] Try to run Xv6 and Linux on it

## Acknowledgement
Some of the code are taken from the [rvemu book](https://book.rvemu.app), adjusted for C instead of Rust.

## License
Licensed under the [Apache license version 2.0](http://www.apache.org/licenses/LICENSE-2.0). You may need to include the license if you used this in your project.
