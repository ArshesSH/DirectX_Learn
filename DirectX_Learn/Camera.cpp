#include "framework.h"
#include "Camera.h"

Camera::Camera()
	:
	camRotation( 0.0f, 0.0f, 0.0f ),
	camPos( 0.0f, 0.0f, -camDefaultDist ),
	camDirection( 0.0f, 0.0f, 0.0f ),
	camUp( 0.0f, 1.0f, 0.0f ),
	pTargetPos( nullptr ),
	camDistance( camDefaultDist ),
	isRButtonDown(false),
	prevMousePoint({0,0})
{
}

void Camera::Setup( D3DXVECTOR3* pTargetPos = nullptr )
{
	this->pTargetPos = pTargetPos;

	GetClientRect( g_hWnd, &clientRect );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4.0f, (float)clientRect.right / (float)clientRect.bottom, 1.0f, 1000.0f );
	g_pD3DDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

void Camera::Update()
{
	GetClientRect( g_hWnd, &clientRect );
	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX( &matRX, camRotation.x );
	D3DXMatrixRotationY( &matRY, camRotation.y );
	matR = matRX * matRY;

	camPos = D3DXVECTOR3( 0.0f, 0.0f, -camDistance );
	D3DXVec3TransformCoord( &camPos, &camPos, &matR );

	if ( pTargetPos )
	{
		camDirection = *pTargetPos;
		camPos = camPos + *pTargetPos;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &camPos, &camDirection, &camUp );
	g_pD3DDevice->SetTransform( D3DTS_VIEW, &matView );
}

void Camera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
	case WM_RBUTTONDOWN:
		{
			prevMousePoint.x = LOWORD( lParam );
			prevMousePoint.y = HIWORD( lParam );
			isRButtonDown = true;
		}
		break;
	
	case WM_RBUTTONUP:
		{
			isRButtonDown = false;
		}
		break;

	case WM_MOUSEMOVE:
		{
			if ( isRButtonDown )
			{
				POINT curMousePoint;
				curMousePoint.x = LOWORD( lParam );
				curMousePoint.y = HIWORD( lParam );
				float deltaX = (float)(curMousePoint.x - prevMousePoint.x);
				float deltaY = (float)(curMousePoint.y - prevMousePoint.y);

				camRotation.y += (deltaX / camHorizontalSpeed);
				camRotation.x += (deltaY / camVerticalSpeed);

				if ( camRotation.x < -D3DX_PI / 2.0f + 0.0001f )
				{
					camRotation.x = -D3DX_PI / 2.0f + 0.0001f;
				}
				if ( camRotation.x > D3DX_PI / 2.0f - 0.0001f )
				{
					camRotation.x = D3DX_PI / 2.0f - 0.0001f;
				}
				prevMousePoint = curMousePoint;
			}
		}
		break;

	case WM_MOUSEWHEEL:
		{
			camDistance -= (GET_WHEEL_DELTA_WPARAM( wParam ) / camZoomSpeed);
			if ( camDistance < camMinDist )
			{
				camDistance = camMinDist;
			}
		}
		break;
	}
}
