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
#include "ui_dbview.h"
#include "dbviewinmo.h"
#include "dbviewmo.h"
#include "dbviewcolhdr.h"
#include "dbviewcolfilter.h"
#include "dbviewcolhdr.h"

#include <QWidget>

static QLatin1String s_one("1");
static QLatin1String s_two("2");
static QLatin1String s_three("3");
static const char * pgidx = "pgidx";


/**
 * @class DbView
 *
 * .
 */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for constructor.
 */
DbTableView::DbTableView(
        QWidget *parent) :
    QWidget (parent),
    ui(new Ui::DbView),
    inmo(new impl::InMo (this))
{
    DBVIEW_TRACE_ENTRY;
    ui->setupUi(this);

    // TODO: As it is not yet implemented we will hide it for now
    ui->tbDownload->hide();

    connect(ui->tableView, &QAbstractItemView::iconSizeChanged,
            this, &DbTableView::iconSizeChanged);

    connect(inmo, &QAbstractItemModel::modelReset,
            this, &DbTableView::modelWasResetted);

    connect(ui->tb1, &QToolButton::clicked,
            this, &DbTableView::goToPageLeft);
    connect(ui->tb2, &QToolButton::clicked,
            this, &DbTableView::goToPageCenter);
    connect(ui->tb3, &QToolButton::clicked,
            this, &DbTableView::goToPageRight);
    connect(ui->tbPrev, &QToolButton::clicked,
            this, &DbTableView::goToPreviousPage);
    connect(ui->tbNext, &QToolButton::clicked,
            this, &DbTableView::goToNextPage);

    connect(ui->tbPg10, &QToolButton::clicked,
            this, &DbTableView::set10RowsPerPage);
    connect(ui->tbPg25, &QToolButton::clicked,
            this, &DbTableView::set25RowsPerPage);
    connect(ui->tbPg50, &QToolButton::clicked,
            this, &DbTableView::set50RowsPerPage);
    connect(ui->tbPg100, &QToolButton::clicked,
            this, &DbTableView::set100RowsPerPage);

    connect(ui->tbDownload, &QToolButton::clicked,
            this, &DbTableView::downloadAsCsv);

    DbViewColHdr * hdr = new DbViewColHdr (this, this);
    setHorizontalHeader (hdr);
    hdr->setSectionsClickable (true);
    connect(hdr, &DbViewColHdr::filterChanged,
            this, &DbTableView::f5);

    setSortingEnabled (true);

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
    inmo->eraseFilters ();
    // inmo deleted by parent-son relation
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * If at all possible avoid working directly with internal table view.
 */
QTableView *DbTableView::internalTableView () const
{
    return ui->tableView;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setUserModel (DbViewMo *model)
{
    DBVIEW_TRACE_ENTRY;
    QItemSelectionModel * sm = ui->tableView->selectionModel ();
    if (sm != NULL) {
        disconnect(sm, &QItemSelectionModel::currentRowChanged,
                   this, &DbTableView::whenCurrentRowChanged);
        disconnect(sm, &QItemSelectionModel::currentColumnChanged,
                   this, &DbTableView::whenCurrentColumnChanged);
        disconnect(sm, &QItemSelectionModel::currentChanged,
                   this, &DbTableView::whenCurrentChanged);
        disconnect(sm, &QItemSelectionModel::selectionChanged,
                   this, &DbTableView::selectionChanged);
    }


    inmo->eraseFilters ();
    ui->tableView->setModel (NULL);
    inmo->setUserModel (model);
    ui->tableView->setModel (inmo);
    setAllFilterWidgets ();
    pageIndexChanged (0);


    sm = ui->tableView->selectionModel ();
    if (sm != NULL) {
        connect(sm, &QItemSelectionModel::currentRowChanged,
                this, &DbTableView::whenCurrentRowChanged);
        connect(sm, &QItemSelectionModel::currentColumnChanged,
                this, &DbTableView::whenCurrentColumnChanged);
        connect(sm, &QItemSelectionModel::currentChanged,
                this, &DbTableView::whenCurrentChanged);
        connect(sm, &QItemSelectionModel::selectionChanged,
                this, &DbTableView::selectionChanged);
    }

    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewMo *DbTableView::userModel () const
{
    return inmo->userModel ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::restoreVisibleStatus()
{
    int i_max = inmo->columnCount ();
    for (int i = 0; i < i_max; ++i) {
        bool b_hidden = !inmo->isColumnVisible (i);
        ui->tableView->setColumnHidden (i, b_hidden);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::f5 ()
{
    DBVIEW_TRACE_ENTRY;
    updateFiltersFromWidgets ();
    inmo->reloadWithFilters ();
    restoreVisibleStatus ();
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::updateFiltersFromWidgets () const
{
    DBVIEW_TRACE_ENTRY;
    const QList<DbViewColFilter*> & filt = inmo->colFilters ();
    int i_max = qMin(filt.count (), inmo->columnCount ());
    DbViewColHdr * hhdr = static_cast<DbViewColHdr*>(horizontalHeader ());
    for (int i = 0; i < i_max; ++i) {
        DbViewColFilter* filter = filt[i];
        if (filter != NULL) {
            QWidget * wdg = hhdr->control (i);
            if (filter != NULL) {
                filter->updateFromWidget (wdg, i);
            }
        }
    }
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setColumnFilter (
        int column, bool include, const QString &value)
{
    DBVIEW_TRACE_ENTRY;
    setColumnFilter (column, new DbViewColFilterPattern (value, include));
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setColumnFilter (
        int column, bool include, const QStringList &value)
{
    DBVIEW_TRACE_ENTRY;
    setColumnFilter (column, new DbViewColFilterList (value, include));
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setColumnFilterChoice (
        int column, bool include, const QStringList &value)
{
    DBVIEW_TRACE_ENTRY;
    setColumnFilter (column, new DbViewColFilterChoice (value, -1, include));
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * This allows the user full control over the filtering including
 * the widget used for changing the values and the result that is returned
 * to collectFilters().
 *
 * @param column The index of the column where this is to be installed.
 * @param value the custom filtering class; ownership of the pointer is
 * transferred to this instance
 */
void DbTableView::setColumnFilter (int column, DbViewColFilter * filter)
{
    DBVIEW_TRACE_ENTRY;
    inmo->setColumnFilter (column, filter);

    DbViewColHdr * hhdr = static_cast<DbViewColHdr*>(horizontalHeader ());
    if (filter != NULL) {
        QWidget * wdg = NULL;
        wdg = filter->createControl (column, hhdr);
        if (wdg != NULL) {
            hhdr->setControl (column, wdg);
        }
    }
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setAllFilterWidgets ()
{
    DBVIEW_TRACE_ENTRY;
    DbViewColHdr * hhdr = static_cast<DbViewColHdr*>(horizontalHeader ());
    hhdr->removeAllControls ();

    const QList<DbViewColFilter*> & filters = inmo->colFilters ();

    int i_max = inmo->columnCount ();

    for (int i = 0; i < i_max; ++i) {
        QWidget * wdg = NULL;
        if (i < filters.count()) {
            DbViewColFilter* filter = filters[i];
            if (filter != NULL) {
                wdg = filter->createControl (i, hhdr);
                if (wdg != NULL) {
                    hhdr->setControl (i, wdg);
                }
            }
        }
    }
    DBVIEW_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QAbstractItemModel * DbTableView::model () const
{
    return inmo->userModel ()->qtModel ();
}
/* ========================================================================= */

void DbTableView::setRootIndex (const QModelIndex &index)
{
    ui->tableView->setRootIndex (index);
}

void DbTableView::setSelectionModel(QItemSelectionModel *selectionModel)
{
    ui->tableView->setSelectionModel (selectionModel);
}

QItemSelectionModel * DbTableView::selectionModel() const
{
    return ui->tableView->selectionModel ();
}

void DbTableView::doItemsLayout()
{
    ui->tableView->doItemsLayout ();
}

QHeaderView *DbTableView::horizontalHeader() const
{
    return ui->tableView->horizontalHeader ();
}

QHeaderView *DbTableView::verticalHeader() const
{
    return ui->tableView->verticalHeader ();
}

void DbTableView::setHorizontalHeader(QHeaderView *header)
{
    ui->tableView->setHorizontalHeader (header);
}

void DbTableView::setVerticalHeader(QHeaderView *header)
{
    ui->tableView->setVerticalHeader (header);
}


int DbTableView::rowViewportPosition(int row) const
{
    return ui->tableView->rowViewportPosition (row);
}

int DbTableView::rowAt(int y) const
{
    return ui->tableView->rowAt (y);
}


void DbTableView::setRowHeight(int row, int height)
{
    ui->tableView->setRowHeight (row, height);
}

int DbTableView::rowHeight(int row) const
{
    return ui->tableView->rowHeight (row);
}


int DbTableView::columnViewportPosition(int column) const
{
    return ui->tableView->columnViewportPosition (column);
}

int DbTableView::columnAt(int x) const
{
    return ui->tableView->columnAt (x);
}


void DbTableView::setColumnWidth(int column, int width)
{
    ui->tableView->setColumnWidth (column, width);
}

int DbTableView::columnWidth(int column) const
{
    return ui->tableView->columnWidth (column);
}


bool DbTableView::isRowHidden(int row) const
{
    return ui->tableView->isRowHidden (row);
}

void DbTableView::setRowHidden(int row, bool hide)
{
    ui->tableView->setRowHidden (row, hide);
}


bool DbTableView::isColumnHidden(int column) const
{
    return ui->tableView->isColumnHidden (column);
}

void DbTableView::setColumnHidden(int column, bool hide)
{
    ui->tableView->setColumnHidden (column, hide);
    inmo->setColumnHidden (column, hide);
}

void DbTableView::setSortingEnabled(bool enable)
{
    ui->tableView->setSortingEnabled (enable);
}

bool DbTableView::isSortingEnabled() const
{
    return ui->tableView->isSortingEnabled ();
}

bool DbTableView::showGrid() const
{
    return ui->tableView->showGrid ();
}

Qt::PenStyle DbTableView::gridStyle() const
{
    return ui->tableView->gridStyle ();
}

void DbTableView::setGridStyle(Qt::PenStyle style)
{
    ui->tableView->setGridStyle (style);
}


void DbTableView::setWordWrap(bool on)
{
    ui->tableView->setWordWrap (on);
}

bool DbTableView::wordWrap() const
{
    return ui->tableView->wordWrap ();
}

void DbTableView::setCornerButtonEnabled(bool enable)
{
    ui->tableView->setCornerButtonEnabled (enable);
}

bool DbTableView::isCornerButtonEnabled() const
{
    return ui->tableView->isCornerButtonEnabled ();
}

void DbTableView::setSpan(int row, int column, int rowSpan, int columnSpan)
{
    ui->tableView->setSpan (row, column, rowSpan, columnSpan);
}

int DbTableView::rowSpan(int row, int column) const
{
    return ui->tableView->rowSpan (row, column);
}

int DbTableView::columnSpan(int row, int column) const
{
    return ui->tableView->columnSpan (row, column);
}

void DbTableView::clearSpans()
{
    ui->tableView->clearSpans ();
}

void DbTableView::sortByColumn(int column, Qt::SortOrder order)
{
    ui->tableView->sortByColumn (column, order);
}

void DbTableView::selectRow(int row)
{
    ui->tableView->selectRow (row);
}

void DbTableView::selectColumn(int column)
{
    ui->tableView->selectColumn (column);
}

void DbTableView::hideRow(int row)
{
    ui->tableView->hideRow (row);
}

void DbTableView::hideColumn(int column)
{
    ui->tableView->hideColumn (column);
}

void DbTableView::showRow(int row)
{
    ui->tableView->showRow (row);
}

void DbTableView::showColumn(int column)
{
    ui->tableView->showColumn (column);
}

void DbTableView::resizeRowToContents(int row)
{
    ui->tableView->resizeRowToContents (row);
}

void DbTableView::resizeRowsToContents()
{
    ui->tableView->resizeRowsToContents ();
}

void DbTableView::resizeColumnToContents(int column)
{
    ui->tableView->resizeColumnToContents (column);
}

void DbTableView::resizeColumnsToContents()
{
    ui->tableView->resizeColumnsToContents ();
}

void DbTableView::sortByColumn(int column)
{
    ui->tableView->sortByColumn (column);
}

void DbTableView::setShowGrid(bool show)
{
    ui->tableView->setShowGrid (show);
}

void DbTableView::whenCurrentChanged (
        const QModelIndex &current, const QModelIndex &previous)
{
    emit currentChanged (
                current.row (), current.column (),
                previous.row (), previous.column ());
}

void DbTableView::whenCurrentRowChanged (
        const QModelIndex &current, const QModelIndex &previous)
{
    emit currentRowChanged (current.row(), previous.row ());
}

void DbTableView::whenCurrentColumnChanged (
        const QModelIndex &current, const QModelIndex &previous)
{
    emit currentColumnChanged (current.column (), previous.column ());
}

void DbTableView::setItemDelegate(QAbstractItemDelegate *delegate)
{
    ui->tableView->setItemDelegate (delegate);
}

QAbstractItemDelegate *DbTableView::itemDelegate() const
{
    return ui->tableView->itemDelegate ();
}


void DbTableView::setSelectionMode(QAbstractItemView::SelectionMode mode)
{
    ui->tableView->setSelectionMode (mode);
}

QAbstractItemView::SelectionMode DbTableView::selectionMode() const
{
    return ui->tableView->selectionMode ();
}


void DbTableView::setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior)
{
    ui->tableView->setSelectionBehavior (behavior);
}

QAbstractItemView::SelectionBehavior DbTableView::selectionBehavior() const
{
    return ui->tableView->selectionBehavior ();
}


QModelIndex DbTableView::currentIndex() const
{
    return ui->tableView->currentIndex ();
}

QModelIndex DbTableView::rootIndex() const
{
    return ui->tableView->rootIndex ();
}


void DbTableView::setEditTriggers(QAbstractItemView::EditTriggers triggers)
{
    ui->tableView->setEditTriggers (triggers);
}

QAbstractItemView::EditTriggers DbTableView::editTriggers() const
{
    return ui->tableView->editTriggers ();
}


void DbTableView::setVerticalScrollMode(QAbstractItemView::ScrollMode mode)
{
    ui->tableView->setVerticalScrollMode (mode);
}

QAbstractItemView::ScrollMode DbTableView::verticalScrollMode() const
{
    return ui->tableView->verticalScrollMode ();
}

void DbTableView::resetVerticalScrollMode()
{
    ui->tableView->resetVerticalScrollMode ();
}


void DbTableView::setHorizontalScrollMode(QAbstractItemView::ScrollMode mode)
{
    ui->tableView->setHorizontalScrollMode (mode);
}

QAbstractItemView::ScrollMode DbTableView::horizontalScrollMode() const
{
    return ui->tableView->horizontalScrollMode ();
}

void DbTableView::resetHorizontalScrollMode()
{
    ui->tableView->resetHorizontalScrollMode ();
}


void DbTableView::setAutoScroll(bool enable)
{
    ui->tableView->setAutoScroll (enable);
}

bool DbTableView::hasAutoScroll() const
{
    return ui->tableView->hasAutoScroll ();
}


void DbTableView::setAutoScrollMargin(int margin)
{
    ui->tableView->setAutoScrollMargin (margin);
}

int DbTableView::autoScrollMargin() const
{
    return ui->tableView->autoScrollMargin ();
}


void DbTableView::setTabKeyNavigation(bool enable)
{
    ui->tableView->setTabKeyNavigation (enable);
}

bool DbTableView::tabKeyNavigation() const
{
    return ui->tableView->tabKeyNavigation ();
}


#ifndef QT_NO_DRAGANDDROP
void DbTableView::setDropIndicatorShown(bool enable)
{
    ui->tableView->setDropIndicatorShown (enable);
}

bool DbTableView::showDropIndicator() const
{
    return ui->tableView->showDropIndicator ();
}


void DbTableView::setDragEnabled(bool enable)
{
    ui->tableView->setDragEnabled (enable);
}

bool DbTableView::dragEnabled() const
{
    return ui->tableView->dragEnabled ();
}

void DbTableView::setDragDropOverwriteMode(bool overwrite)
{
    ui->tableView->setDragDropOverwriteMode (overwrite);
}

bool DbTableView::dragDropOverwriteMode() const
{
    return ui->tableView->dragDropOverwriteMode ();
}

void DbTableView::setDragDropMode(QAbstractItemView::DragDropMode behavior)
{
    ui->tableView->setDragDropMode (behavior);
}

QAbstractItemView::DragDropMode DbTableView::dragDropMode() const
{
    return ui->tableView->dragDropMode ();
}


void DbTableView::setDefaultDropAction(Qt::DropAction dropAction)
{
    ui->tableView->setDefaultDropAction (dropAction);
}

Qt::DropAction DbTableView::defaultDropAction() const
{
    return ui->tableView->defaultDropAction ();
}

#endif

void DbTableView::setAlternatingRowColors(bool enable)
{
    ui->tableView->setAlternatingRowColors (enable);
}

bool DbTableView::alternatingRowColors() const
{
    return ui->tableView->alternatingRowColors ();
}


void DbTableView::setIconSize(const QSize &size)
{
    return ui->tableView->setIconSize (size);
}

QSize DbTableView::iconSize() const
{
    return ui->tableView->iconSize ();
}

void DbTableView::setTextElideMode(Qt::TextElideMode mode)
{
    ui->tableView->setTextElideMode (mode);
}

Qt::TextElideMode DbTableView::textElideMode() const
{
    return ui->tableView->textElideMode ();
}

void DbTableView::keyboardSearch(const QString &search)
{
    ui->tableView->keyboardSearch (search);
}

QRect DbTableView::visualRect(const QModelIndex &index) const
{
    return ui->tableView->visualRect (index);
}

void DbTableView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    ui->tableView->scrollTo (index, hint);
}

QModelIndex DbTableView::indexAt(const QPoint &point) const
{
    return ui->tableView->indexAt (point);
}

void DbTableView::openPersistentEditor(const QModelIndex &index)
{
    ui->tableView->openPersistentEditor (index);
}

void DbTableView::closePersistentEditor(const QModelIndex &index)
{
    ui->tableView->closePersistentEditor (index);
}

void DbTableView::setIndexWidget(const QModelIndex &index, QWidget *widget)
{
    ui->tableView->setIndexWidget (index, widget);
}

QWidget *DbTableView::indexWidget(const QModelIndex &index) const
{
    return ui->tableView->indexWidget (index);
}


void DbTableView::setItemDelegateForRow(int row, QAbstractItemDelegate *delegate)
{
    ui->tableView->setItemDelegateForRow (row, delegate);
}

QAbstractItemDelegate *DbTableView::itemDelegateForRow(int row) const
{
    return ui->tableView->itemDelegateForRow (row);
}


void DbTableView::setItemDelegateForColumn(int column, QAbstractItemDelegate *delegate)
{
    ui->tableView->setItemDelegateForColumn (column, delegate);
}

QAbstractItemDelegate *DbTableView::itemDelegateForColumn(int column) const
{
    return ui->tableView->itemDelegateForColumn (column);
}

QAbstractItemDelegate *DbTableView::itemDelegate(const QModelIndex &index) const
{
    return ui->tableView->itemDelegate (index);
}


QVariant DbTableView::inputMethodQuery(Qt::InputMethodQuery query) const
{
    return ui->tableView->inputMethodQuery (query);
}

QAbstractScrollArea::Shape DbTableView::frameShape() const
{
    return ui->tableView->frameShape ();
}

void DbTableView::setFrameShape(QAbstractScrollArea::Shape value)
{
    ui->tableView->setFrameShape (value);
}

QAbstractScrollArea::Shadow DbTableView::frameShadow() const
{
    return ui->tableView->frameShadow ();
}

void DbTableView::setFrameShadow(QAbstractScrollArea::Shadow value)
{
    ui->tableView->setFrameShadow (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setPageIndex (int value)
{
    inmo->setPageIndex (value);
    restoreVisibleStatus ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbTableView::pageIndex() const
{
    return inmo->pageIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbTableView::firstRowIndex () const
{
    return inmo->firstRowIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setFirstRowIndex (int value)
{
    inmo->setFirstRowIndex (value);
    restoreVisibleStatus ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbTableView::crtRowCount () const
{
    return inmo->crtRowCount ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbTableView::pageRowCount () const
{
    return inmo->pageRowCount ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::downloadAsCsv ()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::goToPage (int value)
{
    inmo->goToPage (value);
    restoreVisibleStatus ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::goToNextPage ()
{
    goToPage (inmo->pageIndex() + 1);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::goToPageCenter ()
{
    goToPageLeft ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::goToPageLeft ()
{
    QToolButton* tb = qobject_cast<QToolButton*>(sender());
    if (tb == NULL)
        return;
    QVariant prop = tb->property (pgidx);
    if (prop.isNull())
        return;
    goToPage (prop.toInt());
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::goToPageRight ()
{
    goToPageLeft ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::goToPreviousPage ()
{
    goToPage (inmo->pageIndex() - 1);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::set100RowsPerPage ()
{
    setRowsPerPage (100);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::set10RowsPerPage ()
{
    setRowsPerPage (10);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::set25RowsPerPage ()
{
    setRowsPerPage (25);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::set50RowsPerPage ()
{
    setRowsPerPage (50);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::setRowsPerPage (int value)
{
    inmo->setPageRowCount (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::rowsPerPageChanged (int value)
{
    // keep the buttons in sync
    bool checks[4] = {false, false, false, false};
    switch (value) {
    case 10: checks[0] = true; break;
    case 25: checks[1] = true; break;
    case 50: checks[2] = true; break;
    case 100: checks[3] = true; break;
    }
    ui->tbPg10->setChecked (checks[0]);
    ui->tbPg25->setChecked (checks[1]);
    ui->tbPg50->setChecked (checks[2]);
    ui->tbPg100->setChecked (checks[3]);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::modelWasResetted ()
{
    pageIndexChanged (inmo->pageIndex());
    rowsPerPageChanged (inmo->pageRowCount ());

    int reccnt = inmo->totalRowCount ();
    QString s_label;
    switch (reccnt) {
    case -1: {
        s_label = tr ("Invalid request");
        break; }
    case 0: {
        s_label = tr ("No records");
        break; }
    case 1: {
        s_label = tr ("1 record");
        break; }
    default: {
        tr("%1 records").arg (reccnt);
        break; }
    }
    ui->labelRecords->setText (s_label);

    restoreVisibleStatus ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
const QList<DbViewColFilter *> &DbTableView::colFilters() const
{
    return inmo->colFilters ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbTableView::hasFilter(int column) const
{
    return inmo->hasFilter (column);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbTableView::pageIndexChanged (int value)
{
    int show_value = value + 1;
    int pgcnt = inmo->pagesCount ();
    Q_ASSERT(pgcnt >= 0);

    // set the text for the three buttons in the middle
    // disable buttons that we cannot use
    // show in a distinct color the current page
    // enable/disable previous/next buttons
    if (pgcnt == 0) {
        ui->tb1->setText (s_one);
        ui->tb2->setText (s_two);
        ui->tb3->setText (s_three);
        ui->tb1->setProperty (pgidx, 0);
        ui->tb2->setProperty (pgidx, 1);
        ui->tb3->setProperty (pgidx, 2);

        ui->tb2->setEnabled (false);
        ui->tb3->setEnabled (false);
        ui->tbNext->setEnabled (false);
        ui->tbPrev->setEnabled (false);

        ui->tb1->setChecked (true);
        ui->tb2->setChecked (false);
        ui->tb3->setChecked (false);
    } else if (pgcnt == 1) {
        ui->tb1->setText (s_one);
        ui->tb2->setText (s_two);
        ui->tb3->setText (s_three);
        ui->tb1->setProperty (pgidx, 0);
        ui->tb2->setProperty (pgidx, 1);
        ui->tb3->setProperty (pgidx, 2);

        ui->tb2->setEnabled (false);
        ui->tb3->setEnabled (false);
        ui->tbNext->setEnabled (false);
        ui->tbPrev->setEnabled (false);

        ui->tb1->setChecked (true);
        ui->tb2->setChecked (false);
        ui->tb3->setChecked (false);
    } else if (pgcnt == 2) {
        ui->tb1->setText (s_one);
        ui->tb2->setText (s_two);
        ui->tb3->setText (s_three);
        ui->tb1->setProperty (pgidx, 0);
        ui->tb2->setProperty (pgidx, 1);
        ui->tb3->setProperty (pgidx, 2);

        ui->tb2->setEnabled (true);
        ui->tb3->setEnabled (false);

        ui->tb1->setChecked (false);
        ui->tb2->setChecked (true);

        if (value == 0) {
            ui->tb1->setChecked (true);
            ui->tb2->setChecked (false);

            ui->tbNext->setEnabled (true);
            ui->tbPrev->setEnabled (false);
        } else {
            ui->tb1->setChecked (false);
            ui->tb2->setChecked (true);

            ui->tbNext->setEnabled (false);
            ui->tbPrev->setEnabled (true);
        }
        ui->tb3->setChecked (false);
    } else if (value == pgcnt-1) {
        ui->tb1->setText (QString::number (show_value-2));
        ui->tb2->setText (QString::number (show_value-1));
        ui->tb3->setText (QString::number (show_value-0));
        ui->tb1->setProperty (pgidx, value-2);
        ui->tb2->setProperty (pgidx, value-1);
        ui->tb3->setProperty (pgidx, value);

        ui->tb2->setEnabled (true);
        ui->tb3->setEnabled (true);

        ui->tb1->setChecked (false);
        ui->tb2->setChecked (false);
        ui->tb3->setChecked (true);

        ui->tbNext->setEnabled (false);
        ui->tbPrev->setEnabled (true);
    } else {

        ui->tb2->setEnabled (true);
        ui->tb3->setEnabled (true);

        if (value == 0) {
            ui->tb1->setText (s_one);
            ui->tb2->setText (s_two);
            ui->tb3->setText (s_three);
            ui->tb1->setProperty (pgidx, 0);
            ui->tb2->setProperty (pgidx, 1);
            ui->tb3->setProperty (pgidx, 2);

            ui->tbPrev->setEnabled (false);

            ui->tb1->setChecked (true);
            ui->tb2->setChecked (false);
            ui->tb3->setChecked (false);
        } else {
            ui->tb1->setText (QString::number (show_value-1));
            ui->tb2->setText (QString::number (show_value));
            ui->tb3->setText (QString::number (show_value+1));
            ui->tb1->setProperty (pgidx, value-1);
            ui->tb2->setProperty (pgidx, value);
            ui->tb3->setProperty (pgidx, value+1);

            ui->tbPrev->setEnabled (true);

            ui->tb1->setChecked (false);
            ui->tb2->setChecked (true);
            ui->tb3->setChecked (false);
        }
        ui->tbNext->setEnabled (true);
    }
    restoreVisibleStatus ();
}
/* ========================================================================= */




