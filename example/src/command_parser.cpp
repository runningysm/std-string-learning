#include "command_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <utility.h>

CommandParser::CommandParser(): command_list_(NULL), defaultHandle_(NULL), command_count_(0)
{
}

CommandParser::~CommandParser()
{
    //释放申请的空间
    if(command_list_ != NULL)
    {
        free(command_list_);
        command_list_ = NULL;
    }
}

//1>判断参数是否合法，
//2>重新申请空间并将命令字和执行函数填充到命令列表的末尾
//3>将命令计数器+1
void CommandParser::addCommand(const char *command, void (*func)(char *))
{
    if(command == NULL || strlen(command) == 0 || func == NULL)
        return;

    command_list_ = (Command *)realloc(command_list_, (command_count_ + 1) * sizeof(Command));
    strncpy(command_list_[command_count_].command, command, COMMAND_LENGTH_MAX);
    command_list_[command_count_].command[COMMAND_BUF_LENGTH] = '\0';
    command_list_[command_count_].func = func;

    command_count_++;
}

//1>判断参数是否合法
//2>将参数赋值给类成员
void CommandParser::setDefaultHandle(void (*func)())
{
    if(func == NULL)
    {
        printf("Set default handle failed, function is empty.\n");
        return;
    }

    defaultHandle_ = func;
}

//1>判断参数是否合法
//2>解析字符串，提取出命令字
//3>根据命令字查找命令列表，找到对应的执行函数并执行
void CommandParser::parse(const char *command_line)
{
    if(command_line == NULL)
    {
        printf("Parse command line failed, command line is empty.\n");
        return;
    }
    //解析字符串
    //判断参数长度是否超出最大受理字符个数
    if(strlen(command_line) > COMMAND_LENGTH_MAX)
    {
        printf("The command length is too long. Max length is %d\n", COMMAND_LENGTH_MAX);
        return;
    }

    //声明缓存，并初始化为0
    char buf[COMMAND_BUF_LENGTH];
    char command[COMMAND_BUF_LENGTH] = {'\0'};
    char param[COMMAND_BUF_LENGTH] = {'\0'};

    //将参数复制到缓存
    strncpy(buf, command_line, COMMAND_LENGTH_MAX);
   
    ///2
    const char *ptr = (const char *)buf;
    
    ptr = strbreak(ptr, command);

    strncpy(param, ptr, COMMAND_LENGTH_MAX);


    /*
    ///1
    //拆分命令字和参数
    commandBreak(buf, command, param);
    */

    /*
    /////2
    char *buf_p = buf;

    //去除字符串前面的空白，最后一个字符为'\0'保证不会越界
    while(isblank(*buf_p))
    {
        buf_p++;
    }
    
    if(buf_p != buf)
    {
        memmove((void *)buf, (const void *)buf_p, sizeof(buf));
        buf_p = buf;
    }
    
    //检测命令是长指令还是短指令
    char *space_p = strchr(buf_p, ' ');

    //短指令
    if(space_p == NULL)
    {
        strncpy(command, (const char *)buf_p, sizeof(command));    
    }
    else//长指令，带参数
    {
        strncpy(command, (const char *)buf_p, space_p - buf_p);
        buf_p = space_p;
        while(*buf_p == ' ')
        {
            buf_p++;
        }
        strncpy(param, (const char *)buf_p, sizeof(param));
    }
    */


    //从table中找到对应的命令并执行
    bool matched = false;
    for(int i=0; i<command_count_; i++)
    {
        if(strncmp((const char *)command, (const char *)command_list_[i].command, COMMAND_LENGTH_MAX) == 0)
        {
            (*command_list_[i].func)(param);
            matched = true;
            break;
        }
    }

    if(!matched && (defaultHandle_ != NULL))
    {
        (*defaultHandle_)();
    }
}

