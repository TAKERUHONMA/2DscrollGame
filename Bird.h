#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ’¹i“Gj
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;

	//‰~‚Ì“–‚½‚è”»’è‚ğ‚·‚é
	bool CollideCircle(float x, float y, float r);
private:
	int hImage;
};
