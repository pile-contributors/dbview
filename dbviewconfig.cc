/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewconfig.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for DbViewConfig class.

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

#include "dbviewconfig.h"
#include "dbview-private.h"
#include "dbviewcolfilter.h"

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
DbViewConfig::DbViewConfig () :
    first_row(0),
    max_rows(10),
    sort_column(-1),
    sort_order(Qt::AscendingOrder),
    filters(),
    ms_timeout(2000),
    parallel(false)
{
    DBVIEW_TRACE_ENTRY;
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewConfig::DbViewConfig (
        const DbViewConfig & other) :
    first_row(other.first_row),
    max_rows(other.max_rows),
    sort_column(other.sort_column),
    sort_order(other.sort_order),
    filters(),
    ms_timeout(other.ms_timeout),
    parallel(other.parallel)
{
    DBVIEW_TRACE_ENTRY;
    if (parallel) {
        filters = DbViewColFilter::clone (other.filters);
    } else {
        filters = other.filters;
    }
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewConfig::~DbViewConfig()
{
    DBVIEW_TRACE_ENTRY;
    if (parallel) {
        eraseFilters ();
    }
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewConfig::straightCopy (const DbViewConfig &other)
{
    first_row = other.first_row;
    max_rows = other.max_rows;
    sort_column = other.sort_column;
    sort_order = other.sort_order;
    filters = other.filters;
    ms_timeout = other.ms_timeout;
    parallel = other.parallel;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewConfig::move (DbViewConfig &other)
{
    straightCopy (other);
    other.filters.clear();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewConfig::eraseFilters ()
{
    DBVIEW_TRACE_ENTRY;

    qDeleteAll (filters);
    filters.clear ();
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
