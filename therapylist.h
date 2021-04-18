#ifndef THERAPYLIST_H
#define THERAPYLIST_H

#include "therapies.h"
#include <QVector>
#include <QDebug>

/**
 * @brief The TherapyList class
 * Stores a list of therapies
 */
class TherapyList
{
public:
    TherapyList();
    ~TherapyList();
    void add(Therapies*);
    void get(int , Therapies**);
    int getSize();
private:
    QVector<Therapies*> collecton;

};

#endif // THERAPYLIST_H
