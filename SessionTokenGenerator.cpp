#include "SessionTokenGenerator.h"

bool SessionTokenGenerator::generateSessionToken(const QString &dataForGenerating,
                                                 const QString &hashingSalt, 
                                                 CoreContext::Hash &token,
                                                 const QCryptographicHash::Algorithm hashingAlgo)
{
    if (dataForGenerating.isEmpty() || hashingSalt.isEmpty())
        return false;
    
    QString    dataForHashing{dataForGenerating + hashingSalt};
    QByteArray tokenBuffer   {QCryptographicHash::hash(dataForHashing.toUtf8(), hashingAlgo)};
    
    if (tokenBuffer.isEmpty()) return false;
    
    token = QString::fromUtf8(tokenBuffer);
    
    return true;
}
