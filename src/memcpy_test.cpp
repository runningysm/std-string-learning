#include<cstring>
#include <cstdio>


int main()
{
    const char *src = "0123456789";
    char dest[20]={0};
    int num = 1234567890;
    int num_temp;

    memcpy(dest, src, strlen(src)+1);
    puts(dest);

    memcpy((void *)&num_temp, (const void *)&num, sizeof(int));
    printf("num:%d\n", num_temp);
    return 0;
}
