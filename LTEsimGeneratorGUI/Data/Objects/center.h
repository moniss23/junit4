#ifndef CENTER_H
#define CENTER_H

#include <QString>

/**
 * @brief The Center class represents center of LTEsim cell object
 */
class Center
{
public:
    Center();
    Center(const QString &name);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
public:
    /**
     * @brief resetParams restores Cell default parameters
     */
    void resetParams();

public:
    QString area;           ///< Name of the area (equal to name of a cell)
    int southBoundary;      ///< South boundary
    int northBoundary;      ///< North boundary
    int westBoundary;       ///< West boundary
    int eastBoundary;       ///< East boundary
};

QDataStream &operator>>(QDataStream &in, Center &center);
QDataStream &operator<<(QDataStream &out, const Center &center);

#endif // CENTER_H
