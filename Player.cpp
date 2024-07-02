#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stone.h"
#include "Camera.h"
#include "Field.h"

namespace {
	const float MOVE_SPEED = 0.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;
	const float GRAVITY = 9.8f / 60.0f;
}

Player::Player(GameObject* parent) : GameObject(sceneTop),counter(0)
{
	hImage = LoadGraph("Assets/aoi.png");
	assert(hImage > 0);
	transform_.position_.x = 10.0f;
	transform_.position_.y = GROUND;
	jumpSpeed = 0.0f;
	onGround = true;
	
}

Player::~Player()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Player::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Stone* st = Instantiate<Stone>(GetParent());

	if (pField != nullptr) 
	{
		//(50,64)‚Æ(14,64)‚àŒ©‚é
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 64);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 64);
		int push = max(pushR, pushL);//‚Q‚Â‚Ì‘«Œ³‚Ì‚ß‚èž‚Ý‚Ì‘å‚«‚¢•û
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

	counter -= 1;
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;

		if (++frameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 4;
			frameCounter = 0;
		}
		int hitX = transform_.position_.x + 50;
		int hitY = transform_.position_.y + 63;
		if (pField != nullptr) 
		{
			int push = pField->CollisionRight(hitX, hitY);
			transform_.position_.x -= push;
		}
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.position_.x -= MOVE_SPEED;

		if (++frameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 4;
			frameCounter = 0;
		}
		int hitX = transform_.position_.x - 50;
		int hitY = transform_.position_.y - 63;
		if (pField != nullptr)
		{
			int push = pField->CollisionLeft(hitX, hitY);
			transform_.position_.x += push;
		}
	}
	else
	{
		animFrame = 0;
		frameCounter = 0;
	}

	//if (CheckHitKey(KEY_INPUT_SPACE))
	//{
	//	if(prevSpaceKey == false)
	//	{
	//		if (onGround)
	//		{
	//			jumpSpeed = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
	//			onGround = false;
	//		}
	//	}
	//	prevSpaceKey = true;
	//}
	//else
	//{
	//	prevSpaceKey = false;
	//}
	jumpSpeed += GRAVITY;
	transform_.position_.y += jumpSpeed;

	if (CheckHitKey(KEY_INPUT_O))
	{
		if (counter <= 0)
		{
			counter = 160;
			st->SetPosition(transform_.position_.x, transform_.position_.y);
		}
	}



	//ƒJƒƒ‰‚ÌˆÊ’u’²®
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	if (x > 400)
	{
		x = 400;
		cam->SetValue((int)transform_.position_.x - x);
	}
	else if(x <=0)
	{
		cam->SetValue((int)transform_.position_.x);
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawRectGraph(x, y, animFrame * 64, 0, 64, 64, hImage, TRUE);
}

void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}
