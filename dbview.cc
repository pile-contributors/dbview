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
    ui(new Ui::DbView)
{
    DBVIEW_TRACE_ENTRY;
    ui->setupUi(this);

    connect(ui->tableView, &QAbstractItemView::iconSizeChanged,
            this, &DbTableView::iconSizeChanged);
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

/* ------------------------------------------------------------------------- */
/**
 * If at all possible avoid working directly with internal table view.
 */
QTableView *DbTableView::internalTableView ()
{
    return ui->tableView;
}
/* ========================================================================= */


void DbTableView::setModel (QAbstractItemModel *model)
{
    ui->tableView->setModel (model);
}

QAbstractItemModel * DbTableView::model () const
{
    return ui->tableView->model ();
}

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


