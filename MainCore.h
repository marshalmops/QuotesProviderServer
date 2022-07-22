#ifndef MAINCORE_H
#define MAINCORE_H

#include <QObject>

class MainCore : public QObject
{
    Q_OBJECT
public:
    explicit MainCore(QObject *parent = nullptr);
    
signals:
    
};

#endif // MAINCORE_H
