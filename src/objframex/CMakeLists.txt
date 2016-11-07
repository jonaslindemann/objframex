add_executable(	ObjFrameX main.cpp SkyBox.h SkyBox.cpp NodeSet.h NodeSet.cpp 
	PositionalObject.h PositionalObject.cpp GeomPoint.h GeomPoint.cpp 
	GeomLine.h GeomLine.cpp GeomPoints.h GeomPoints.cpp GeomLines.h GeomLines.cpp 
	WorldSettings.h WorldSettings.cpp ModelController.h ModelController.cpp
        BasicFrameFactory.h BasicFrameFactory.cpp Structure.h Structure.cpp
        PickHandler.h PickHandler.cpp KeyboardFpsManipulator.h KeyboardFpsManipulator.cpp 
	Grid.h Grid.cpp)

	# Link to OpenSceneGraph libs
TARGET_LINK_LIBRARIES(ObjFrameX ${OPENSCENEGRAPH_LIBRARIES} )

# Link to open gl libs
TARGET_LINK_LIBRARIES(ObjFrameX ${OPENGL_LIBRARIES} )

if (WIN32)
TARGET_LINK_LIBRARIES(ObjFrameX Xinput )
endif()

#target_link_libraries(ObjFrameX ${OSG_LIBRARY} ${OSGDB_LIBRARY} ${OSGGA_LIBRARY} ${OSGVIEWER_LIBRARY} ${OSGSHADOW_LIBRARY} ${OSGUTIL_LIBRARY} ${OPENTHREADS_LIBRARY} )


