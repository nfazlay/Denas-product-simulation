#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <QString>

using namespace std;


#include "therapies.h"

Therapies::Therapies(){}


Therapies::Therapies(Therapies& t){
    name = t.getName();
    power = t.getPower();
    frequency = t.getFrequency();
}

Therapies::~Therapies(){}

int Therapies::getPower(){
    return  power;
}

void Therapies::setPower(int p){
    power = p;
}

int Therapies::getFrequency(){
    return  frequency;
}

QString Therapies::getName(){
    return name;
}

