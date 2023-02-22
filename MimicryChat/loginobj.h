#ifndef LOGINOBJ_H
#define LOGINOBJ_H
#include <QObject>
#include <QString>
#include "socketclient.h"

class LoginObj:public QObject
{
    Q_OBJECT
public:
    LoginObj();

    static LoginObj* getInstance();

    SocketClientThread* clientThread = nullptr;

    QString ip = "127.0.0.1";
    int state = 0;  //状态
    int port = 7777;

    QString userName;
    QString passwd;
    QString passwd1, passwd2;


    Q_INVOKABLE void clientConn_click();
    Q_INVOKABLE void signIn_click(const QVariant& in_userName, const QVariant& in_passwd);
    Q_INVOKABLE void signUp_click(const QVariant& in_userName, const QVariant& in_passwd);

    const QString &getUserName() const;
    void setUserName(const QString &newUserName);
    const QString &getPasswd() const;
    void setPasswd(const QString &newPasswd);

    const QString &getPasswd1() const;
    void setPasswd1(const QString &newPasswd1);

    const QString &getPasswd2() const;
    void setPasswd2(const QString &newPasswd2);

    int getPort() const;
    void setPort(int newPort);

signals:
    void userNameChanged();
    void passwdChanged();

    void passwd1Changed();

    void passwd2Changed();

    void portChanged();

private:
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString passwd READ getPasswd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(QString passwd1 READ getPasswd1 WRITE setPasswd1 NOTIFY passwd1Changed)
    Q_PROPERTY(QString passwd2 READ getPasswd2 WRITE setPasswd2 NOTIFY passwd2Changed)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
};

#endif // LOGINOBJ_H
