#ifndef STRINGVARIANTMAPMODEL_H
#define STRINGVARIANTMAPMODEL_H

#include <QAbstractListModel>

#include "Error.h"

class StringVariantMapModel : public QAbstractListModel
{
    Q_OBJECT
    
    enum CustomRoles {
        CR_VALUE = Qt::UserRole + 1
    };
    
public:
    using StringVariantMap = QVector<std::pair<QString, QVariant>>;
    
    explicit StringVariantMapModel(const QMap<QString, QVariant> &prevMap = QMap<QString, QVariant>{},
                                   QObject *parent = nullptr);
    
    virtual int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    virtual QVariant data(const QModelIndex &index, 
                          int role) const override;
    
    Error addStringValuePair   (const std::pair<QString, QVariant> &stringVariantPair); 
    Error removeStringValuePair(const QModelIndex &index);
    
    QMap<QString, QVariant>&& getStringVariantMap() const;
    
private:
    virtual bool insertRows(int row = 1,
                            int count = 1, 
                            const QModelIndex &parent = QModelIndex{}) override;
    virtual bool removeRows(int row,
                            int count = 1, 
                            const QModelIndex &parent = QModelIndex{}) override;
    
    bool checkKeyUniqueness(const QString &key) const;
    
private:
    StringVariantMap m_stringVariantMap;
    
};

#endif // STRINGVARIANTMAPMODEL_H
