#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ���i�G�j
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;

	//�~�̓����蔻�������
	bool CollideCircle(float x, float y, float r);
private:
	int hImage;
};
