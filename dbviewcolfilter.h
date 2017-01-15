/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewcolfilter.h
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the definition for DbViewColFilter class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef DBVIEWCOLFILTER_H
#define DBVIEWCOLFILTER_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbview-config.h>

#include <QString>
#include <QStringList>
#include <QDoubleSpinBox>
#include <QRegExp>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class DbViewColHdr;

QT_BEGIN_NAMESPACE
class QWidget;
class QVariant;
class QAbstractItemModel;
QT_END_NAMESPACE

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! Interface for filters.
class DBVIEW_EXPORT DbViewColFilter {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

protected:

    bool include_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Default Constructor.
    DbViewColFilter (
            bool include = true);

    //! Copy constructor.
    DbViewColFilter (
            const DbViewColFilter & other) {
        include_ = other.include_;
    }

    //! destructor
    virtual ~DbViewColFilter();

    //! Is this an including filter or an exlcluding one?
    bool
    include() const;


    //! Is this an including filter or an exlcluding one?
    void
    setInclude (
            bool include);

    //! The widget to be used for filtering the content of the table.
    QWidget *
    createControl (
            int column,
            DbViewColHdr *parent);

    //! Create an exact duplicate of this one.
    virtual DbViewColFilter *
    clone() const = 0;

    //! Tell if this filter accepts provided piece of data.
    virtual bool
    acceptsData (
            const QVariant & data) const = 0;

    //! Get the filter values from inside the wisget.
    virtual void
    updateFromWidget (
            QWidget * wdg,
            int column);

protected:

    //! The widget to be used for filtering the content of the table.
    virtual QWidget *
    control (
            int column,
            DbViewColHdr *parent);

private:



public:

    //! Clones all filters in the list.
    static QList<DbViewColFilter*>
    clone (
            const QList<DbViewColFilter*> &filters);

    //! For a row in a model tell if all filters accept it.
    static bool
    acceptsRow (
            const QList<DbViewColFilter*> &filters,
            QAbstractItemModel * model,
            int row);


    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewColFilter */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! A string pattern.
class DBVIEW_EXPORT DbViewColFilterPattern : public DbViewColFilter {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    QRegExp pattern_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewColFilterPattern (
            const QString & value = QString(),
            bool include = true);

    //! Copy constructor.
    DbViewColFilterPattern (
            const DbViewColFilterPattern & other) :
        DbViewColFilter (other)
    {
        pattern_ = other.pattern_;
    }

    QString
    pattern() const;

    void
    setPattern (
            const QString &pattern);

    //! Create an exact duplicate of this one.
    virtual DbViewColFilter *
    clone() const {
        return new DbViewColFilterPattern (*this);
    }

    //! Tell if this filter accepts provided piece of data.
    virtual bool
    acceptsData (
            const QVariant & data) const;

    //! Get the filter values from inside the wisget.
    virtual void
    updateFromWidget (
            QWidget * wdg,
            int column);


protected:

    //! The widget to be used for filtering the content of the table.
    virtual QWidget *
    control (
            int column,
            DbViewColHdr *parent);

private:

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewColFilterPattern */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! A list of values that may be included or excluded.
class DBVIEW_EXPORT DbViewColFilterList : public DbViewColFilter {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    QStringList values_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewColFilterList (
            const QStringList & value = QStringList(),
            bool include = true);

    //! Copy constructor.
    DbViewColFilterList (
            const DbViewColFilterList & other) :
        DbViewColFilter (other)
    {
        values_ = other.values_;
    }

    QStringList values() const;
    void setValues(const QStringList &values);

    //! Create an exact duplicate of this one.
    virtual DbViewColFilter *
    clone() const {
        return new DbViewColFilterList (*this);
    }

    //! Tell if this filter accepts provided piece of data.
    virtual bool
    acceptsData (
            const QVariant & data) const;


    //! Get the filter values from inside the wisget.
    virtual void
    updateFromWidget (
            QWidget * wdg,
            int column);

protected:

