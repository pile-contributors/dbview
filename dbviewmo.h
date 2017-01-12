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

    //! The model to be used in forms.
    virtual QAbstractItemModel *
    qtModel () = 0;


    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */



    //! The user requested data to be filtered.
    virtual void
    reloadWithFilters (
            const QList<DbViewColFilter*> &filters);

protected:

private:


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

