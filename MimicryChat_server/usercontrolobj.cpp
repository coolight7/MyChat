#include "usercontrolobj.h"



UserControlObj::UserControlObj()
{
    this->socketList = SocketListModel::getInstance();
}

UserControlObj *UserControlObj::getInstance()
{
    static UserControlObj* obj = new UserControlObj();
    return obj;
}

void UserControlObj::setUserInfo(const UserInfo_c &in_user, bool in_isLogin)
{
    this->setUid(in_user.uid);
    this->setUserName(in_user.userName);
    this->setImg(in_user.img);
    this->setPasswd(in_user.passwd);
    this->setState(in_user.state);
    this->setIsLogin(in_isLogin);
}

bool UserControlObj::getIsLogin() const
{
    return isLogin;
}

void UserControlObj::setIsLogin(bool newIsLogin)
{
    if (isLogin == newIsLogin)
        return;
    isLogin = newIsLogin;
    emit isLoginChanged();
}

void UserControlObj::setNormalAccount()
{
    if(this->state == ACCOUNT_NORMAL)
        return;
    else {
        auto it = socketList->m_data.begin();
        if(it != socketList->m_data.end()) {
            if((*it)->setNormalAccount(this->uid)) {
                setState(ACCOUNT_NORMAL);
            }
        }
    }
}

void UserControlObj::setSealedAccount()
{
    if(this->state == ACCOUNT_SEALED)
        return;
    else {
        auto it = socketList->m_data.begin();
        if(it != socketList->m_data.end()) {
            if((*it)->setSealedAccount(this->uid)) {
                setState(ACCOUNT_SEALED);
            }
        }
    }
}

void UserControlObj::setNomsgAccount()
{
    if(this->state == ACCOUNT_NOMSG)
        return;
    else {
        auto it = socketList->m_data.begin();
        if(it != socketList->m_data.end()) {
            if((*it)->setNomsgAccount(this->uid)) {
                setState(ACCOUNT_NOMSG);
            }
        }
    }
}

void UserControlObj::send_client_tip(const QString &in_msg)
{
    auto it = socketList->m_data.begin();
    if(it != socketList->m_data.end()) {
        (*it)->send_clientTip_toOne(this->uid, in_msg);
    }
}

int UserControlObj::getState() const
{
    return state;
}

void UserControlObj::setState(int newState)
{
    if (state == newState)
        return;
    state = newState;
    emit stateChanged();
}

const QString &UserControlObj::getImg() const
{
    return img;
}

void UserControlObj::setImg(const QString &newImg)
{
    if (img == newImg)
        return;
    img = newImg;
    emit imgChanged();
}

const QString &UserControlObj::getPasswd() const
{
    return passwd;
}

void UserControlObj::setPasswd(const QString &newPasswd)
{
    if (passwd == newPasswd)
        return;
    passwd = newPasswd;
    emit passwdChanged();
}

const QString &UserControlObj::getUserName() const
{
    return userName;
}

void UserControlObj::setUserName(const QString &newUserName)
{
    if (userName == newUserName)
        return;
    userName = newUserName;
    emit userNameChanged();
}

int UserControlObj::getUid() const
{
    return uid;
}

void UserControlObj::setUid(int newUid)
{
    if (uid == newUid)
        return;
    uid = newUid;
    emit uidChanged();
}
