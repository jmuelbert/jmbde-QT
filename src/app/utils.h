#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include "string"
#include <QString>
#include <QDebug>
#include <QStandardPaths>
#include <QFileInfo>
#include <QTime>
#include <QSettings>
#include <QDirIterator>

namespace  Utils
{


const QString JmBdeDBPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1String("/juergen-muelbert.de/");
const QString DBName = QLatin1String("jmbdedb.db");

inline bool fileExists(const QString &url)
{
    QFileInfo path(url);
    if (path.exists()) return true;
    else return false;
}

} // namespace Utils
#endif // UTILS_H
