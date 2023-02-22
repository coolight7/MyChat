#include "chatfilterlistmodel.h"

ChatFilterListModel::ChatFilterListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->filterList.clear();
    this->setting = new QSettings("ChatFilter.ini", QSettings::IniFormat);
    this->readSetting();

    m_roleNames.insert(STR, "str");
}


ChatFilterListModel *ChatFilterListModel::getInstance()
{
    static ChatFilterListModel* obj = new ChatFilterListModel();
    return obj;
}

void ChatFilterListModel::readSetting()
{
    setting->beginGroup("FILTER");

    int num = 0;
    if(setting->childKeys().contains("num")) {  //如果存在num
        num = setting->value("num").toInt();
        for(int i = 0; i < num; ++i) {
            filterList.push_back(setting->value("str" + QString::number(i)).toString());
        }
    }
    setting->endGroup();
}

void ChatFilterListModel::saveSetting()
{
    setting->beginGroup("FILTER");
    setting->setValue("num", filterList.size());
    int i = 0;
    for(auto it = filterList.begin(), endit = filterList.end(); it != endit; ++it, ++i) {
        setting->setValue("str" + QString::number(i), *it);
    }
    setting->endGroup();
}

QString ChatFilterListModel::filterStr(const QString& in_str)
{
    if(in_str == "")
        return in_str;
    QString re_str = in_str;
    ChatFilterListModel* chatFilter = ChatFilterListModel::getInstance();
    for(auto it = chatFilter->filterList.begin(), endit = chatFilter->filterList.end(); it != endit; ++it) {
        re_str.replace(*it, "*");
    }
    return re_str;
}

void ChatFilterListModel::append(const QString &in_str)
{
    emit beginInsertRows(QModelIndex(), filterList.size(), filterList.size());
    filterList.push_back(in_str);
    emit endInsertRows();
}

void ChatFilterListModel::remove(int index)
{
    if(index < 0 || index >= filterList.size())
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    filterList.removeAt(index);
    emit endRemoveRows();
}


int ChatFilterListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return filterList.count();
}

QVariant ChatFilterListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case STR:{
        return filterList[index.row()];
    }break;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> ChatFilterListModel::roleNames() const
{
    return m_roleNames;
}
