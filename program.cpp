#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <QString>

using namespace std;


#include "program.h"

Program::Program(QString n, int f, int p){
    name = n;
    frequency = f;
    power = p;
}
