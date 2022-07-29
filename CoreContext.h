#ifndef CORECONTEXT_H
#define CORECONTEXT_H

#include <stdint.h>
#include <QString>
#include <QVector>
#include <QCryptographicHash>

namespace CoreContext
{

using Id   = uint64_t;
using Hash = QString;

constexpr static const QCryptographicHash::Algorithm C_DEFAULT_TEXT_HASHING_ALGO = QCryptographicHash::Algorithm::Sha256;

enum TaskType : uint8_t {
    TT_INVALID = 0,
    TT_CORE_TASK,
    TT_NETWORK_TASK
};

enum CoreTaskType : uint8_t {
    CTT_INVALID = 0,
    CTT_GET_DAILY_QUOTE,
    CTT_GET_HOURLY_QUOTE
};

enum EntityType : uint8_t {
    ET_INVALID = 0,
    ET_GRADE,
    ET_QUOTE,
    ET_USER,
    ET_SESSION,
    ET_ENTITY_RIGHTS_GROUP
};

enum QuoteGrade : int8_t {
    QG_LIKE = -1,
    QG_INVALID = 0,
    QG_DISLIKE = 1
};

static const QVector<std::pair<QString, QCryptographicHash::Algorithm>> stringHashingAlgoVector = {
    {"SHA256",    QCryptographicHash::Algorithm::Sha256},
    {"SHA512",    QCryptographicHash::Algorithm::Sha512},
    {"MD5",       QCryptographicHash::Algorithm::Md5},
    {"KECCAK256", QCryptographicHash::Algorithm::Keccak_256}
};

};

#endif // CORECONTEXT_H
