#include "worker.h"

Worker::Worker(){};
Worker::~Worker(){};
int Worker::getCode() const {return Code;}
QString Worker::getSurname() const {return Surname;}
QString Worker::getName() const {return Name;}
QString Worker::getPatronymic() const {return Patronymic;}
QString Worker::getSex() const {return Sex;}
QString Worker::getBirthday() const
{
    QString day, month, year;
    day = QString::number(Birthday.day);
    month = QString::number(Birthday.month);
    year = QString::number(Birthday.year);

    if (day.size()==1) day = "0" + day;
    if (month.size()==1) month = "0" + month;
    return day+"."+month+"."+year;
}
QString Worker::getCenter() const {return Center;}
QString Worker::getPosition() const {return Position;}
int Worker::getSalary() const {return Salary;}
Worker* Worker::getPrev() const {return Prev;}
Worker* Worker::getNext() const {return Next;}

void Worker::setCode(int code) {Code = code;}
void Worker::setSurname(const QString& surname) {Surname = surname;}
void Worker::setName(const QString& name) {Name = name;}
void Worker::setPatronymic(const QString& patronymic) {Patronymic = patronymic;}
void Worker::setSex(const QString& sex) {Sex = sex;}
void Worker::setBirthday(int day, int month, int year) {Birthday.day = day; Birthday.month = month; Birthday.year = year;}
void Worker::setCenter(const QString& center) {Center = center;}
void Worker::setPosition(const QString& position){Position = position;}
void Worker::setSalary(int salary) {Salary = salary;}
void Worker::setPrev(Worker *Obj) {Prev = Obj;}
void Worker::setNext(Worker *Obj) {Next = Obj;}

void Worker::Add(Worker **Begin)
{
    if(*Begin)
    {
        Worker *P = (*Begin)->getNext();
        Next = P;
        Prev = (*Begin);
        P->setPrev(this);
        (*Begin)->setNext(this);
    }
    (*Begin) = this;
}
void Worker::Delete(Worker **Begin)
{
    if (*Begin)
    {
        this->getPrev()->setNext(this->getNext());
        this->getNext()->setPrev(this->getPrev());
        if (this->getNext() == this) *Begin = nullptr;
        else if (this == *Begin) *Begin = this->getPrev();
        delete this;
    }
}
