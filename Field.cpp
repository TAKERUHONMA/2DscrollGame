#include "Field.h"
#include "Player.h"
#include <assert.h>
#include "Engine/CsvReader.h"

Field::Field(GameObject* scene)
{
	hImage = LoadGraph("Assets/bgchar.png");
	assert(hImage > 0);
}

Field::~Field()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Field::Update()
{
}

void Field::Draw()
{
}

void Field::Reset()
{
	CsvReader csv;
	bool ret = csv.Load("Assets/stage1.csv");
	assert(ret);
	int width = csv.GetWidth();
	int height = csv.GetHeight();

}
