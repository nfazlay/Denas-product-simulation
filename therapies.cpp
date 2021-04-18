#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <QString>

using namespace std;


#include "therapies.h"

/**
 * @brief Therapies::Therapies
 */
Therapies::Therapies(){}

/**
 * @brief Therapies::Therapies
 * copy constructor
 * @param t contructor to copy from
 */
Therapies::Therapies(Therapies& t){
    name = t.getName();
    power = t.getPower();
    frequency = t.getFrequency();
}

Therapies::~Therapies(){}

/**
 * @brief Therapies::getPower
 * @return power
 */
int Therapies::getPower(){
    return  power;
}

/**
 * @brief Therapies::setPower
 * @param p set power to p
 */
void Therapies::setPower(int p){
    power = p;
}

/**
 * @brief Therapies::getFrequency
 * @return frequency
 */
int Therapies::getFrequency(){
    return  frequency;
}

/**
 * @brief Therapies::getName
 * @return name of therapy (QString)
 */
QString Therapies::getName(){
    return name;
}

