#include "Stone.h"
#include <assert.h>
#include "Camera.h"

namespace {
	const float MOVE_SPEED = 0.5f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;
	const float GRAVITY = 9.8f / 60.0f;
}

Stone::Stone(GameObject* scene) : GameObject(scene)
{
	hImage = LoadGraph("Assets/stone.png");
	assert(hImage > 0);
}

Stone::~Stone()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Stone::Update()
{
	if (timer <= 300)
	{	
		transform_.position_.x += 3.0f;
		transform_.position_.y += sqrtf(2 * GRAVITY * JUMP_HEIGHT);
	}
	else
	{
		transform_.position_.x += 3.0f;
		transform_.position_.y -= sqrtf(2 * GRAVITY * JUMP_HEIGHT);
	}
	jumpSpeed += GRAVITY;
	transform_.position_.y += jumpSpeed;
	if (transform_.position_.y >= GROUND)
	{
		transform_.position_.y = GROUND;
		jumpSpeed = 0.0f;
	}
	
	if (transform_.position_.y == 400)
	{
		KillMe();
	}

	--timer;
}

void Stone::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawGraph(x, y, hImage, TRUE);
}

void Stone::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer = 600;
}
