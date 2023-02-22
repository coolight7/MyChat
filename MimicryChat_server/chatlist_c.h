#ifndef CHATLIST_C_H
#define CHATLIST_C_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include <QList>

class Chat_c {
public:
    Chat_c (int in_mid, int in_uid, int in_type, const QString& in_content, int in_chatTime, int in_state) {
        mid     = in_mid;
        uid     = in_uid;
        type    = in_type;
        content = in_content;
        chatTime = in_chatTime;
        state   = in_state;
    }

    int mid;
    int uid;
    int type;
    QString content;
    int chatTime;
    int state;
};

class ChatList_c  : public QAbstractListModel
{
    Q_OBJECT
public:

    explicit ChatList_c(QObject *parent = nullptr);

    static ChatList_c* getInstance();

    enum ChatInfo_Roles {
        MID = Qt::DisplayRole + 1,
        UID,
        TYPE,
        CONTENT,
        CHATTIME,
        CSTATE
    };
    Q_INVOKABLE void send_remove_msg(int mid);

    bool changeItem_state(int mid, int in_state);
    void append(const Chat_c& in_chat);
    Q_INVOKABLE void append(int in_mid, int in_uid, int in_type, const QString& in_content, int in_chatTime, int in_state);
    Q_INVOKABLE void remove(int index);

    Q_INVOKABLE int getListSize();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<Chat_c> m_data;
private:

    QHash<int, QByteArray> m_roleNames;

};


#endif // CHATLIST_C_H
