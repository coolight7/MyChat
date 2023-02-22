QT += quick

QT += network

SOURCES += \
        chatfilterlistmodel.cpp \
        chatlist_c.cpp \
        chatpost.cpp \
        globalenum.cpp \
        initsocketobj.cpp \
        main.cpp \
        qmlfun.cpp \
        settingcontrolobj.cpp \
        socketlistmodel.cpp \
        socketserver.cpp \
        usercontrolobj.cpp \
        userinfo.cpp \
        userlistobj.cpp \
        userloginlistmodel.cpp

resources.files = main.qml \
    compoents/FooterBar.qml \
    compoents/ImgMask.qml \
    compoents/InitSocket.qml \
    compoents/LogListView.qml \
    compoents/SettingControl.qml \
    compoents/SettingList.qml \
    compoents/TipBar.qml \
    compoents/TitleBar.qml \
    compoents/UserControl.qml \
    compoents/UserList.qml \
    src/icon/bell_dark.svg \
    src/icon/bell_light.svg \
    src/icon/bug_dark.svg \
    src/icon/bug_light.svg \
    src/icon/settings_dark.svg \
    src/icon/settings_light.svg \
    src/icon/user_dark.svg \
    src/icon/user_light.svg \
    src/image/gravatar.png



resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    compoents/FooterBar.qml \
    compoents/ImgMask.qml \
    compoents/InitSocket.qml \
    compoents/LogListView.qml \
    compoents/SettingControl.qml \
    compoents/SettingList.qml \
    compoents/TipBar.qml \
    compoents/TitleBar.qml \
    compoents/UserControl.qml \
    compoents/UserList.qml \
    src/icon/bell_dark.svg \
    src/icon/bell_light.svg \
    src/icon/bug_dark.svg \
    src/icon/bug_light.svg \
    src/icon/settings_dark.svg \
    src/icon/settings_light.svg \
    src/icon/user_dark.svg \
    src/icon/user_light.svg \
    src/image/gravatar.png

HEADERS += \
    chatfilterlistmodel.h \
    chatlist_c.h \
    chatpost.h \
    globalenum.h \
    initsocketobj.h \
    qmlfun.h \
    settingcontrolobj.h \
    socketlistmodel.h \
    socketserver.h \
    usercontrolobj.h \
    userinfo.h \
    userlistobj.h \
    userloginlistmodel.h
