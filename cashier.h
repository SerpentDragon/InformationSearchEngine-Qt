#ifndef CASHIER_H
#define CASHIER_H

#include "worker.h"

class Cashier : public Worker
{
    int Experience;
    int Hours_in_Month;
public:
    Cashier();
    Cashier(int, const QString&, const QString&, const QString&, const QString&, int, int, int, const QString&, const QString&, int, int, int);
    ~Cashier();
    int getExperience() const;
    int getHiM() const;

    void setExperience(int);
    void setHiM(int);
};

#endif // CASHIER_H
