#ifndef NOWCHATLISTMODEL_H
#define NOWCHATLISTMODEL_H

#include <QAbstractListModel>

class Room_c;

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



class NowChatListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ChatInfo_Roles {
        MID = Qt::DisplayRole + 1,
        UID,
        TYPE,
        CONTENT,
        CHATTIME,
        CSTATE
    };

    static NowChatListModel* getInstance();

    explicit NowChatListModel(QObject *parent = nullptr);

    bool changeItem_state(int mid, int in_state);
    void append(const Chat_c& in_chat);
    Q_INVOKABLE void append(int in_mid, int in_uid, int in_type, const QString& in_content, int in_chatTime, int in_state);
    Q_INVOKABLE void remove(int index);

    Q_INVOKABLE void send_TCP_msg_click(int in_type, const QString& in_msg);
    Q_INVOKABLE void send_TCP_text_click(const QString& in_msg);
    Q_INVOKABLE void send_remove_msg_click(int in_mid);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<Room_c>::Iterator roomIt;
private:
    QList<Chat_c> m_data;
    QHash<int, QByteArray> m_roleNames;


};

#endif // NOWCHATLISTMODEL_H
