#include "CameraCtl.h"

USING_NS_CC;

CameraCtl::CameraCtl()
{
}


CameraCtl::~CameraCtl()
{
}

void CameraCtl::FollowPlayer(Vec3 position)
{
	camera->getDefaultCamera()->setPosition3D(position);
	camera->getDefaultCamera()->lookAt(Vec3(position.x, position.y, 0.0f));
}
