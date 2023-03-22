#ifndef SPONSORSHIP_DEBUG_H
#define SPONSORSHIP_DEBUG_H

#include <Sponsorship/global.h>

#include <QtCore/qloggingcategory.h>

#define sponsorshipDebug()    qCDebug(sponsorship)
#define sponsorshipInfo()     qCInfo(sponsorship)
#define sponsorshipWarning()  qCWarning(sponsorship)
#define sponsorshipCritical() qCritical(sponsorship)
#define sponsorshipFatal()    qCFatal(sponsorship)

#ifdef QT_DEBUG
#   define SPONSORSHIP_DEBUG
#   define SPONSORSHIP_INFO
#   define SPONSORSHIP_WARNING
#   define SPONSORSHIP_CRITICAL
#   define SPONSORSHIP_FATAL
#endif

SPONSORSHIP_EXPORT Q_DECLARE_LOGGING_CATEGORY(sponsorship)

#endif // SPONSORSHIP_DEBUG_H
