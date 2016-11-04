#pragma once

#include <osg/Group>

#include "GeomPoint.h"
#include "GeomLine.h"
#include "GeomLines.h"
#include "GeomPoints.h"

class Structure : public osg::Group {
private:
public:
        Structure(GeomPoints* points, GeomLines* lines);

        Structure(const Structure& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY)
                : osg::Group(copy, copyop) {}

        META_Node(osg, osg::Group);

protected:
        ~Structure() {};
};

