#ifndef SETTINGCONTROLOBJ_H
#define SETTINGCONTROLOBJ_H

#include <QObject>
#include <QString>
#include "socketserver.h"

class SettingControlObj:public QObject
{
    Q_OBJECT
public:
    SettingControlObj();

    static SettingControlObj* getInstance();

    void setRoomInfo(SocketServer_c* in_server);

    int     rid     = -1;
    QString rname   = "";
    QString rimg    = "gravatar.png";

    Q_INVOKABLE void saveEditInfo(const QString& in_rname, const QString& in_rimg);

    int getRid() const;
    void setRid(int newRid);
    const QString &getRname() const;
    void setRname(const QString &newRname);

    const QString &getRimg() const;
    void setRimg(const QString &newRimg);

    SocketServer_c* socketServer = nullptr;

signals:
    void ridChanged();
    void rnameChanged();

    void rimgChanged();

private:
    Q_PROPERTY(int rid READ getRid WRITE setRid NOTIFY ridChanged)
    Q_PROPERTY(QString rname READ getRname WRITE setRname NOTIFY rnameChanged)
    Q_PROPERTY(QString rimg READ getRimg WRITE setRimg NOTIFY rimgChanged)
};

#endif // SETTINGCONTROLOBJ_H
