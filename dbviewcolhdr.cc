/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewcolhdr.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for DbViewColHdr class.

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

#include "dbviewcolhdr.h"
#include "dbview.h"

#include <QPainter>

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
DbViewColHdr::DbViewColHdr (DbTableView *table, QWidget *parent)
    : QHeaderView (Qt::Horizontal, parent),
      table_(table),
      controls_()
{
    Q_ASSERT(table != NULL);
    connect(this, &QHeaderView::sectionResized,
            this, &DbViewColHdr::resizeControl);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewColHdr::~DbViewColHdr()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::setControl (int column, QWidget *widget)
{
    int fcnt = controls_.count ();
    if (column == fcnt) {
        controls_.append (widget);
    } else if (column > fcnt) {
        do {
             controls_.append (NULL);
             ++fcnt;
        } while (column > fcnt);
        controls_.append (widget);
    } else {
        QWidget * prev = controls_[column];
        controls_[column] = widget;
        if (prev!= NULL) {
            delete prev;
        }
    }
    if (widget != NULL) {
        widget->setParent (this);
        int width = 30;
        if (count() > column) {
            width = sectionSize(column);
        }
        widget->resize (width, this->height());
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::paintSection (
        QPainter *painter, const QRect &rect, int logicalIndex) const
{
    // const QList<DbViewColFilter*> & filters = table_->colFilters ();

    if (!table_->hasFilter (logicalIndex)) {
        QHeaderView::paintSection (painter, rect, logicalIndex);
        return;
    } else {
        painter->fillRect (rect, painter->brush());
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::resizeControl (int logicalIndex, int oldSize, int newSize)
{
    if (controls_.count() <= logicalIndex)
        return;

    QWidget * w = controls_[logicalIndex];
    w->resize (newSize, w->height ());
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
