#include "dbviewinmo.h"
#include "dbviewmo.h"
#include "dbviewcolfilter.h"

#include <QtConcurrent\QtConcurrent>

using namespace impl;
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
InMo::InMo(QObject *parent) :
    QAbstractTableModel(parent),
    user_model_(NULL),
    page_row_count_(10),
    page_index_(0),
    filters_(),
    separate_thread_(false),
    ms_timeout_(2000),
    crt_row_count_(0),
    first_row_index_(0),
    pages_count_(1)
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

    connect(model, &QAbstractItemModel::rowsInserted,
            this, &InMo::reloadCachedData);
    connect(model, &QAbstractItemModel::rowsRemoved,
            this, &InMo::reloadCachedData);
    connect(model, &QAbstractItemModel::columnsInserted,
            this, &InMo::reloadCachedData);
    connect(model, &QAbstractItemModel::columnsRemoved,
            this, &InMo::reloadCachedData);

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

    reloadCachedData ();
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

    disconnect(model, &QAbstractItemModel::rowsInserted,
               this, &InMo::reloadCachedData);
    disconnect(model, &QAbstractItemModel::rowsRemoved,
               this, &InMo::reloadCachedData);
    disconnect(model, &QAbstractItemModel::columnsInserted,
               this, &InMo::reloadCachedData);
    disconnect(model, &QAbstractItemModel::columnsRemoved,
               this, &InMo::reloadCachedData);

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

    reloadCachedData ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setPageRowCount (int value)
{
    Q_ASSERT(value > 0);
    beginResetModel ();
    page_row_count_ = value;
    reloadCachedData ();
    endResetModel ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setPageIndex (int value)
{
    Q_ASSERT(value > 0);
    beginResetModel ();
    page_index_ = value;
    reloadCachedData ();
    endResetModel ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setFirstRowIndex (int value)
{
    if (user_model_ == NULL)
        return;
    int pg = value / page_row_count_;
    setPageIndex (pg);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setColumnFilter (int column, DbViewColFilter *value)
{
    int fcnt = filters_.count ();
    if (column == fcnt) {
        filters_.append (value);
    } else if (column > fcnt) {
        do {
             filters_.append (NULL);
             ++fcnt;
        } while (column > fcnt);
        filters_.append (value);
    } else {
        DbViewColFilter * prev = filters_[column];
        filters_[column] = value;
        if (prev != NULL) {
            delete prev;
        }
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::reloadCachedData ()
{
    if (user_model_ == NULL) {
        page_index_ = 0;
        crt_row_count_ = 0;
        first_row_index_ = 0;
        pages_count_ = 1;
    } else {
        QAbstractItemModel * mm = user_model_->qtModel ();
        int tot_row_count = mm->rowCount();
        crt_row_count_ = qMin(page_row_count_, tot_row_count);
        first_row_index_ = page_row_count_ * page_index_;
        pages_count_ = tot_row_count / page_row_count_;
        int displ = pages_count_ * page_row_count_;
        if (displ < tot_row_count)
            ++pages_count_;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant InMo::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    if (user_model_ == NULL)
        return QVariant();

    Q_ASSERT(user_model_ != NULL);

    if (orientation == Qt::Horizontal) {
        return user_model_->qtModel ()->headerData (section, orientation, role);
    }

    int row = section + first_row_index_;
    switch (role) {
    case Qt::DisplayRole: {
        return QString::number (row+1);
    }
    case Qt::EditRole: {
        return row+1;
    }
    }

    return user_model_->rowHeaderData (
                section, row, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int InMo::rowCount (const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
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

    int row = index.row() + first_row_index_;
    return user_model_->data (index.row(), row, index.column(), role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::reloadWithFilters ()
{
    if (separate_thread_) {
        QList<DbViewColFilter*> temp_filters_;
        foreach(DbViewColFilter* flt, filters_) {
            if (flt == NULL) {
                temp_filters_.append (NULL);
            } else {
                temp_filters_.append (flt->clone ());
            }
        }
        QtConcurrent::run (
                    user_model_, &DbViewMo::reloadWithFilters,
                    first_row_index_, page_row_count_, filters_,
                    ms_timeout_);
    } else {
        user_model_->reloadWithFilters (
                    first_row_index_, page_row_count_, filters_,
                    ms_timeout_);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::eraseFilters ()
{
    qDeleteAll (filters_);
    filters_.clear ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::goToPage (int value)
{
    int first_row = value * page_row_count_;
    int tot_rows = user_model_->qtModel ()->rowCount ();

    if (first_row >= tot_rows) {
        first_row = (pages_count_ - 1) * page_row_count_;
    }
    if (first_row < 0) {
        first_row = 0;
    }
    user_model_->reloadWithFilters (first_row, page_row_count_, filters_);
}
/* ========================================================================= */

