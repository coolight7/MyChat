#include "userlistobj.h"

int UserListObj::startUid = -1;

UserListObj::UserListObj()
{
    userList.clear();

    m_roleNames.insert(UID, "uid");
    m_roleNames.insert(USERNAME, "userName");
    m_roleNames.insert(PASSWD, "passwd");
    m_roleNames.insert(IMG, "img");
    m_roleNames.insert(STATE, "state");
    m_roleNames.insert(ISLOGIN, "islogin");


    //读取用户列表信息
    userSetting = new QSettings("userList.ini", QSettings::IniFormat);
    userSetting->beginGroup("USER");
    if(userSetting->childKeys().contains("startUid")){   //如果存在startUid
        this->startUid = userSetting->value("startUid").toInt();
    } else {
        this->startUid = 100;
    }
    if(userSetting->childKeys().contains("userNum")) {    //如果存在,则读取除了
        int userNum = userSetting->value("userNum").toInt();
        for(int i = 0; i < userNum; ++i) {
            userList.push_back(UserInfo_c(
                                   userSetting->value("uid" + QString::number(i)).toInt(),
                                   userSetting->value("userName" + QString::number(i)).toString(),
                                   userSetting->value("passwd" + QString::number(i)).toString(),
                                   userSetting->value("img" + QString::number(i)).toString(),
                                   userSetting->value("state" + QString::number(i)).toInt()
                                   ));
        }
    }
    userSetting->endGroup();
}

UserListObj *UserListObj::getInstance()
{
    static UserListObj* obj = new UserListObj();
    return obj;
}

void UserListObj::append(int in_uid, const QString &in_userName, const QString &in_passwd, int in_state)
{
    emit beginInsertRows(QModelIndex(), userList.size(), userList.size());
    userList.push_back(UserInfo_c(in_uid, in_userName, in_passwd, in_state));
    emit endInsertRows();
}

void UserListObj::remove(int index)
{
    if(index < 0 || index >= userList.size())
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    userList.removeAt(index);
    emit endRemoveRows();
}

void UserListObj::setUserControl(int index)
{
    if(index < 0 || index >= userList.size())
        return;
    UserControlObj* userControl = UserControlObj::getInstance();
    userControl->setUserInfo(userList.at(index), false);
}

int UserListObj::getListSize()
{
    return userList.size();
}

int UserListObj::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return userList.count();
}

QVariant UserListObj::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case UID:{
        return userList[index.row()].uid;
    }break;
    case USERNAME:{
        return userList[index.row()].userName;
    }break;
    case IMG:{
        return userList[index.row()].img;
    }break;
    case PASSWD:{
        return userList[index.row()].passwd;
    }break;
    case STATE:{
        return userList[index.row()].state;
    }break;
    case ISLOGIN:{
        return userList[index.row()].isLogin;
    }break;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> UserListObj::roleNames() const
{
     return m_roleNames;
}


QVector<UserInfo_c>::Iterator UserListObj::getUserInfo(int in_uid)
{
    UserListObj* userList = UserListObj::getInstance();
    if(in_uid < STARTUID || in_uid >= startUid) {
        return userList->userList.end();
    }
    for(auto it = userList->userList.begin(), endit = userList->userList.end(); it != endit; ++it) {
        if((*it).uid == in_uid) {
            return it;
        }
    }
    return userList->userList.end();
}


void UserListObj::saveUserList() {
    userSetting->beginGroup("USER");
    userSetting->setValue("startUid", this->startUid);
    int len = userList.size();
    userSetting->setValue("userNum", len);
    for(int i = 0; i < len; ++i) {
        userSetting->setValue("uid" + QString::number(i), userList[i].uid);
        userSetting->setValue("userName" + QString::number(i), userList[i].userName);
        userSetting->setValue("passwd" + QString::number(i), userList[i].passwd);
        userSetting->setValue("img" + QString::number(i), userList[i].img);
        userSetting->setValue("state" + QString::number(i), userList[i].state);
    }
    userSetting->endGroup();
}
