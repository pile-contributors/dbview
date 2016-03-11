/**
 * @file dbview.h
 * @brief Declarations for DbView class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_DBVIEW_H_INCLUDE
#define GUARD_DBVIEW_H_INCLUDE

#include <dbview/dbview-config.h>
#include <QTableView>

//! A table view of a database table.
class DBVIEW_EXPORT DbView : public QTableView {

public:

    //! Default constructor.
    DbView (
            QWidget *parent = 0);

    //! Destructor.
    virtual ~DbView();

protected:

private:

};

#endif // GUARD_DBVIEW_H_INCLUDE
