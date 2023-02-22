#ifndef QMLFUN_H
#define QMLFUN_H

#include <QString>
#include <QObject>
#include <QVariant>

class QmlFun
{
public:
    QmlFun();

    static void tip(const QString& in_str, int in_time) {
        QVariant arg_1 = in_str;
        QVariant arg_2 = in_time;
        QMetaObject::invokeMethod(qml_mainWin, "tip", Q_ARG(QVariant, arg_1), Q_ARG(QVariant, arg_2));
    }

    static void callFun(const QString& in_funName) {
        QMetaObject::invokeMethod(qml_mainWin, in_funName.toLatin1().constData());
    }

    static QObject* qml_mainWin;

};

#endif // QMLFUN_H
