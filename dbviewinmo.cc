#include "dbviewinmo.h"
#include "dbviewmo.h"
#include "dbviewcolfilter.h"

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
void InMo::setUserModel(DbViewMo *model)
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
void InMo::connectModel (DbViewMo *user_model)
{
    QAbstractItemModel * model = user_model->qtModel ();
    Q_ASSERT(model != NULL);

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
    QAbstractItemModel * model = user_model_->qtModel ();
    Q_ASSERT(model != NULL);

    disconnect(model, &QAbstractItemModel::dataChanged,
            this, &QAbstractItemModel::dataChanged);
    disconnect(model, &QAbstractItemModel::headerDataChanged,
            this, &QAbstractItemModel::headerDataChanged);
    disconnect(model, &QAbstractItemModel::layoutChanged,
            this, &QAbstractItemModel::layoutChanged);
    disconnect(model, &QAbstractItemModel::layoutAboutToBeChanged,
            this, &QAbstractItemModel::layoutAboutToBeChanged);

    disconnect(model, &QAbstractItemModel::rowsAboutToBeInserted,
            this, &QAbstractItemModel::rowsAboutToBeInserted);
    disconnect(model, &QAbstractItemModel::rowsInserted,
            this, &QAbstractItemModel::rowsInserted);
    disconnect(model, &QAbstractItemModel::rowsAboutToBeRemoved,
            this, &QAbstractItemModel::rowsAboutToBeRemoved);
    disconnect(model, &QAbstractItemModel::rowsRemoved,
            this, &QAbstractItemModel::rowsRemoved);

    disconnect(model, &QAbstractItemModel::columnsAboutToBeInserted,
            this, &QAbstractItemModel::columnsAboutToBeInserted);
    disconnect(model, &QAbstractItemModel::columnsInserted,
            this, &QAbstractItemModel::columnsInserted);
    disconnect(model, &QAbstractItemModel::columnsAboutToBeRemoved,
            this, &QAbstractItemModel::columnsAboutToBeRemoved);
    disconnect(model, &QAbstractItemModel::columnsRemoved,
            this, &QAbstractItemModel::columnsRemoved);

    disconnect(model, &QAbstractItemModel::modelAboutToBeReset,
            this, &QAbstractItemModel::modelAboutToBeReset);
    disconnect(model, &QAbstractItemModel::modelReset,
            this, &QAbstractItemModel::modelReset);
    disconnect(model, &QAbstractItemModel::rowsAboutToBeMoved,
            this, &QAbstractItemModel::rowsAboutToBeMoved);
    disconnect(model, &QAbstractItemModel::rowsMoved,
            this, &QAbstractItemModel::rowsMoved);

    disconnect(model, &QAbstractItemModel::columnsAboutToBeMoved,
            this, &QAbstractItemModel::columnsAboutToBeMoved);
    disconnect(model, &QAbstractItemModel::columnsMoved,
            this, &QAbstractItemModel::columnsMoved);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant InMo::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    if (user_model_ == NULL)
        return QVariant();

    QAbstractItemModel * model = user_model_->qtModel ();
    Q_ASSERT(model != NULL);

    if (orientation == Qt::Horizontal) {
        return model->headerData (section, orientation, role);
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

    QAbstractItemModel * model = user_model_->qtModel ();
    return model->columnCount ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant InMo::data (const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QAbstractItemModel * model = user_model_->qtModel ();
    Q_ASSERT(model != NULL);

    // FIXME: Implement me!
    return QVariant();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::reloadWithFilters (const QList<DbViewColFilter *> &filters)
{
    user_model_->reloadWithFilters (filters);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
