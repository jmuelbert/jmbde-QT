#ifndef MYPACKAGE_H
#define MYPACKAGE_H

#include <QObject>

class MyPackage : public QObject
{
	Q_OBJECT

public:
	explicit MyPackage(QObject *parent = nullptr);
};

#endif // MYPACKAGE_H
