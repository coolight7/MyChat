#include "socketserver.h"
#include "socketlistmodel.h"
#include "initsocketobj.h"
#include "qmlfun.h"
#include "userlistobj.h"
#include "userloginlistmodel.h"
#include <QDateTime>
#include "socketlistmodel.h"
#include "chatfilterlistmodel.h"


SocketServer_c::SocketServer_c():QObject()
{
    m_TCPServer = new QTcpServer(this);
    m_userList.clear();
    chatlist = ChatList_c::getInstance();
}

bool SocketServer_c::ServerCreate(int in_port, const QString& in_name)
{
    if(m_TCPServer->listen(QHostAddress::Any, in_port))
    {
        QObject::connect(m_TCPServer, &QTcpServer::newConnection, this, &SocketServer_c::ServerNewConn);
        SocketListModel* socketList = SocketListModel::getInstance();
        socketList->append(this);
        this->port = in_port;
        this->name = in_name;
        chatlistSetting = new QSettings("chatList_" + QString::number(this->port) + ".ini", QSettings::IniFormat);
        this->read_chatList();
        return true;
    } else {
        return false;
    }
}

void SocketServer_c::ServerNewConn()
{
    QTcpSocket* socket = m_TCPServer->nextPendingConnection();
    UserSocket_c* userSocket = new  UserSocket_c(socket, this);
    //把新加入的连接添加到用户链表中
    m_userList.push_back(userSocket);
    QmlFun::addLog("有新连接加入...");
    //连接信号
    QObject::connect(socket, &QTcpSocket::readyRead, userSocket, &UserSocket_c::readData);

    //TODO 发送房间信息
    userSocket->send_roomInfo(this->port, this->name, this->img);
}

//in_time:时间戳，单位秒
void SocketServer_c::send_tcp_msg(int in_uid, int in_type, const QString& in_msg,qint64 in_time = -1, int in_state = 200)
{
    if(in_time < 0) {
        in_time = QDateTime::currentDateTime().currentSecsSinceEpoch();
    }
    int mid = startMid;
    ++startMid;
    chatlist->append(mid, in_uid, in_type, in_msg, in_time, in_state);
    //发送6部分信息，mid & uid & type & msg & time & state
    for(auto it = m_userList.begin(); it != m_userList.end(); ++it) {
        (*it)->send_tcp_msg(mid, in_uid, in_type, in_msg, in_time, in_state);
    }
}

void SocketServer_c::send_tcp_msg_tip(const QString &in_msg, qint64 in_time = -1)
{
    if(in_time < 0) {
        in_time = QDateTime::currentDateTime().currentSecsSinceEpoch();
    }
    int mid = startMid;
    ++startMid;
    chatlist->append(mid, 0, MSG_TYPE_TIP, in_msg, in_time, 200);
    //发送6部分信息，mid & uid & type & msg & time & state
    for(auto it = m_userList.begin(); it != m_userList.end(); ++it) {
        (*it)->send_tcp_msg_tip(mid,in_msg, in_time);
    }
}

void SocketServer_c::send_clientTip_toOne(int in_uid, const QString &in_msg)
{
    if(in_uid < 0)
        return;
    for(auto it = m_userList.begin(), endit = m_userList.end(); it != endit; ++it) {
        if(((*it)->userInfoIt)->uid == in_uid) {
            (*it)->send_client_tip(in_msg);
            return;
        }
    }
}

bool SocketServer_c::send_remove_msg(int in_mid, int in_uid)
{
    if(in_mid >= startMid || in_mid < 0) {  //mid不对，或者非本人发送，撤回失败
        return false;
    }
    //把信息state置为 -100 已撤回（删除）
    for(auto it = chatlist->m_data.begin(), endit = chatlist->m_data.end(); it != endit; ++it) {
        if((*it).mid == in_mid) {
            if(in_uid != 0 && (*it).uid != in_uid) {       //如果不是本人发的信息
                return false;
            }
            chatlist->changeItem_state(in_mid, -100);
            //发送2部分信息，mid & uid (要撤回的消息id，发起撤回的用户id)
            for(auto uit = m_userList.begin(); uit != m_userList.end(); ++uit) {
                (*uit)->writeData(ChatPost_c(MSG_GET_REMOVE,
                                             QString::number(in_mid) +
                                             "&" + QString::number(in_uid)
                                             ));
            }
            UserListObj* userListobj = UserListObj::getInstance();
            auto uinfoIt = userListobj->getUserInfo(in_uid);
            if(uinfoIt != userListobj->userList.end())
                this->send_tcp_msg_tip((*uinfoIt).userName + " 撤回了一条消息");
            else
                QmlFun::addLog("uid: " + QString::number(in_uid) + " 用户信息未找到");
            return true;
        } else if((*it).mid > in_mid) {
            return false;
        }
    }
    return false;
}

