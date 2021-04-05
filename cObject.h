#ifndef COBJECT_H
#define COBJECT_H

#include <QObject>
#include <QDebug>
#include <QThread>

class cObject : public QObject
{
    Q_OBJECT
public:
    explicit cObject(QObject *parent = nullptr);
    void DoSetup(QThread &cThread);

signals:

public slots:
};

#endif // COBJECT_H
