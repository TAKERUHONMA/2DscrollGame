#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stone.h"

namespace {
	const float MOVE_SPEED = 0.5f;
	const float GROUND = 400.0f;
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
	counter -= 1;
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.position_.x -= MOVE_SPEED;
	}

	if (counter <= 0)
	{
		counter = 80;
		if (CheckHitKey(KEY_INPUT_O))
		{
			Stone* st = Instantiate<Stone>(GetParent());
			st->SetPosition(transform_.position_);
		}
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if(prevSpaceKey == false)
		{
			if (onGround)
			{
				jumpSpeed = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
				onGround = false;
			}
		}
		prevSpaceKey = true;
	}
	else
	{
		prevSpaceKey = false;
	}
	jumpSpeed += GRAVITY;
	transform_.position_.y += jumpSpeed;
	if (transform_.position_.y >= GROUND)
	{
		transform_.position_.y = GROUND;
		jumpSpeed = 0.0f;
		onGround = true;
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
}
