#ifndef STRINGVARIANTMAPWIDGET_H
#define STRINGVARIANTMAPWIDGET_H

#include <QListView>

#include "Error.h"

#include "StringVariantMapModel.h"
#include "StringVariantPairInputDialog.h"

class StringVariantMapWidget : public QWidget
{
    Q_OBJECT
public:
    StringVariantMapWidget(const QString &label,
                           const QMap<QString, QVariant> &prevMap = QMap<QString, QVariant>{},
                           QWidget *parent = nullptr);
    
    QMap<QString, QVariant> getStringVariantMap() const;
    
signals:
    void errorOccured(const Error error);
    
    void contentChanged();
    
public slots:
    void addStringValuePair();
    void removeCurrentItem ();
    
private:
    QListView             *m_stringVariantMapView;
    StringVariantMapModel *m_model;
    
    QPushButton *m_addStringVariantPairButton;
    QPushButton *m_removeStringVariantPairButton;
};

#endif // STRINGVARIANTMAPWIDGET_H
