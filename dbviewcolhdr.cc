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
#include <QCursor>
#include <QDebug>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

static const int horiz_space = 1;
static const int vert_space = 1;


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
      controls_(),
      half_(height())
{
    Q_ASSERT(table != NULL);
    connect(this, &QHeaderView::sectionResized,
            this, &DbViewColHdr::resizeControl);
    int height_fix = half_*2 + 3*vert_space;
    setFixedHeight (height_fix);
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
        setHdrGeom (column, widget);
        widget->show ();
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QWidget *DbViewColHdr::control (int column)
{
    if (controls_.count() <= column)
        return NULL;
    return controls_[column];
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::setHdrGeom (
        int column, QWidget * widget, int width, int delta)
{
    if (isSectionHidden (column)) {
        widget->hide();
        return;
    } else if (!widget->isVisible()) {
        widget->show ();
    }

    if (width == -1) {
        width = sectionSize (column);
    }
    width -= horiz_space*2;
    if (width <= 0) {
        widget->hide();
        return;
    }

    if (widget == NULL) {
        if (column >= controls_.count())
            return;
        widget = controls_[column];
        if (widget == NULL)
            return;
    }


    if (column > count ()) {
        widget->hide ();
        qWarning () << "Cannot set header geometry for widget because the index "
                    << column << " is out of valid range [0; "
                    << count()
                    << ")";
    } else {
        int posx = sectionPosition (column) + horiz_space - delta;
        if (posx+width < 0) {
            return;
        }
        int posy = vert_space*2+half_;
        int h = widget->sizeHint().height();
        int h_lim = half_-2*vert_space;
        if (h > h_lim) {
            h = h_lim;
        } else {
            posy += (h_lim - h) / 2;
        }
        widget->setGeometry (QRect (posx, posy, width, h));
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::paintSection (
        QPainter *painter, const QRect &rect, int column) const
{
    // const QList<DbViewColFilter*> & filters = table_->colFilters ();
    QHeaderView::paintSection (painter, rect, column);
//    if (!table_->hasFilter (column)) {
//        QHeaderView::paintSection (painter, rect, column);
//        return;
//    } else {
//        painter->fillRect (rect, painter->brush());
//       // painter->draw (rect, painter->brush());

//    }
}
/* ========================================================================= */

#if 0
/* ------------------------------------------------------------------------- */
void DbViewColHdr::paintSection (
        QPainter *painter, const QRect &rect, int column) const
{
    // const QList<DbViewColFilter*> & filters = table_->colFilters ();
//    if (!table_->hasFilter (column)) {
//        QHeaderView::paintSection (painter, rect, column);
//        return;
//    } else {
//        painter->fillRect (rect, painter->brush());
//       // painter->draw (rect, painter->brush());

//    }

    if (!rect.isValid())
        return;
    QAbstractItemModel * mm = model ();


    // get the state of the section
    QStyleOptionHeader opt;
    initStyleOption(&opt);
    QStyle::State state = QStyle::State_None;
    if (isEnabled())
        state |= QStyle::State_Enabled;
    if (window()->isActiveWindow())
        state |= QStyle::State_Active;
    if (sectionsClickable()) {
        QPoint mousepos = mapFromGlobal (QCursor::pos());
        int hover = logicalIndexAt (mousepos);
        if (column == hover)
            state |= QStyle::State_MouseOver;
//        if (column == d->pressed)
//            state |= QStyle::State_Sunken;
        else if (highlightSections()) {
//            if (d->sectionIntersectsSelection(column))
//                state |= QStyle::State_On;
//            if (d->isSectionSelected(column))
//                state |= QStyle::State_Sunken;
        }

    }
    if (isSortIndicatorShown() && sortIndicatorSection() == column)
        opt.sortIndicator = (sortIndicatorOrder() == Qt::AscendingOrder)
                            ? QStyleOptionHeader::SortDown : QStyleOptionHeader::SortUp;

    // setup the style options structure
    opt.rect = rect;
    opt.section = column;
    opt.state |= state;
    opt.textAlignment = Qt::AlignHCenter | Qt::AlignTop;

    opt.iconAlignment = Qt::AlignLeft | Qt::AlignTop;
    opt.text = mm->headerData(
                column, Qt::Horizontal, Qt::DisplayRole).toString();

    int margin = 2 * style()->pixelMetric (QStyle::PM_HeaderMargin, 0, this);

    const Qt::Alignment headerArrowAlignment = static_cast<Qt::Alignment>(style()->styleHint(QStyle::SH_Header_ArrowAlignment, 0, this));
    const bool isHeaderArrowOnTheSide = headerArrowAlignment & Qt::AlignVCenter;
    if (isSortIndicatorShown() && sortIndicatorSection() == column && isHeaderArrowOnTheSide)
        margin += style()->pixelMetric(QStyle::PM_HeaderMarkSize, 0, this);

    if (textElideMode() != Qt::ElideNone)
        opt.text = opt.fontMetrics.elidedText(
                    opt.text, textElideMode(), rect.width() - margin);

    QVariant variant = mm->headerData(column, Qt::Horizontal,
                                    Qt::DecorationRole);
    opt.icon = qvariant_cast<QIcon>(variant);
    if (opt.icon.isNull())
        opt.icon = qvariant_cast<QPixmap>(variant);
    QVariant foregroundBrush = mm->headerData(
                column, Qt::Horizontal, Qt::ForegroundRole);
    if (foregroundBrush.canConvert<QBrush>())
        opt.palette.setBrush(
                    QPalette::ButtonText,
                    qvariant_cast<QBrush>(foregroundBrush));

    QPointF oldBO = painter->brushOrigin();
    QVariant backgroundBrush = mm->headerData (
                column, Qt::Horizontal, Qt::BackgroundRole);
    if (backgroundBrush.canConvert<QBrush>()) {
        opt.palette.setBrush(QPalette::Button, qvariant_cast<QBrush>(backgroundBrush));
        opt.palette.setBrush(QPalette::Window, qvariant_cast<QBrush>(backgroundBrush));
        painter->setBrushOrigin(opt.rect.topLeft());
    }

    // the section position
    int visual = visualIndex(column);
    Q_ASSERT(visual != -1);
    bool first = visual == 0;
    bool last = visual == count()-1;
    if (first && last)
        opt.position = QStyleOptionHeader::OnlyOneSection;
    else if (first)
        opt.position = QStyleOptionHeader::Beginning;
    else if (last)
        opt.position = QStyleOptionHeader::End;
    else
        opt.position = QStyleOptionHeader::Middle;
    opt.orientation = Qt::Horizontal;
    // the selected position
    opt.selectedPosition = QStyleOptionHeader::NotAdjacent;
    // draw the section
    style()->drawControl (QStyle::CE_Header, &opt, painter, this);

    painter->setBrushOrigin(oldBO);
}
/* ========================================================================= */
#endif

/* ------------------------------------------------------------------------- */
void DbViewColHdr::resizeControl (int column, int oldSize, int newSize)
{
    Q_UNUSED(oldSize);
    Q_UNUSED(newSize);
    if (controls_.count() <= column)
        return;

    positionControls (column);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static const char * widget_column_key = "widget_column_key";
void DbViewColHdr::setWidgetColumn (QWidget *wdg, int column)
{
    wdg->setProperty(widget_column_key, column);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbViewColHdr::widgetColumn (QWidget *wdg)
{
    bool b_ok;
    int result = wdg->property(widget_column_key).toInt (&b_ok);
    if (!b_ok) {
        result = -1;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::removeAllControls ()
{
    foreach(QWidget * wdg, controls_) {
        if (wdg != NULL) {
            wdg->deleteLater ();
        }
    }
    controls_.clear ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::positionControls (int first, int delta)
{
    int i_max = qMin(count(), controls_.count());
    for (int i = first; i < i_max; ++i) {
        QWidget * wdg = controls_[i];
        if (wdg != NULL) {
            setHdrGeom (i, wdg, -1, delta);
        }
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColHdr::filterTriggerByFilters ()
{
    QWidget * wdg = qobject_cast<QWidget *>(sender ());
    if (wdg == NULL) {
        return;
    }

    int col = DbViewColHdr::widgetColumn (wdg);
    if (col == -1)
        return;

    emit filterChanged(col);
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
