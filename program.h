#ifndef PROGRAM_H
#define PROGRAM_H
#include <QString>

#include "therapies.h"

using namespace std;
/**
 * @brief The Program class
 * Derived from the therapies class
 * Contained programmed therapy with set frequency and
 * power value
 */
class Program: public Therapies{
public:
    Program(QString, int, int);
};
#endif // PROGRAM_H
