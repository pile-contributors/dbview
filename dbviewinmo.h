#ifndef DBVIEWINMO_H
#define DBVIEWINMO_H

#include <QAbstractTableModel>

class DbViewMo;
class DbViewColFilter;

namespace impl
{

//! Internal model used by the tableview.
class InMo : public QAbstractTableModel
{
    Q_OBJECT

public:

    //! Default constructor.
    explicit
    InMo(
            QObject *parent = 0);

    //! The model that has actual data.
    DbViewMo *
    userModel () const {
        return user_model_;
    }

    //! Change the model that has actual data.
    void
    setUserModel (
            DbViewMo *model);

    QVariant
    headerData (
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole) const override;

    int
    rowCount (
            const QModelIndex &parent = QModelIndex()) const override;

    int
    columnCount (
            const QModelIndex &parent = QModelIndex()) const override;

    QVariant
    data (
            const QModelIndex &index,
            int role = Qt::DisplayRole) const override;

    //! The user requested data to be filtered.
    virtual void
    reloadWithFilters ();

    //! Number of rows this model has.
    int
    crtRowCount() const {
        return crt_row_count_;
    }

    //! Number of rows per page.
    int
    pageRowCount() const {
        return page_row_count_;
    }

    //! Set the number of rows per page.
    void
    setPageRowCount (
            int value);

    //! Set the number of rows per page - no side effects.
    void
    justSetPageRowCount (
            int value) {
        Q_ASSERT(value > 0);
        page_row_count_ = value;
    }

    //! Set the model to provide a certain page.
    void
    goToPage (
            int value);


    //! Index of the current page.
    int
    pageIndex() const {
        return page_index_;
    }

    //! Set the index of the current page.
    void
    setPageIndex (
            int value);

    //! Set the index of the current page - no side effects.
    void
    justSetPageIndex (
            int value) {
        Q_ASSERT(value > 0);
        page_index_ = value;
    }

    //! Index of the first row on current page.
    int
    firstRowIndex () const {
        return first_row_index_;
    }

    //! Change the index of the first row on current page.
    void
    setFirstRowIndex (
            int value);

    //! The total number of pages.
    int
    pagesCount () const {
        return pages_count_;
    }



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

    //! Get the filters to be used with the model.
    const QList<DbViewColFilter*> &
    colFilters () const {
        return filters_;
    }

    //! Tell if a column has a filter installed.
    bool
    hasFilter (
            int column) const {
        if (filters_.count() <= column)
            return false;
        return (filters_[column] != NULL);
    }

    //! Filter contents in a column using a custom filtering.
    virtual void
    setColumnFilter (
            int column,
            DbViewColFilter * value);

    //! Delete all filters.
    void
    eraseFilters ();

private:

    //! Change a filter to the one specified in argument.
    void
    changeFilterData (
            int column,
            DbViewColFilter * value);

    ///@}
    /*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */




public slots:

    //! Connect to this slot any signals that inform about the data we cache.
    virtual void
    reloadCachedData ();

private:
    void connectModel (DbViewMo *model);
    void disconnectModel ();


    DbViewMo * user_model_; /**< Changed by the user. */
    int page_row_count_; /**< Changed by the user. */
    int page_index_; /**< Changed by the user; zero-based. */
    QList<DbViewColFilter*> filters_; /**< The list of filters (expands as required). */
    bool separate_thread_; /**< aquiure data using a separate thread */
    int ms_timeout_; /**< Timeout for the separate thread in miliseconds. */

    int crt_row_count_; /**< derived from underlying model */
    int first_row_index_; /**< derived from page_index_; zero-based */
    int pages_count_; /**< derived from underlying model */
};
} // namespace impl

#endif // DBVIEWINMO_H
