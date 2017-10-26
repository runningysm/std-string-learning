#include <utility.h>
#include <string.h>

const char *strbreak(const char *str, char *key)
{
    if(str == NULL)
    {
        *key = '\0';
        return str;
    }
    
    //得到前导空白的个数
    size_t num = strspn(str, " \t");

    str += num;
    
    //得到当前位置开始，不是空白和null的字符个数
    num = strcspn(str, " \t");

    strncpy(key, str, num);

    return (str + num);
}


