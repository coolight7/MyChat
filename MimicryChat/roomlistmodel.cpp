#include "roomlistmodel.h"

RoomListModel *RoomListModel::getInstance()
{
    static RoomListModel* obj = new RoomListModel();
    return obj;
}

RoomListModel::RoomListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.clear();

    nowChat = NowChatListModel::getInstance();

    m_roleNames.insert(RId, "rid");
    m_roleNames.insert(RName, "rname");
    m_roleNames.insert(RImg, "rimg");

}

bool RoomListModel::changeRoomInfo(int in_rid, const QString &in_name, const QString &in_img)
{
    if(in_rid <= 0 || m_data.size() <= 0)
        return false;

    int i = 0;
    for(auto it = m_data.begin(); it != m_data.end(); ++it, ++i) {
        if((*it).rid == in_rid)      //找到了对应的信息
        {
            (*it).rname = in_name;
            (*it).rimg  = in_img;
            emit dataChanged(createIndex(i, 0), createIndex(i, 0), {RName, RImg});
            return true;
        }else if((*it).rid > in_rid) {
            return false;
        }
    }
    return false;

}

void RoomListModel::send_close_client_click()
{
    for(auto it = m_data.begin(), endit = m_data.end(); it != endit; ++it) {
        (*it).client->send_close_client();
    }
}

void RoomListModel::append(const Room_c &in_room)
{
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(in_room);
    emit endInsertRows();
    auto it = m_data.end() - 1;
    if(m_data.size() == 1) {    //只有一个房间
        nowChat->roomIt = it;
    }
}

int RoomListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant RoomListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case RId:{
        return m_data[index.row()].rid;
    }break;
    case RName:{
        return m_data[index.row()].rname;
    }break;
    case RImg:{
        return m_data[index.row()].rimg;
    }break;
    }

    return QVariant();
}

QHash<int, QByteArray> RoomListModel::roleNames() const
{
    return m_roleNames;
}
