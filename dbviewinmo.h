#ifndef DBVIEWINMO_H
#define DBVIEWINMO_H

#include <QAbstractTableModel>

namespace impl
{

//! Internal model used by the tableview.
class InMo : public QAbstractTableModel
{
    Q_OBJECT

public:

    //! Default constructor.
    explicit
    InMo(
            QObject *parent = 0);

    //! The model that has actual data.
    QAbstractItemModel *
    userModel () const {
        return user_model_;
    }

    //! Change the model that has actual data.
    void
    setUserModel (
            QAbstractItemModel *model);

    QVariant
    headerData (
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole) const override;

    int
    rowCount (
            const QModelIndex &parent = QModelIndex()) const override;

    int
    columnCount (
            const QModelIndex &parent = QModelIndex()) const override;

    QVariant
    data (
            const QModelIndex &index,
            int role = Qt::DisplayRole) const override;

private:
    void connectModel (QAbstractItemModel *model);
    void disconnectModel ();


    QAbstractItemModel * user_model_;
    int crt_row_count_;
};
} // namespace impl

#endif // DBVIEWINMO_H
