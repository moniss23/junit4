#ifndef PARAMETERSFILEDATA_H
#define PARAMETERSFILEDATA_H

#include <Data/Interfaces/serializeinterface.h>

/**
 * @brief The ParametersFileData class contains filename and parameters script content
 */
class ParametersFileData : public SerializeInterface
{
public:
    /***********************************************
     *              PUBLIC API                     *
     ***********************************************/

    QString filename;           ///< name of pramaters file
    QString content;            ///< parameters script content

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    ~ParametersFileData() {}

    /**
     * @brief getElementType is used to return QString that represnt type of element
     * @return  QString("ParametersFileData")
     */
    virtual QString getElementType() const;
    /**
     * @brief serializeData is used to put all members into QByteArray and returns it
     * @return QByteArray with all class members serialized
     */
    virtual QByteArray serializeData();
    /**
     * @brief deserializeData is used to load data to class members from QByteArray
     * @param rawData is QByteArray with serialized class members
     */
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // PARAMETERSFILEDATA_H
