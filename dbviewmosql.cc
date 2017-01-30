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
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

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
    QSqlQueryModel(parent),
    DbViewMo(),
    cfg_(),
    db_(db),
    table_(table),
    total_count_(-1)
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewMoSql::~DbViewMoSql()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Basic implementation only works with a single column.
 */
bool DbViewMoSql::filterAcceptsRow (
        int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    // next apply filters in columns, if any
    return DbViewColFilter::acceptsRow (
                cfg_.filters, const_cast<DbViewMoSql*>(this), sourceRow);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbViewMoSql::readTotalCount (
        const QString & where_clause)
{
    QString s_crt_query = QString (
                "SELECT COUNT(*) FROM %1 %2;")
            .arg (table_)          // 1
            .arg (where_clause);
    qDebug () << s_crt_query;
    QSqlQuery query (s_crt_query, db_);

    if (!query.exec()) {
        qDebug() << "personsCount error:  "
                 << query.lastError();
        return -1;
    } else if (query.next ()) {
        bool b_ok;

        int result = query.value (0).toInt (&b_ok);
        if (!b_ok) {
            qDebug() << "NAN:  " << query.value (0).toString();
            result = -1;
        }
        return result;
    } else {
        qDebug() << "No result (!)";
        return -1;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewMoSql::reloadWithFilters (DbViewConfig cfg)
{
    cfg_.move (cfg);


    QString where_clause = getWhereClause (cfg_);

    total_count_ = readTotalCount (where_clause);
    if (total_count_ == -1) {
        return;
    }
    QString ordering;
    if (cfg.sort_order == Qt::AscendingOrder) {
        ordering = "ASC";
    } else {
        ordering = "DESC";
    }
    QString order_by;
    if (cfg.sort_column == -1) {
        order_by = QString();
    } else {
        order_by = QString ("ORDER BY %1 %2").arg (
                    record ().fieldName (cfg.sort_column))
                .arg (ordering);
    }
    QString s_crt_query = QString (
                "SELECT * FROM %1 %2 %3 LIMIT %4 OFFSET %5;")
            .arg (table_)          // 1
            .arg (where_clause)    // 2
            .arg (order_by)        // 3
            .arg (cfg.max_rows)    // 4
            .arg (cfg.first_row);  // 5
    qDebug () << s_crt_query;
    QSqlQuery q (s_crt_query, db_);

    setQuery (q);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbViewMoSql::rowCount (const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return total_count_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewMoSql::setData (
        const QModelIndex &index, const QVariant &value, int role)
{
    return QAbstractItemModel::setData (index, value, role);
}
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

/* ------------------------------------------------------------------------- */
/**
 * The sql model will only store current page.
 *
 * @param display_row index of the row inside current page
 * @param true_row index of the row in the whole model
 * @param column index of the column
 * @param role the role
 * @return appropriate value
 */
QVariant DbViewMoSql::data (
        int display_row, int true_row, int column, int role) const
{
    Q_UNUSED(true_row);
    const QAbstractItemModel * mm = qtModelC ();

    return mm->data (mm->index (display_row, column), role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The sql model will only store current page.
 *
 * @param display_row index of the row inside current page
 * @param true_row index of the row in the whole model
 * @param role the role
 * @return appropriate value
 */
QVariant DbViewMoSql::rowHeaderData (
        int display_row, int true_row, int role) const
{
    Q_UNUSED(true_row);
    return qtModelC()->headerData (
                display_row, Qt::Vertical, role);
}
/* ========================================================================= */

static const QLatin1String s_and (" AND ");
static const QLatin1String s_space (" ");
static const QLatin1String s_where (" WHERE ");
/* ------------------------------------------------------------------------- */
/**
 * The sql model will only store current page.
 *
 * @param display_row index of the row inside current page
 * @param true_row index of the row in the whole model
 * @param role the role
 * @return appropriate value
 */
QString DbViewMoSql::getWhereClause (
        const DbViewConfig & cfg) const
{
    int i = 0;
    QString result;
    foreach (DbViewColFilter* filter, cfg.filters) {
        if (filter != NULL) {
            QString s_filt = filter->asSql ();
            if (!s_filt.isEmpty()) {
                if (!result.isEmpty()) {
                    result.append (s_and);
                }
                result.append (s_filt.arg (record ().fieldName (i)));
            }
        }
        ++i;
    }
    if (!result.isEmpty()) {
        result.prepend (s_where);
    }

    return result;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
