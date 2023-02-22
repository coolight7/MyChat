#ifndef USERLISTOBJ_H
#define USERLISTOBJ_H
#include <QObject>
#include <QString>
#include <QSettings>
#include <QMap>
#include <QAbstractListModel>

#include "userinfo.h"
#include "usercontrolobj.h"


class UserListObj: public QAbstractListModel
{
    Q_OBJECT
public:
    UserListObj();
    enum User_Rolse {
        UID = Qt::DisplayRole + 1,
        USERNAME,
        PASSWD,
        IMG,
        STATE,
        ISLOGIN
    };
    static UserListObj* getInstance();




    Q_INVOKABLE void append(int in_uid, const QString& in_userName, const QString& in_passwd, int in_state = 200);
    Q_INVOKABLE void remove(int index);

    Q_INVOKABLE void setUserControl(int index);

    Q_INVOKABLE int getListSize();

    QHash<int, QByteArray> m_roleNames;
    QList<UserInfo_c> userList;
    QSettings* userSetting;


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

#define STARTUID 100
    static int startUid;

    static QVector<UserInfo_c>::Iterator getUserInfo(int in_uid);


    Q_INVOKABLE void saveUserList();

    ~UserListObj() {
        saveUserList();
    }

};

#endif // USERLISTOBJ_H
