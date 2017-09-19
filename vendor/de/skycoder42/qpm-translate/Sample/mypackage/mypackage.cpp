#include "mypackage.h"
#include <QDebug>

MyPackage::MyPackage(QObject *parent) :
	QObject(parent)
{
	qDebug() << tr("MyPackage translation");
}
