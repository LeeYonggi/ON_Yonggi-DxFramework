#include "stdafx.h"
#include "Character.h"


void Character::Init()
{
	AddComponent<TexVertexRenderer>();
	m_sprite = GetComponent<TexVertexRenderer>();
	m_sprite->AddanimeImage("test", L"./PNG/horse/%d.png", 1, 8, 150);
	m_sprite->SetAnimeConfirm(true);
	transform.position = { 640, 360, 0 };
	transform.rotation = { 0, 0, 0 };
}

void Character::Update()
{
}

void Character::Render()
{
}

void Character::Release()
{
}

Character::Character()
{
}


Character::~Character()
{
}
