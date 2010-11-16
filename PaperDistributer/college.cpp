#include "college.h"

College::College():id(0), name(""), paperNumber(0), isJury(false)
{
}

College::College(int id, QString name, int paperNumber, bool isJury)
{
    this->id = id;
    this->name = name;
    this->paperNumber = paperNumber;
    this->isJury = isJury;
}

int College::getId()
{
    return this->id;
}

void College::setId(int id)
{
    this->id = id;
}

QString College::getName()
{
    return this->name;
}

void College::setName(QString name)
{
    this->name = name;
}

int College::getPaperNumber()
{
    return this->paperNumber;
}

void College::setPaperNumber(int paperNumber)
{
    this->paperNumber = paperNumber;
}

bool College::getIsJury()
{
    return this->isJury;
}

void College::setIsJury(bool isJury)
{
    this->isJury = isJury;
}
