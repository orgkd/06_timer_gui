#include "mytimer.h"

mytimer::mytimer(QObject *parent) :
    QTimer(parent)
{
    running = false;
    setSingleShot(true);
}
