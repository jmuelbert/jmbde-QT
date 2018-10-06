#ifndef UTILS_H
#define UTILS_H

#include "string"
#include <QDebug>
#include <QDirIterator>
#include <QFileInfo>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>
#include <QString>
#include <QTime>

namespace Utils {

const QString JmBdeDBPath =
    QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) +
    QLatin1String("/juergen-muelbert.de/");
const QString DBName = QLatin1String("jmbdedb.db");

inline bool fileExists(const QString &url) {
  QFileInfo path(url);
  if (path.exists())
    return true;
  else
    return false;
}

} // namespace Utils
#endif // UTILS_H
