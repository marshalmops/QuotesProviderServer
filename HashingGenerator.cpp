#include "HashingGenerator.h"

bool HashingGenerator::generateToken(const QString &dataForGenerating,
                                                 const QString &hashingSalt, 
                                                 CoreContext::Hash &token,
                                                 const QCryptographicHash::Algorithm hashingAlgo)
{
    if (dataForGenerating.isEmpty() || hashingSalt.isEmpty())
        return false;
    
    QString    dataForHashing{dataForGenerating + hashingSalt};
    QByteArray tokenBuffer   {QCryptographicHash::hash(dataForHashing.toUtf8(), hashingAlgo)};
    
    if (tokenBuffer.isEmpty()) return false;
    
    token = QString::fromUtf8(tokenBuffer.toBase64());
    
    return true;
}

bool HashingGenerator::generateHash(const QString &dataForGenerating,
                                    CoreContext::Hash &hash,
                                    const QCryptographicHash::Algorithm hashingAlgo)
{
    if (dataForGenerating.isEmpty()) return false;
    
    QByteArray tokenBuffer{QCryptographicHash::hash(dataForGenerating.toUtf8(), hashingAlgo)};
    
    if (tokenBuffer.isEmpty()) return false;
    
    hash = QString::fromUtf8(tokenBuffer.toBase64());
    
    return true;
}
