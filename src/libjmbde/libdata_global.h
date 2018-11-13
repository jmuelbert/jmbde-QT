#ifndef LIBDATA_GLOBAL_H
#define LIBDATA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JMBDE_LIBRARY)
#define LIBDATASHARED_DLLSPEC Q_DECL_EXPORT
#else
#define LIBDATASHARED_DLLSPEC Q_DECL_IMPORT
#endif

#endif // LIBDATA_GLOBAL_H
