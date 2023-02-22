#ifndef INITSOCKETOBJ_H
#define INITSOCKETOBJ_H

#include <QObject>
#include "socketserver.h"

class InitSocketObj:public QObject
{
    Q_OBJECT
public:
    InitSocketObj();

    static InitSocketObj* getInstance();

    int     state   = 0;        //状态
    QString name    = "牛马一家亲";   //房间名
    int     rid     = 7777;     //房间id，端口号
    SocketServerThread_c* serverThread = nullptr;


    Q_INVOKABLE void create();


    const QString &getName() const;
    void setName(const QString &newName);
    int getRid() const;
    void setRid(int newRid);

signals:
    void nameChanged();
    void ridChanged();


private:
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int rid READ getRid WRITE setRid NOTIFY ridChanged)
};

#endif // INITSOCKETOBJ_H
