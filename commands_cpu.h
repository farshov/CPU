#ifndef COMMANDS_CPU_H
#define COMMANDS_CPU_H

enum Comands_cpu{
    CMD_HLT = 0,
    CMD_PUSH = 1,
    CMD_POP = 2,
    CMD_ADD = 3,
    CMD_SUB = 4,
    CMD_MUL = 5,
    CMD_DIV = 6,
    CMD_OUT = 7,
    CMD_IN = 8,
    CMD_MOD = 9,
    CMD_PUSH_ = 10,
    CMD_POP_ = 21
};

enum Jumps_cpu{
    CMD_JA = 11,
    CMD_JAE = 12,
    CMD_JB = 13,
    CMD_JBE = 14,
    CMD_JE = 15,
    CMD_JRE = 16,
    CMD_JMP = 17,
    CMD_CALL = 18,
    CMD_RET = 19,
    CMD_DUP = 20
};

enum Registers_cpu{
    CMD_ax = 0,
    CMD_bx = 1,
    CMD_cx = 2,
    CMD_dx = 3
};

enum Secrets_cpu{
    CMD_SHAMILV05 = 228
};
#endif
