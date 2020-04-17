#include <stdint.h>
// uint16_t arr[NUM_ELEMENTS] = {...};

uint16_t square(uint16_t n) {
    if (n == 0)
        return 0;

    // x = floor(n/2)
    uint16_t x = (n >> 1);
    if (n & 1)
        return ((square(x) << 2) + (x << 2) + 1);
    else
        return ((square(x) << 2));
}
