#ifndef DOUBLEINPUTVALIDATOR_H
#define DOUBLEINPUTVALIDATOR_H

#include <QObject>
#include <QValidator>
class DoubleInputValidator : public QDoubleValidator
{
public:
    DoubleInputValidator(double bottom, double top, int decimals, QObject* parent = 0);
    QValidator::State validate(QString &, int &) const;
};

#endif // DOUBLEINPUTVALIDATOR_H
