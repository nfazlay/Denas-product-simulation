#ifndef THERAPIES_H
#define THERAPIES_H


#include <QString>
using namespace std;


class Therapies{
public:
    Therapies();
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