    //! The widget to be used for filtering the content of the table.
    virtual QWidget *
    control (
            int column,
            DbViewColHdr *parent);

private:

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewColFilterPattern */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! A list of possible options with only one being active.
class DBVIEW_EXPORT DbViewColFilterChoice : public DbViewColFilter {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    QStringList values_;
    int current_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewColFilterChoice (
            const QStringList & value = QStringList(),
            int current = -1,
            bool include = true);

    //! Copy constructor.
    DbViewColFilterChoice (
            const DbViewColFilterChoice & other) :
        DbViewColFilter (other)
    {
        values_ = other.values_;
        current_ = other.current_;
    }

    QStringList values() const;
    void setValues(const QStringList &values);

    int current() const;
    void setCurrent(int current);

    //! Create an exact duplicate of this one.
    virtual DbViewColFilter *
    clone() const {
        return new DbViewColFilterChoice (*this);
    }

    //! Tell if this filter accepts provided piece of data.
    virtual bool
    acceptsData (
            const QVariant & data) const;

    //! Get the filter values from inside the wisget.
    virtual void
    updateFromWidget (
            QWidget * wdg,
            int column);

protected:

    //! The widget to be used for filtering the content of the table.
    virtual QWidget *
    control (
            int column,
            DbViewColHdr *parent);

private:

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewColFilterPattern */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! A list of values that may be included or excluded.
template<class T>
class DbViewColFilterNumber : public DbViewColFilter {
    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */

public:

    //! The list of known ways to compare two numbers.
    enum Compare {
        CMP_UNDEFINED = 0,

        CMP_EQUAL,          // ==	Equal to
        CMP_NOT_EQUAL,      // !=	Not equal to
        CMP_LESS,           // <	Less than
        CMP_GREATHER,       // >	Greater than
        CMP_LESSEQUAL,      // <=	Less than or equal to
        CMP_GREATHEREQUAL,  // >=	Greater than or equal to

        CMP_MAX
    };

    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

private:

    T value_;
    Compare cmp_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewColFilterNumber (
            T value, Compare relation) :
        DbViewColFilter (),
        value_(value),
        cmp_(relation)
    {}

    //! Copy constructor.
    DbViewColFilterNumber (
            const DbViewColFilterNumber & other) :
        DbViewColFilter (other)
    {
        value_ = other.value_;
        cmp_ = other.cmp_;
    }

    //! Compare based on internal comparation rule and include/exclude.
    bool compare (T other) {
        switch (cmp_) {
        case CMP_EQUAL: return include_ && (value_ == other);
        case CMP_NOT_EQUAL: return include_ && (value_ != other);
        case CMP_LESS: return include_ && (value_ < other);
        case CMP_GREATHER: return include_ && (value_ > other);
        case CMP_LESSEQUAL: return include_ && (value_ <= other);
        case CMP_GREATHEREQUAL: return include_ && (value_ >= other);
        }
        return false;
    }

    //! Create an exact duplicate of this one.
    virtual DbViewColFilter *
    clone() const {
        return new DbViewColFilterNumber<T> (*this);
    }

    //! Tell if this filter accepts provided piece of data.
    virtual bool
    acceptsData (
            const QVariant & data) const {
        Q_ASSERT(false);

        return true;
    }

    //! Get the filter values from inside the wisget.
    virtual void
    updateFromWidget (
            QWidget * wdg,
            int column) {
        QDoubleSpinBox * result = qobject_cast<QDoubleSpinBox *>(wdg);
        if (result == NULL) {
            return NULL;
        }
        value_ = result->value ();
    }

protected:

    //! The widget to be used for filtering the content of the table.
    virtual QWidget *
    control (
            int column,
            DbViewColHdr *parent) {
        QDoubleSpinBox * result = new QDoubleSpinBox (parent);
        result->setToolTip (
                    QObject::tr (
                        "Enter the value to filter this column by"));
        QObject::connect(
                    result, &QDoubleSpinBox::valueChanged,
                    parent, &DbViewColHdr::filterTriggerByFilters);
        return result;
    }

private:

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewColFilterPattern */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // DBVIEWCOLFILTER_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

