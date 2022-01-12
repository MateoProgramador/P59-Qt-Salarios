#ifndef OBRERO_H
#define OBRERO_H

#include <QObject>

class Obrero : public QObject
{
    Q_OBJECT
public:
    explicit Obrero(QObject *parent = nullptr);

signals:

};

#endif // OBRERO_H
