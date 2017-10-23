#ifndef _COMMAND_PARSE_H_
#define _COMMAND_PARSE_H_

#define COMMAND_LENGTH_MAX (20)
#define COMMAND_BUFF_LENGTH (50)

class CommandParse
{
    public:
        CommandParse();
        //将新的命令加到解析器中
        void addCommand(const char *command, void (*func)());
        //设置当没有找到输入的命令时的默认执行函数
        void setDefaultHandle(void (*func)());
        //对象数据入口，接收要解析的命令字符串
        void parse(const char *command_line);

    private:
        struct Command
        {
            char command[COMMAND_LENGTH_MAX + 1];
            void (*func)();
        };

        Command *command_list_; //command table pointor
        unsigned int command_count_; //number of command

        void (*defaultHandle_)(); 
        char command_buff_[COMMAND_BUFF_LENGTH];
        char **last;

};

#endif
