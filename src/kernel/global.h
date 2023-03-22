#ifndef SPONSORSHIP_GLOBAL_H
#define SPONSORSHIP_GLOBAL_H

#include <Sponsorship/config.h>

#ifdef SPONSORSHIP_SHARED
#   ifdef BUILD_SPONSORSHIP_LIB
#       define SPONSORSHIP_EXPORT Q_DECL_EXPORT
#   else
#       define SPONSORSHIP_EXPORT Q_DECL_IMPORT
#   endif
#else
#    define SPONSORSHIP_EXPORT
#endif

#define SPONSORSHIP_DECLARE_PRIVATE(Class) friend class Class##Private;
#define SPONSORSHIP_DECLARE_PUBLIC(Class) friend class Class;

#define SPONSORSHIP_D(Class) Class##Private *d = static_cast<Class##Private *>(qGetPtrHelper(this->d));
#define SPONSORSHIP_Q(Class) Class *q = static_cast<Class *>(this->q);

#endif // SPONSORSHIP_GLOBAL_H
