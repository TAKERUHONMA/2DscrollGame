#pragma once
#include "Engine/GameObject.h"

class Livingthings
	: public GameObject 
{
public:
	Livingthings(GameObject* scene);
	~Livingthings();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// ���̍��W���Z�b�g����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPosition(int x, int y);

	//�~�̓����蔻�������
	bool CollideCircle(float x, float y, float r);
private:
	bool prevSpaceKey;
	float jumpSpeed;
	int counter;
	bool onGround;
	float sinAngle;
	int hImage;
	float baseY;//��������Y���W
};

