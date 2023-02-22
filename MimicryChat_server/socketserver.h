#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QVector>
#include <QSettings>

#include "globalenum.h"
#include "userinfo.h"
#include "chatpost.h"
#include "chatlist_c.h"

class SocketServer_c;

#define DEFOULT_ROOM_IMG "gravatar.png"

//用户连接
class UserSocket_c : public QObject {
public:
    UserSocket_c(QTcpSocket * in_TCPSocket, SocketServer_c* in_server) : QObject() {
        m_TCPSocket = in_TCPSocket;
        server = in_server;
    }

    void readData();
    void writeData(const ChatPost_c& in_chat);

    //发送提示栏提示
    void send_client_tip(const QString& in_msg);
    //发送消息
    void send_tcp_msg(int in_mid, int in_uid, int in_type, const QString& in_msg,qint64 in_time, int in_state);
    //发送消息提示
    void send_tcp_msg_tip(int in_mid, const QString &in_msg, qint64 in_time);
    //命令客户端关闭连接
    void send_toclose(const QString& in_msg);
    //刷新用户信息
    void send_update_userInfo();
    //让客户端新建房间信息
    void send_roomInfo(int in_port, const QString& name, const QString& img);
    //让客户端刷新房间信息
    void send_update_roomInfo(int in_port, const QString& name, const QString& img);

    QTcpSocket* m_TCPSocket;
    QList<UserInfo_c>::Iterator userInfoIt;
    SocketServer_c* server;
};

//服务端
class SocketServer_c: public QObject
{
public:
    SocketServer_c();

    //创建server
    bool ServerCreate(int point, const QString& in_name);
    void ServerNewConn();

    //发送聊天消息
    void send_tcp_msg(int in_uid, int in_type, const QString& in_msg,qint64 in_time, int in_state);
    //发送聊天消息提示
    void send_tcp_msg_tip(const QString &in_msg, qint64 in_time);
    //定点发送提示栏提示信息
    void send_clientTip_toOne(int in_uid, const QString& in_msg);
    //撤回信息
    bool send_remove_msg(int in_mid, int in_uid);
    //设置新房间信息
    void send_roomInfo();

    void send_update_roomInfo();

    //恢复账号为正常状态
    bool setNormalAccount(int in_uid);
    //封禁账号
    bool setSealedAccount(int in_uid);
    //禁言
    bool setNomsgAccount(int in_uid);

    void send_close_server();

    void read_chatList();
    void save_chatList();

#define MID_START 1000

    int startMid = MID_START;
    int port;
    QString name;
    QString img = DEFOULT_ROOM_IMG;

    QVector<UserSocket_c*>::Iterator getUserSocket(int in_uid);


    ChatList_c* chatlist;
    QSettings* chatlistSetting;

    ~SocketServer_c();
    QVector<UserSocket_c*> m_userList;

private:
    QTcpServer* m_TCPServer;

};

//服务端线程
class SocketServerThread_c:public QThread {
public:
    SocketServer_c *server = nullptr;
    int& state;
    /* state
     * 引用指示外部state
     *  200:创建成功
     *  -200：创建失败
    */
    QString name;
    int port;


    SocketServerThread_c(const QString& in_name ,int in_port, int& in_state)
        :state(in_state) {
        name = in_name;
        port = in_port;
    }

    void run () override;

    ~SocketServerThread_c() {
        delete[]server;
    }

};

#endif // SOCKETSERVER_H
