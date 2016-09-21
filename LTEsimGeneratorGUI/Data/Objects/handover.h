#ifndef HANDOVER_H
#define HANDOVER_H

#include <QString>

/**
 * @brief The Handover class represents LTEsim handover object
 */
class Handover
{
public:
    Handover();
    Handover(const QString &name);
    ~Handover();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
public:
    /**
     * @brief resetParams restores Handover default parameters
     */
    void resetParams();

public:
    QString area;           ///< Name of handover area
    int southBoundary;      ///< South boundary
    int northBoundary;      ///< North boundary
    int westBoundary;       ///< West boundary
    int eastBoundary;       ///< East boundary
};

QDataStream &operator>>(QDataStream &in, Handover &handover);
QDataStream &operator<<(QDataStream &out, const Handover &handover);

#endif // HANDOVER_H
