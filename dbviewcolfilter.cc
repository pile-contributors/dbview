/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewcolfilter.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for DbViewColFilter class.

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

#include "dbviewcolfilter.h"
#include "dbview-private.h"

#include <qglobal.h>
#include <QTextEdit>
#include <QListWidget>
#include <QComboBox>

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
DbViewColFilter::DbViewColFilter (bool include) :
    include_(include)
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewColFilter::~DbViewColFilter()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewColFilter::include() const
{
    return include_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilter::setInclude(bool include)
{
    include_ = include;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Default implementation simply returns NULL, meaning that the column
 * is not to be filtered.
 *
 * The ownership of the pointer is transferred o the caller.
 *
 * @return pointer to widget or NULL.
 */
QWidget *DbViewColFilter::control (int column, QWidget * parent)
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<DbViewColFilter *> DbViewColFilter::clone (
        const QList<DbViewColFilter *> &filters)
{
    QList<DbViewColFilter*> result;
    foreach(DbViewColFilter* flt, filters) {
        if (flt == NULL) {
            result.append (NULL);
        } else {
            result.append (flt->clone ());
        }
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewColFilter::acceptsRow (
        const QList<DbViewColFilter *> &filters,
        QAbstractItemModel *model, int row)
{
    int i_max = qMin(model->columnCount (), filters.length ());
    QModelIndex index;
    for (int i = 0; i < i_max; ++i) {
        DbViewColFilter* filter = filters[i];
        if (filter == NULL)
            continue;
        index = model->index (row, i);
        if (!filter->acceptsData (index.data (Qt::EditRole))) {
            return false;
        }
    }
    return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
DbViewColFilterPattern::DbViewColFilterPattern (
        const QString &value, bool include) :
    DbViewColFilter (include),
    pattern_(value)
{
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString DbViewColFilterPattern::pattern() const
{
    return pattern_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilterPattern::setPattern(const QString &pattern)
{
    pattern_ = pattern;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The ownership of the pointer is transferred o the caller.
 *
 * @return pointer to widget or NULL.
 */
QWidget * DbViewColFilterPattern::control (int column, QWidget * parent)
{
    Q_UNUSED(column);
    QTextEdit * result = new QTextEdit (parent);
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewColFilterPattern::acceptsData (const QVariant &data) const
{
    UNIMPLEMENTED_TRAP;
    return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
DbViewColFilterList::DbViewColFilterList (
        const QStringList &value, bool include) :
    DbViewColFilter (include),
    values_(value)
{
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList DbViewColFilterList::values() const
{
    return values_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilterList::setValues (const QStringList &values)
{
    values_ = values;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The ownership of the pointer is transferred o the caller.
 *
 * @return pointer to widget or NULL.
 */
QWidget * DbViewColFilterList::control (int column, QWidget * parent)
{
    Q_UNUSED(column);
    QListWidget * result = new QListWidget (parent);
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewColFilterList::acceptsData (const QVariant &data) const
{
    UNIMPLEMENTED_TRAP;
    return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
DbViewColFilterChoice::DbViewColFilterChoice (
        const QStringList &value, int current, bool include) :
    DbViewColFilter (include),
    current_(current),
    values_(value)
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList DbViewColFilterChoice::values() const
{
    return values_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilterChoice::setValues(const QStringList &values)
{
    values_ = values;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int DbViewColFilterChoice::current() const
{
    return current_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilterChoice::setCurrent (int current)
{
    current_ = current;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The ownership of the pointer is transferred o the caller.
 *
 * @return pointer to widget or NULL.
 */
QWidget * DbViewColFilterChoice::control (int column, QWidget * parent)
{
    Q_UNUSED(column);
    QComboBox * result = new QComboBox (parent);
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewColFilterChoice::acceptsData (const QVariant &data) const
{
    UNIMPLEMENTED_TRAP;
    return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */




