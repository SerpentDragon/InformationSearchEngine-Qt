#ifndef MED_CENTER_H
#define MED_CENTER_H

#include "worker.h"

class Med_Center
{
    QString Name;
    QString Address;
    QString Phone_number;
    Worker *head;
    Med_Center *Prev;
    Med_Center *Next;
public:
    Med_Center();
    Med_Center(const QString&, const QString&, const QString&);
    QString getName() const;
    QString getAddress() const;
    QString getPhoneNumber() const;
    Worker *gethead() const;
    Med_Center *getPrev() const;
    Med_Center *getNext() const;

    void setName(const QString&);
    void setAddress(const QString&);
    void setPhoneNumber(const QString&);
    void sethead(Worker**);
    void setPrev(Med_Center*);
    void setNext(Med_Center*);

    void Add(Med_Center**);
    void Delete(Med_Center**);
};

#endif // MED_CENTER_H
