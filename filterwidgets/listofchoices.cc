/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         dateinterval.cc
\date         January 2017
\author       Nicu Tofan

\brief        Contains the implementation for ListOfChoices class.

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

#include "listofchoices.h"
#include "ui_listofchoices.h"
#include <QStandardItemModel>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace filterwidget;
using namespace filterwidget::gui;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
ListOfChoices::ListOfChoices (QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListOfChoices),
    own_model_(false)
{
    ui->setupUi(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ListOfChoices::~ListOfChoices()
{
    if (own_model_) {
        delete ui->listView->model ();
    }
    delete ui;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool ListOfChoices::inclusive() const
{
    return ui->inclusiveCheckBox->checkState() == Qt::Checked;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void ListOfChoices::setinclusive(bool value)
{
    ui->inclusiveCheckBox->setChecked (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void ListOfChoices::setValues (const QStringList & value)
{
    if (own_model_) {
        ui->listView->model ()->deleteLater ();
    }
    own_model_ = true;

    QStandardItemModel *model = new QStandardItemModel();

    int i = 0;
    foreach(const QString & s, value) {
        QStandardItem *item = new QStandardItem (s);
        item->setCheckable (true);
        item->setCheckState (Qt::Checked);
        model->setItem (i++, item);
    }

    ui->listView->setModel( model );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void ListOfChoices::setSelectedValues (const QStringList & value)
{
    QAbstractItemModel * mm = ui->listView->model ();
    int i_max = mm->rowCount ();
    for (int i = 0; i < i_max; ++i) {
        QModelIndex mi = mm->index (i, 0);
        if (value.contains (mi.data (Qt::DisplayRole).toString ())) {
            mm->setData (mi, Qt::Checked, Qt::CheckStateRole);
        }
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void ListOfChoices::setSelectedValues (const QList<int> & value)
{
    QAbstractItemModel * mm = ui->listView->model ();

    int i_max = mm->rowCount ();
    foreach(int i, value) {
        if (i < 0)
            continue;
        if (i >= i_max)
            continue;
        QModelIndex mi = mm->index (i, 0);
        mm->setData (mi, Qt::Checked, Qt::CheckStateRole);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList ListOfChoices::selectedValues () const
{
    QStringList result;
    QAbstractItemModel * mm = ui->listView->model ();

    int i_max = mm->rowCount ();
    for (int i = 0; i < i_max; ++i) {
        QModelIndex mi = mm->index(i, 0);
        if (mi.data(Qt::CheckStateRole).toInt() == Qt::Checked) {
            result.append (mi.data(Qt::DisplayRole).toString());
        }
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList ListOfChoices::allValues () const
{
    QStringList result;
    QAbstractItemModel * mm = ui->listView->model ();

    int i_max = mm->rowCount ();
    for (int i = 0; i < i_max; ++i) {
        QModelIndex mi = mm->index(i, 0);
        result.append (mi.data(Qt::DisplayRole).toString());
    }
    return result;
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
