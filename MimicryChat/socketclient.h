#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <QTcpSocket>
#include <QDebug>
#include <QThread>

#include "qmlfun.h"
#include "userinfo.h"
#include "globalenum.h"
#include "chatpost.h"
#include "nowchatlistmodel.h"

class RoomListModel;
class SocketClientThread;

class SocketClient: public QObject
{

public:
    SocketClient(SocketClientThread* in_clientThread);

    bool connectToHost(QString ip, int port);
    void readData();
    void writeData(const ChatPost_c& in_chat);
    void flush();


    QTcpSocket* m_TCPSocket         = nullptr;
    UserInfo_c* user                = nullptr;
    NowChatListModel* nowChatList   = nullptr;
    SocketClientThread* clientThread = nullptr;


    ~SocketClient(){
        m_TCPSocket->abort();
        delete[]m_TCPSocket;
    }
};

class SocketClientThread : public QThread
{
    Q_OBJECT
public:
    SocketClient* client = nullptr;
    int& state;
    QString ip = "127.0.0.1";
    int port = 7777;
    int waitTime = 500;


    void sendSignIn(const QString& in_userName, const QString& in_passwd) {
        QmlFun::tip("正在尝试登录...", 3000);
        client->writeData(ChatPost_c(SIGNIN_POST, in_userName + "&" + in_passwd));
    }
    void sendSignUp(const QString& in_userName, const QString& in_passwd) {
        QmlFun::tip("正在尝试注册...", 3000);
        client->writeData(ChatPost_c(SIGNUP_POST, in_userName + "&" + in_passwd));
    }
    void send_TCP_msg(int in_type, const QString &in_msg);
    void send_remove_msg(int mid);

    void send_close_client();



    SocketClientThread(const QString& in_ip, int in_port, int& in_state)
        :state(in_state) {
        state = 0;
        ip = in_ip;
        port = in_port;
        client = new SocketClient(this);
    }

    void run() override;

    ~SocketClientThread() {
        delete[]client;
    }

protected:


};


#endif // SOCKETCLIENT_H
