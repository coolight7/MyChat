#ifndef USERCONTROLOBJ_H
#define USERCONTROLOBJ_H

#include <QObject>
#include <QString>

#include "userinfo.h"
#include "socketlistmodel.h"

class UserControlObj:public QObject
{
    Q_OBJECT
public:
    UserControlObj();

    static UserControlObj* getInstance();

    void setUserInfo(const UserInfo_c& in_user, bool in_isLogin);

    int uid     = -1;
    QString userName = "null";      //用户名
    QString passwd   = "null";      //密码
    QString img = "gravatar.png";   //头像图片
    bool isLogin = false;
    int state   = ACCOUNT_NORMAL;   //账号状态

    SocketListModel* socketList;

    //恢复账号为正常状态
    Q_INVOKABLE void setNormalAccount();
    //封禁账号
    Q_INVOKABLE void setSealedAccount();
    //禁言
    Q_INVOKABLE void setNomsgAccount();
    //发送提示
    Q_INVOKABLE void send_client_tip(const QString& in_msg);

    int getUid() const;
    void setUid(int newUid);
    const QString &getUserName() const;
    void setUserName(const QString &newUserName);

    const QString &getPasswd() const;
    void setPasswd(const QString &newPasswd);

    const QString &getImg() const;
    void setImg(const QString &newImg);

    int getState() const;
    void setState(int newState);

    bool getIsLogin() const;
    void setIsLogin(bool newIsLogin);

signals:
    void uidChanged();
    void userNameChanged();

    void passwdChanged();

    void imgChanged();

    void stateChanged();

    void isLoginChanged();

private:
    Q_PROPERTY(int uid READ getUid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString passwd READ getPasswd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(QString img READ getImg WRITE setImg NOTIFY imgChanged)
    Q_PROPERTY(int state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(bool isLogin READ getIsLogin WRITE setIsLogin NOTIFY isLoginChanged)
};

#endif // USERCONTROLOBJ_H
