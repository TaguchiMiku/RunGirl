#pragma once
#include "cocos2d.h"

class CameraCtl
{
public:
	CameraCtl();
	~CameraCtl();

	void FollowPlayer(cocos2d::Vec3 position);
private:
	cocos2d::Camera* camera;
};

