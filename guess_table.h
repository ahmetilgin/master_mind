#ifndef GUESS_TABLE_H
#define GUESS_TABLE_H

#include <QObject>
#include <QAbstractTableModel>
#include <map>
class guess_table: public QAbstractTableModel
{
    Q_OBJECT
public slots:
    void insert_history(QString input, QString result);
public:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
    guess_table();
private:
    struct result{
        QString guess;
        QString result;
    };
    std::vector<result> result_history;
};

#endif // GUESS_TABLE_H
