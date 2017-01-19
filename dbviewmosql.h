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


    //! Basic implementation only works with a single column.
    bool
    filterAcceptsRow (
        int sourceRow,
        const QModelIndex &sourceParent) const;


    virtual void
    reloadWithFilters (
            DbViewConfig cfg);



    //! Is this a valid model or not?
    bool
    isValid() const;


//    virtual QVariant
//    data (
//            const QModelIndex &index,
//            int role = Qt::DisplayRole) const;

    virtual bool
    setData (
            const QModelIndex &index,
            const QVariant &value,
            int role = Qt::EditRole);

//    virtual QVariant
//    headerData (
//            int section,
//            Qt::Orientation orientation,
//            int role = Qt::DisplayRole) const;

//    virtual bool
//    setHeaderData (
//            int section,
//            Qt::Orientation orientation,
//            const QVariant &value,
//            int role = Qt::EditRole);

//    virtual QMap<int,QVariant>
//    itemData (
//            const QModelIndex &index) const;

//    virtual bool
//    setItemData (
//            const QModelIndex &index,
//            const QMap<int,QVariant> &roles);


protected:

private:


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

