/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewmo.h
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the definition for DbViewMo class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef DBVIEWMO_H
#define DBVIEWMO_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbview-config.h>
#include <dbview/dbviewconfig.h>
#include <QtGlobal>
#include <QVariantList>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class DbViewColFilter;
QT_END_NAMESPACE

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! The interface for a model used in DbView and some helpers.
class DBVIEW_EXPORT DbViewMo {
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
    int first_row_;
    int max_rows_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewMo();

    //! destructor
    virtual ~DbViewMo();


    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name Interface
     * Methods that need to be implemented by the
     * subclass.
     */
    ///@{

    //! The model we're ghosting.
    virtual const QAbstractItemModel *
    qtModelC () const = 0;

    //! The model we're ghosting.
    virtual QAbstractItemModel *
    qtModel () = 0;

    //! Get the data.
    virtual QVariant
    data (
            int display_row,
            int true_row,
            int column,
            int role) const;

    //! Get the number of records in the backend.
    virtual int
    totalRowCount () const = 0;

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


    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewMo */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // DBVIEWMO_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

