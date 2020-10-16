#include "ft_printf.h"

int main(int argc, char const *argv[])
{
    int a = 10;
    int ret = ft_printf("%p\n",&a);    
    printf ("ret = %d\n", ret);
    return 0;
}