void SocketServer_c::send_roomInfo()
{
    for(auto it = m_userList.begin(), endit = m_userList.end(); it != endit; ++it) {
        (*it)->send_roomInfo(this->port, this->name, this->img);
    }
}

void SocketServer_c::send_update_roomInfo()
{
    for(auto it = m_userList.begin(), endit = m_userList.end(); it != endit; ++it) {
        (*it)->send_update_roomInfo(this->port, this->name, this->img);
    }
}

bool SocketServer_c::setNormalAccount(int in_uid)
{
    UserListObj* userListObj = UserListObj::getInstance();
    auto userObjIt = userListObj->getUserInfo(in_uid);
    if(userObjIt != userListObj->userList.end()) {   //如果设置成功
        userObjIt->state = ACCOUNT_NORMAL;
        auto uit = this->getUserSocket(in_uid);
        if(uit != m_userList.end()) {
            UserLoginListModel* userLoginlist = UserLoginListModel::getInstance();      //修改已登录用户列表信息
            userLoginlist->setNormalAccount(in_uid);
            (*uit)->send_update_userInfo();     //发送信号修改同步用户信息
        }
        QmlFun::addLog(userObjIt->userName + " 账号状态恢复正常");
        return true;
    } else {
        return false;
    }
}

bool SocketServer_c::setSealedAccount(int in_uid)
{
    UserListObj* userListObj = UserListObj::getInstance();
    auto userObjIt = userListObj->getUserInfo(in_uid);
    if(userObjIt != userListObj->userList.end()) {   //如果设置成功
        userObjIt->state = ACCOUNT_SEALED;
        auto uit = this->getUserSocket(in_uid);
        if(uit != m_userList.end()) {
            UserLoginListModel* userLoginlist = UserLoginListModel::getInstance();      //修改已登录用户列表信息
            userLoginlist->setSealedAccount(in_uid);
            (*uit)->send_toclose("您已被封禁");
        }
        QmlFun::addLog(userObjIt->userName + " 已封禁");
        return true;
    } else {
        return false;
    }
}

bool SocketServer_c::setNomsgAccount(int in_uid)
{
    UserListObj* userListObj = UserListObj::getInstance();
    auto userObjIt = userListObj->getUserInfo(in_uid);
    if(userObjIt != userListObj->userList.end()) {   //如果设置成功
        userObjIt->state = ACCOUNT_NOMSG;
        auto uit = this->getUserSocket(in_uid);
        if(uit != m_userList.end()) {
            UserLoginListModel* userLoginlist = UserLoginListModel::getInstance();      //修改已登录用户列表信息
            userLoginlist->setNomsgAccount(in_uid);
            (*uit)->send_update_userInfo();     //发送信号修改同步用户信息
        }
        QmlFun::addLog(userObjIt->userName + " 已禁言");
        return true;
    }else {
        return false;
    }
}

void SocketServer_c::send_close_server()
{
    for(auto it = m_userList.begin(); it != m_userList.end(); ++it) {
        (*it)->writeData(ChatPost_c(SERVER_CLOSE, ""));
    }
}

void SocketServer_c::read_chatList()
{
    chatlistSetting->beginGroup("CHATLIST");
    if(chatlistSetting->childKeys().contains("startMid")) {
        startMid = chatlistSetting->value("startMid").toInt();
    }
    if(chatlistSetting->childKeys().contains("chatNum")) {      //如果存在chatNum
        int smid = MID_START, num = 0;
        int chatNum = chatlistSetting->value("chatNum").toInt();
        if(chatNum > 100) {
            num = 100;
            smid = MID_START + chatNum - 100;
        } else {
            num = chatNum;
        }
        for(; num-- > 0; ++smid) {
            chatlist->append(
                              smid,
                              chatlistSetting->value("uid" + QString::number(smid)).toInt(),
                              chatlistSetting->value("type" + QString::number(smid)).toInt(),
                              chatlistSetting->value("content" + QString::number(smid)).toString(),
                              chatlistSetting->value("chatTime" + QString::number(smid)).toInt(),
                              chatlistSetting->value("state" + QString::number(smid)).toInt()
                              );
        }
    }
    chatlistSetting->endGroup();
}

