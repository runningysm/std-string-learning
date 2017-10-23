#include <cstdio>
#include <cstring>

int main()
{
    char str[20]={"abcdefg" "01234"};
    char *p = str;
    putchar(*p++);    //a
    putchar(*(p++));  //b
    putchar(++*p);    //d
    putchar(*++p);    //d
    putchar(*p++);    //d
    putchar(*p);      //e
    putchar('\n');
    return 0;
}
