/**
 * @file dbTableview.h
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

//! A table view of a database table.
class DBVIEW_EXPORT DbTableView : public QTableView {

public:

    //! Default constructor.
    DbTableView (
            QWidget *parent = 0);

    //! Destructor.
    virtual ~DbTableView();

protected:

private:

};

#endif // GUARD_DBTABLEVIEW_H_INCLUDE
