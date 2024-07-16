#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// プレイヤーの座標をセットする
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);

	void Reset();
private:
	int hImage;
	int kazu;

	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int counter;
	int count;
	int animType; //状況
	int animFrame;//コマ
	int frameCounter;
	float transparency;//透明度

	enum State {
		S_Walk=0,
		S_Cry,
	};
	State state;
};