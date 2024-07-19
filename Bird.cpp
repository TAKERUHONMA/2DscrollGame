#include "Bird.h"
#include <assert.h>
#include "Camera.h"
#include "TestScene.h"
#include "Field.h"

namespace {
	static const int SCREEN_WIDTH = 1280;
	const float GRAVITY = 9.8f / 60.0f;//重力加速度
};

Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
	counter = 0;
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
	Field* pField = GetParent()->FindGameObject<Field>();
	counter -= 1;

	if (pField != nullptr)
	{
		//(50,64)と(14,64)も見る
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 64);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 64);
		int push = max(pushR, pushL);//２つの足元のめり込みの大きい方
		if (push >= 1)
		{
			transform_.position_.y -= push - 1;
			jumpSpeed = 0.0f;
			onGround = true;
		}
		else
		{
			onGround = false;
		}
	}

	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

	if (x > SCREEN_WIDTH) //即値、マジックナンバー
		return;
	else if (x < 0 - 64) 
	{
		KillMe();
		return;
	}


	
	//sinAngle += 3.0f;//度
	//float sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
	//transform_.position_.y = baseY + sinValue * 50;

	transform_.position_.x -= 0.5f;
	
	jumpSpeed += GRAVITY;//速度 += 加速度
	transform_.position_.y += jumpSpeed; //座標 += 速度

	if (transform_.position_.y >= 700)
	{
		KillMe();
	}

	if (counter == 0)
	{
		counter = 160;
	}

	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
	}
}

void Bird::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
	
	//DrawCircle(x + 32.0f, y + 32.0f, 24.0f, GetColor(255, 0, 0),0);
}

bool Bird::CollideCircle(float x, float y, float r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if ((dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Bird::Reset()
{
	KillMe();
}

void Bird::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	baseY = y;
}