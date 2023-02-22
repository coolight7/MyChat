#ifndef CHATFILTERLISTMODEL_H
#define CHATFILTERLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QSettings>
#include <QVector>

class ChatFilterListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Filter_Roles {
        STR = Qt::DisplayRole + 1
    };

    explicit ChatFilterListModel(QObject *parent = nullptr);

    static ChatFilterListModel* getInstance();

    void readSetting();
    Q_INVOKABLE void saveSetting();

    static QString filterStr(const QString& in_str);

    Q_INVOKABLE void append(const QString& in_str);
    Q_INVOKABLE void remove(int index);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QSettings* setting = nullptr;
    QList<QString> filterList;
    QHash<int, QByteArray> m_roleNames;

};

#endif // CHATFILTERLISTMODEL_H
