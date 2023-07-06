#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int int_add(int x, int y)
{
    return x + y;
}

EMSCRIPTEN_KEEPALIVE
int int_mul(int x, int y)
{
    return x * y;
}
