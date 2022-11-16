#ifndef MODEL_H
#define MODEL_H

#include <certificate.h>
#include <client.h>
#include <server.h>
#include <grpc++/grpc++.h>

#include <vector>
#include <array>
#include <iostream>
#include <utility>
#include <QAbstractListModel>

class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    enum {
          DoneRole = Qt::UserRole,
      };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE void startclient(QString login,QString password);
    Q_INVOKABLE void endclient();
    void add(std::vector<std::string>info );
    void clear_data();


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:

    std::vector<std::string> incidents;
    Client client;
    std::pair <std::string,std::string> metadata;
    std::string user_agent = "YegorClient";
};

#endif // MODEL_H
