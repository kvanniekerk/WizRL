#include "game_math.h"

int roll(char* dice) { // handles d6, nd6
    srand(time(NULL));

    int result = 0;
    int min = 1;
    char diceCount[5];

    char* pos = strchr(dice, 'd');

    if (pos != NULL) {
        size_t length = pos - dice;
        memcpy(diceCount, dice, length);
        diceCount[length] = '\0';
        
        char* sides = pos + 1;
        char* endptr;

        int rolls = atoi(diceCount);
        int max = atoi(sides);
        if (rolls == 0)
            rolls++;

        for (int i = 0; i< rolls; i++)
        {
            result += (rand() % max + min);
        }
    
        printf("Input: %s\n", dice);
        printf("Number of dice: %d\n", rolls);
        printf("Number of sides on dice: %d\n", max);
        printf("Result: %d\n", result);
    }

    return 0;
}
