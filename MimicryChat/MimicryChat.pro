QT += quick
QT += network

SOURCES += \
        chatpost.cpp \
        globalenum.cpp \
        loginobj.cpp \
        main.cpp \
        nowchatlistmodel.cpp \
        qmlfun.cpp \
        roomlistmodel.cpp \
        socketclient.cpp \
        userinfo.cpp

resources.files = main.qml \
components/ChatPost.qml \
components/ChatView.qml \
components/Content.qml \
components/ImgMask.qml \
components/Login.qml \
components/RoomList.qml \
components/TipBar.qml \
components/UserBar.qml \
src/icon/bell_dark.svg \
src/icon/bell_light.svg \
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
    components/ChatPost.qml \
    components/ChatView.qml \
    components/Content.qml \
    components/ImgMask.qml \
    components/Login.qml \
    components/RoomList.qml \
    components/TipBar.qml \
    components/UserBar.qml \
    src/icon/bell_dark.svg \
    src/icon/bell_light.svg \
    src/image/gravatar.png

HEADERS += \
    chatpost.h \
    globalenum.h \
    loginobj.h \
    nowchatlistmodel.h \
    qmlfun.h \
    roomlistmodel.h \
    socketclient.h \
    userinfo.h
