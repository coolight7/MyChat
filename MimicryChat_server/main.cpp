#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "qmlfun.h"
#include "socketserver.h"
#include "socketlistmodel.h"
#include "initsocketobj.h"
#include "userloginlistmodel.h"
#include "userlistobj.h"
#include "usercontrolobj.h"
#include "settingcontrolobj.h"
#include "chatfilterlistmodel.h"
#include "chatlist_c.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //QQmlContext* context = engine.rootContext();
    //导包名 主版本号 次版本号 使用时对象名
    qmlRegisterSingletonInstance("InitSocketObj",       1, 0, "InitSocketObj",          InitSocketObj::getInstance());
    qmlRegisterSingletonInstance("UserListObj",         1, 0, "UserListObj",            UserListObj::getInstance());
    qmlRegisterSingletonInstance("UserControlObj",      1, 0, "UserControlObj",         UserControlObj::getInstance());
    qmlRegisterSingletonInstance("SocketListModel",     1, 0, "SocketListModel",        SocketListModel::getInstance());
    qmlRegisterSingletonInstance("UserLoginListModel",  1, 0, "UserLoginListModel",     UserLoginListModel::getInstance());
    qmlRegisterSingletonInstance("SettingControlObj",   1, 0, "SettingControlObj",      SettingControlObj::getInstance());
    qmlRegisterSingletonInstance("ChatFilterListModel", 1, 0, "ChatFilterListModel",    ChatFilterListModel::getInstance());
    qmlRegisterSingletonInstance("ChatList",            1, 0, "ChatList",               ChatList_c::getInstance());


    const QUrl url(u"qrc:/MimicryChat_server/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto qmlList = engine.rootObjects();
    QmlFun::qml_mainWin = qmlList.first();

    return app.exec();
}
