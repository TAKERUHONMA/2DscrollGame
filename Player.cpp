#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stone.h"

namespace {
	const float MOVE_SPEED = 0.5f;
	const float GROUND = 400.0f;
}

Player::Player(GameObject* parent) : GameObject(sceneTop)
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
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.position_.x -= MOVE_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone* st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//ƒWƒƒƒ“ƒv
		jumpSpeed = -1.0f;
	}
	jumpSpeed += 9.8f / 60.0f;
	transform_.position_.y += jumpSpeed;
	if (transform_.position_.y >= GROUND)
	{
		transform_.position_.y = GROUND;
		jumpSpeed = 0.0f;
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
}
