#ifndef COMMON_CONSTANS_H
#define COMMON_CONSTANS_H
#include <QStringList>
#include <management_window/encryption.h>
#include <management_window/projectmanagement.h>

#define largeMapRows 6  //number of cells on vertical axis
#define largeMapColumns 4 //number of cells on horizontal axis

#define smallMapRows 6  //number of cells on vertical axis
#define smallMapColumns 2 //number of cells on horizontal axis

extern QString* projectName;
extern ProjectManagement* projectMng;
extern const QString beginningOfHandoverSector;
extern const QString endOfHandoverSector;
extern const QString beginningOfCellSector;
extern const QString endOfCellSector;
extern const QString endOfUESector;
extern const QString endofStatSector;
extern const QString endOfMapSector;

#endif // COMMON_CONSTANS_H