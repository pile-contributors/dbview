
# enable/disable cmake debug messages related to this pile
set (DBVIEW_DEBUG_MSG OFF)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (dbviewInit
          dbview_use_mode)

    # default name
    if (NOT DBVIEW_INIT_NAME)
        set(DBVIEW_INIT_NAME "DbView")
    endif ()

    # compose the list of headers and sources
    set(DBVIEW_HEADERS
        "dbview.h"
        "dbview-globals.h"
        "dbviewcolhdr.h"
        "dbviewcolfilter.h"
        "dbviewmosi.h"
        "dbviewmosql.h"
        "dbviewconfig.h"
        "dbviewmo.h"
        "filterwidgets/listofchoices.h"
        "filterwidgets/floatinterval.h"
        "filterwidgets/integerinterval.h"
        "filterwidgets/timeinterval.h"
        "filterwidgets/dateinterval.h"
        "filterwidgets/datetimeinterval.h"
        "filterwidgets/stringpattern.h")
    set(DBVIEW_SOURCES
        "dbview.cc"
        "dbviewmo.cc"
        "dbviewcolfilter.cc"
        "dbviewcolhdr.cc"
        "dbviewmosi.cc"
        "dbviewmosql.cc"
        "dbviewconfig.cc"
        "dbviewinmo.cc"
        "filterwidgets/listofchoices.cc"
        "filterwidgets/floatinterval.cc"
        "filterwidgets/integerinterval.cc"
        "filterwidgets/timeinterval.cc"
        "filterwidgets/dateinterval.cc"
        "filterwidgets/datetimeinterval.cc"
        "filterwidgets/stringpattern.cc")
    set(DBVIEW_UIS
        "dbview.ui"
        "filterwidgets/listofchoices.ui"
        "filterwidgets/floatinterval.ui"
        "filterwidgets/integerinterval.ui"
        "filterwidgets/timeinterval.ui"
        "filterwidgets/dateinterval.ui"
        "filterwidgets/datetimeinterval.ui"
        "filterwidgets/stringpattern.ui")

    set(DBVIEW_QT_MODS
        concurrent sql)

    pileSetSources(
        "${DBVIEW_INIT_NAME}"
        "${DBVIEW_HEADERS}"
        "${DBVIEW_SOURCES}"
        "${DBVIEW_UIS}")

    pileSetCommon(
        "${DBVIEW_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${dbview_use_mode}"
        ""
        "database"
        "qt;GUI")

endmacro ()
