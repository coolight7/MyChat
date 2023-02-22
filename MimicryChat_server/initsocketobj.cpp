#include "initsocketobj.h"

InitSocketObj::InitSocketObj()
{

}

InitSocketObj *InitSocketObj::getInstance()
{
    static InitSocketObj* obj = new InitSocketObj();
    return obj;
}


void InitSocketObj::create()
{
    if(serverThread == nullptr) {
        serverThread = new SocketServerThread_c(this->name, this->rid, this->state);
    }
    if(serverThread->state == -200) {
        delete[]serverThread;
        if(serverThread == nullptr) {
            serverThread = new SocketServerThread_c(this->name, this->rid, this->state);
        }
    }
    serverThread->run();
}

int InitSocketObj::getRid() const
{
    return rid;
}

void InitSocketObj::setRid(int newRid)
{
    if (rid == newRid)
        return;
    rid = newRid;
    emit ridChanged();
}

const QString &InitSocketObj::getName() const
{
    return name;
}

void InitSocketObj::setName(const QString &newName)
{
    if (name == newName)
        return;
    name = newName;
    emit nameChanged();
}
