#ifndef STRINGVARIANTPAIRINPUTDIALOG_H
#define STRINGVARIANTPAIRINPUTDIALOG_H

#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QUrl>
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class StringVariantPairInputDialog : public QDialog
{
    Q_OBJECT
    
    enum InputType {
        IT_INVALID = 0,
        IT_STRING,
        IT_NUMBER,
        IT_URL
    };
    
    static const QVector<std::pair<StringVariantPairInputDialog::InputType, QString>>& getInputTypeStringVector();
    
public:
    StringVariantPairInputDialog(QString &key,
                                 QVariant &value,
                                 QWidget *parent = nullptr);
    
public slots:
    void processAccept();
    
private:
    bool stringToVariantOfInputType(const InputType type,
                                    const QString &string,
                                    QVariant &variant);
    QVariant stringToNumberVariant(const QString &string);
    
private:
    QString  &m_key;
    QVariant &m_value;
    
    QLineEdit *m_keyLineEdit;
    QLineEdit *m_valueLineEdit;
    
    QComboBox *m_inputTypeComboBox;
    
    QPushButton *m_acceptButton;
    QPushButton *m_cancelButton;
};

#endif // STRINGVARIANTPAIRINPUTDIALOG_H
