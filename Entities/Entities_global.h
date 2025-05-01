#ifndef ENTITIES_GLOBAL_H
#define ENTITIES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENTITIES_LIBRARY)
#define ENTITIES_EXPORT Q_DECL_EXPORT

#else
#define ENTITIES_EXPORT Q_DECL_IMPORT
#endif

#endif // ENTITIES_GLOBAL_H
