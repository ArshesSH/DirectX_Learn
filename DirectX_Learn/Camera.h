#pragma once
class Camera
{
public:
	Camera();

	void Setup( D3DXVECTOR3* pTargetPos );
	void Update();
	void WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
private:
	static constexpr float camDefaultDist = 5.0f;

	D3DXVECTOR3 camPos;
	D3DXVECTOR3 camDirection;
	D3DXVECTOR3 camUp;
	D3DXVECTOR3* pTargetPos;

	POINT prevMousePoint;
	bool isRButtonDown;
	float camDistance;
	D3DXVECTOR3 camRotation;

	float camHorizontalSpeed = 100.0f;
	float camVerticalSpeed = 100.0f;

	float camAngleYLimit = 2.0f;
	float camZoomSpeed = 100.0f;

	float camMinDist = 3.0f;

	RECT clientRect;
};

