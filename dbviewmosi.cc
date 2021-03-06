/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewmosi.cc
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the implementation for DbViewMoSi class.

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

#include "dbviewmosi.h"
#include "dbviewcolfilter.h"

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
DbViewMoSi::DbViewMoSi (
        QAbstractItemModel *user_model,
        QObject * parent) :
    QSortFilterProxyModel(parent),
    DbViewMo(),
    cfg_()
{
    if (user_model != NULL) {
        setSourceModel(user_model);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DbViewMoSi::~DbViewMoSi()
{

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DbViewMoSi::filterAcceptsRow (int sourceRow,
        const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)
    // next apply filters in columns, if any
    QAbstractItemModel *user_model = sourceModel ();
    return DbViewColFilter::acceptsRow (cfg_.filters, user_model, sourceRow);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DbViewMoSi::reloadWithFilters (DbViewConfig cfg)
{
    cfg_.move (cfg);
    // QAbstractItemModel *user_model = sourceModel ();
    // needed so that a filtering is trigered
    setFilterKeyColumn(0);
    Q_ASSERT(cfg_.sort_column >= -1);
    sort(cfg_.sort_column, cfg_.sort_order);
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
