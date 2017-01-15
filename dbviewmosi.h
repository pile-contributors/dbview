/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewmosi.h
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the definition for DbViewMoSi class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef DBVIEWMOSI_H
#define DBVIEWMOSI_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbviewmo.h>
#include <QSortFilterProxyModel>

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

//! Allows pagination, sorting and filtering.
class DBVIEW_EXPORT DbViewMoSi : public QSortFilterProxyModel, public DbViewMo
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

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewMoSi (
            QAbstractItemModel * user_model=NULL,
            QObject * parent = NULL);

    //! destructor
    virtual ~DbViewMoSi();

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

protected:

private:


    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewMoSi */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // DBVIEWMOSI_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

