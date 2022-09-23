#pragma once

#define g_pDeviceManager DeviceManager::GetInstance()
#define g_pD3DDevice DeviceManager::GetInstance()->GetDevice()

class DeviceManager
{
	SINGLETON( DeviceManager )

public:
	//DeviceManager( D3DCOLOR screenDefaultColor );

	LPDIRECT3DDEVICE9 GetDevice();
	void Destroy();

private:
	void Init();

public:
	D3DCOLOR screenDefaultColor;
private:
	LPDIRECT3D9			pD3D;
	LPDIRECT3DDEVICE9	pD3DDevice;
};

