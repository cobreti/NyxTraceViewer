#ifndef CONFIGWRITER_HPP
#define CONFIGWRITER_HPP

#include <QObject>


class CConfigWriter : public QObject
{
    Q_OBJECT

public:
    CConfigWriter();
    virtual ~CConfigWriter();

    void Save();
};


#endif // CONFIGWRITER_HPP
