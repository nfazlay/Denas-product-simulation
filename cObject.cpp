include "cObject.h"

cObject::cObject(QObject *parent) : QObject(parent)
{

}

void cObject::DoSetup(QThread &cThread){
    connect(&cThread, SIGNAL(started()), this, SLOT(DoWork()));
}
