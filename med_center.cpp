#include "med_center.h"

Med_Center::Med_Center(){};
Med_Center::Med_Center(const QString& name, const QString& address, const QString& phone_number)
{
    Name = name;
    Address = address;
    Phone_number = phone_number;
    head = nullptr;
    Prev = Next = this;
}
QString Med_Center::getName() const {return Name;}
QString Med_Center::getAddress() const {return Address;}
QString Med_Center::getPhoneNumber() const {return Phone_number;}
Worker* Med_Center::gethead() const {return head;}
Med_Center* Med_Center::getPrev() const {return Prev;}
Med_Center* Med_Center::getNext() const {return Next;}

void Med_Center::setName(const QString& name) {Name = name;}
void Med_Center::setAddress(const QString& address) {Address = address;}
void Med_Center::setPhoneNumber(const QString& phone_number) {Phone_number = phone_number;}
void Med_Center::sethead(Worker **Obj) {head = *Obj;}
void Med_Center::setPrev(Med_Center *Obj) {Prev = Obj;}
void Med_Center::setNext(Med_Center *Obj) {Next = Obj;}

void Med_Center::Add(Med_Center **Begin)
{
    if (*Begin)
    {
        Med_Center *P = (*Begin)->getNext();
        Next = P;
        Prev = (*Begin);
        P->setPrev(this);
        (*Begin)->setNext(this);
    }
    (*Begin) = this;
}
void Med_Center::Delete(Med_Center **Begin)
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
