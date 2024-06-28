#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ƒvƒŒƒCƒ„[‚ª“Š‚°‚éÎ
/// </summary>
class Stone : public GameObject
{
public:
	Stone(GameObject* scene);
	~Stone();
	void Update() override;
	void Draw() override;
	void SetPosition(int x,int y);
	void SetPositionY(int y) { transform_.position_.y = y; }
	int GetPositionY() { return transform_.position_.y; }
private:
	int hImage;
	int timer;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
};
