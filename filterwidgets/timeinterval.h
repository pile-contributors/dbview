/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         timeinterval.h
\date         January 2017
\author       Nicu Tofan

\brief        Contains the definition for TimeInterval class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef FILTERWIDGET_GUI_TIMEINTERVAL_H
#define FILTERWIDGET_GUI_TIMEINTERVAL_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbview-config.h>

#include <QWidget>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace Ui {
class TimeInterval;
}

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */
namespace filterwidget {
namespace gui {

//! Shows a widget that allows selecting a time interval.
class DBVIEW_EXPORT TimeInterval : public QWidget {
    Q_OBJECT

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

    Ui::TimeInterval *ui; /**< automatically generated by Qt from the .ui file */

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    explicit TimeInterval (
            QWidget *parent = NULL);

    ~TimeInterval();

    QTime
    startInterval () const;

    QTime
    endInterval () const;

    bool
    inclusive () const;

    void
    setStartInterval (
            const QTime & value);

    void
    setEndInterval (
            const QTime & value);

    void
    setinclusive (
            bool value);

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

}; /* class TimeInterval */
} // namespace gui
} // namespace filterwidget

/*  CLASS    =============================================================== */
//
//
//
//


#endif // FILTERWIDGET_GUI_TIMEINTERVAL_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
