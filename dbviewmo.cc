/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewmo.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for DbViewMo class.

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

#include "dbviewmo.h"

#include <QAbstractItemModel>

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
DbViewMo::DbViewMo ()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewMo::~DbViewMo()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Default implementation simply forwards the request to
 * underlying model.
 *
 * @param display_row index of the row inside current page
 * @param true_row index of the row in the whole model
 * @param column index of the column
 * @param role the role
 * @return appropriate value
 */
QVariant DbViewMo::data (
        int display_row, int true_row, int column, int role) const
{
    Q_UNUSED(display_row);
    QAbstractItemModel * mm = qtModel ();

    return mm->data (mm->index (true_row, column), role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Default implementation simply forwards the request to
 * underlying model.
 *
 * @param display_row index of the row inside current page
 * @param true_row index of the row in the whole model
 * @param role the role
 * @return appropriate value
 */
QVariant DbViewMo::rowHeaderData (
        int display_row, int true_row, int role) const
{
    Q_UNUSED(display_row);
    return qtModel()->headerData (
                true_row, Qt::Vertical, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The entries in the list may be: strings, string lists
 *
 * @param filters the list of values to filter the model by,
 *                 one for each column
 */
void DbViewMo::reloadWithFilters (
        int first_row, int max_rows,
        const QList<DbViewColFilter*> &filters,
        int ms_timeout)
{

}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
