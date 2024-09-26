#include <stdio.h>
#include <stdint.h>

// Инициализация состояния
uint32_t state[4];

// Функция генерации псевдослучайного числа с помощью xorshift128
uint32_t xorshift128() {
    uint32_t t = state[3];
    uint32_t const s = state[0];
    state[3] = state[2];
    state[2] = state[1];
    state[1] = s;
    t ^= t << 11;
    t ^= t >> 8;
    return state[0] = t ^ s ^ (s >> 19);
}

int main() {
    uint32_t seed;
    printf("Write seed: ");
    scanf("%u", &seed);

    // Инициализация начального состояния с использованием введенного числа
    state[0] = seed;
    state[1] = seed ^ 0x12345678; // произвольные модификации для разнообразия
    state[2] = seed ^ 0x87654321;
    state[3] = seed ^ 0xABCDEF01;

    // Генерация и вывод 100 случайных чисел
    for (int i = 0; i < 100; ++i) {
        printf("%u\n", xorshift128());
    }

    return 0;
}
