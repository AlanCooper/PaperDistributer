#ifndef COLLEGE_H
#define COLLEGE_H
#include <QString>

class College
{
public:
    College();
    College(int id, QString name, int paperNumber, bool isJury);
    int getId();
    QString getName();
    int getPaperNumber();
    bool getIsJury();

    void setId(int id);
    void setName(QString name);
    void setPaperNumber(int paperNumber);
    void setIsJury(bool isJury);
private:
    int id;
    QString name;
    int paperNumber;
    bool isJury;
};

#endif // COLLEGE_H
