#include "../include/command_parse.h"
#include <cstdlib>
#include <cstring>
#include <cctype>

CommandParse::CommandParse(): command_list_(NULL), defaultHandle_(NULL), command_count_(0)
{
    memset((void *)command_buff_, '\0', sizeof(command_buff_));
}

//1>判断参数是否合法，
//2>重新申请空间并将命令字和执行函数填充到命令列表的末尾
//3>将命令计数器+1
void CommandParse::addCommand(const char *command, void (*func)())
{
    if(command == NULL || strlen(command) == 0 || func == NULL)
        return;

    command_list_ = (Command *)realloc(command_list_, (command_count_ + 1) * sizeof(Command));
    strncpy(command_list_[command_count_].command, command, COMMAND_LENGTH_MAX);
    command_list_[command_count_].command[COMMAND_LENGTH_MAX] = '\0';
    command_list_[command_count_].func = func;

    command_count_++;
}

//1>判断参数是否合法
//2>将参数赋值给类成员
void CommandParse::setDefaultHandle(void (*func)())
{
    if(func == NULL)
        return;

    defaultHandle_ = func;
}

//1>判断参数是否合法
//2>解析字符串，提取出命令字
//3>根据命令字查找命令列表，找到对应的执行函数并执行
void CommandParse::parse(const char *command_line)
{
    if(command_line == NULL)
        return;

    //解析字符串
    
    strncpy(command_buff_, command_line, sizeof(command_buff_) -1);
    
    char *p = command_buff_;

    //去除字符串前面的空白，最后一个字符为'\0'保证不会越界
    while(isblank(*p))
    {
        p++;
    }
    
    char command_temp[COMMAND_LENGTH_MAX] = {0};
    //TODO:get command
    char *command_p = strtok_r(p, " ", last);

    int i = 0;
    for(; i<command_count_; i++)
    {
        if(strncmp((const char *)command_p, (const char *)command_list_[i].command, COMMAND_LENGTH_MAX) == 0)
        {
            (*command_list_[i].func)();
        }
    }

    if(i >= command_count_)
    {
        if(defaultHandle_ != NULL)
        {
            (*defaultHandle_)();
        }
    }
}


int main()
{
    CommandParse command_parse;
    command_parse.parse("hello");

    return 0;
}




























