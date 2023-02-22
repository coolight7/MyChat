#include "loginobj.h"
#include "roomlistmodel.h"
#include "qmlfun.h"

LoginObj::LoginObj()
{
}

LoginObj *LoginObj::getInstance()
{
    static LoginObj* obj = new LoginObj();
    return obj;
}

int LoginObj::getPort() const
{
    return port;
}

void LoginObj::setPort(int newPort)
{
    if (port == newPort)
        return;
    port = newPort;
    emit portChanged();
}

const QString &LoginObj::getPasswd2() const
{
    return passwd2;
}

void LoginObj::setPasswd2(const QString &newPasswd2)
{
    if (passwd2 == newPasswd2)
        return;
    passwd2 = newPasswd2;
    emit passwd2Changed();
}

const QString &LoginObj::getPasswd1() const
{
    return passwd1;
}

void LoginObj::setPasswd1(const QString &newPasswd1)
{
    if (passwd1 == newPasswd1)
        return;
    passwd1 = newPasswd1;
    emit passwd1Changed();
}

const QString &LoginObj::getPasswd() const
{
    return passwd;
}

void LoginObj::setPasswd(const QString &newPasswd)
{
    if (passwd == newPasswd)
        return;
    passwd = newPasswd;
    emit passwdChanged();
}

const QString &LoginObj::getUserName() const
{
    return userName;
}

void LoginObj::setUserName(const QString &newUserName)
{
    if (userName == newUserName)
        return;
    userName = newUserName;
    emit userNameChanged();
}

void LoginObj::clientConn_click()
{
    if(state == 100) {
        QmlFun::tip("正在连接" + QString::number(clientThread->port) + " 中...", 3000);
        return;
    }
    clientThread = new SocketClientThread(ip, port, state);
    clientThread->run();
}

void LoginObj::signIn_click(const QVariant& in_userName, const QVariant& in_passwd)
{
    clientThread->sendSignIn(in_userName.toString(), in_passwd.toString());
}

void LoginObj::signUp_click(const QVariant &in_userName, const QVariant &in_passwd)
{
    clientThread->sendSignUp(in_userName.toString(), in_passwd.toString());
}


