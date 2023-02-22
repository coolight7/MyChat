#ifndef USERINFO_H
#define USERINFO_H
#include <QObject>
#include <QString>

class UserInfo_c:public QObject
{
    Q_OBJECT
public:
    UserInfo_c();

    UserInfo_c (int in_uid, const QString& in_userName, const QString& in_passwd, int in_state = 200) {
        uid = in_uid;
        userName    = in_userName;
        passwd      = in_passwd;
        state       = in_state;
    }

    static UserInfo_c* getInstance();


    int uid             = -1;
    QString userName    = "游客";       //用户名
    QString passwd      = "";          //密码
    QString img         = "gravatar.png"; //头像图
    int state           = -1;          //账号状态


    int getUid() const;
    void setUid(int newUid);
    const QString &getUserName() const;
    void setUserName(const QString &newUserName);

    const QString &getPasswd() const;
    void setPasswd(const QString &newPasswd);

    int getState() const;
    void setState(int newState);

    const QString &getImg() const;
    void setImg(const QString &newImg);

signals:
    void uidChanged();
    void userNameChanged();

    void passwdChanged();

    void stateChanged();

    void imgChanged();

private:
    Q_PROPERTY(int uid READ getUid WRITE setUid NOTIFY uidChanged)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString passwd READ getPasswd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(int state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString img READ getImg WRITE setImg NOTIFY imgChanged)
};

#endif // USERINFO_H