void SocketServer_c::save_chatList()
{
    chatlistSetting->beginGroup("CHATLIST");
    chatlistSetting->setValue("startMid", startMid);
    chatlistSetting->setValue("chatNum", chatlist->m_data.size());
    for(auto it =  chatlist->m_data.begin(), endit = chatlist->m_data.end();
        it != endit;
        ++it) {
        int mid = (*it).mid;
        chatlistSetting->setValue("uid"      + QString::number(mid), (*it).uid);
        chatlistSetting->setValue("type"     + QString::number(mid), (*it).type);
        chatlistSetting->setValue("content"  + QString::number(mid), (*it).content);
        chatlistSetting->setValue("chatTime" + QString::number(mid), (*it).chatTime);
        chatlistSetting->setValue("state"    + QString::number(mid), (*it).state);
    }
    chatlistSetting->endGroup();
}

QVector<UserSocket_c*>::Iterator SocketServer_c::getUserSocket(int in_uid)
{
    if(in_uid < 0)
        return m_userList.end();
    for(auto it = this->m_userList.begin(), endit = m_userList.end(); it != endit; ++it) {
        if(in_uid == (*((*it)->userInfoIt)).uid) {
            return it;
        }
    }
    return m_userList.end();
}


SocketServer_c::~SocketServer_c()
{
    for(auto it = m_userList.begin(); it != m_userList.end(); ++it) {
        delete[](*it);
    }
    m_userList.clear();
    m_TCPServer->close();
    m_TCPServer->deleteLater();
}

//---------UserSocket_c--------

void UserSocket_c::readData()
{
    QByteArray buffer;
    buffer =  m_TCPSocket->readAll();

    QList<QByteArray> byteList  = buffer.split('|');

    QmlFun::addLog("请求：type=" + byteList[0] + " content=" + byteList[1]);

    switch(byteList[0].toInt()) {
    case SIGNIN_POST:{  //登录请求
        QString uname, passwd;
        QList<QByteArray> conlist = (byteList[1]).split('&');
        uname = conlist[0];
        passwd = conlist[1];
        QList<UserInfo_c>* userList = &(UserListObj::getInstance()->userList);
        for(auto it = userList->begin(); it != userList->end(); ++it) {
            if((*it).userName == uname) {
                if( (*it).state == ACCOUNT_SEALED) {    //不能是封禁状态
                    send_client_tip("该账号已被封禁");
                    return;
                }
                if((*it).passwd == passwd) { //登录成功
                    QmlFun::addLog(uname + " 登录成功");
                    (*it).isLogin = true;
                    this->userInfoIt = it;
                    UserLoginListModel* userLogin = UserLoginListModel::getInstance();
                    userLogin->append((*it));
                    writeData(ChatPost_c(SIGNIN_SUCCESS,      //返回5部分数据：uid & userName & passwd & img & state
                                         QString::number((*it).uid) +
                                         "&" + (*it).userName +
                                         "&" + (*it).passwd +
                                         "&" + (*it).img +
                                         "&" + QString::number((*it).state)
                                         ));
                    this->server->send_tcp_msg_tip((*it).userName + " 进入房间");
                } else { //密码错误
                    QmlFun::addLog(uname + " 登录失败，密码错误");
                    send_client_tip("登录失败，密码错误");
                }
                return;
            }
        }
        //未注册
        QmlFun::addLog(uname + " 登录失败，账号不存在");
        send_client_tip("登录失败，请先注册账号");
    }break;
    case SIGNUP_POST:{  //注册请求
        QString uname, passwd;
        QList<QByteArray> conlist = (byteList[1]).split('&');
        uname = conlist[0];
        passwd = conlist[1];
        UserListObj* ulistObj = UserListObj::getInstance();
        QList<UserInfo_c>* userList = &(ulistObj->userList);
        for(auto it = userList->begin(); it != userList->end(); ++it) {
            if((*it).userName == uname) {       //已经存在用户
                QmlFun::addLog(uname + " 注册失败，用户名已经存在");
                send_client_tip("注册失败，用户名已经存在");
                return;
            }
        }
        UserInfo_c user = UserInfo_c(ulistObj->startUid, uname, passwd);
        (ulistObj->startUid)++;
        user.isLogin = true;
        userList->push_back(user);
        this->userInfoIt = userList->end() - 1;
        UserLoginListModel* userLogin = UserLoginListModel::getInstance();
        userLogin->append(user);
        writeData(ChatPost_c(SIGNUP_SUCCESS,      //返回5部分数据：uid & userName & passwd & img & state
                             QString::number(user.uid) +
                             "&" + user.userName +
                             "&" + user.passwd +
                             "&" + user.img +
                             "&" + QString::number(user.state)
                             ));
        this->server->send_tcp_msg_tip(user.userName + " 进入房间");
    }break;
    case MSG_POST_TCP_MSG:{    //发送普通文本聊天信息
        QList<QByteArray> conlist = (byteList[1]).split('&');
        int uid = (*(this->userInfoIt)).uid, state = (*(this->userInfoIt)).state;
        if(state == ACCOUNT_SEALED) {
            send_client_tip("该账号已被封禁");
            return;
        } else if(state == ACCOUNT_NOMSG) {
            send_client_tip("您已被禁言");
            return;
        }
        //转发给所有连接的客户端
        this->server->send_tcp_msg(uid, conlist[0].toInt(), ChatFilterListModel::filterStr(conlist[1]));
    }break;
    case MSG_POST_REMOVE:{       //撤回聊天信息
        int in_mid = byteList[1].toInt();
        if(this->server->send_remove_msg(in_mid, (*(this->userInfoIt)).uid) == false) {
            this->send_client_tip("撤回失败");
        }
        QmlFun::addLog((*(this->userInfoIt)).userName + " 撤回一条信息");
    }break;
    case CLIENT_CLOSE:{         //客户端关闭连接
        UserLoginListModel* userLoginList = UserLoginListModel::getInstance();
        userLoginList->remove((*(this->userInfoIt)).uid, true);
        QmlFun::addLog((*(this->userInfoIt)).userName + " 退出房间");
        this->server->send_tcp_msg_tip((*(this->userInfoIt)).userName + " 进入房间");
    }break;
    }
}

