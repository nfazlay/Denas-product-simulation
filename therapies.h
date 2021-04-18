#ifndef THERAPIES_H
#define THERAPIES_H


#include <QString>
using namespace std;

/**
 * @brief The Therapies class
 * Base class for Therapy
 * There are two types of therapies
 * program and frequency
 */
class Therapies{
public:
    Therapies();
    Therapies(Therapies&);
    ~Therapies();
    void setPower(int);
    int getPower();
    int getFrequency();
    QString getName();

protected:
    QString name = "";
    int power = 0;
    int frequency = 0;
};

#endif // THERAPIES_H
