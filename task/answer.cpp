#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <fstream>

using namespace std;

void sieveOfEratosthenes(uint16_t upperLimit, ofstream &filename);
int square(uint16_t n);

int main() {
    ofstream answerFile;

    answerFile.open("answer_square.txt", ofstream::out | ofstream::trunc);
    for (int i = 0; i < 100; i++) {
        answerFile << square(i) << endl;
    }
    answerFile.close();
    
    answerFile.open("answer_primalityTest.txt", ofstream::out | ofstream::trunc);
    sieveOfEratosthenes(1000, answerFile);
    answerFile.close();

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

void sieveOfEratosthenes(uint16_t upperLimit, ofstream &filename) {
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
            filename << i << endl;
    }
    return;
}
