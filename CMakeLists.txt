cmake_minimum_required( VERSION 3.0 )
project( ObjFrameX )

set( OSG_DIR "D:/Users/Jonas/Libraries/OpenSceneGraph-3.4.0/build" )

find_package(OpenSceneGraph 2.0.0 REQUIRED osgDB osgUtil osgViewer osgGA osgShadow osgUtil)

include_directories(${OSG_INCLUDE_DIR})

subdirs(src)



