#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "stack_lib.h"
#include "commands_cpu.h"
#define N 5000

class CPU
{
public:

    CPU();
    ~CPU();

    void Launch();

private:

    void Push();
    void Pop();
    void Add();
    void Sub();
    void Mul();
    void Div();
    void Mod();
    void Out();
    void In();
    void Ja();
    void Jae();
    void Jb();
    void Jbe();
    void Je();
    void Jre();
    void Jmp();
    void Call();
    void Ret();
    void Dup();
    void Push_();
    void Pop_();
    void Read_file();
    void Shama();
    void Copy_file_to_RAM(FILE * input);
    void Dump_cpu();
    void Dump_ram();

private:

    int register_cpu[4];
    int ram[N];
    int ip;
    Stack main_stack;
    Stack secondary_stack;
    size_t ram_size;
};

int main()
{
    CPU intel;
    intel.Launch();
    return 0;
}

CPU::CPU():
    ram_size(0),
    ip(0)
    {
    }

CPU::~CPU()
{
    ip = 0;
}

void CPU::Dump_ram()
{
    printf("\nDUMP_RAM_________________\n\n");
    if(ram_size == 0)
        printf("RAM is empty\n");
    else
    {
        printf("ram_size : %d\n", ram_size);
        for(int i = 0; i < ram_size; i++)
        {
            printf("ip:%d     val:%d\n", i, ram[i]);
        }
    }
    printf("_________________________\n\n");
}

void CPU::Dump_cpu()
{
    printf("MAIN");
    main_stack.Dump();
    printf("SECONDARY");
    secondary_stack.Dump();
    printf("\nDUMP_CPU_________________\n\n");
    printf("Size of RAM = %d\n", ram_size);
    printf("IP %d\n", ip);
    printf("Register ax  =  %d\n", register_cpu[0]);
    printf("Register bx  =  %d\n", register_cpu[1]);
    printf("Register cx  =  %d\n", register_cpu[2]);
    printf("Register dx  =  %d\n", register_cpu[3]);
    printf("_________________________\n\n");
}

void CPU::Copy_file_to_RAM(FILE * input)
{
    int current = 0, i = 0, k = 0;
    char num[10] = "";
    while((current = fgetc(input)) != EOF)
    {
        if(current != ' ')
        {
            num[k] = current;
            k++;
        }
        else
        {
            ram[i] = atoi(num);
            for(int l = 0; l < k; l++)
            {
                num[l] = 0;
            }
            i++;
            k = 0;
            ram_size++;
        }
    }
    ram[i] = atoi(num);
    ram_size++;
}

void CPU::Read_file()
{
    FILE * input = fopen("C:\\Users\\User\\Desktop\\Codes\\ilab\\CPU\\comands.txt", "r");
    assert(input != NULL && "INPUT FILE DOES NOT EXIST");
    Copy_file_to_RAM(input);
    fclose(input);
}

void CPU::Out()
{
    int num = 0;
    num = main_stack.Pop();
    printf("Top element of the stack: %d\n", num);
}

void CPU::In()
{
    int num = 0;
    printf("Type the number from the keyboard: ");
    scanf("%d", &num);
    printf("\n");
    main_stack.Push(num);
}

void CPU::Pop()
{
    main_stack.Pop();
}

void CPU::Add()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    main_stack.Push(num2 + num1);
}

void CPU::Sub()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    main_stack.Push(num2 - num1);
}

void CPU::Mul()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    printf("%d %d ==\n", num1, num2);
    main_stack.Push(num2 * num1);
}

void CPU::Div()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    assert(num1 != 0 && "!!!DIVISION BY ZERO IS NOT ALLOWED!!!");
    main_stack.Push(num2 / num1);
}

void CPU::Mod()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    assert(num1 != 0 && "!!!DIVISION BY ZERO IS NOT ALLOWED!!!");
    main_stack.Push(num2 % num1);
}

void CPU::Ja()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    if(num1 > num2)
    {
        ip = ram[++ip] - 1;
        assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
    }
    else
    {
        ip++;
    }
}

void CPU::Jae()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    if(num1 >= num2)
    {
        ip = ram[++ip] - 1;
        assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
    }
    else
    {
        ip++;
    }
}

void CPU::Jmp()
{
    ip = ram[++ip] - 1;
    assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
}
void CPU::Jb()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    if(num1 < num2)
    {
        ip = ram[++ip] - 1;
        assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
    }
    else
    {
        ip ++;
    }
}

void CPU::Jbe()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();

    if(num2 <= num1)
    {
        ip = ram[++ip] - 1;
        assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
    }
    else
    {
        ip++;
    }
}

void CPU::Je()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    if(num1 == num2)
    {
        ip = ram[++ip] - 1;
        assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
    }
    else
    {

        ip++;
    }
}

void CPU::Jre()
{
    int num1 = main_stack.Pop();
    int num2 = main_stack.Pop();
    if(num1 != num2)
    {
        ip = ram[++ip] - 1;
        assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
    }
    else
    {
        ip++;
    }
}

void CPU::Call()
{
    secondary_stack.Push(ip);
    ip = ram[++ip] - 1;
    assert(ip <= ram_size && "THE JUMP WENT BEYOND THE LIMITS OF RAM");
}

void CPU::Ret()
{
    ip = secondary_stack.Pop() + 1;
}

void CPU::Dup()
{
    int num = main_stack.Pop();
    main_stack.Push(num);
    main_stack.Push(num);
}

void CPU::Push()
{
    main_stack.Push(ram[++ip]);
}

void CPU::Push_()
{
     int val =  register_cpu[ram[++ip]];
     main_stack.Push(val);
}

void CPU::Pop_()
{
    int val = main_stack.Pop();
    register_cpu[ram[++ip]] = val;
}

void CPU::Shama()
{
    for(int i = 0; i < 25; i++)
    {
        printf("SHAMIL PETUH  .!.  SHAMIL PETUH  .!.  SHAMIL PETUH  .!.  SHAMIL PETUH  .!.  SHAMIL PETUH  .!.  SHAMIL PETUH\n");
    }
    printf("!!!HAHAHAHAH ZATROLIL LALKU!!!\n\n");
    printf(";)\n\n");
}

void CPU::Launch()
{
    Read_file();
    while(ram[ip] != 0)
    {
        switch(ram[ip])
        {
        case CMD_PUSH:
            Push();
            break;
        case CMD_POP:
            Pop();
            break;
        case CMD_ADD:
            Add();
            break;
        case CMD_PUSH_:
            Push_();
            break;
        case CMD_POP_:
            Pop_();
            break;
        case CMD_SUB:
            Sub();
            break;
        case CMD_MUL:
            Mul();
            break;
        case CMD_DIV:
            Div();
            break;
        case CMD_MOD:
            Mod();
            break;
        case CMD_OUT:
            Out();
            break;
        case CMD_IN:
            In();
            break;
        case CMD_JA:
            Ja();
            break;
        case CMD_JAE:
            Jae();
            break;
        case CMD_JB:
            Jb();
            break;
        case CMD_JBE:
            Jbe();
            break;
        case CMD_JE:
            Je();
            break;
        case CMD_JRE:
            Jre();
            break;
        case CMD_JMP:
            Jmp();
            break;
        case CMD_CALL:
            Call();
            break;
        case CMD_RET:
            Ret();
            break;
        case CMD_DUP:
            Dup();
            break;
        case CMD_SHAMILV05:
            Shama();
            break;
        default:
            assert(0 && "!!!INVALID COMMAND!!!");
        }
    ip++;
    }
    Dump_cpu();
    printf("End of working");
}
