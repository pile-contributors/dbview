/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         dateinterval.h
\date         January 2017
\author       Nicu Tofan

\brief        Contains the definition for ListOfChoices class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef FILTERWIDGET_GUI_LISTOFCHOICES_H
#define FILTERWIDGET_GUI_LISTOFCHOICES_H
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
class ListOfChoices;
}

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */
namespace filterwidget {
namespace gui {

//! Shows a widget that allows selecting a date interval.
class DBVIEW_EXPORT ListOfChoices : public QWidget {
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

    Ui::ListOfChoices *ui; /**< automatically generated by Qt from the .ui file */
    bool own_model_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    explicit ListOfChoices (
            QWidget *parent = NULL);

    ~ListOfChoices();

    bool
    inclusive () const;

    void
    setinclusive (
            bool value);

    void
    setSelectedValues (
            const QList<int> &value);

    void
    setSelectedValues (
            const QStringList &value);

    void
    setValues (
            const QStringList &value);

    QStringList
    allValues() const;

    QStringList
    selectedValues() const;

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

}; /* class ListOfChoices */
} // namespace gui
} // namespace filterwidget

/*  CLASS    =============================================================== */
//
//
//
//


#endif // FILTERWIDGET_GUI_LISTOFCHOICES_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
