#ifndef SESSIONTOKENGENERATOR_H
#define SESSIONTOKENGENERATOR_H

#include <QCryptographicHash>

#include "CoreContext.h"

class SessionTokenGenerator
{
public:
    constexpr static const QCryptographicHash::Algorithm C_DEFAULT_HASHING_ALGO = QCryptographicHash::Algorithm::Sha256;
    
public:
    SessionTokenGenerator() = delete;
    
    static bool generateSessionToken(const QString &dataForGenerating,
                                     const QString &hashingSalt,
                                     CoreContext::Hash &token,
                                     const QCryptographicHash::Algorithm hashingAlgo = C_DEFAULT_HASHING_ALGO);
};

#endif // SESSIONTOKENGENERATOR_H
