#include "dbviewinmo.h"

using namespace impl;
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
InMo::InMo(QObject *parent) :
    QAbstractTableModel(parent),
    user_model_(NULL)
{
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setUserModel(QAbstractItemModel *model)
{
    beginResetModel();
    if (user_model_!= NULL) {
        disconnectModel ();
    }
    user_model_ = model;
    if (model != NULL) {
        connectModel (model);
    }
    endResetModel();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::connectModel (QAbstractItemModel *model)
{
    connect(model, &QAbstractItemModel::dataChanged,
            this, &QAbstractItemModel::dataChanged);
    connect(model, &QAbstractItemModel::headerDataChanged,
            this, &QAbstractItemModel::headerDataChanged);
    connect(model, &QAbstractItemModel::layoutChanged,
            this, &QAbstractItemModel::layoutChanged);
    connect(model, &QAbstractItemModel::layoutAboutToBeChanged,
            this, &QAbstractItemModel::layoutAboutToBeChanged);

    connect(model, &QAbstractItemModel::rowsAboutToBeInserted,
            this, &QAbstractItemModel::rowsAboutToBeInserted);
    connect(model, &QAbstractItemModel::rowsInserted,
            this, &QAbstractItemModel::rowsInserted);
    connect(model, &QAbstractItemModel::rowsAboutToBeRemoved,
            this, &QAbstractItemModel::rowsAboutToBeRemoved);
    connect(model, &QAbstractItemModel::rowsRemoved,
            this, &QAbstractItemModel::rowsRemoved);

    connect(model, &QAbstractItemModel::columnsAboutToBeInserted,
            this, &QAbstractItemModel::columnsAboutToBeInserted);
    connect(model, &QAbstractItemModel::columnsInserted,
            this, &QAbstractItemModel::columnsInserted);
    connect(model, &QAbstractItemModel::columnsAboutToBeRemoved,
            this, &QAbstractItemModel::columnsAboutToBeRemoved);
    connect(model, &QAbstractItemModel::columnsRemoved,
            this, &QAbstractItemModel::columnsRemoved);

    connect(model, &QAbstractItemModel::modelAboutToBeReset,
            this, &QAbstractItemModel::modelAboutToBeReset);
    connect(model, &QAbstractItemModel::modelReset,
            this, &QAbstractItemModel::modelReset);
    connect(model, &QAbstractItemModel::rowsAboutToBeMoved,
            this, &QAbstractItemModel::rowsAboutToBeMoved);
    connect(model, &QAbstractItemModel::rowsMoved,
            this, &QAbstractItemModel::rowsMoved);

    connect(model, &QAbstractItemModel::columnsAboutToBeMoved,
            this, &QAbstractItemModel::columnsAboutToBeMoved);
    connect(model, &QAbstractItemModel::columnsMoved,
            this, &QAbstractItemModel::columnsMoved);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::disconnectModel ()
{
    disconnect(user_model_, &QAbstractItemModel::dataChanged,
            this, &QAbstractItemModel::dataChanged);
    disconnect(user_model_, &QAbstractItemModel::headerDataChanged,
            this, &QAbstractItemModel::headerDataChanged);
    disconnect(user_model_, &QAbstractItemModel::layoutChanged,
            this, &QAbstractItemModel::layoutChanged);
    disconnect(user_model_, &QAbstractItemModel::layoutAboutToBeChanged,
            this, &QAbstractItemModel::layoutAboutToBeChanged);

    disconnect(user_model_, &QAbstractItemModel::rowsAboutToBeInserted,
            this, &QAbstractItemModel::rowsAboutToBeInserted);
    disconnect(user_model_, &QAbstractItemModel::rowsInserted,
            this, &QAbstractItemModel::rowsInserted);
    disconnect(user_model_, &QAbstractItemModel::rowsAboutToBeRemoved,
            this, &QAbstractItemModel::rowsAboutToBeRemoved);
    disconnect(user_model_, &QAbstractItemModel::rowsRemoved,
            this, &QAbstractItemModel::rowsRemoved);

    disconnect(user_model_, &QAbstractItemModel::columnsAboutToBeInserted,
            this, &QAbstractItemModel::columnsAboutToBeInserted);
    disconnect(user_model_, &QAbstractItemModel::columnsInserted,
            this, &QAbstractItemModel::columnsInserted);
    disconnect(user_model_, &QAbstractItemModel::columnsAboutToBeRemoved,
            this, &QAbstractItemModel::columnsAboutToBeRemoved);
    disconnect(user_model_, &QAbstractItemModel::columnsRemoved,
            this, &QAbstractItemModel::columnsRemoved);

    disconnect(user_model_, &QAbstractItemModel::modelAboutToBeReset,
            this, &QAbstractItemModel::modelAboutToBeReset);
    disconnect(user_model_, &QAbstractItemModel::modelReset,
            this, &QAbstractItemModel::modelReset);
    disconnect(user_model_, &QAbstractItemModel::rowsAboutToBeMoved,
            this, &QAbstractItemModel::rowsAboutToBeMoved);
    disconnect(user_model_, &QAbstractItemModel::rowsMoved,
            this, &QAbstractItemModel::rowsMoved);

    disconnect(user_model_, &QAbstractItemModel::columnsAboutToBeMoved,
            this, &QAbstractItemModel::columnsAboutToBeMoved);
    disconnect(user_model_, &QAbstractItemModel::columnsMoved,
            this, &QAbstractItemModel::columnsMoved);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant InMo::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    if (user_model_ == NULL)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        return user_model_->headerData (section, orientation, role);
    }


    // FIXME: Implement me!
    return QVariant();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int InMo::rowCount (const QModelIndex &parent) const
{
    if (user_model_ == NULL)
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return crt_row_count_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int InMo::columnCount (const QModelIndex &parent) const
{
    if (user_model_ == NULL)
        return 0;
    if (parent.isValid())
        return 0;

    return user_model_->columnCount ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant InMo::data (const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
