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

    //! Constructor.
    DbViewColFilter (
            bool include = true);

    //! destructor
    virtual ~DbViewColFilter();

    bool include() const;
    void setInclude(bool include);

protected:

private:


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

    QString pattern_;

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

    QString pattern() const;
    void setPattern(const QString &pattern);

protected:

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

    QStringList values() const;
    void setValues(const QStringList &values);

protected:

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

    QStringList values() const;
    void setValues(const QStringList &values);

    int current() const;
    void setCurrent(int current);

protected:

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


protected:

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

