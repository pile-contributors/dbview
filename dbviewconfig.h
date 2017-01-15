/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewconfig.h
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the definition for DbViewConfig class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef DBVIEWCONFIG_H
#define DBVIEWCONFIG_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbview-config.h>
#include <Qt>
#include <QList>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class DbViewColFilter;


/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! .
class DBVIEW_EXPORT DbViewConfig
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

public:

    int first_row;
    int max_rows;
    int sort_column;
    Qt::SortOrder sort_order;
    QList<DbViewColFilter*> filters;
    int ms_timeout;
    bool parallel;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Default constructor.
    DbViewConfig();

    //! Copy constructor.
    DbViewConfig (
            const DbViewConfig & other);

    //! destructor
    virtual ~DbViewConfig();

    //! Simple copy of values.
    void straightCopy (
            const DbViewConfig & other);

    //! Simple copy of values and ensure no side effects from destructor.
    void move (
            DbViewConfig & other);

    void
    eraseFilters();

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewConfig */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // DBVIEWCONFIG_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

