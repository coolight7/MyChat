#ifndef ROOMLISTMODEL_H
#define ROOMLISTMODEL_H

#include <QAbstractListModel>
#include "socketclient.h"
#include "nowchatlistmodel.h"

class Room_c {
public:
    Room_c (int in_rid, const QString& in_rname, const QString& in_rimg = "gravatar.png", SocketClientThread* in_client = nullptr) {
        rid = in_rid;
        rname = in_rname;
        rimg = in_rimg;
        client = in_client;
    }

    int rid;
    QString rname;
    QString rimg;
    SocketClientThread* client = nullptr;
};


class RoomListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    static RoomListModel* getInstance();

    enum RoomInfo_Roles {
        RId = Qt::UserRole + 1,
        RName,
        RImg
    };

    explicit RoomListModel(QObject *parent = nullptr);

    bool changeRoomInfo(int in_rid, const QString& in_name, const QString& in_img);
    Q_INVOKABLE void send_close_client_click();

    void append(const Room_c& in_room);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int,QByteArray> roleNames() const override;

    NowChatListModel* nowChat = nullptr;

    QList<Room_c> m_data;
private:

    QHash<int, QByteArray> m_roleNames;

};

#endif // ROOMLISTMODEL_H
