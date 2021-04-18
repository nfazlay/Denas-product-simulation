#include "therapylist.h"

/**
 * @brief TherapyList::TherapyList
 * Constructor
 */
TherapyList::TherapyList()
{
}

/**
 * @brief TherapyList::~TherapyList
 * Destructor deallocates data in the list
 */
TherapyList::~TherapyList()
{
    qDeleteAll(collecton);
    collecton.clear();

}

/**
 * @brief TherapyList::add
 * @param therapy
 * adds therapy* to the end of list
 */
void TherapyList::add(Therapies* therapy)
{
    collecton.push_back(therapy);
}

/**
 * @brief TherapyList::get
 * @param i index to get therapy from
 * @param therapy return to this parameter
 */
void TherapyList::get(int i, Therapies **therapy)
{
    *therapy = collecton.at(i);
}

/**
 * @brief TherapyList::getSize
 * @return size of list
 */
int TherapyList::getSize()
{
    return collecton.size();
}
