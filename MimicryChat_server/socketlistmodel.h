#ifndef SOCKETLISTMODEL_H
#define SOCKETLISTMODEL_H

#include <QAbstractListModel>

#include "socketserver.h"

//服务端列表
class SocketListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SocketListModel(QObject *parent = nullptr);

    static SocketListModel* getInstance();



    enum SOCKETINFO_Roles{
        RNAME = Qt::DisplayRole + 1,
        RID,
        RIMG,
    };

    void append(SocketServer_c* in_room);
    void flushView(int index);

    Q_INVOKABLE void setRoomControl(int index);

    Q_INVOKABLE void saveChatList();
    Q_INVOKABLE void send_close_server_click();

    Q_INVOKABLE int getListSize();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

    QList<SocketServer_c*> m_data;

private:

    QHash<int, QByteArray> m_roleNames;

};

#endif // SOCKETLISTMODEL_H
