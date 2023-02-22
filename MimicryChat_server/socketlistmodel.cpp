#include "socketlistmodel.h"
#include "settingcontrolobj.h"

SocketListModel::SocketListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames.insert(RNAME, "rname");
    m_roleNames.insert(RID, "rid");
    m_roleNames.insert(RIMG, "rimg");
}

SocketListModel *SocketListModel::getInstance()
{
    static SocketListModel* obj = new SocketListModel();
    return obj;
}

void SocketListModel::append(SocketServer_c *in_room)
{
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(in_room);
    emit endInsertRows();
}

void SocketListModel::flushView(int index)
{
    if(index < 0 || index >= m_data.size())
        return;
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), {RNAME, RIMG});
}

void SocketListModel::setRoomControl(int index)
{
    if(index < 0 || index >= m_data.size())
        return;
    SettingControlObj* settingControl = SettingControlObj::getInstance();
    auto item = m_data.at(index);
    settingControl->setRoomInfo(item);
}

void SocketListModel::saveChatList()
{
    for(auto it = m_data.begin(), endit = m_data.end(); it != endit; ++it) {
        (*it)->save_chatList();
    }
}

void SocketListModel::send_close_server_click()
{
    for(auto it = m_data.begin(), endit = m_data.end(); it != endit; ++it) {
        (*it)->send_close_server();
    }
}

int SocketListModel::getListSize()
{
    return m_data.size();
}

int SocketListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant SocketListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case RNAME:{
        return m_data[index.row()]->name;
    }break;
    case RID:{
        return m_data[index.row()]->port;
    }break;
    case RIMG:{
        return m_data[index.row()]->img;
    }break;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> SocketListModel::roleNames() const
{
    return m_roleNames;
}
