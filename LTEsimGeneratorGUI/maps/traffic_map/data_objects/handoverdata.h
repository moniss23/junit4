#ifndef HANDOVERDATA_H
#define HANDOVERDATA_H
#include <QString>

class HandoverData
{
public:

    HandoverData(QString l_name);

//----------------------------Getters------------------------------------------------

    QString getHandoverName();
    QString getSouthBoundary();
    QString getNorthBoundary();
    QString getWestBoundary();
    QString getEastBoundary();

//----------------------------Setters------------------------------------------------


    void setHandoverName(QString l_name);
    void setSouthBoundary(QString l_south);
    void setNorthBoundary(QString l_north);
    void setWestBoundary(QString l_west);
    void setEastBoundary(QString l_east);

    void readParamsFromScript();

private:

    QString m_handoverName;
    int m_southBoundary;
    int m_northBoundary;
    int m_westBoundary;
    int m_eastBoundary;




};

#endif // HANDOVERDATA_H
