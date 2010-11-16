#ifndef DISTRIBUTER_H
#define DISTRIBUTER_H

#include "college.h"
#include <QVector>
#include <QStringList>

class Distributer
{
public:
    Distributer();
    void setColleges(const QVector<College>& colleges);
    void distribute();
    QVector< QVector<int> > getResult();
    QStringList getHLabel();
    QStringList getVLabel();
    QVector<int> getAmount();
    QVector<int> assigned;
    QString csvString();
private:
    QVector<College> colleges;
    QVector< QVector<int> > result;
};

#endif // DISTRIBUTER_H
