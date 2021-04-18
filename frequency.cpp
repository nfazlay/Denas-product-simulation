#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <QString>

using namespace std;


#include "frequency.h"

/**
 * @brief Frequency::Frequency
 * @param n name
 * @param f frequency
 * @param p power
 */
Frequency::Frequency(QString n, int f, int p){
    name = n;
    frequency = f;
    power = p;
}
