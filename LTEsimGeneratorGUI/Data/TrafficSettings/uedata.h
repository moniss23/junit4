#ifndef UEDATA_H
#define UEDATA_H

#include "Data/Interfaces/serializeinterface.h"

#include <QVector>

/**
 * @brief The UEData class contains data of user equipment
 */
class UEData : public SerializeInterface
{
public:
    /**
     * @brief UEData default constructor and destructor
     */
    UEData();
    ~UEData();

    QString pairName;                                                                   ///< UE pair name
    int amountOfPairs = 100;                                                            ///< amount of pairs
    std::pair<QString,QString> mobilityModelsPair{"RandomWalker","RandomWalker"};       ///< UE mobility model
    std::pair<QString,QString> csModelsPair{"PowerOnPowerOff", "PowerOnPowerOff"};      ///< UE CS model
    std::pair<QString,QString> psModelsPair{"NoPs", "NoPs"};                            ///< UE PS model
    std::pair<QString,QString> ueTypesPair{"iratHO", "iratHO"};                         ///< UE type
    std::pair<QString,QString> ueArea;                                                  ///< UE area

    //TODO: remove as soon as reading ueArea is ready
    QVector <QPair<int, int>> position { {2000,2000}, {4000,2000} };                    ///< UE position

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    /**
     * @brief getElementType is used to check element typr
     * @return QString  "UEData"
     */
    QString getElementType() const;
    /**
     * @brief serializeData is an inherited method that serializes this class to QByteArray
     * @return QByteArray with serialized object of the class
     */
    QByteArray serializeData();
    /**
     * @brief deserializeData is an inherited method that deserializes it's parameter to fill the fields in this class' instance
     * @param rawData is QByteArray that contains all the data needed to creata an instance of trafficFileData class
     */
    void deserializeData(const QByteArray &rawData);
};

#endif // UEDATA_H
