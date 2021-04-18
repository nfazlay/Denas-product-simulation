#ifndef FREQUENCY_H
#define FREQUENCY_H
#include <QString>

#include "therapies.h"

using namespace std;
/**
 * @brief The Frequency class
 * Frequency class derived from therapies class
 * No set power for frequency
 */
class Frequency: public Therapies{
public:
    Frequency(QString, int, int);
};

#endif // FREQUENCY_H
