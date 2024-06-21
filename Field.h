#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 地面（プレイフィールド）
/// </summary>
class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 右側の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めり込んだ量(ドット)</returns>
	int CollisionRight(int x, int y);

	/// <summary>
	/// 下の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めり込んだ量(ドット)</returns>
	int CollisionDown(int x, int y);
	void Reset();
private:
	int hImage;

	bool IsWallBlock(int x, int y);
};
