#ifndef GLOBALENUM_H
#define GLOBALENUM_H

enum GlobalEnum {
    ACCOUNT_NORMAL      = 200,          //账号状态正常
    ACCOUNT_SEALED      = 201,          //封禁（不可登录，发言等所有操作）
    ACCOUNT_NOMSG       = 202,          //禁言（可登录，可接收信息，但不可发言）

    SERVER_CLOSE        = 701,          //服务端关闭连接
    CLIENT_SHOWTIP      = 1001,         //让客户端显示提示
    CLIENT_SETROOMINFO  = 1002,         //让客户端设置房间信息
    CLIENT_CLOSE        = 1003,         //客户端下线请求信息
    CLIENT_TO_CLOSE     = 1004,         //服务端令客户端下线
    CLIENT_UPDATE_USERINFO = 1005,      //更新用户信息命令
    CLIENT_UPDATE_ROOMINFO = 1006,      //让客户端刷新房间信息

    SIGNIN_POST         = 1101,         //登录请求
    SIGNIN_SUCCESS      = 1102,         //登录成功
    SIGNUP_POST         = 1201,         //注册请求
    SIGNUP_SUCCESS      = 1202,         //注册成功
    MSG_POST_TCP_MSG    = 7001,         //发送普通文本聊天信息
    MSG_GET_TCP_MSG     = 7002,         //接收普通文本聊天信息
    MSG_POST_REMOVE     = 8001,         //请求撤回聊天信息
    MSG_GET_REMOVE      = 8002,         //接收撤回聊天信息的信号

    MSG_TYPE_TEXT       = 10001,        //聊天信息类型：普通文本
    MSG_TYPE_TIP        = 10010,        //聊天信息类型，提示信息
};


#endif // GLOBALENUM_H
