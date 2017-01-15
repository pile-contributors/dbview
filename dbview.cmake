
# enable/disable cmake debug messages related to this pile
set (DBVIEW_DEBUG_MSG ON)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (dbviewInit
          ref_cnt_use_mode)

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
        "dbviewconfig.h"
        "dbviewmo.h")
    set(DBVIEW_SOURCES
        "dbview.cc"
        "dbviewmo.cc"
        "dbviewcolfilter.cc"
        "dbviewcolhdr.cc"
        "dbviewmosi.cc"
        "dbviewconfig.cc"
        "dbviewinmo.cc")
    set(DBVIEW_UIS
        "dbview.ui")

    set(DBVIEW_QT_MODS
        widgets, concurrent)

    pileSetSources(
        "${DBVIEW_INIT_NAME}"
        "${DBVIEW_HEADERS}"
        "${DBVIEW_SOURCES}"
        "${DBVIEW_UIS}")

    pileSetCommon(
        "${DBVIEW_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${ref_cnt_use_mode}"
        ""
        "database"
        "qt;GUI")

endmacro ()
