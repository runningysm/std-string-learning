#include<cstring>
#include<cassert>
#include<cstdio>

char *strncpy_test(char *dest, const char *src, size_t n)
{
    assert((dest != NULL) && (src != NULL));

    char *dest_temp = dest;
    int i = 0;

    while(i++<n && (*dest_temp++ = *src++) != '\0');

    while(i++<n)
    {
        *dest_temp++ = '\0';
        puts("#");
    }

    return dest;
}


int main()
{
    const char *src = "0123456789";
    char dest[20] = {0};
    /*
    strncpy_test(dest, src, strlen(src)+1);
    puts((char *)dest);
    strncpy_test(dest, "****", 7);
    puts((char *)dest);
    printf("sizeof(char *src):%ld\n", sizeof(src));
    */
    strncpy(dest, src, strlen(src)+1);
    puts((char *)dest);
    strncpy(dest, "****", 7);
    puts((char *)dest);
    printf("sizeof(char *src):%ld\n", sizeof(src));


    return 0;
}