//将字符串拆分成命令字和参数的形式
//去除前导空格.命令字的结尾，可能是space, table \0
//前提条件：有内容的字符串，，有开头有结尾，长度不得超过最长字符串长度
void CommandParser::commandBreak(char *buf, char *command, char *param)
{
    //如果字符长度为0
    if(strlen(buf) == 0)
    {
        *command = '\0';
        *param   = '\0';
    }
    else
    {

        char buf_tmp[COMMAND_BUF_LENGTH];//存储传入的待分析的字符串
        strncpy(buf_tmp, buf, sizeof(buf_tmp));

        char *ptr = buf_tmp;//作为缓存的操作指针

        //去除字符串前面的空白,去除空白之后结果一种是正规字符串，一种是空字符串
        while(*ptr != '\0')
        {
            if(!isblank(*ptr))
                break;
            else
                ptr++;
        }
        
        //字符长度为0
        if(strlen(ptr) == 0)
        {
            *command = '\0';
            *param   = '\0';
        }
        else//前导不为0的正规字符串
        {
            ///4//没有去除后面的blank
            size_t num = strcspn((const char *)ptr, " \t");

            strncpy(command, (const char *)ptr, num);
            strncpy(param, (const char *)(ptr + num), COMMAND_LENGTH_MAX);


        /*
            ///3
            bool matched = false;
            while(*ptr != '\0')
            {
                if(isblank(*ptr))
                {
                    matched = true;
                    break;
                }
                else
                {
                    *command++ = *ptr++;
                }
            }

            *command = '\0';

            if(matched)
            {
                strncpy(param, (const char *)(ptr + 1), COMMAND_LENGTH_MAX);
            }
            else
            {
                *param = '\0';
            }
        */

        /*
            /////2
            char * ptr_end = ptr;
            bool matched = false;

        
            //找到命令字结束的位置
            while(*ptr_end != '\0')
            {
                if(isblank(*ptr_end))
                {
                    matched = true;
                    break;
                }
                else
                {
                    ptr_end++;
                }
            }

            if(matched)
            {
                strncpy(command, (const char *)ptr, ptr_end - ptr);
                command[ptr_end - ptr] = '\0';

                ptr = ptr_end + 1;
                strncpy(param, (const char *)ptr, COMMAND_LENGTH_MAX);
            }
            else
            {
                strncpy(command, (const char *)ptr, ptr_end - ptr);
                command[ptr_end - ptr] = '\0';

                *param = '\0';
            }
        
        */

        /*
            /////1
            //查找命令字的结束位置
            char *ptr_s = strchr(ptr, ' ');
            char *ptr_t = strchr(ptr, '\t');

            //属于短指令
            if(ptr_s == NULL && ptr_t == NULL)
            {
                strncpy(command, (const char *)ptr, COMMAND_LENGTH_MAX);
                *param = '\0';
            }

            //存在space但是不存在table
            if(ptr_s != NULL && ptr_t == NULL)
            {
                strncpy(command, (const char *)ptr, ptr_s - ptr);
                command[ptr_s - ptr] = '\0';

                ptr = ptr_s + 1;
                strncpy(param, (const char *)ptr, COMMAND_LENGTH_MAX);
            }
            //不存在space但是存在table
            if(ptr_s == NULL && ptr_t != NULL)
            {
                strncpy(command, (const char *)ptr, ptr_t - ptr);
                command[ptr_t - ptr] = '\0';

                ptr = ptr_t + 1;
                strncpy(param, (const char *)ptr, COMMAND_LENGTH_MAX);
            }
            //存在space并且存在table
            if(ptr_s != NULL && ptr_t != NULL)
            {
                char *p = ptr_s < ptr_t ? ptr_s : ptr_t;
                strncpy(command, (const char *)p, p - ptr);
                command[p - ptr] = '\0';

                ptr = p + 1;
                strncpy(param, (const char *)ptr, COMMAND_LENGTH_MAX);
            }
        */


        }//end else of strlen(ptr) == 0 
    }//end else of strlen(buf) == 0
}

/*
int main()
{
    CommandParser command_parse;

    command_parse.parse("hello");

    return 0;
}

*/

























