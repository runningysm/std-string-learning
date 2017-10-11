#include<cstdio>

int main()
{
    printf("int :%ld\n", sizeof(int));
    struct temp0
    {
        int t0;
        char t1;
        short t2;
    };

    printf("temp:%ld\n", sizeof(temp0));
    struct temp1
    {
        int t0;
        char t1;
        short t2;
    }__attribute__((packed));
    printf("temp1:%ld\n", sizeof(temp1));
    return 0;
}
