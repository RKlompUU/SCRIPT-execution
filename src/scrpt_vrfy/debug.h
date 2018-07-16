#ifndef DEBUG_H
#define DEBUG_H

#include <vector>
#include <string>
#include <script/script.h>

void dump_stack(std::vector<std::vector<unsigned char>> &stack);
std::string op2str(opcodetype opcode);

#endif
