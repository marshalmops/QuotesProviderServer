#ifndef HASHINGGENERATOR_H
#define HASHINGGENERATOR_H

#include <QCryptographicHash>

#include "CoreContext.h"

class HashingGenerator
{
public:
    constexpr static const QCryptographicHash::Algorithm C_DEFAULT_HASHING_ALGO = QCryptographicHash::Algorithm::Sha256;
    
public:
    HashingGenerator() = delete;
    
    static bool generateToken(const QString &dataForGenerating,
                              const QString &hashingSalt,
                              CoreContext::Hash &token,
                              const QCryptographicHash::Algorithm hashingAlgo = C_DEFAULT_HASHING_ALGO);
    static bool generateHash(const QString &dataForGenerating,
                             CoreContext::Hash &hash,
                             const QCryptographicHash::Algorithm hashingAlgo = C_DEFAULT_HASHING_ALGO);
};

#endif // HASHINGGENERATOR_H