void UserSocket_c::writeData(const ChatPost_c& in_chat)
{
    m_TCPSocket->write((QString::number(in_chat.type) + "|" + in_chat.content).toUtf8());
    m_TCPSocket->flush();
}

void UserSocket_c::send_client_tip(const QString &in_msg)
{
    writeData(ChatPost_c(CLIENT_SHOWTIP, in_msg));
}

void UserSocket_c::send_tcp_msg(int in_mid, int in_uid, int in_type, const QString &in_msg, qint64 in_time = -1, int in_state = 200)
{
    if(in_time < 0) {
        in_time = QDateTime::currentDateTime().currentSecsSinceEpoch();
    }
    writeData(ChatPost_c(MSG_GET_TCP_MSG,
                                 QString::number(in_mid) +      //startMid,先取值，再++
                                 "&" + QString::number(in_uid) +
                                 "&" + QString::number(in_type) +
                                 "&" + in_msg +
                                 "&" + QString::number(in_time) +
                                 "&" + QString::number(in_state)
                         ));
}

void UserSocket_c::send_tcp_msg_tip(int in_mid, const QString &in_msg, qint64 in_time = -1)
{
    if(in_time < 0) {
        in_time = QDateTime::currentDateTime().currentSecsSinceEpoch();
    }
    writeData(ChatPost_c(MSG_GET_TCP_MSG,
                                 QString::number(in_mid) +
                                 "&0&" + QString::number(MSG_TYPE_TIP) +
                                 "&" + in_msg +
                                 "&" + QString::number(in_time) +
                                 "&200"
                         ));
}

void UserSocket_c::send_toclose(const QString& in_msg)
{
    writeData(ChatPost_c(CLIENT_TO_CLOSE, in_msg));
}

void UserSocket_c::send_update_userInfo()
{
    writeData(ChatPost_c(CLIENT_UPDATE_USERINFO,       //返回5部分数据：uid & userName & passwd & img & state
                         QString::number((*(this->userInfoIt)).uid) +
                         "&" + (*(this->userInfoIt)).userName +
                         "&" + (*(this->userInfoIt)).passwd +
                         "&" + (*(this->userInfoIt)).img +
                         "&" + QString::number((*(this->userInfoIt)).state)
                         ));
}

void UserSocket_c::send_roomInfo(int in_port, const QString& name, const QString& img)
{
    //发送房间信息
    this->writeData(ChatPost_c(CLIENT_SETROOMINFO,  QString::number(in_port) + "&" + name + "&" + img));
}

void UserSocket_c::send_update_roomInfo(int in_port, const QString& name, const QString& img)
{
    this->writeData(ChatPost_c(CLIENT_UPDATE_ROOMINFO,
                               QString::number(in_port) + "&" + name + "&" + img ));
}

void SocketServerThread_c::run()
{
    state = 100;
    server = new SocketServer_c();
    if(server->ServerCreate(this->port, this->name)) {
        //成功
        QmlFun::tip("创建成功 port=" + QString::number(this->port), 3000);
        QmlFun::addLog("创建房间成功，房间号：" + QString::number(this->port));
        QmlFun::callFun("createSuccess");
        state = 200;
    } else {
        QmlFun::tip("创建失败 port=" + QString::number(this->port), 3000);
        QmlFun::addLog("创建房间失败，房间号：" + QString::number(this->port));
        //失败
        state = -200;
        return;
    }
}
