#include "PickHandler.h"

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>
#include <osg/BoundingBox>
#include <osgViewer/Viewer>
#include <osgUtil/LineSegmentIntersector>

#include "WorldSettings.h"

#include <iostream>

PickHandler::PickHandler()
{

}

osg::MatrixTransform* PickHandler::getOrCreateSelectionBox()
{
    if (!m_selectionBox)
    {
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->addDrawable(
			new osg::ShapeDrawable(
					new osg::Box(osg::Vec3(), 1.0f)
            )
		);

        m_selectionBox = new osg::MatrixTransform;
        m_selectionBox->setNodeMask(0x1);
        m_selectionBox->addChild(geode);
		m_selectionBox->getOrCreateStateSet()->setAttribute(WorldSettings::getInstance().selectionMaterial());
		osg::StateSet* ss = m_selectionBox->getOrCreateStateSet();
		ss->setMode(GL_NORMALIZE, osg::StateAttribute::ON);

		ss->setMode(GL_BLEND, osg::StateAttribute::ON);
		ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		ss->setRenderBinDetails(1, "DepthSortedBin");

        //ss->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        //ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));
    }
    return m_selectionBox.get();

}

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    if (ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE||
            ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON||
            (ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL) )
        return false;

    osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);

    if (viewer)
    {
        osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
                new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
        osgUtil::IntersectionVisitor iv(intersector.get());
        iv.setTraversalMask(~0x1);
        viewer->getCamera()->accept(iv);

        if (intersector->containsIntersections())
        {
            const osgUtil::LineSegmentIntersector::Intersection& result =
                    *(intersector->getIntersections().begin());

			std::string owner;
			result.drawable->getUserValue("Owner", owner);
			std::cout << "owner = " << owner << std::endl;

			osg::ref_ptr<osg::MatrixTransform> selectionBox = this->getOrCreateSelectionBox();

			if ((owner == "GeomPoint")||(owner == "GeomLine"))
			{

				selectionBox->setNodeMask(true ? ~0 : 0);
				osg::BoundingBox bb = result.drawable->getBoundingBox();
				osg::Vec3 worldCenter = bb.center() * osg::computeLocalToWorld(result.nodePath);

				selectionBox->setMatrix(
							osg::Matrix::scale(
								bb.xMax()-bb.xMin(),
								bb.yMax()-bb.yMin(),
								bb.zMax()-bb.zMin()
								) * osg::Matrix::translate(worldCenter)
							);
			}
			else
			{
				selectionBox->setNodeMask(false ? ~0 : 0);
			}


        }
    }
    return false;
}
