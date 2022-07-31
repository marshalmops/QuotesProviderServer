#include "StringVariantMapModel.h"

StringVariantMapModel::StringVariantMapModel(const QMap<QString, QVariant> &prevMap, QObject *parent)
    : QAbstractListModel{parent},
      m_stringVariantMap{}
{
    if (!prevMap.keys().empty()) {
        foreach (const auto &key, prevMap.keys())
            m_stringVariantMap.push_back(std::pair<QString, QVariant>(key, prevMap.value(key)));
    }
}

int StringVariantMapModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid() ? -1 : m_stringVariantMap.size());
}

QVariant StringVariantMapModel::data(const QModelIndex &index, 
                                     int role) const
{
    QVariant value{};
    
    if (!index.isValid())          return value;
    if (index.row() >= rowCount()) return value;
    if (role != Qt::DisplayRole && role <= Qt::UserRole)
        return value;
    
    const auto& curItem = m_stringVariantMap.at(index.row());
    
    switch (role) {
    case Qt::DisplayRole:       {value = curItem.first;  break;}
    case CustomRoles::CR_VALUE: {value = curItem.second; break;}
    }
    
    return value;
}

Error StringVariantMapModel::addStringValuePair(const std::pair<QString, QVariant> &stringVariantPair)
{
    if (stringVariantPair.first.isEmpty() || !stringVariantPair.second.isValid())
    {
        return Error{tr("Provided pair insertion data is incorrect!").toStdString(), true};
    }
    
    if (!checkKeyUniqueness(stringVariantPair.first))
        return Error{tr("Provided pair with the key already exists!").toStdString()};
    
    m_stringVariantMap.push_back(std::move(stringVariantPair));
    
    return (insertRows(rowCount()) ? Error{} : Error{tr("Pair insertion failed!").toStdString(), true});
}

Error StringVariantMapModel::removeStringValuePair(const QModelIndex &index)
{
    if (!index.isValid() || index.row() >= rowCount()) 
        return Error{tr("Provided pair removing data is incorrect!").toStdString()};
    
    m_stringVariantMap.removeAt(index.row());
    
    return (removeRows(index.row()) ? Error{} : Error{tr("Pair removing failed!").toStdString(), true});
}

QMap<QString, QVariant> StringVariantMapModel::getStringVariantMap() const
{
    QMap<QString, QVariant> stringVariantMap{};
    
    foreach (const auto &item, m_stringVariantMap)
        stringVariantMap[item.first] = item.second;
    
    return stringVariantMap;
}

bool StringVariantMapModel::insertRows(int row, 
                                       int count,
                                       const QModelIndex &parent)
{
    if (row < 0 || row > rowCount() || count < 1 || parent.isValid())
        return false;
    
    beginInsertRows(parent, row, row + count);
    endInsertRows();
    
    return true;
}

bool StringVariantMapModel::removeRows(int row,
                                       int count,
                                       const QModelIndex &parent)
{
    if (row < 0 || count < 1 || parent.isValid())
        return false;
    
    beginRemoveRows(parent, row, row + count);
    endRemoveRows();
    
    return true;
}

bool StringVariantMapModel::checkKeyUniqueness(const QString &key) const
{
    if (key.isEmpty()) return false;
    
    foreach (const auto &item, m_stringVariantMap)
        if (item.first == key) return false;
    
    return true;
}
