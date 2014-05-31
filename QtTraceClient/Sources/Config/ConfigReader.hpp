#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QObject>


class CConfigReader : public QObject
{
    Q_OBJECT

public:
    CConfigReader();
    virtual ~CConfigReader();

    void Load();

};


#endif // CONFIGREADER_H
