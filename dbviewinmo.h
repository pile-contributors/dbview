#ifndef DBVIEWINMO_H
#define DBVIEWINMO_H

#include <QAbstractTableModel>
#include <dbview/dbviewconfig.h>

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

    virtual ~InMo();

    //! The model that has actual data.
    DbViewMo *
    userModel () const {
        return user_model_;
    }

    //! Change the model that has actual data.
    void
    setUserModel (
            DbViewMo *model);

    //! Total numebr of records in underlying model.
    int
    totalRowCount () const;


    QVariant
    headerData (
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole) const override;

    //! This only returns the number of rows in current page
    int
    rowCount (
            const QModelIndex &parent = QModelIndex()) const override;

    //! The number of rows in the model.
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
        return cfg_.max_rows;
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
        cfg_.max_rows = value;
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
        return cfg_.first_row;
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

    //! We are requested to sort the model.
    virtual void
    sort (
            int column,
            Qt::SortOrder order = Qt::AscendingOrder);

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
        return cfg_.filters;
    }

    //! Tell if a column has a filter installed.
    bool
    hasFilter (
            int column) const {
        if (cfg_.filters.count() <= column)
            return false;
        return (cfg_.filters[column] != NULL);
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

    void
    runReload ();

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
    DbViewConfig cfg_;

    int page_index_; /**< Changed by the user; zero-based. */
    int crt_row_count_; /**< derived from underlying model */
    int pages_count_; /**< derived from underlying model */
};
} // namespace impl

#endif // DBVIEWINMO_H
