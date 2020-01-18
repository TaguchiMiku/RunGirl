#include "Score.h"
#include "debug/_DebugConOut.h"

USING_NS_CC;

Score * Score::createScore()
{
	return Score::create();
}

Score::Score()
{
	score = 0;
	time = 0;
	this->scheduleUpdate();
}

Score::~Score()
{
	int a = 0;
}

void Score::AddScore(int point)
{
	score += point;
}

int Score::GetScore()
{
	return score;
}

Label* Score::DrawScore()
{
	std::string st = StringUtils::format("%d", score);
	auto label = Label::createWithTTF(st, "../Resources/fonts/Molot.otf", 32);
	return label;
}

void Score::update(float delta)
{
	TRACE("%d\n", score);
	time++;
	if ((time * (1 - delta)) >= 60)
	{
		time = 0;
		score++;
	}
}
