/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewmosql.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for DbViewMoSql class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include "dbviewmosql.h"
#include "dbviewcolfilter.h"

#include <QSqlQuery>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */


/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
DbViewMoSql::DbViewMoSql (
        const QSqlDatabase & db,
        const QString & table,
        QObject * parent) :
    QAbstractItemModel(parent),
    DbViewMo(),
    cfg_(),
    db_(db),
    table_(table)
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewMoSql::~DbViewMoSql()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewMoSql::filterAcceptsRow (int sourceRow,
        const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    // next apply filters in columns, if any
    return DbViewColFilter::acceptsRow (
                cfg_.filters, const_cast<DbViewMoSql*>(this), sourceRow);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewMoSql::reloadWithFilters (DbViewConfig cfg)
{
    cfg_.move (cfg);


    QString where_clause;
    QString ordering;
    if (cfg.sort_order == Qt::AscendingOrder) {
        ordering = "ASC";
    } else {
        ordering = "DESC";
    }
    QString order_by = record().fieldName (cfg.sort_column);;
    QSqlQuery q (QString (
                     "SELECT * FROM %1 %2 ORDER BY %3 %4 LIMIT %5 OFFSET %6;")
                 .arg (table_)          // 1
                 .arg (where_clause)    // 2
                 .arg (order_by)        // 3
                 .arg (ordering)        // 4
                 .arg (cfg.max_rows)    // 5
                 .arg (cfg.first_row),  // 6
                 db_);


    // QAbstractItemModel *user_model = sourceModel ();
    // needed so that a filtering is trigered
    // setFilterKeyColumn(0);
    Q_ASSERT(cfg_.sort_column >= -1);
    sort(cfg_.sort_column, cfg_.sort_order);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewMoSql::isValid() const
{
    /// @todo
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//QVariant DbViewMoSql::data (
//        const QModelIndex &index, int role) const
//{
//    /* MUST be implemented */
//    return QVariant();
//}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewMoSql::setData (
        const QModelIndex &index, const QVariant &value, int role)
{
    return QAbstractItemModel::setData (index, value, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//QVariant DbViewMoSql::headerData (
//        int section, Qt::Orientation orientation, int role) const
//{
//    return QAbstractItemModel::headerData (section, orientation, role);
//}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//bool DbViewMoSql::setHeaderData (
//        int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    return QAbstractItemModel::setHeaderData (section, orientation, value, role);
//}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//QMap<int, QVariant> DbViewMoSql::itemData (const QModelIndex &index) const
//{
//    return QAbstractItemModel::itemData (index);
//}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//bool DbViewMoSql::setItemData (
//        const QModelIndex & index, const QMap<int, QVariant> & roles)
//{
//    return QAbstractItemModel::setItemData (index, roles);
//}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::ItemFlags DbViewMoSql::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags (index);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewMoSql::sort (
        int column, Qt::SortOrder order)
{
    return QAbstractItemModel::sort (column, order);
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
