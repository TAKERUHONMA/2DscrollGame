#include "Bird.h"
#include <assert.h>
#include "Camera.h"

Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
}

Bird::~Bird()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Bird::Update()
{
}

void Bird::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
	DrawCircle(x + 32.0f, y + 32.0f, 24.0f, GetColor(255, 0, 0));
}

void Bird::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	daseY = y;
}

bool Bird::CollideCircle(float x, float y, float r)
{
	//x, y, r が相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;

	if (dx * dx * dy * dy < (r + myR) * (r + myR))
		return true;
	return false;
}
