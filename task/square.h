#include <stdint.h>
// uint16_t arr[NUM_ELEMENTS] = {...};

uint16_t square(uint16_t n);
uint16_t square_alt(uint16_t);

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

uint16_t square_alt(uint16_t n) {
    uint16_t k = 0;
    for (uint16_t i = 0; i < n; i++) {
        k += n;
    }
    return k;
}
