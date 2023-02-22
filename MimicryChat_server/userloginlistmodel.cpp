#include "userloginlistmodel.h"
#include "userlistobj.h"


UserLoginListModel *UserLoginListModel::getInstance()
{
    static UserLoginListModel* obj = new UserLoginListModel();
    return obj;
}

UserLoginListModel::UserLoginListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.clear();

    m_roleNames.insert(UID, "uid");
    m_roleNames.insert(USERNAME, "userName");
    m_roleNames.insert(PASSWD, "passwd");
    m_roleNames.insert(IMG, "img");
    m_roleNames.insert(STATE, "state");
    m_roleNames.insert(ISLOGIN, "islogin");
}

void UserLoginListModel::remove(int in_uid, bool)
{
    if(in_uid < 0)
        return;
    int i = 0;
    for(auto it = m_data.begin(), endit = m_data.end(); it != endit; ++it, ++i) {
        if((*it).uid == in_uid) {
            this->remove(i);
        }
    }
}

void UserLoginListModel::append(const UserInfo_c &in_user)
{
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(in_user);
    emit endInsertRows();
}

void UserLoginListModel::append(int in_uid, const QString &in_userName, const QString &in_passwd, int in_state)
{
    emit beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(UserInfo_c(in_uid, in_userName, in_passwd, in_state));
    emit endInsertRows();
}

void UserLoginListModel::remove(int index)
{
    if(index < 0 || index >= m_data.size())
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
}

bool UserLoginListModel::setAccountState(int in_uid, int in_state)
{
    if(in_uid < 0)
        return false;
    int i = 0;
    for(auto it = m_data.begin(), endit = m_data.end(); it != endit; ++it, ++i) {
        if((*it).uid == in_uid) {
            (*it).state = in_state;
            return true;
        }
    }
    return false;
}

bool UserLoginListModel::setNormalAccount(int in_uid)
{
    return this->setAccountState(in_uid, ACCOUNT_NORMAL);
}
//封禁
bool UserLoginListModel::setSealedAccount(int in_uid)
{
    return this->setAccountState(in_uid, ACCOUNT_SEALED);
}

bool UserLoginListModel::setNomsgAccount(int in_uid)
{
    return this->setAccountState(in_uid, ACCOUNT_NOMSG);
}

int UserLoginListModel::getListSize()
{
    return m_data.size();
}

void UserLoginListModel::setUserControl(int index)
{
    if(index < 0 || index >= m_data.size())
        return;
    UserControlObj* userControl = UserControlObj::getInstance();
    userControl->setUserInfo(m_data.at(index), true);
}


int UserLoginListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant UserLoginListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case UID:{
        return m_data[index.row()].uid;
    }break;
    case USERNAME:{
        return m_data[index.row()].userName;
    }break;
    case IMG:{
        return m_data[index.row()].img;
    }break;
    case PASSWD:{
        return m_data[index.row()].passwd;
    }break;
    case STATE:{
        return m_data[index.row()].state;
    }break;
    case ISLOGIN:{
        return m_data[index.row()].isLogin;
    }break;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> UserLoginListModel::roleNames() const
{
     return m_roleNames;
}
