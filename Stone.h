#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[���������
/// </summary>
class Stone : public GameObject
{
public:
	Stone(GameObject* scene);
	~Stone();
	void Update() override;
	void Draw() override;
	void SetPosition(int x,int y);
private:
	int hImage;
	int timer;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
};
