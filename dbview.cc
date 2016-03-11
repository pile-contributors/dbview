/**
 * @file dbview.cc
 * @brief Definitions for DbView class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "dbview.h"
#include "dbview-private.h"

/**
 * @class DbView
 *
 * Detailed description.
 */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for constructor.
 */
DbTableView::DbTableView(
        QWidget *parent) :
    QTableView (parent)
{
    DBVIEW_TRACE_ENTRY;

    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
DbTableView::~DbTableView()
{
    DBVIEW_TRACE_ENTRY;

    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */
