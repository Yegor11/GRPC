#include "model.h"

Model::Model(QObject *parent) : QAbstractListModel(parent), client(grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials())){}

void Model::add( std::vector<std::string> info)
{
    for (int var = 0; var < info.size() ; ++var) {
       beginInsertRows( QModelIndex(), incidents.size(),incidents.size());
       incidents.emplace_back(info[var]);
       endInsertRows();
    }
}

void Model::clear_data()
{
    beginResetModel();
    incidents.clear();
    endResetModel();
}

int Model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() )
        return 0;

    return incidents.size();
}

void Model::startclient(QString login_str, QString password_str)
{
    // making login and collecting metadata from it
    metadata = client.login(login_str.toUtf8().constData(), password_str.toUtf8().constData());

    // adding active incidents to model data t ostore it
    add(std::vector<std::string> { client.getActiveIncidentIds(metadata.first,metadata.second,user_agent)});

}

void Model::endclient()
{
    // making logout operetion
     client.logout(metadata.first,metadata.second,user_agent);

     //clearing model data
     clear_data();

}

QVariant Model::data(const QModelIndex &index, int role) const
{   
    if (!index.isValid() )
        return QVariant();
    switch (role) {
    case DoneRole:
        return QVariant(QString::fromStdString(incidents[index.row()]));
    }

    return QVariant();
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "description";
    return names;
}
