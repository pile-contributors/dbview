#include "dbviewinmo.h"
#include "dbviewmo.h"
#include "dbviewcolfilter.h"
#include "dbview-globals.h"

#include <QtConcurrent\QtConcurrent>

using namespace impl;
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
InMo::InMo(QObject *parent) :
    QAbstractTableModel(parent),
    user_model_(NULL),
    page_index_(0),
    crt_row_count_(0),
    pages_count_(1)
{
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
InMo::~InMo()
{
    if (!cfg_.parallel) {
        cfg_.eraseFilters ();
    }
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
        runReload ();
        connectModel (model);
    }
    endResetModel();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int InMo::totalRowCount() const
{
    if (user_model_ == NULL) {
        return -1;
    } else {
        return user_model_->totalRowCount ();
    }
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
    cfg_.max_rows = value;
    setFirstRowIndex(cfg_.first_row);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setPageIndex (int value)
{
    Q_ASSERT(value >= 0);
    page_index_ = value;
    reloadWithFilters ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setFirstRowIndex (int value)
{
    if (user_model_ == NULL)
        return;
    int pg = value / cfg_.max_rows;
    setPageIndex (pg);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::sort (int column, Qt::SortOrder order)
{
    cfg_.sort_column = column;
    cfg_.sort_order = order;
    reloadWithFilters ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::setColumnFilter (int column, DbViewColFilter *value)
{
    int fcnt = cfg_.filters.count ();
    if (column == fcnt) {
        cfg_.filters.append (value);
    } else if (column > fcnt) {
        do {
             cfg_.filters.append (NULL);
             ++fcnt;
        } while (column > fcnt);
        cfg_.filters.append (value);
    } else {
        DbViewColFilter * prev = cfg_.filters[column];
        cfg_.filters[column] = value;
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
        cfg_.first_row = 0;
        pages_count_ = 1;
    } else {
        int tot_row_count = user_model_->totalRowCount ();
        cfg_.first_row = cfg_.max_rows * page_index_;
        crt_row_count_ = qMin(cfg_.max_rows, tot_row_count-cfg_.first_row);
        pages_count_ = tot_row_count / cfg_.max_rows;
        int displ = pages_count_ * cfg_.max_rows;
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
        if (role == Qt::TextAlignmentRole) {
            return (int)Qt::Alignment(Qt::AlignHCenter | Qt::AlignTop);
        }
        return user_model_->qtModel ()->headerData (section, orientation, role);
    }

    int row = section + cfg_.first_row;
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

    int row = index.row() + cfg_.first_row;
    return user_model_->data (index.row(), row, index.column(), role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::runReload ()
{
    if (cfg_.parallel) {
        QtConcurrent::run (
                    user_model_, &DbViewMo::reloadWithFilters, cfg_);
    } else {
        user_model_->reloadWithFilters (cfg_);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::reloadWithFilters ()
{
    disconnectModel ();
    runReload ();
    connectModel (user_model_);
    beginResetModel();
    endResetModel();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::eraseFilters ()
{
    qDeleteAll (cfg_.filters);
    cfg_.filters.clear ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void InMo::goToPage (int value)
{
    page_index_ = value;
    cfg_.first_row = value * cfg_.max_rows;
    int tot_rows = user_model_->totalRowCount ();

    if (cfg_.first_row >= tot_rows) {
        page_index_ = pages_count_ - 1;
        cfg_.first_row = page_index_ * cfg_.max_rows;
    }
    if (cfg_.first_row < 0) {
        cfg_.first_row = 0;
        page_index_ = 0;
    }
    reloadWithFilters ();
}
/* ========================================================================= */

