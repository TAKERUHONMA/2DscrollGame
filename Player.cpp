#include "Engine/SceneManager.h"
#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include "Stone.h"
#include "Camera.h"
#include "Field.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Gool.h"
#include "TestScene.h"

namespace {
	const float MOVE_SPEED = 2.0f;
	const float GROUND = 400.0f;
	const float JUMP_HEIGHT = 64.0f * 4.0f;//ジャンプの高さ
	const float GRAVITY = 9.8f / 60.0f;//重力加速度
	const int MAX_STONE = 20; //小石を投げれる最大数
	float STONE_NUMBER = 940;
	//const float INITIALVELOCITY = 18.0f;

}


Player::Player(GameObject* parent) : GameObject(sceneTop), counter(0), count(0), rcount(0)
{
	hImage = LoadGraph("Assets/player2.png");
	kazu = LoadGraph("Assets/suji.png");
	assert(hImage > 0);
	transform_.position_.x = 10.0f;
	transform_.position_.y = GROUND;
	jumpSpeed = 0.0f;
	onGround = true;
	animType = 0;
	animFrame = 0;
	frameCounter = 0;
	state = S_Walk;
	transparency = 0;
	readyTimer = 1.5f;
	Reset();
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

	counter -= 1;
	//rcount += 1;

	if (state == S_Cry)
	{
		if (frameCounter >= 4)
		{
			frameCounter = 0;
		}
		return;
	}

	TestScene* scene = dynamic_cast<TestScene*>(GetParent());
	if (!scene->CanMove())
		return;

	//前進
	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
		if (++frameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 3;
			frameCounter = 0;
		}
		int hitX = transform_.position_.x + 50;
		int hitY = transform_.position_.y + 60;
		if (pField != nullptr) {
			int push = pField->CollisionRight(hitX, hitY);
			transform_.position_.x -= push;
		}
	}
	else if (CheckHitKey(KEY_INPUT_A))//後退
	{
		if (transform_.position_.x <= 1)
		{
			transform_.position_.x = 0;
		}
		else
		{
			transform_.position_.x -= MOVE_SPEED;
			if (++frameCounter >= 8)
			{
				animFrame = (animFrame + 1) % 3;
				frameCounter = 0;
			}
			int hitX = transform_.position_.x - 14;
			int hitY = transform_.position_.y + 60;
			if (pField != nullptr)
			{
				int push = pField->CollisionLeft(hitX, hitY);
				transform_.position_.x += push;
			}
		}
	}
	else
	{
		animFrame = 0;
		frameCounter = 0;
	}

	//if (CheckHitKey(KEY_INPUT_SPACE)) 
	//{
	//	if (prevSpaceKey == false) 
	//	{
	//		if (onGround) {
	//			jumpSpeed = -sqrtf(2 * (GRAVITY)*JUMP_HEIGHT);
	//			onGround = false;
	//		}
	//	}
	//	prevSpaceKey = true;
	//}
	//else
	//{
	//	prevSpaceKey = false;
	//}

	jumpSpeed += GRAVITY;//速度 += 加速度
	transform_.position_.y += jumpSpeed; //座標 += 速度

	
	if (pField != nullptr)
	{
		//(50,64)と(14,64)も見る
		int pushR = pField->CollisionDown(transform_.position_.x + 80, transform_.position_.y + 80);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 80);
		int push = max(pushR, pushL);//２つの足元のめり込みの大きい方
		if (push >= 1) {
			transform_.position_.y -= push - 1;
			jumpSpeed = 0.0f;
			onGround = true;
		}
		else {
			onGround = false;
		}
	}

	//if (CheckHitKey(KEY_INPUT_SPACE)) 
	//{
	//	if (prevSpaceKey == false) 
	//	{
	//		if (onGround) 
	//		{
	//			jumpSpeed = -sqrtf(2 * (GRAVITY)*JUMP_HEIGHT);
	//			onGround = false;
	//		}
	//	}
	//	prevSpaceKey = true;
	//}
	//else 
	//{
	//	prevSpaceKey = false;
	//}

	jumpSpeed += GRAVITY;//速度 += 加速度
	transform_.position_.y += jumpSpeed; //座標 += 速度

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

	/*if (CheckHitKey(KEY_INPUT_SPACE)) {
		canJump = false;
	}
	if (canJump == false) {
		transform_.position_.y = 0.5 * GRAVITY * time_ * time_ - INITIALVELOCITY * time_ + GROUND;
		time_ += 0.5f;
		if (transform_.position_.y > GROUND) {
			transform_.position_.y = GROUND;
			time_ = 0.0f;
			canJump = true;
		}
	}*/

	//石を投げる
	if (count == MAX_STONE)
	{

	}
	else
	{
		if (CheckHitKey(KEY_INPUT_O))
		{
			if (counter <= 0)
			{
				counter = 160;
				if (counter == 160)
				{
					count += 1;
					STONE_NUMBER -= 47;
				}
				st->SetPosition(transform_.position_);
			}
		}
	}

	//敵1の当たり判定
	std::list<Enemy1*> pBirds = GetParent()->FindGameObjects<Enemy1>();
	for (Enemy1* pBird : pBirds)
	{
		if (pBird->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f))
		{
			animType = 4;
			animFrame = 0;
			state = S_Cry;
			scene->StartDead();
			//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			//pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		}
	}

	//敵2の当たり判定
	std::list<Enemy2*> pLivingthings = GetParent()->FindGameObjects<Enemy2>();
	for (Enemy2* pLivingthing : pLivingthings)
	{
		if (pLivingthing->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f))
		{
			animType = 4;
			animFrame = 0;
			//state = S_Cry;
			scene->StartDead();
			//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			//pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		}
	}

	//ゴールの当たり判定
	std::list<Gool*> pGools = GetParent()->FindGameObjects<Gool>();
	for (Gool* pGool : pGools)
	{
		if (pGool->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 110.0f))
		{
			animType = 4;
			animFrame = 0;

			readyTimer -= 1.0f / 60.0f;
			if (readyTimer <= 0.0f)
			{
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
			}

			//state = S_Cry;
			//rcount = 100;
			//if (rcount == 99)
			//{
			//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			//	pSceneManager->ChangeScene(SCENE_ID_GAMECLEAR);
			//}
			//else
			//{
			//	rcount--;
			//}
			////SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);

		}
	}

	//ここでカメラ位置の調整
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int x = (int)transform_.position_.x - cam->GetValue();
	if (x <= 1)
	{
		x = 1;
		cam->SetValue((int)transform_.position_.x);
	}
	else
	{
		if (x > 400)
		{
			x = 400;
			cam->SetValue((int)transform_.position_.x - x);
		}
	}

	//落下した時
	if (transform_.position_.y >= 700)
	{
		scene->StartDead();
		KillMe();
	}

	//リセット
	if (CheckHitKey(KEY_INPUT_R))
	{
		Reset();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency + 500);
	}


}

void Player::Draw()
{
	DrawRectGraph(145, -10, 0, STONE_NUMBER, 92, 64, kazu, TRUE);

	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();

	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawRectGraph(x, y, animFrame * 80, 180, 88, 88, hImage, TRUE);
}

//プレイヤーのポジション
void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}


void Player::Reset()
{
	count = 0;
	STONE_NUMBER = 940;
	DrawRectGraph(170, 0, 0, STONE_NUMBER, 64, 64, kazu, TRUE);
}