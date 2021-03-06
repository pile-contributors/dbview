/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         dateinterval.cc
\date         January 2017
\author       Nicu Tofan

\brief        Contains the implementation for DateInterval class.

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

#include "dateinterval.h"
#include "ui_dateinterval.h"

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
DateInterval::DateInterval (QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateInterval)
{
    ui->setupUi(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DateInterval::~DateInterval()
{
    delete ui;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QDate DateInterval::startInterval() const
{
    return ui->startDateEdit->date ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QDate DateInterval::endInterval() const
{
    return ui->endDateEdit->date ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool DateInterval::inclusive() const
{
    return ui->inclusiveCheckBox->checkState() == Qt::Checked;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DateInterval::setStartInterval(const QDate &value)
{
    ui->startDateEdit->setDate (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DateInterval::setEndInterval(const QDate &value)
{
    ui->endDateEdit->setDate (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void DateInterval::setinclusive(bool value)
{
    ui->inclusiveCheckBox->setChecked (value);
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
