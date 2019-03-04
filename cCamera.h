#pragma once
#include "Component.h"


class cCamera :
	public Component
{
private:
	D3DXVECTOR3 viewtargetPoint;
	D3DXVECTOR3 viewworldUp;
public:
	void SetCam(D3DXVECTOR3 viewtargetPoint, D3DXVECTOR3 viewworldUp);
	void Render() override;

	cCamera();
	~cCamera();
};

