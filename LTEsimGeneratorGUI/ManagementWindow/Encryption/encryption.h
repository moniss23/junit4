#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>

const QString cipher_key="myvoiceismypassportverifyme";

const char* crypt(const char* plaintext,int text_len,const char* key,int key_len,bool terminatingZero=false);

QString itoa(int i);


#endif // ENCRYPTION_H
