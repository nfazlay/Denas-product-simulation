#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @brief The states enum
 * Contains the staes of the machine
 */
enum states{
    OFF = -1,
    HOME= 0,
    MENU= 1,
    PROG= 2,
    FREQ= 3,
    POWER= 4,
    RECORDS= 5,
    TREATMENT = 6,
    FINISHED = 7
};

/**
 * @brief The buttons enum
 * Button constants
 */
enum buttons{
    UP= 8,
    DOWN = 9,
    SELECT = 10,
    SKINON = 11,
    SKINOFF = 12,
    RECORD = 13
};

#endif // CONSTANTS_H
