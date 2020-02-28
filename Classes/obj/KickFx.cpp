#include "KickFx.h"
#include "../Animation/AnimCtl.h"
#include "obj/Player.h"

USING_NS_CC;

KickFx * KickFx::createKick()
{
	return KickFx::create();
}

KickFx::KickFx()
{
}


KickFx::~KickFx()
{
}

void KickFx::Init(std::string animName, Vec2 position, Vec2 scale, cocos2d::Layer* layer)
{
	SetAddAnim(animName);
	setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	setPosition(position);
	setScale(scale.x, scale.y);
	layer->addChild(this, 3);

	this->scale = 1.0f;
}

void KickFx::SetAddAnim(std::string animName)
{
	lpAnimCtl.AddAnimation("player", animName, 0.1f);
	lpAnimCtl.RunAnimation(this, "player-" + animName, -1, 0);
}

void KickFx::Update(Player* player)
{
	if (player->GetAttackFlag())
	{
		if (scale < 2.0f)
		{
			scale += 0.2f;
		}
		setPosition(Vec2(player->getPosition().x + 5.0f - scale, player->getPosition().y - player->getContentSize().height / 2.0f));
		setScale(scale);
		setOpacity(240);
	}
	else
	{
		scale = 1.0f;
		setOpacity(0);
	}
}
