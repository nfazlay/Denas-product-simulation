#ifndef PROGRAM_H
#define PROGRAM_H
#include <QString>

#include "therapies.h"

using namespace std;

class Program: public Therapies{
public:
    Program(QString, int, int);
};
#endif // PROGRAM_H
