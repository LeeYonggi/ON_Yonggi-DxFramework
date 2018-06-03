#include "stdafx.h"
#include "Camera01.h"


void Camera01::Init()
{
	AddComponent<cCamera>();
	transform.position = { 0.0f, 0.0f, MAX_SIZE_DIVISION };
	transform.rotation = { 0.0f, 0.0f, 0.0f };
	GetComponent<cCamera>()->SetCam({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
}

void Camera01::Update()
{
}

void Camera01::Render()
{
}

void Camera01::Release()
{
}

Camera01::Camera01()
{
}


Camera01::~Camera01()
{
}
