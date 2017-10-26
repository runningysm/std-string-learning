#include <command_parser.h>
#include <stdio.h>
#include <string.h>
#include <utility.h>

void hello(char *param)
{
    char str[COMMAND_BUF_LENGTH]="hello";
    char param_1[COMMAND_BUF_LENGTH]="";
    const char *ptr = strbreak(param, param_1);

    strcat(str, (const char *)param_1);
    puts(str);
}

void goodbye(char *param)
{
    puts("goodbye world");
}

void getCommand(char *command)
{
    
}
int main()
{
    CommandParser command_parser;

    command_parser.addCommand("hello", hello);
    command_parser.addCommand("goodbye", goodbye);

    command_parser.parse("   \thello -p");
    command_parser.parse("goodbye oot");

    return 0;
}
