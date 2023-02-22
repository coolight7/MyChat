#include "userinfo.h"

UserInfo_c::UserInfo_c()
{

}

UserInfo_c *UserInfo_c::getInstance()
{
    static UserInfo_c* obj = new UserInfo_c();
    return obj;
}

const QString &UserInfo_c::getImg() const
{
    return img;
}

void UserInfo_c::setImg(const QString &newImg)
{
    if (img == newImg)
        return;
    img = newImg;
    emit imgChanged();
}

int UserInfo_c::getState() const
{
    return state;
}

void UserInfo_c::setState(int newState)
{
    if (state == newState)
        return;
    state = newState;
    emit stateChanged();
}

const QString &UserInfo_c::getPasswd() const
{
    return passwd;
}

void UserInfo_c::setPasswd(const QString &newPasswd)
{
    if (passwd == newPasswd)
        return;
    passwd = newPasswd;
    emit passwdChanged();
}

const QString &UserInfo_c::getUserName() const
{
    return userName;
}

void UserInfo_c::setUserName(const QString &newUserName)
{
    if (userName == newUserName)
        return;
    userName = newUserName;
    emit userNameChanged();
}

int UserInfo_c::getUid() const
{
    return uid;
}

void UserInfo_c::setUid(int newUid)
{
    if (uid == newUid)
        return;
    uid = newUid;
    emit uidChanged();
}
