cmake_minimum_required( VERSION 3.0 )
project( ObjFrameX )

if (WIN32)
	set( OSG_DIR "c:/Users/Jonas/Development/OpenSceneGraph-runtime" )
endif (WIN32)

find_package(OpenSceneGraph 2.0.0 REQUIRED osgDB osgUtil osgViewer osgGA osgShadow osgUtil)

include_directories(${OSG_INCLUDE_DIR})

subdirs(src)



