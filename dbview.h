/**
 * @file dbview.h
 * @brief Declarations for DbTableView class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_DBTABLEVIEW_H_INCLUDE
#define GUARD_DBTABLEVIEW_H_INCLUDE

#include <dbview/dbview-config.h>
#include <QTableView>

class DbViewMo;
class DbViewColFilter;

namespace Ui {
class DbView;
}

namespace impl {
class InMo;
}

//! A table view of a database table.
class DBVIEW_EXPORT DbTableView : public QWidget {
    Q_OBJECT

    Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid)
    Q_PROPERTY(Qt::PenStyle gridStyle READ gridStyle WRITE setGridStyle)
    Q_PROPERTY(bool sortingEnabled READ isSortingEnabled WRITE setSortingEnabled)
    Q_PROPERTY(bool wordWrap READ wordWrap WRITE setWordWrap)
    Q_PROPERTY(bool autoScroll READ hasAutoScroll WRITE setAutoScroll)
    Q_PROPERTY(int autoScrollMargin READ autoScrollMargin WRITE setAutoScrollMargin)
    Q_PROPERTY(QAbstractItemView::EditTriggers editTriggers READ editTriggers WRITE setEditTriggers)
    Q_PROPERTY(bool tabKeyNavigation READ tabKeyNavigation WRITE setTabKeyNavigation)
#ifndef QT_NO_DRAGANDDROP
    Q_PROPERTY(bool showDropIndicator READ showDropIndicator WRITE setDropIndicatorShown)
    Q_PROPERTY(bool dragEnabled READ dragEnabled WRITE setDragEnabled)
    Q_PROPERTY(bool dragDropOverwriteMode READ dragDropOverwriteMode WRITE setDragDropOverwriteMode)
    Q_PROPERTY(QAbstractItemView::DragDropMode dragDropMode READ dragDropMode WRITE setDragDropMode)
    Q_PROPERTY(Qt::DropAction defaultDropAction READ defaultDropAction WRITE setDefaultDropAction)
#endif
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(QTableView::SelectionMode selectionMode READ selectionMode WRITE setSelectionMode)
    Q_PROPERTY(QTableView::SelectionBehavior selectionBehavior READ selectionBehavior WRITE setSelectionBehavior)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
    Q_PROPERTY(Qt::TextElideMode textElideMode READ textElideMode WRITE setTextElideMode)
    Q_PROPERTY(QTableView::ScrollMode verticalScrollMode READ verticalScrollMode WRITE setVerticalScrollMode RESET resetVerticalScrollMode)
    Q_PROPERTY(QTableView::ScrollMode horizontalScrollMode READ horizontalScrollMode WRITE setHorizontalScrollMode RESET resetHorizontalScrollMode)

public:

    //! Default constructor.
    DbTableView (
            QWidget *parent = 0);

    //! Destructor.
    virtual ~DbTableView();

    //! Get a pointer to internal table view.
    virtual QTableView*
    internalTableView () const;

    //! Change the model that we're presenting.
    virtual void
    setUserModel (
            DbViewMo *model);

    //! Get the model that we're presenting.
    virtual  DbViewMo *
    userModel () const;

    //! Restores visible status to the one saved inside.
    void
    restoreVisibleStatus ();

    //! Set the index of the current page.
    void
    setPageIndex (
            int value);

    //! Index of the current page.
    int
    pageIndex() const;

    //! Index of the first row on current page.
    int
    firstRowIndex () const;

    //! Change first row.
    void
    setFirstRowIndex (
            int value);

    //! Number of rows this model has.
    int
    crtRowCount() const;

    //! Number of rows per page.
    int
    pageRowCount() const;



public Q_SLOTS:

    //! Reaquire the data.
    virtual void
    f5 ();

    void
    downloadAsCsv ();

    void
    goToPage (
            int value);

    void
    goToNextPage ();

    void
    goToPreviousPage ();

    //! Forwards the call to setRowsPerPage().
    void
    set10RowsPerPage ();

    //! Forwards the call to setRowsPerPage().
    void
    set25RowsPerPage ();

    //! Forwards the call to setRowsPerPage().
    void
    set50RowsPerPage ();

    //! Forwards the call to setRowsPerPage().
    void
    set100RowsPerPage ();

    //! Change the number of rows in a page.
    void
    setRowsPerPage (
            int value);

private Q_SLOTS:

    //! Handles signals from the left-most page number button.
    void
    goToPageLeft ();

    //! Handles signals from the center page number button.
    void
    goToPageCenter ();

    //! Handles signals from the right-most page number button.
    void
    goToPageRight ();

    //! We're informed that the index of current page changed.
    void
    pageIndexChanged (
        int value);

    //! We're informed that the number of rows in each page changed.
    void
    rowsPerPageChanged (
        int value);


    void
    modelWasResetted ();

    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name Filters
     * This section deals with filters that may be applied
     * to columns. The implementation is based on a list of
     * DbViewColFilter that are owned by this instance
     * and deal with the GUI control and the filter value
     * that is send back to the model through its
     * DbViewMo::reloadWithFilters() method.
     */
    ///@{

