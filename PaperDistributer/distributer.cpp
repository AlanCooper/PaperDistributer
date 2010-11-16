#include "distributer.h"
#include <QObject>
#include <QTextStream>
#include <QStringList>

Distributer::Distributer()
{
}

void Distributer::setColleges(const QVector<College> &colleges)
{
    this->colleges = colleges;
}

QVector< QVector<int> > Distributer::getResult()
{
    return this->result;
}

QVector<int> Distributer::getAmount()
{
    return this->assigned;
}

QStringList Distributer::getHLabel()
{

    QStringList hLabel;
    if (colleges.size() <= 0)
    {
        return hLabel;
    }
    for (int i = 0; i < this->colleges.size(); i++)
    {
        QString label;
        QTextStream stream(&label);
        stream << colleges[i].getId();
        hLabel.append(label);
    }
    hLabel.append(QObject::tr("Amount"));
    return hLabel;
}

QStringList Distributer::getVLabel()
{
    QStringList vLabel;
    for (int i = 0; i < this->colleges.size(); i++)
    {
        QString label;
        QTextStream stream(&label);
        stream << colleges[i].getId() << " " << colleges[i].getName();
        vLabel.append(label);
    }
    return vLabel;
}

QString Distributer::csvString()
{
    QString csv;
    QTextStream stream(&csv);
    QStringList hHeader = this->getHLabel();
    QStringList vHeader = this->getVLabel();
    for (int i = 0; i < hHeader.size(); i++)
    {
        stream << "," << hHeader.at(i);
    }
    stream << endl;
    for (int i = 0; i < vHeader.size(); i++)
    {
        stream << vHeader.at(i) << ",";
        for (int j = 0; j < vHeader.size(); j++)
        {
            stream << this->result[i][j] << ",";
        }
        stream << this->assigned[i] << endl;
    }
    return csv;
}

/*
 *This algorithm provided by Li Jing, I  doubt the accuracy of this
 */
void Distributer::distribute()
{
    int collegeNumber = this->colleges.size();
    QVector<int> paperNumber(collegeNumber, 0);
    for (int i = 0; i < collegeNumber; i++)
    {
        paperNumber[i] = colleges[i].getPaperNumber();
    }

    int paperSum = 0;
    for (int i = 0; i < collegeNumber; i++)
    {
        paperSum += colleges[i].getPaperNumber();
    }

    QVector<int> available(collegeNumber, 0);
    for (int i = 0; i < collegeNumber; i++)
    {
        available[i] = paperSum - colleges[i].getPaperNumber();
    }

    int availableCollegeNumber = 0;
    for (int i = 0; i < collegeNumber; i++)
    {
        if (colleges[i].getIsJury())
        {
            availableCollegeNumber++;
        }
    }
    QVector<double> need(collegeNumber, -100);
    for (int i = 0; i < collegeNumber; i++)
    {
        if (colleges[i].getIsJury())
        {
            need[i] = (double)paperSum / availableCollegeNumber;
        }
    }

     QVector<int> limit(collegeNumber, 0);
     for (int i = 0; i < collegeNumber; i++)
     {
         limit[i] = paperNumber[i] / 3;
     }
    result = QVector< QVector<int> >(collegeNumber, QVector<int>(collegeNumber, 0));
    this->assigned = QVector<int>(collegeNumber, 0);


    while (paperSum > 0)
    {
        int collegeToDistribute = 0;
        for (int i = 0; i < collegeNumber; i++)
        {
            if (paperNumber[i] > 0)
            {
                collegeToDistribute = i;
                break;
            }
        }

        int maxIndex = 0;
        double maxP = -10;
        for (int i = 0; i < collegeNumber; i++)
        {
            if (need[i] > -100 && i != collegeToDistribute
                && result[i][collegeToDistribute] <= limit[collegeToDistribute])
            {

                if (maxP < need[i] / available[i])
                {
                    maxP = need[i] / available[i];
                    maxIndex = i;
                }
                else if (maxP == need[i] / available[i])
                {
                    if (result[i][collegeToDistribute] < result[maxIndex][collegeToDistribute])
                    {
                        maxP = need[i] / available[i];
                        maxIndex = i;
                    }
                }
            }
        }
        result[maxIndex][collegeToDistribute]++;
        paperSum--;
        paperNumber[collegeToDistribute]--;
        need[maxIndex] -= 1;
        assigned[maxIndex]++;
        for (int i = 0; i < collegeNumber; i++)
        {
            if (i != collegeToDistribute)
            {
                available[i]--;
            }
        }
    }
}
