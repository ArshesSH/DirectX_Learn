#pragma once

class Graphics
{
public:
	Graphics()
	{
		D3DXMatrixIdentity( &matWorld );
	}

	void DrawLine( const std::vector<PC_VERTEX>& lineVertices )
	{
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
		g_pD3DDevice->DrawPrimitiveUP( D3DPT_LINELIST, lineVertices.size() / 2, &lineVertices[0], sizeof( PC_VERTEX ) );
	}
	void DrawTriangle( const std::vector<PC_VERTEX>& triVertices )
	{
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );
		g_pD3DDevice->SetFVF( PC_VERTEX::FVF );
		g_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, triVertices.size() / 3, &triVertices[0], sizeof( PC_VERTEX ) );
	}
private:
	D3DXMATRIXA16 matWorld;
};

