#ifndef SECURITY_H
#define SECURITY_H

#include "worker.h"

class Security : public Worker
{
    int Rank;
    QString Organization;
public:
    Security();
    Security(int, const QString&, const QString&, const QString&, const QString&, int, int, int, const QString& center, const QString& position, int, int, const QString&);
    ~Security();
    int getRank() const;
    QString getOrganization() const;

    void setRank(int);
    void setOrganization(const QString&);
};
#endif // SECURITY_H
