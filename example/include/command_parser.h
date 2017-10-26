#ifndef _COMMAND_PARSE_H_
#define _COMMAND_PARSE_H_

#define COMMAND_LENGTH_MAX (20)
#define COMMAND_BUF_LENGTH (COMMAND_LENGTH_MAX + 1)

class CommandParser
{
    public:
        CommandParser();
        ~CommandParser();
        //将新的命令加到解析器中
        void addCommand(const char *command, void (*func)(char *));
        //设置当没有找到输入的命令时的默认执行函数
        void setDefaultHandle(void (*func)());
        //对象数据入口，接收要解析的命令字符串
        void parse(const char *command_line);

    private:
        //将命令拆分成命令字和参数
        void commandBreak(char *buf, char *command, char *param);
    private:
        struct Command
        {
            char command[COMMAND_BUF_LENGTH];
            void (*func)(char *);
        };

        Command *command_list_; //command table pointor
        unsigned int command_count_; //number of command

        void (*defaultHandle_)(); 

};

#endif
