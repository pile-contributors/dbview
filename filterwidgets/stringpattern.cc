/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         stringpattern.cc
\date         January 2017
\author       Nicu Tofan

\brief        Contains the implementation for StringPattern class.

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

#include "stringpattern.h"
#include "ui_stringpattern.h"

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
StringPattern::StringPattern (QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StringPattern)
{
    ui->setupUi(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
StringPattern::~StringPattern()
{
    delete ui;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QRegExp::PatternSyntax StringPattern::syntax () const
{
    return selectionToPattern(ui->matchTypeCombo->currentIndex());
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString StringPattern::patternString () const
{
    return ui->patternLineEdit->text ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QRegExp StringPattern::regex () const
{
    return QRegExp (patternString(), caseSensitivity(), syntax());
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::CaseSensitivity StringPattern::caseSensitivity () const
{
    return ui->casesensitiveCheckBox->checkState() == Qt::Checked ?
        Qt::CaseSensitive : Qt::CaseInsensitive;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QRegExp::PatternSyntax StringPattern::selectionToPattern (int index) const
{
    switch (index) {
        case 0: return QRegExp::Wildcard;
        case 1: return QRegExp::RegExp;
        case 2: return QRegExp::RegExp2;
        case 3: return QRegExp::WildcardUnix;
        case 4: return QRegExp::W3CXmlSchema11;
        default: return QRegExp::FixedString;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int StringPattern::patternToSelection (QRegExp::PatternSyntax value) const
{
    switch (value) {
        case QRegExp::Wildcard: return 0;
        case QRegExp::RegExp: return 1;
        case QRegExp::RegExp2: return 2;
        case QRegExp::WildcardUnix: return 3;
        case QRegExp::W3CXmlSchema11: return 4;
        default: return 5;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool StringPattern::inclusive() const
{
    return ui->inclusiveCheckBox->checkState() == Qt::Checked;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void StringPattern::setSyntax (QRegExp::PatternSyntax value)
{
    ui->matchTypeCombo->setCurrentIndex (
                patternToSelection (value));
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void StringPattern::setPatternString (const QString &value)
{
    ui->patternLineEdit->setText (value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void StringPattern::setRegex (const QRegExp &value)
{
    setPatternString (value.pattern ());
    setSyntax (value.patternSyntax ());
    setCaseSensitivity (value.caseSensitivity());
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void StringPattern::setCaseSensitivity (Qt::CaseSensitivity cs)
{
    ui->casesensitiveCheckBox->setChecked (cs == Qt::CaseSensitive);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void StringPattern::setInclusive (bool value)
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
