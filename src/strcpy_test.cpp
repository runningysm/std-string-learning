#include<cstring>
#include<assert.h>
#include<cstdio>

char *strcpy_test(char *dest, const char *src)
{
    char *d = dest;

    assert((dest != NULL) && (src != NULL));

    while((*d++ = *src++) != '\0');

    return dest;
}

int main()
{
    char dest[20] = {0};
    const char *src0 = "0123456789";
    const char *src1 = "abcdefghij";
    const char *p = NULL;

    strcpy_test((char *)dest, src0);
    printf("strcpy_test:%s\n", dest);
    strcpy((char *)dest, src1);
    printf("strcpy:%s\n", dest);
    //strcpy(dest, p);
    return 0;
}

