#include "game_math.h"

int roll(char* dice) { // handles dx, ndx, ndx+y
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
        int max = atoi(sides);
        int rolls = atoi(diceCount);


        if (rolls == 0)
            rolls++;

        for (int i = 0; i< rolls; i++)
        {
            result += (rand() % max + min);
        }
        
        int mod = 0;
        char* pos = strchr(dice, '+');

        if (pos != NULL) {
            char* modifier = pos + 1;
            mod = atoi(modifier);
            result += mod;
        }
    
       /* printf("Input: %s\n", dice);
        printf("Number of dice: %d\n", rolls);
        printf("Number of sides on dice: %d\n", max);
        printf("Modifier: %d\n", mod);
        printf("Result: %d\n", result);  */
    }

    return result;
}
