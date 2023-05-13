#ifndef DOCTOR_H
#define DOCTOR_H

#include "worker.h"

class Doctor : public Worker
{
    QString Specialization;
    int Experience;
    int Category;
public:
    Doctor();
    Doctor(int, const QString&, const QString&, const QString&, const QString& sex, int, int, int, const QString&, const QString&, int, const QString&, int, int);
    ~Doctor();
    QString getSpecialization() const;
    int getExperience() const;
    int getCategory() const;

    void setSpecialization(const QString&);
    void setExperience(int);
    void setCategory(int);
};

#endif // DOCTOR_H
