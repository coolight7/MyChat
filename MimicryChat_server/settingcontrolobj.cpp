#include "settingcontrolobj.h"
#include "socketlistmodel.h"

SettingControlObj::SettingControlObj()
{

}

SettingControlObj *SettingControlObj::getInstance()
{
    static SettingControlObj* obj = new SettingControlObj();
    return obj;
}

void SettingControlObj::setRoomInfo(SocketServer_c* in_server)
{
    this->socketServer = in_server;
    this->setRid(in_server->port);
    this->setRname(in_server->name);
    this->setRimg(in_server->img);
}

void SettingControlObj::saveEditInfo(const QString& in_rname, const QString& in_rimg)
{
    if(this->socketServer == nullptr)
        return;
    this->rname = in_rname;
    this->rimg  = in_rimg;
    this->socketServer->img = in_rimg;
    this->socketServer->name = in_rname;
    (SocketListModel::getInstance())->flushView(0);
    this->socketServer->send_update_roomInfo();
}

const QString &SettingControlObj::getRimg() const
{
    return rimg;
}

void SettingControlObj::setRimg(const QString &newRimg)
{
    if (rimg == newRimg)
        return;
    rimg = newRimg;
    emit rimgChanged();
}

const QString &SettingControlObj::getRname() const
{
    return rname;
}

void SettingControlObj::setRname(const QString &newRname)
{
    if (rname == newRname)
        return;
    rname = newRname;
    emit rnameChanged();
}

int SettingControlObj::getRid() const
{
    return rid;
}

void SettingControlObj::setRid(int newRid)
{
    if (rid == newRid)
        return;
    rid = newRid;
    emit ridChanged();
}
