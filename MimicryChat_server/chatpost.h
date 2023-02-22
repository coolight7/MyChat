#ifndef CHATPOST_H
#define CHATPOST_H
#include <QString>

class ChatPost_c
{
public:
    ChatPost_c(int in_type, const QString& in_content);

    //消息类型
    int type;
    //内容
    QString content;

};

#endif // CHATPOST_H
