#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[�L����
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	//void GetPosition(int x, int y) { transform_.position_.x = x, transform_.position_.y = y; }
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int counter;
	int animType; //�^�C�v
	int animFrame; //�R�}
	int frameCounter;

	//float cameraX; //�J�����̈ʒu
};