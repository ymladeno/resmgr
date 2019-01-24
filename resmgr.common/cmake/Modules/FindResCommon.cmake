# Create imported target rescmn
add_library(rescmn STATIC IMPORTED GLOBAL)

set_target_properties(rescmn PROPERTIES 
                      IMPORTED_LOCATION "${CMAKE_HOME_DIRECTORY}/../resmgr.common/dbg/qnx7_ntox86_64/lib/librescmn.a")