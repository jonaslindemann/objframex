include_directories(../objframex ../osgoculusviewer)

# Source files for library
SET(OCULUS_SRC ../osgoculusviewer/oculusviewer.cpp ../osgoculusviewer/oculusdevice.cpp ../osgoculusviewer/oculuseventhandler.cpp ../osgoculusviewer/oculusupdateslavecallback.cpp)
# Header files for library
SET(OCULUS_H ../osgoculusviewer/oculusviewer.h ../osgoculusviewer/oculusdevice.h ../osgoculusviewer/oculuseventhandler.h ../osgoculusviewer/oculusupdateslavecallback.h)


add_executable(	ObjFrameX-VR main.cpp ../objframex/SkyBox.h ../objframex/SkyBox.cpp ../objframex/NodeSet.h ../objframex/NodeSet.cpp 
	../objframex/PositionalObject.h ../objframex/PositionalObject.cpp ../objframex/GeomPoint.h ../objframex/GeomPoint.cpp 
	../objframex/GeomLine.h ../objframex/GeomLine.cpp ../objframex/GeomPoints.h ../objframex/GeomPoints.cpp ../objframex/GeomLines.h ../objframex/GeomLines.cpp 
	../objframex/WorldSettings.h ../objframex/WorldSettings.cpp ../objframex/ModelController.h ../objframex/ModelController.cpp
        ../objframex/BasicFrameFactory.h ../objframex/BasicFrameFactory.cpp ../objframex/Structure.h ../objframex/Structure.cpp
        ../objframex/PickHandler.h ../objframex/PickHandler.cpp KeyboardFpsManipulator.h KeyboardFpsManipulator.cpp 
	../objframex/Grid.h ../objframex/Grid.cpp ${OCULUS_H} ${OCULUS_SRC})

target_link_libraries(ObjFrameX-VR ${OSG_LIBRARY} ${OSGDB_LIBRARY} ${OSGGA_LIBRARY} ${OSGVIEWER_LIBRARY} ${OSGSHADOW_LIBRARY} ${OSGUTIL_LIBRARY} ${OPENTHREADS_LIBRARY} ${OCULUS_SDK_LIBRARIES} ${OPENGL_LIBRARIES} )


