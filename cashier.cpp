#include "cashier.h"

Cashier::Cashier(){};
Cashier::Cashier(int code, const QString& surname, const QString& name, const QString& patronymic, const QString& sex, int day, int month, int year, const QString& center, const QString& position, int salary, int experience, int hours_in_month)
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
    Experience = experience;
    Hours_in_Month = hours_in_month;
    Prev = Next = this;
}
Cashier::~Cashier(){};
int Cashier::getExperience() const {return Experience;}
int Cashier::getHiM() const {return Hours_in_Month;}

void Cashier::setExperience(int experience) {Experience = experience;}
void Cashier::setHiM(int hours_in_month) {Hours_in_Month = hours_in_month;}
