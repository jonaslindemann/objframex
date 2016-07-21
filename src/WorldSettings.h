#pragma once

#include <osg/ShapeDrawable>
#include <osg/Material>

const unsigned int rcvShadowMask = 0x1;
const unsigned int castShadowMask = 0x2;

class WorldSettings {
private:
	WorldSettings();

	osg::ref_ptr<osg::TessellationHints> m_tesselationHints;
	osg::ref_ptr<osg::ShapeDrawable> m_pointShape;
	osg::ref_ptr<osg::Material> m_pointMaterial;
	osg::ref_ptr<osg::Material> m_lineMaterial;
	double m_lineRadius;
	double m_nodeRadius;

	void updateShapes();

public:
	static WorldSettings& getInstance();

	void setPointShape(osg::ShapeDrawable* shape);
	osg::ShapeDrawable* pointShape();

	void setPointMaterial(osg::Material* material);
	osg::Material* pointMaterial();

	void setLineMaterial(osg::Material* material);
	osg::Material* lineMaterial();

	void setLineRadius(double radius);
	double lineRadius();

	void setNodeRadius(double radius);
	double nodeRadius();

	osg::TessellationHints* tesselationHints();


public:
	WorldSettings(WorldSettings const&) = delete;
	void operator=(WorldSettings const&) = delete;

	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
};
