#include "chatlist_c.h"
#include "socketlistmodel.h"
#include "qmlfun.h"

ChatList_c::ChatList_c(QObject *parent)
    : QAbstractListModel(parent) {
    m_data.clear();

    m_roleNames.insert(MID, "mid");
    m_roleNames.insert(UID, "uid");
    m_roleNames.insert(TYPE, "type");
    m_roleNames.insert(CONTENT, "content");
    m_roleNames.insert(CHATTIME, "chattime");
    m_roleNames.insert(CSTATE, "cstate");

}

ChatList_c *ChatList_c::getInstance()
{
    static ChatList_c* obj = new ChatList_c();
    return obj;
}

void ChatList_c::send_remove_msg(int mid)
{
    SocketListModel* socketList = SocketListModel::getInstance();
    auto it = socketList->m_data.begin(), endit = socketList->m_data.end();
    if(it != endit) {
        (*it)->send_remove_msg(mid, 0);
    }
}

bool ChatList_c::changeItem_state(int in_mid, int in_state)
{
    if(in_mid <= 0 || m_data.size() <= 0)
        return false;
    int i = 0;
    for(auto it = m_data.begin(); it != m_data.end(); ++it, ++i) {
        if((*it).mid == in_mid)      //找到了对应的信息
        {
            (*it).state = in_state;
            emit dataChanged(createIndex(i, 0), createIndex(i, 0), {CSTATE});
            return true;
        }else if((*it).mid > in_mid) {
            return false;
        }
    }
    return false;
}

void ChatList_c::append(const Chat_c &in_chat)
{
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(in_chat);
    emit endInsertRows();
}

void ChatList_c::append(int in_mid, int in_uid, int in_type, const QString &in_content, int in_chatTime, int in_state)
{
    Chat_c chat(in_mid, in_uid, in_type, in_content, in_chatTime, in_state);
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(chat);
    emit endInsertRows();
    QmlFun::callFun("chatListScrollToEnd");
}

void ChatList_c::remove(int index)
{
    if(index < 0 || index >= m_data.size())
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
}

int ChatList_c::getListSize()
{
    return m_data.size();
}

int ChatList_c::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant ChatList_c::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case MID:{
        return m_data[index.row()].mid;
    }break;
    case UID:{
        return m_data[index.row()].uid;
    }break;
    case TYPE:{
        return m_data[index.row()].type;
    }break;
    case CONTENT:{
        return m_data[index.row()].content;
    }break;
    case CHATTIME:{
        return m_data[index.row()].chatTime;
    }break;
    case CSTATE:{
        return m_data[index.row()].state;
    }break;
    }

    return QVariant();
}

QHash<int, QByteArray> ChatList_c::roleNames() const
{
    return m_roleNames;
}
