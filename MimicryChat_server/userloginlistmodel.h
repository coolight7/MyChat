#ifndef USERLOGINLISTMODEL_H
#define USERLOGINLISTMODEL_H

#include <QAbstractListModel>
#include "userinfo.h"
#include "usercontrolobj.h"


class UserLoginListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum User_Rolse {
        UID = Qt::DisplayRole + 1,
        USERNAME,
        PASSWD,
        IMG,
        STATE,
        ISLOGIN
    };
    static UserLoginListModel* getInstance();

    explicit UserLoginListModel(QObject *parent = nullptr);

    void remove(int in_uid, bool);
    void append(const UserInfo_c& in_user);
    Q_INVOKABLE void append(int in_uid, const QString& in_userName, const QString& in_passwd, int in_state = 200);
    Q_INVOKABLE void remove(int index);

    //设置账号状态
    bool setAccountState(int in_uid, int in_state);
    //恢复账号为正常状态
    bool setNormalAccount(int in_uid);
    //封禁账号
    bool setSealedAccount(int in_uid);
    //禁言
    bool setNomsgAccount(int in_uid);

    Q_INVOKABLE int getListSize();

    Q_INVOKABLE void setUserControl(int index);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    QList<UserInfo_c> m_data;
    QHash<int, QByteArray> m_roleNames;

};

#endif // USERLOGINLISTMODEL_H
