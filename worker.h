#ifndef WORKER_H
#define WORKER_H

#include <QString>

struct Data
{
    int day;
    int month;
    int year;
};

class Worker
{
protected:
    int Code;
    QString Surname;
    QString Name;
    QString Patronymic;
    QString Sex;
    Data Birthday;
    QString Center;
    QString Position;
    int Salary;
    Worker *Prev = this;
    Worker *Next = this;

public:
    Worker();
    virtual ~Worker();
    int getCode() const;
    QString getSurname() const;
    QString getName() const;
    QString getPatronymic() const;
    QString getSex() const;
    QString getBirthday() const;
    QString getCenter() const;
    QString getPosition() const;
    int getSalary() const;
    Worker* getPrev() const;
    Worker* getNext() const;

    void setCode(int);
    void setSurname(const QString&);
    void setName(const QString&);
    void setPatronymic(const QString&);
    void setSex(const QString&);
    void setBirthday(int, int, int);
    void setCenter(const QString&);
    void setPosition(const QString&);
    void setSalary(int);
    void setPrev(Worker*);
    void setNext(Worker*);

    void Add(Worker **Begin);
    void Delete(Worker **Begin);
};

#endif // WORKER_H
