/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file         dbviewcolhdr.h
  \date         January 2017
  \author       Nicu Tofan

  \brief        Contains the definition for DbViewColHdr class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef DBVIEWCOLHDR_H
#define DBVIEWCOLHDR_H
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <dbview/dbview-config.h>
#include <QHeaderView>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class DbTableView;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

//! Header for columns.
class DBVIEW_EXPORT DbViewColHdr : public QHeaderView {
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

    DbTableView * table_;
    QList<QWidget*> controls_;
    int half_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    DbViewColHdr (
            DbTableView * table,
            QWidget * parent = NULL);

    //! destructor
    virtual ~DbViewColHdr();

    //! Set the control for a column.
    void
    setControl (
            int column,
            QWidget * widget);

    //! Get the control for a column.
    QWidget *
    control (
            int column);

    //! Tell if a column has a control installed.
    bool
    hasControl (
            int column) const {
        if (controls_.count() <= column)
            return false;
        return (controls_[column] != NULL);
    }

    //! Remove the controls for all columns.
    void
    removeAllControls ();


public slots:

    void
    positionAllControls (
            int first=0);

    void
    filterTriggerByFilters();

protected:

    void
    paintSection (
            QPainter *painter,
            const QRect &rect,
            int logicalIndex) const;

private:

    void
    setHdrGeom (
            int logicalIndex,
            QWidget *widget = 0,
            int width = -1);

signals:

    //! Emmited when the way a model is filtered has changed.
    void
    filterChanged (
            int column);


private slots:

    void
    resizeControl (
            int logicalIndex,
            int oldSize,
            int newSize);

public:

    static void
    setWidgetColumn (
            QWidget * wdg,
            int column);

    static int
    widgetColumn (
            QWidget * wdg);


    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //
}; /* class DbViewColHdr */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // DBVIEWCOLHDR_H
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

