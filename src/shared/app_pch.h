#if defined __cplusplus
#include <QtGlobal>

#ifdef Q_WS_WIN
#define _POSIX_
#include <limits.h>
#undef _POSIX_
#endif

#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QObject>
#include <QPointer>
#include <QRegExp>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QVariant>

#include <stdlib.h>
#endif
