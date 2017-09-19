#include <QCoreApplication>
#include <QTranslator>
#include <mypackage.h>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	auto t = new QTranslator(qApp);
	qDebug() << t->load(QLocale(),
						"sample",
						"_",
						QCoreApplication::applicationDirPath());
	a.installTranslator(t);

	MyPackage p;
	qDebug() << QCoreApplication::translate("CONTEXT", "main translation");

	return a.exec();
}
