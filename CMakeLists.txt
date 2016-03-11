if (NOT DBVIEW_BUILD_MODE)
    set (DBVIEW_BUILD_MODE STATIC)
endif ()

include(pile_support)
pileInclude (DbView)
dbviewInit(${DBVIEW_BUILD_MODE})
