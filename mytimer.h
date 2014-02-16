#ifndef MYTIMER_H
#define MYTIMER_H

#include "commonimport.h"

class mytimer : public QTimer
{
    Q_OBJECT
public:
    explicit mytimer(QObject *parent = 0);

public:
    bool running;

signals:

public slots:

};

#endif // MYTIMER_H
