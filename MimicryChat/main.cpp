#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qmlfun.h"
#include "socketclient.h"
#include "roomlistmodel.h"
#include "nowchatlistmodel.h"
#include "loginobj.h"
#include "userinfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //QQmlContext* context = engine.rootContext();

    qmlRegisterSingletonInstance("NowChatListModel", 1, 0, "NowChatListModel", NowChatListModel::getInstance());
    qmlRegisterSingletonInstance("RoomListModel", 1, 0, "RoomListModel", RoomListModel::getInstance());
    qmlRegisterSingletonInstance("LoginObj", 1, 0, "LoginObj", LoginObj::getInstance());
    qmlRegisterSingletonInstance("UserInfo", 1, 0, "UserInfo", UserInfo_c::getInstance());

    const QUrl url(u"qrc:/MimicryChat/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {

        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    auto qmlList = engine.rootObjects();
    QmlFun::qml_mainWin = qmlList.first();

    return app.exec();
}
