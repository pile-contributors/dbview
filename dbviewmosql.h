/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewmosql.h
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the definition for DbViewMoSql class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef DBVIEWMOSQL_H
#define DBVIEWMOSQL_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbviewmo.h>
#include <QSortFilterProxyModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

QT_BEGIN_NAMESPACE
// class QSqlDatabase;
QT_END_NAMESPACE

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! Allows pagination, sorting and filtering in a sql database.
class DBVIEW_EXPORT DbViewMoSql : public QSqlQueryModel, public DbViewMo
{
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    DbViewConfig cfg_;
    QSqlDatabase db_;
    QString table_;
    int total_count_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewMoSql (
            const QSqlDatabase & db,
            const QString & table,
            QObject * parent = NULL);

    //! destructor
    virtual ~DbViewMoSql();


    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name DbViewMo Interface
     *
     */
    ///@{

public:

    //! The model we're ghosting.
    virtual const QAbstractItemModel *
    qtModelC () const {
        return this;
    }

    //! The model we're ghosting.
    virtual QAbstractItemModel *
    qtModel () {
        return this;
    }

    //! Get the data.
    virtual QVariant
    data (
            int display_row,
            int true_row,
            int column,
            int role) const;

    //! Get the header data; never display or edit roles.
    virtual QVariant
    rowHeaderData (
            int display_row,
            int true_row,
            int role) const;

    //! The user requested data to be filtered.
    virtual void
    reloadWithFilters (
            DbViewConfig cfg);

    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */


    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name QSqlQueryModel Interface
     *
     */
    ///@{

public:

    //! The total number of rows.
    virtual int
    rowCount (
            const QModelIndex &parent = QModelIndex()) const;

    //! Change model data.
    virtual bool
    setData (
            const QModelIndex &index,
            const QVariant &value,
            int role = Qt::EditRole);

    //! Item flags.
    Qt::ItemFlags
    flags (
            const QModelIndex &index) const;

    //! Perform model sorting.
    void
    sort (
            int column,
            Qt::SortOrder order);

    //! Tell if currently installed filter accepts indicated row.
    bool
    filterAcceptsRow (
        int sourceRow,
        const QModelIndex &sourceParent) const;


    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */


    int
    readTotalCount (
            const QString &where_clause = QString ());

    QString
    getWhereClause (
            const DbViewConfig &cfg) const;

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewMoSql */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // DBVIEWMOSQL_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

