#include "guess_table.h"
#define COLUMN_COUNT 5

guess_table::guess_table()
{

}

void guess_table::insert_history(QString input, QString result)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    result_history.push_back(guess_table::result{input, result});
    endInsertRows();
}

int guess_table::rowCount(const QModelIndex &) const
{
    return result_history.size();
}

int guess_table::columnCount(const QModelIndex & ) const
{
    return COLUMN_COUNT;
}

QVariant guess_table::data(const QModelIndex &index, int role) const
{
//    QString("%1, %2").arg(index.column()).arg(index.row())
    switch (role) {
        case Qt::DisplayRole:{
            if(index.column() < COLUMN_COUNT - 1)
                return result_history.at(index.row()).guess.at(index.column());
            else
                return result_history.at(index.row()).result;
        }
        default:
            break;
    }

    return QVariant();
}

QHash<int, QByteArray> guess_table::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}
