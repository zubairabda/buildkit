#include <stdio.h>
#include "foo.h"

int main(void)
{
    struct foo f = {0};
    f.a = 4;
    f.b = 7;
    f.c = 12.0f;
    printf("foo fields:\na = %d, b = %d, c = %f\n", f.a, f.b, f.c);
    return 0;
}

