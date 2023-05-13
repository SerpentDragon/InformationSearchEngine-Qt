#include "doctor.h"

Doctor::Doctor(){};
Doctor::Doctor(int code, const QString& surname, const QString& name, const QString& patronymic, const QString& sex, int day, int month, int year, const QString& center, const QString& position, int salary, const QString& specialization, int experience, int category)
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
    Specialization = specialization;
    Experience = experience;
    Category = category;
    Prev = Next = this;
}
Doctor::~Doctor(){};
QString Doctor::getSpecialization() const {return Specialization;}
int Doctor::getExperience() const {return Experience;}
int Doctor::getCategory() const {return Category;}

void Doctor::setSpecialization(const QString& specialization) {Specialization = specialization;}
void Doctor::setExperience(int experience) {Experience = experience;}
void Doctor::setCategory(int category) {Category = category;}
