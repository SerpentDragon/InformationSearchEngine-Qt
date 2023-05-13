#include "security.h"

Security::Security(){};
Security::Security(int code, const QString& surname, const QString& name, const QString& patronymic, const QString& sex, int day, int month, int year, const QString& center, const QString& position, int salary, int rank, const QString& organization)
{
    Code = code;
    Surname = surname;
    Name = name;
    Patronymic = patronymic;
    Sex = sex;
    Birthday.day = day;
    Birthday.month = month;
    Birthday.year = year;
    Center = center;
    Position = position;
    Salary = salary;
    Rank = rank;
    Organization = organization;
    Prev = Next = this;
}
Security::~Security(){};
int Security::getRank() const {return Rank;}
QString Security::getOrganization() const {return Organization;}

void Security::setRank(int rank) {Rank = rank;}
void Security::setOrganization(const QString& organization) {Organization = organization;}
