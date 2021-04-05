#include "therapylist.h"

TherapyList::TherapyList()
{

}

TherapyList::~TherapyList()
{
    qDeleteAll(collecton);
    collecton.clear();

}

void TherapyList::add(Therapies* therapy)
{
    collecton.push_back(therapy);
}

void TherapyList::get(int i, Therapies **therapy)
{
    *therapy = collecton.at(i);
}

int TherapyList::getSize()
{
    return collecton.size();
}
