#include <stdint.h>
// Include the task square() too

void sieveOfEratosthenes(uint16_t upperLimit) {
    // To have upperLimit as the last index, default boolean is true
    bool numberList[upperLimit + 1];

    // Instead of i <= root of n, we can use condition squared i <= n
    for (uint16_t i = 2; square(i) <= n; i++) {
        if (numberList[i]) {
            for (uint16_t j = square(i); j <= upperLimit; j += i)
                numberList[j] = false;
        }
    }

    // Print out the remaining (prime) numbers after eliminating composite numbers
    // for (i = 2; i <= upperLimit; i++) {
    //     if (numberList[i])
    //         printf("%d\n" ,numberList[i]);
    // }
    return void;
}
