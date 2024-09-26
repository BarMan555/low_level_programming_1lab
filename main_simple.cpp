#include <stdio.h>
#include <stdint.h>

// Инициализация состояния
uint32_t state[4];  // resd 4

// Функция генерации псевдослучайного числа с помощью xorshift128
uint32_t xorshift128() {
    uint32_t t = state[3]; // r9d
    uint32_t s = state[0]; // r10d
    state[3] = state[2];
    state[2] = state[1];
    state[1] = s;
    t ^= t << 11;
    t ^= t >> 8;

    s ^= s >> 19;
    t ^= s;
    state[0] = t;

    return state[0];
}

int main() {
    uint32_t seed; // r8d
    printf("Write seed: ");
    scanf("%u", &seed);

    // Инициализация начального состояния с использованием введенного числа
    state[0] = seed;
    
    seed ^= 0x12345678;
    state[1] = seed; 

    seed ^= 0x87654321;
    state[2] = seed;

    seed ^= 0xABCDEF01;
    state[3] = seed;

    // Генерация и вывод 100 случайных чисел
    int i = 0; // ecx
start_cycle:
    if (i == 100) goto end_cycle;
    printf("%u\n", xorshift128());
    i += 1;
    goto start_cycle;
end_cycle:
    
    return 0;
}
