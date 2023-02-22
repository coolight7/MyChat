#include "nowchatlistmodel.h"
#include "roomlistmodel.h"

NowChatListModel *NowChatListModel::getInstance()
{
    static NowChatListModel* obj = new NowChatListModel();
    return obj;
}

NowChatListModel::NowChatListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.clear();

    m_roleNames.insert(MID, "mid");
    m_roleNames.insert(UID, "uid");
    m_roleNames.insert(TYPE, "type");
    m_roleNames.insert(CONTENT, "content");
    m_roleNames.insert(CHATTIME, "chattime");
    m_roleNames.insert(CSTATE, "cstate");
    //TODO 导入历史记录
}

bool NowChatListModel::changeItem_state(int in_mid, int in_state)
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

void NowChatListModel::append(const Chat_c &in_chat)
{
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(in_chat);
    emit endInsertRows();
}

void NowChatListModel::append(int in_mid, int in_uid, int in_type, const QString &in_content, int in_chatTime, int in_state)
{
    Chat_c chat(in_mid, in_uid, in_type, in_content, in_chatTime, in_state);
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(chat);
    emit endInsertRows();
}

void NowChatListModel::remove(int index)
{
    if(index < 0 || index >= m_data.size())
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
}

void NowChatListModel::send_TCP_msg_click(int in_type, const QString &in_msg)
{
    (*(this->roomIt)).client->send_TCP_msg(in_type, in_msg);
}

void NowChatListModel::send_TCP_text_click(const QString &in_msg)
{
    this->send_TCP_msg_click(MSG_TYPE_TEXT, in_msg);
}

void NowChatListModel::send_remove_msg_click(int in_mid)
{
    (*(this->roomIt)).client->send_remove_msg(in_mid);
}

int NowChatListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant NowChatListModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> NowChatListModel::roleNames() const
{
    return m_roleNames;
}
