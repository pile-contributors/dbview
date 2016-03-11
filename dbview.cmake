
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
        "dbview.h")
    set(DBVIEW_SOURCES
        "dbview.cc")

    pileSetSources(
        "${DBVIEW_INIT_NAME}"
        "${DBVIEW_HEADERS}"
        "${DBVIEW_SOURCES}")

    pileSetCommon(
        "${DBVIEW_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${ref_cnt_use_mode}"
        ""
        "category1"
        "tag1;tag2")

endmacro ()
