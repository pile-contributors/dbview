/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         integerinterval.h
\date         January 2017
\author       Nicu Tofan

\brief        Contains the definition for IntegerInterval class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef FILTERWIDGET_GUI_INTEGERINTERVAL_H
#define FILTERWIDGET_GUI_INTEGERINTERVAL_H
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
class IntegerInterval;
}

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */
namespace filterwidget {
namespace gui {

//! Shows a widget that allows selecting a integer interval.
class DBVIEW_EXPORT IntegerInterval : public QWidget {
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

    Ui::IntegerInterval *ui; /**< automatically generated by Qt from the .ui file */

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    explicit IntegerInterval (
            QWidget *parent = NULL);

    ~IntegerInterval();

    int
    startInterval () const;

    int
    endInterval () const;

    bool
    inclusive () const;

    void
    setStartInterval (
            int value);

    void
    setEndInterval (
            int value);

    void
    setinclusive (
            bool value);

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

}; /* class IntegerInterval */
} // namespace gui
} // namespace filterwidget

/*  CLASS    =============================================================== */
//
//
//
//


#endif // FILTERWIDGET_GUI_INTEGERINTERVAL_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
