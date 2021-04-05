#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <QString>

using namespace std;


#include "frequency.h"

Frequency::Frequency(QString n, int f, int p){
    name = n;
    frequency = f;
    power = p;
}