public:
    void
    updateFiltersFromWidgets() const;

    //! Get the filters to be used with the model.
    const QList<DbViewColFilter*> &
    colFilters () const;

    //! Tell if a column has a filter installed.
    bool
    hasFilter (
            int column) const;

    //! Filter contents in a column using a simple string filtering.
    virtual void
    setColumnFilter (
            int column,
            bool include,
            const QString & value);

    //! Filter contents in a column using a custom filtering.
    virtual void
    setColumnFilter (
            int column,
            bool include,
            const QStringList & value);

    //! Filter contents in a column using a custom filtering.
    virtual void
    setColumnFilterChoice (
            int column,
            bool include,
            const QStringList & value);

    //! Filter contents in a column using a custom filtering.
    virtual void
    setColumnFilter (
            int column,
            DbViewColFilter * filter);

private:

    //! Update the header to show proper widgets.
    void
    setAllFilterWidgets ();

    //! Remove any widgets that we have set fopr header.
    void
    clearAllFilterWidgets ();

    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */




    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name QAbstractItemView Emulation
     * Methods with same signature as those found in
     * QAbstractItemView.
     */
    ///@{
public:
    QAbstractScrollArea::Shape frameShape() const;
    void setFrameShape(QAbstractScrollArea::Shape);
    QAbstractScrollArea::Shadow frameShadow() const;
    void setFrameShadow(QAbstractScrollArea::Shadow);

    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */


    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name QAbstractItemView Emulation
     * Methods with same signature as those found in
     * QAbstractItemView.
     */
    ///@{


    void setItemDelegate(QAbstractItemDelegate *delegate);
    QAbstractItemDelegate *itemDelegate() const;

    void setSelectionMode(QAbstractItemView::SelectionMode mode);
    QAbstractItemView::SelectionMode selectionMode() const;

    void setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior);
    QAbstractItemView::SelectionBehavior selectionBehavior() const;

    QModelIndex currentIndex() const;
    QModelIndex rootIndex() const;

    void setEditTriggers(QAbstractItemView::EditTriggers triggers);
    QAbstractItemView::EditTriggers editTriggers() const;

    void setVerticalScrollMode(QAbstractItemView::ScrollMode mode);
    QAbstractItemView::ScrollMode verticalScrollMode() const;
    void resetVerticalScrollMode();

    void setHorizontalScrollMode(QAbstractItemView::ScrollMode mode);
    QAbstractItemView::ScrollMode horizontalScrollMode() const;
    void resetHorizontalScrollMode();

    void setAutoScroll(bool enable);
    bool hasAutoScroll() const;

    void setAutoScrollMargin(int margin);
    int autoScrollMargin() const;

    void setTabKeyNavigation(bool enable);
    bool tabKeyNavigation() const;

#ifndef QT_NO_DRAGANDDROP
    void setDropIndicatorShown(bool enable);
    bool showDropIndicator() const;

    void setDragEnabled(bool enable);
    bool dragEnabled() const;

    void setDragDropOverwriteMode(bool overwrite);
    bool dragDropOverwriteMode() const;

    void setDragDropMode(QAbstractItemView::DragDropMode behavior);
    QAbstractItemView::DragDropMode dragDropMode() const;

    void setDefaultDropAction(Qt::DropAction dropAction);
    Qt::DropAction defaultDropAction() const;
