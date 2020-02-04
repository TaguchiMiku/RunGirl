/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "effect/EffectMng.h"
#include <memory>
#include <vector>
#include <utility>
#include "ResultScene.h"

//zOrderの番号を動的に変える際に順番が分からなくならないようにするために
//enumで順番を作っておき、それで指定する
enum SceneZoder
{
	BG_BACK,
	PLAYER,
	BG_FRONT,
	LABEL,
	MENU,
	UI
};

class Player;
class Enemy;
class NormalItem;
class Score;
class BackScroll;
class Attack;
class CountDown;
class TimerMng;
class MapCreate;
class EnemyCreate;
class ItemCreate;
class GameScene : public cocos2d::Scene
{
public:
	~GameScene();
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	void update(float delta);
	void NextScene(float millsecond);
	void visitor(cocos2d::Renderer *renderer,
				 const cocos2d::Mat4& parentTransform,
				 uint32_t parentFlags);
private:
	Player* player;
	Enemy* enemy;
	Score* score;
	CountDown* cntDwn;
	MapCreate* map;
	TimerMng* timer;
	EnemyCreate* enemyCt;
	ItemCreate* itemCt;
	efk::EffectEmitter* effect;
	efk::EffectEmitter* tapEffect;

	cocos2d::Sprite* collSpr;
	cocos2d::Rect plRect;
	cocos2d::Rect eneRect;
	cocos2d::Rect atkRect;
	cocos2d::Node* hpBar;
	std::vector<BackScroll*> backSrl;
	Attack* attack;
	float after;
	float before;
	CkSound* sound;
	float scaleX;
	bool timeUpFlag;
	bool onceFlag;
	bool onceBGMFlag;
	bool gameFlag;
	float time;
};

#endif // __HELLOWORLD_SCENE_H__
