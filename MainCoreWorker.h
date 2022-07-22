#ifndef MAINCOREWORKER_H
#define MAINCOREWORKER_H

#include <QObject>

class MainCoreWorker : public QObject
{
    Q_OBJECT
public:
    explicit MainCoreWorker(QObject *parent = nullptr);
    
signals:
    
};

#endif // MAINCOREWORKER_H