#endif

    void setAlternatingRowColors(bool enable);
    bool alternatingRowColors() const;

    void setIconSize(const QSize &size);
    QSize iconSize() const;

    void setTextElideMode(Qt::TextElideMode mode);
    Qt::TextElideMode textElideMode() const;

    virtual void keyboardSearch(const QString &search);

    void openPersistentEditor(const QModelIndex &index);
    void closePersistentEditor(const QModelIndex &index);

    void setIndexWidget(const QModelIndex &index, QWidget *widget);
    QWidget *indexWidget(const QModelIndex &index) const;

    void setItemDelegateForRow(int row, QAbstractItemDelegate *delegate);
    QAbstractItemDelegate *itemDelegateForRow(int row) const;

    void setItemDelegateForColumn(int column, QAbstractItemDelegate *delegate);
    QAbstractItemDelegate *itemDelegateForColumn(int column) const;

    QAbstractItemDelegate *itemDelegate(const QModelIndex &index) const;

    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const;


    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */


    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
    /** @name QTableView Emulation
     * Methods with same signature as those found in
     * QTableView.
     */
    ///@{

private:
    virtual void setModel(QAbstractItemModel *model) {}
    virtual QAbstractItemModel * model () const;

    virtual void setRootIndex(const QModelIndex &index);
    virtual void setSelectionModel(QItemSelectionModel *selectionModel);
    virtual QItemSelectionModel* selectionModel() const;
    virtual void doItemsLayout();

public:
    QHeaderView *horizontalHeader() const;
    QHeaderView *verticalHeader() const;
    void setHorizontalHeader(QHeaderView *header);
    void setVerticalHeader(QHeaderView *header);

    int rowViewportPosition(int row) const;
    int rowAt(int y) const;

    void setRowHeight(int row, int height);
    int rowHeight(int row) const;

    int columnViewportPosition(int column) const;
    int columnAt(int x) const;

    void setColumnWidth(int column, int width);
    int columnWidth(int column) const;

    bool isRowHidden(int row) const;
    void setRowHidden(int row, bool hide);

    bool isColumnHidden(int column) const;
    void setColumnHidden(int column, bool hide);

    void setSortingEnabled(bool enable);
    bool isSortingEnabled() const;

    bool showGrid() const;

    Qt::PenStyle gridStyle() const;
    void setGridStyle(Qt::PenStyle style);

    void setWordWrap(bool on);
    bool wordWrap() const;

    void setCornerButtonEnabled(bool enable);
    bool isCornerButtonEnabled() const;

    virtual QRect visualRect(const QModelIndex &index) const;
    virtual void scrollTo(const QModelIndex &index, QTableView::ScrollHint hint = QTableView::EnsureVisible);
    virtual QModelIndex indexAt(const QPoint &p) const;

    void setSpan(int row, int column, int rowSpan, int columnSpan);
    int rowSpan(int row, int column) const;
    int columnSpan(int row, int column) const;
    void clearSpans();

    void sortByColumn(int column, Qt::SortOrder order);


    void selectRow(int row);
    void selectColumn(int column);
    void hideRow(int row);
    void hideColumn(int column);
    void showRow(int row);
    void showColumn(int column);
    void resizeRowToContents(int row);
    void resizeRowsToContents();
    void resizeColumnToContents(int column);
    void resizeColumnsToContents();
    void sortByColumn(int column);
    void setShowGrid(bool show);

private Q_SLOTS:

    void whenCurrentChanged (const QModelIndex &current, const QModelIndex &previous);
    void whenCurrentRowChanged (const QModelIndex &current, const QModelIndex &previous);
    void whenCurrentColumnChanged (const QModelIndex &current, const QModelIndex &previous);


    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

Q_SIGNALS:

    void
    iconSizeChanged (
            const QSize &size);

    void
    currentRowChanged (
            int crt_row,
            int prev_row);

    void
    currentColumnChanged (
            int crt_col,
            int prev_col);

    void
    currentChanged (
            int crt_row,
            int crt_col,
            int prev_row,
            int prev_col);

    void
    selectionChanged (
            const QItemSelection &selected,
            const QItemSelection &deselected);

protected:

private:
    Ui::DbView *ui;
    impl::InMo * inmo;
};

#endif // GUARD_DBTABLEVIEW_H_INCLUDE
