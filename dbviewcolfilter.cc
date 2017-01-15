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
#include "dbviewcolhdr.h"

#include <qglobal.h>
#include <QLineEdit>
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
QWidget *DbViewColFilter::createControl (int column, DbViewColHdr *parent)
{
    QWidget * wdg = control (column, parent);
    if (wdg != NULL) {
        DbViewColHdr::setWidgetColumn (wdg, column);
    }
    return wdg;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilter::updateFromWidget(QWidget *wdg, int column)
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
QWidget *DbViewColFilter::control (int column, DbViewColHdr *parent)
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
    pattern_(value, Qt::CaseInsensitive, QRegExp::Wildcard)
{
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString DbViewColFilterPattern::pattern() const
{
    return pattern_.pattern ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilterPattern::setPattern(const QString &pattern)
{
    pattern_.setPattern (pattern);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The ownership of the pointer is transferred o the caller.
 *
 * @return pointer to widget or NULL.
 */
QWidget * DbViewColFilterPattern::control (int column, DbViewColHdr *parent)
{
    Q_UNUSED(column);
    QLineEdit * result = new QLineEdit (parent);
    result->setToolTip (
                QObject::tr (
                    "Enter text pattern to filter this column"));
    QObject::connect(
                result, &QLineEdit::editingFinished,
                parent, &DbViewColHdr::filterTriggerByFilters);
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewColFilterPattern::acceptsData (const QVariant &data) const
{
    return include() && pattern_.exactMatch (data.toString ());
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewColFilterPattern::updateFromWidget (QWidget *wdg, int column)
{
    QLineEdit * result = qobject_cast<QLineEdit *>(wdg);
    if (result == NULL) {
        return;
    }
    pattern_.setPattern (result->text ());
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
QWidget * DbViewColFilterList::control (int column, DbViewColHdr *parent)
{
    Q_UNUSED(column);
    QListWidget * result = new QListWidget (parent);
    result->setToolTip (
                QObject::tr (
                    "Select the items to include"));
    QObject::connect(
                result, &QListWidget::itemSelectionChanged,
                parent, &DbViewColHdr::filterTriggerByFilters);
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

/* ------------------------------------------------------------------------- */
void DbViewColFilterList::updateFromWidget (QWidget *wdg, int column)
{
    QListWidget * result = qobject_cast<QListWidget *>(wdg);
    if (result == NULL) {
        return;
    }

    Q_ASSERT(false);
    // pattern_ = result->text ();
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
QStringList DbViewColFilterChoice::values () const
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
QWidget * DbViewColFilterChoice::control (int column, DbViewColHdr *parent)
{
    Q_UNUSED(column);
    QComboBox * result = new QComboBox (parent);
    result->setToolTip (
                QObject::tr (
                    "Select the items to include"));
    QObject::connect(
                result, SIGNAL(currentIndexChanged(const QString &)),
                parent, SLOT(filterTriggerByFilters()));
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

/* ------------------------------------------------------------------------- */
void DbViewColFilterChoice::updateFromWidget (QWidget *wdg, int column)
{
    QListWidget * result = qobject_cast<QListWidget *>(wdg);
    if (result == NULL) {
        return;
    }

    Q_ASSERT(false);
    current_ = result->currentRow ();
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */




