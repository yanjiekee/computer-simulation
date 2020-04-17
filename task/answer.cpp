#include <stdio.h>
#include <math.h>
#include <stdint.h>

void sieveOfEratosthenes(uint16_t upperLimit);
int square(uint16_t n);

int main() {
    sieveOfEratosthenes(1000);
    return 0;
}

int square(uint16_t n) {
    if (n == 0)
        return 0;

    // x = floor(n/2)
    uint16_t x = (n >> 1);
    if (n & 1)
        return ((square(x) << 2) + (x << 2) + 1);
    else
        return ((square(x) << 2));
}

void sieveOfEratosthenes(uint16_t upperLimit) {
    // To have upperLimit as the last index, default boolean is true
    bool numberList[upperLimit + 1];

    for (uint16_t i = 0; i <= upperLimit; i++) {
        numberList[i] = true;
    }

    // Instead of i <= root of n, we can use condition squared i <= n
    for (uint16_t i = 2; (i * i) <= upperLimit; i++) {
        if (numberList[i]) {
            for (uint16_t j = (i * i); j <= upperLimit; j += i)
                numberList[j] = false;
        }
    }

    // Print out the remaining (prime) numbers after eliminating composite numbers
    for (int i = 2; i <= upperLimit; i++) {
        if (numberList[i])
            printf("%d\n" ,i);
    }
    return;
}
