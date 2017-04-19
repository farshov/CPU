#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "commands_cpu.h"
#define N 5000
#define MAX_SIZE 5000

class Asm
{
public:
    Asm();
    ~Asm();
    void Safe_labels();
    void Write_file();
    void Pop_asm();

private:
    size_t labels_[MAX_SIZE];
    bool label_map_[MAX_SIZE];
    char comands_[MAX_SIZE];
    size_t number_of_comand;
    size_t place;
    char buffer[MAX_SIZE];
    FILE * input_;
    FILE * output_;
    inline bool Check_single_command(const char * current, int cmd_code, const char * cmd_word);
    inline void Check_num_register(const char * current);
};

int main()
{
    Asm my_asm;
    my_asm.Safe_labels();
    my_asm.Write_file();
    printf("Successful assembly");
    return 0;
}

Asm::Asm():
    place(0),
    number_of_comand(0)
    {
        for(int i = 0; i < MAX_SIZE; i++)
        {
            label_map_[i] = 0;
        }
    }

Asm::~Asm()
{
    number_of_comand = 0;
    fclose(input_);
    fclose(output_);
}

void Asm::Safe_labels()
{
    input_ = fopen("C:\\Users\\User\\Desktop\\Codes\\ilab\\assembler\\input.txt", "r");
    assert(input_ != NULL && "INPUT FILE DOES NOT EXIST");
    int label, k = 0, length = 0, position = 0;
    char arg[MAX_SIZE] = {};
    while(fscanf(input_, "%s", arg) == 1)
    {
        length = strlen(arg);
        if(!strcmp(arg, "ja") || !strcmp(arg, "jae") || !strcmp(arg, "jb") ||
           !strcmp(arg, "jbe") || !strcmp(arg, "je") || !strcmp(arg, "jre") ||
           !strcmp(arg, "jmp") || !strcmp(arg, "call"))
        {
            position ++;
            for(k = 0; k < length + 2; k++)
            {
                arg[k] = 0;
            }
            fscanf(input_, "%s", arg);

            length = strlen(arg);
            for(k = 0; k < length + 2; k++)
            {
                arg[k] = 0;
            }
            position ++;
        }
        else if(arg[length - 1] == ':')
        {
            label = atoi(arg);
            labels_[label] = position;
            label_map_[label] = 1;

            for(k = 0; k < length + 2; k++)
            {
                arg[k] = 0;
            }
        }
        else
        {
            position ++;
        }
    }
    fclose(input_);
}

inline void Asm::Check_num_register(const char * current)
{
    size_t spaces = 0;
    if(!strcmp(current, "ax"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_ax);
        }
    else if(!strcmp(current, "bx"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_bx);
        }
    else if(!strcmp(current, "cx"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_cx);
        }
    else if(!strcmp(current, "dx"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_dx);
        }
    else
    {
        assert(0 && "INVALID REGISTER");
    }
    place += spaces;
}

inline bool Asm::Check_single_command(const char * current, int cmd_code, const char * cmd_word)
    {
        size_t spaces = 0;
        if(!strcmp(current, cmd_word))
        {
            spaces = sprintf(buffer + place, "%d ", cmd_code);
            place += spaces;
            return true;
        }
        else
        {
            return false;
        }
}

void Asm::Write_file()
{
    bool hlt_control = 0;
    input_ = fopen("C:\\Users\\User\\Desktop\\Codes\\ilab\\assembler\\input.txt", "r");
    assert(input_ != NULL && "INPUT FILE DOES NOT EXIST");
    output_ = fopen("C:\\Users\\User\\Desktop\\Codes\\ilab\\CPU\\comands.txt", "w");
    assert(output_ != NULL && "OUTPUT FILE DOES NOT EXIST");
    int arg = 0;
    char current[N] = {};
    size_t spaces = 0;
    while(fscanf(input_, "%s", current) == 1)
    {
        if(strchr(current, ':') != NULL)
        {
            spaces = 0;
        }
        else if(!strcmp(current, "push"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_PUSH);
            place += spaces;

            spaces = fscanf(input_, "%d", &arg);
            assert(spaces != 0 && "MISSING OR INCORRECT ARGUMENT OF PUSH");
            spaces = sprintf(buffer + place, "%d ", arg);
            place += spaces;
        }
        else if(!strcmp(current, "push_"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_PUSH_);
            place += spaces;
            spaces = fscanf(input_, "%s", current);
            Check_num_register(current);
        }
        else if(!strcmp(current, "pop_"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_POP_);
            place += spaces;
            spaces = fscanf(input_, "%s", current);
            Check_num_register(current);
        }

        else if(Check_single_command(current, CMD_SHAMILV05, "secret"));
        else if (Check_single_command(current, CMD_POP, "pop"));
        else if (Check_single_command(current, CMD_ADD, "add"));
        else if (Check_single_command(current, CMD_SUB, "sub"));
        else if (Check_single_command(current, CMD_MUL, "mul"));
        else if (Check_single_command(current, CMD_DIV, "div"));
        else if (Check_single_command(current, CMD_OUT, "out"));
        else if (Check_single_command(current, CMD_IN, "in"));
        else if (Check_single_command(current, CMD_MOD, "mod"));
        else if (Check_single_command(current, CMD_DUP, "dup"));
        else if (Check_single_command(current, CMD_RET, "ret"));

        else if(!strcmp(current, "ja") || !strcmp(current, "jae") || !strcmp(current, "jb") || !strcmp(current, "jbe") || !strcmp(current, "je") || !strcmp(current, "jre") || !strcmp(current, "jmp") || !strcmp(current, "call"))
        {
            if (Check_single_command(current, CMD_JA, "ja"));
            else if (Check_single_command(current, CMD_JAE, "jae"));
            else if (Check_single_command(current, CMD_JMP, "jmp"));
            else if (Check_single_command(current, CMD_JB, "jb"));
            else if (Check_single_command(current, CMD_JBE, "jbe"));
            else if (Check_single_command(current, CMD_JE, "je"));
            else if (Check_single_command(current, CMD_JRE, "jre"));
            else if (Check_single_command(current, CMD_CALL, "call"));

            spaces = fscanf(input_, "%d:", &arg);
            assert(label_map_[arg] == 1 && "!!!THERE IS NO SUCH LABEL IN FILE!!!");
            arg = labels_[arg];
            spaces = sprintf(buffer + place, "%d ", arg);
            place += spaces;
        }
        else if(!strcmp(current, "hlt"))
        {
            spaces = sprintf(buffer + place, "%d ", CMD_HLT);
            place += spaces;
            hlt_control = 1;
        }
        else
        {
            assert(0 && "!!!INVALID COMMAND!!!");
        }
    }
    if(buffer[place - spaces] != '0')
    {
        assert(hlt_control && "!!!MISSING HLT!!!");
    }
    fprintf(output_, "%s", buffer);
}
