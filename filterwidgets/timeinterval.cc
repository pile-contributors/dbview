/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         timeinterval.cc
\date         January 2017
\author       Nicu Tofan

\brief        Contains the implementation for TimeInterval class.

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

#include "timeinterval.h"
#include "ui_timeinterval.h"

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
TimeInterval::TimeInterval (QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeInterval)
{
    ui->setupUi(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
TimeInterval::~TimeInterval()
{
    delete ui;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QTime TimeInterval::startInterval() const
{
    return ui->startTimeEdit->time ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QTime TimeInterval::endInterval() const
{
    return ui->endTimeEdit->time ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool TimeInterval::inclusive() const
{
    return ui->inclusiveCheckBox->checkState() == Qt::Checked;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void TimeInterval::setStartInterval(const QTime &value)
{
    ui->startTimeEdit->setTime (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void TimeInterval::setEndInterval(const QTime &value)
{
    ui->endTimeEdit->setTime (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void TimeInterval::setinclusive(bool value)
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