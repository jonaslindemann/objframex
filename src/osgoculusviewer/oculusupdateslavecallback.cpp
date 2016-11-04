/*
 * oculusupdateslavecallback.cpp
 *
 *  Created on: Jul 07, 2015
 *      Author: Björn Blissing
 */

#include "oculusupdateslavecallback.h"

#include <iostream>

void OculusUpdateSlaveCallback::updateSlave(osg::View& view, osg::View::Slave& slave)
{
	using namespace std;

	if (m_cameraType == LEFT_CAMERA)
	{
		m_device->updatePose(m_swapCallback->frameIndex());
	}

	osg::Vec3 position = m_device->position();
	osg::Quat orientation = m_device->orientation();

	osg::Matrix viewOffset = (m_cameraType == LEFT_CAMERA) ? m_device->viewMatrixLeft() : m_device->viewMatrixRight();

	osg::Vec3 eye;
	osg::Vec3 center;
	osg::Vec3 up;

	// invert orientation (conjugate of Quaternion) and position to apply to the view matrix as offset
	viewOffset.preMultRotate(orientation.conj());
	viewOffset.preMultTranslate(-position);

	viewOffset.getLookAt(eye, center, up);

	/*
	cout << "eye->" << endl;
	cout << eye.x() << ", " << eye.y() << ", " << eye.z() << endl;
	cout << "center->" << endl;
	cout << center.x() << ", " << center.y() << ", " << center.z() << endl;
	cout << "up->" << endl;
	cout << up.x() << ", " << up.y() << ", " << up.z() << endl;
	*/

	slave._viewOffset = viewOffset;

	slave.updateSlaveImplementation(view);
}
