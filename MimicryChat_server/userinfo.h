#ifndef USERINFO_C_H
#define USERINFO_C_H

#include <QString>
#include "globalenum.h"



class UserInfo_c
{
public:
    UserInfo_c() {
        uid = -1;
        userName = "";
        passwd = "";
        state = -1;
        isLogin = false;
    }
    UserInfo_c (int in_uid, const QString& in_userName, const QString& in_passwd, int in_state = ACCOUNT_NORMAL) {
        uid         = in_uid;
        userName    = in_userName;
        passwd      = in_passwd;
        state       = in_state;
        isLogin     = false;
    }
    UserInfo_c (int in_uid, const QString& in_userName, const QString& in_passwd, const QString& in_img, int in_state = ACCOUNT_NORMAL) {
        uid         = in_uid;
        userName    = in_userName;
        passwd      = in_passwd;
        img         = in_img;
        state       = in_state;
        isLogin     = false;
    }

    int uid;
    QString userName;   //用户名
    QString passwd;     //密码
    QString img = "gravatar.png";   //头像图片
    int state;          //账号状态
    bool isLogin;       //是否已登录
};




#endif // USERINFO_C_H
