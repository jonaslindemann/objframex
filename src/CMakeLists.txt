add_executable(ObjFrameX main.cpp SkyBox.h SkyBox.cpp NodeSet.h NodeSet.cpp PositionalObject.h PositionalObject.cpp GeomPoint.h GeomPoint.cpp GeomLine.h GeomLine.cpp GeomPoints.h GeomPoints.cpp GeomLines.h GeomLines.cpp WorldSettings.h WorldSettings.cpp)
target_link_libraries(ObjFrameX ${OSG_LIBRARY} ${OSGDB_LIBRARY} ${OSGGA_LIBRARY} ${OSGVIEWER_LIBRARY} ${OSGSHADOW_LIBRARY} ${OSGUTIL_LIBRARY} ${OPENTHREADS_LIBRARY} )


