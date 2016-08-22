#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector>

class StatisticsData
{
public:
    StatisticsData();
    StatisticsData(StatisticsData& statisticsData);

    StatisticsData& operator =(const StatisticsData& rhc);

    bool getStatMapFor(QString key);
    void setStatMapFor(QString key, bool value=false);
    QString getElementType() const;


public:
    const static QStringList namesList;

private:
    QVector<std::tuple<QString,bool>> statisticsMap;
};

#endif // STATISTICSDATA_H
