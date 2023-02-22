#include "socketclient.h"
#include "roomlistmodel.h"
#include <QDateTime>


SocketClient::SocketClient(SocketClientThread* in_clientThread)
{
    m_TCPSocket = new QTcpSocket();
    user = UserInfo_c::getInstance();
    nowChatList = NowChatListModel::getInstance();
    clientThread = in_clientThread;
}

bool SocketClient::connectToHost(QString ip, int port)
{
    m_TCPSocket->abort();
    m_TCPSocket->connectToHost(ip, port);
    if(!m_TCPSocket->waitForConnected(30000)) {
        return false;
    }
    connect(m_TCPSocket, &QTcpSocket::readyRead, this, &SocketClient::readData);
    return true;
}

void SocketClient::readData()
{
    QByteArray buffer;
    buffer =  m_TCPSocket->readAll();

    qDebug() << buffer;

    QList<QByteArray> byteList  = buffer.split('|');


    switch(byteList[0].toInt()) {
    case CLIENT_SHOWTIP:{  //显示内容到提示栏
        QmlFun::tip(byteList[1], 3000);
    }break;
    case CLIENT_SETROOMINFO:{   //设置房间信息
        QList<QByteArray> conlist = (byteList[1]).split('&');
        (RoomListModel::getInstance())->append(Room_c(conlist[0].toInt(), conlist[1], conlist[2], this->clientThread));
    }break;
    case SIGNIN_SUCCESS:{ //登录成功
        QList<QByteArray> conlist = (byteList[1]).split('&');
        QmlFun::tip(conlist[1] + "登录成功", 3000);
        user->setUid(conlist[0].toInt());
        user->setUserName(conlist[1]);
        user->setPasswd(conlist[2]);
        user->setImg(conlist[3]);
        user->setState(conlist[4].toInt());
        QmlFun::callFun("loginSuccess");
        this->clientThread->state = 201;
    }break;
    case SIGNUP_SUCCESS:{   //注册成功
        QList<QByteArray> conlist = (byteList[1]).split('&');
        QmlFun::tip(conlist[1] + "注册成功", 3000);
        user->setUid(conlist[0].toInt());
        user->setUserName(conlist[1]);
        user->setPasswd(conlist[2]);
        user->setImg(conlist[3]);
        user->setState(conlist[4].toInt());
        QmlFun::callFun("loginSuccess");
        this->clientThread->state = 201;
    }break;
    case MSG_GET_TCP_MSG:{ //接收信息 包含 mid & uid & type & msg & time & state
        QList<QByteArray> conlist = (byteList[1]).split('&');
        nowChatList->append(Chat_c(
                                conlist[0].toInt(),
                                conlist[1].toInt(),
                                conlist[2].toInt(),
                                conlist[3],
                                conlist[4].toInt(),
                                conlist[5].toInt()));
        QmlFun::callFun("chatView_scrollToBottom");
    }break;
    case MSG_GET_REMOVE:{   //撤回信息
        QList<QByteArray> conlist = (byteList[1]).split('&');
        nowChatList->changeItem_state(conlist[0].toInt(), -100);
    }break;
    case SERVER_CLOSE:{     //服务端关闭连接
        QmlFun::tip(QString::number(this->clientThread->port) + " 房间已关闭", 3000);
        nowChatList->append(Chat_c(0, 0, MSG_TYPE_TIP,
                                   QString::number(this->clientThread->port) + " 房间已关闭",
                                   QDateTime::currentDateTime().currentSecsSinceEpoch(),
                                   200));
        this->m_TCPSocket->abort();
    }break;
    case CLIENT_TO_CLOSE:{      //服务端命令关闭客户端
        nowChatList->append(Chat_c(0, 0, MSG_TYPE_TIP,
                            byteList[1],
                            QDateTime::currentDateTime().currentSecsSinceEpoch(),
                            200));
        QmlFun::tip("您已被踢出 " + QString::number(this->clientThread->port) + " 房间", 3000);
        nowChatList->append(Chat_c(0, 0, MSG_TYPE_TIP,
                                   "您已被踢出 " + QString::number(this->clientThread->port) + " 房间",
                                   QDateTime::currentDateTime().currentSecsSinceEpoch(),
                                   200));
        this->clientThread->send_close_client();
        this->m_TCPSocket->abort();
    }break;
    case CLIENT_UPDATE_USERINFO:{   //更新用户信息
        QList<QByteArray> conlist = (byteList[1]).split('&');
        user->setUid(conlist[0].toInt());
        user->setUserName(conlist[1]);
        user->setPasswd(conlist[2]);
        user->setImg(conlist[3]);
        user->setState(conlist[4].toInt());
        QmlFun::callFun("chatPost_flushUserState");
    }break;
    case CLIENT_UPDATE_ROOMINFO:{   //更新房间信息
        QList<QByteArray> conlist = (byteList[1]).split('&');
        (RoomListModel::getInstance())->changeRoomInfo(conlist[0].toInt(), conlist[1], conlist[2]);
    }break;
    }
}

void SocketClient::writeData(const ChatPost_c& in_chat)
{
    m_TCPSocket->write((QString::number(in_chat.type) + "|" + in_chat.content).toUtf8());
    m_TCPSocket->flush();
}

void SocketClient::flush()
{
    m_TCPSocket->flush();
}


void SocketClientThread::send_TCP_msg(int in_type, const QString &in_msg)
{
    client->writeData(ChatPost_c(MSG_POST_TCP_MSG, QString::number(in_type) + "&" + in_msg));
}

void SocketClientThread::send_remove_msg(int in_mid)
{
    client->writeData(ChatPost_c(MSG_POST_REMOVE, QString::number(in_mid)));
}

void SocketClientThread::send_close_client()
{
    if(this->state == 201) {
        this->state = -100;
        client->writeData(ChatPost_c(CLIENT_CLOSE, ""));
    }else
        return;
}

void SocketClientThread::run()
{
    state = 100;
    QmlFun::tip("正在连接 " + QString::number(this->port), 3000);
    client->connectToHost(ip, port);
    if(!client->m_TCPSocket->waitForConnected(waitTime)) {
        state = -200;
        QmlFun::callFun("connectError");
        QmlFun::tip("连接失败" + QString::number(this->port), 3000);
        return;
    }
    state = 200;
    QmlFun::callFun("connectSuccess");
    QmlFun::tip("连接成功" + QString::number(this->port), 3000);
}
