#include "framework.h"
#include "HeightMap.h"

HeightMap::HeightMap()
	:
	pMesh(nullptr),
	pTexture(nullptr)
{
}

HeightMap::~HeightMap()
{
	Destroy();
}

void HeightMap::Setup( const char* const szFolder, const char* const szRaw, const char* const szTex, DWORD dwBytePerPixel )
{
	/*--- Get File Size ---*/
	std::string folderStr( szFolder );
	std::string rawStr = folderStr + std::string( szRaw );
	std::string textureStr = folderStr + std::string( szTex );

	pTexture = g_pTextureManager->GetTexture( textureStr );

	FILE* pF = nullptr;
	fopen_s( &pF, rawStr.c_str(), "rb" );
	fseek( pF, 0, SEEK_END );
	int nFileSize = ftell( pF );

	int nNumVertices = nFileSize / dwBytePerPixel;

	int nRow = (int)(sqrt( (float)nNumVertices ) + 0.0001f);
	int nCol = nRow;
	nTile = nRow - 1;

	fseek( pF, 0, SEEK_SET );

	/*--- Get Vertices ---*/
	std::vector<PNT_VERTEX> pntVertices( nNumVertices );
	vertices.resize( nNumVertices );

	std::vector<DWORD> indices;
	indices.reserve( nTile * nTile * 2 * 3 );

	for ( int i = 0; i < nNumVertices; ++i )
	{
		PNT_VERTEX v;
		v.p = D3DXVECTOR3( (float)(i % nCol), ((unsigned char)fgetc( pF ) / 10.0f), (float)(i / nCol) );
		v.n = D3DXVECTOR3( 0, 1, 0 );
		v.t = D3DXVECTOR2( i % nCol / float( nCol ), (i / nCol) / float( nCol ) );

		pntVertices[i] = v;
		vertices[i] = v.p;
		if ( dwBytePerPixel == 3 )
		{
			fgetc( pF );
			fgetc( pF );
		}
	}
	fclose( pF );

	/*--- Create Noraml Vec ---*/
	for ( int x = 1; x < nTile; ++x )
	{
		for ( int z = 1; z < nTile; ++z )
		{
			int left = (z + 0) * nCol + x - 1;
			int right = (z + 0) * nCol + x + 1;
			int up = (z + 1) * nCol + x + 0;
			int down = (z - 1) * nCol + x + 0;

			D3DXVECTOR3 leftToRight = vertices[right] - vertices[left];
			D3DXVECTOR3 downToUp = vertices[up] - vertices[down];
			D3DXVECTOR3 normal;
			D3DXVec3Cross( &normal, &downToUp, &leftToRight );
			D3DXVec3Normalize( &normal, &normal );
			int nindex = z * nCol + x;
			pntVertices[nindex].n = normal;
		}
	}

	/*--- Index Buffer ---*/
	/*
	* 0---3
	* | \ |
	* 1---2
	*/
	for ( int x = 0; x < nTile; ++x )
	{
		for ( int z = 0; z < nTile; ++z )
		{
			int v0 = (z + 0) * nCol + x + 0;
			int v1 = (z + 1) * nCol + x + 0;
			int v2 = (z + 0) * nCol + x + 1;
			int v3 = (z + 1) * nCol + x + 1;

			indices.push_back( v0 );
			indices.push_back( v1 );
			indices.push_back( v2 );

			indices.push_back( v2 );
			indices.push_back( v1 );
			indices.push_back( v3 );
		}
	}

	/*--- Create Mesh ---*/
	D3DXCreateMeshFVF( indices.size() / 3, pntVertices.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, PNT_VERTEX::FVF, g_pD3DDevice, &pMesh
	);

	/*--- Send Information to GPU ---*/
	PNT_VERTEX* pV = nullptr;
	pMesh->LockVertexBuffer( 0, (LPVOID*)&pV );
	memcpy( pV, &pntVertices[0], pntVertices.size() * sizeof( PNT_VERTEX ));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = nullptr;
	pMesh->LockIndexBuffer( 0, (LPVOID*)&pI );
	memcpy( pI, &indices[0], indices.size() * sizeof( DWORD ) );
	pMesh->UnlockIndexBuffer();

	DWORD* pA = nullptr;
	pMesh->LockAttributeBuffer( 0, &pA );
	ZeroMemory( pA, (indices.size() / 3) * sizeof( DWORD ) );
	pMesh->UnlockAttributeBuffer();

	/*--- Initialize ---*/
	std::vector<DWORD> adjacencies( indices.size() );
	pMesh->GenerateAdjacency( 0.0f, &adjacencies[0] );
	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&adjacencies[0],
		0, 0, 0
	);

	ZeroMemory( &mtl, sizeof( D3DMATERIAL9 ) );
	mtl.Ambient = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	mtl.Diffuse = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	mtl.Specular = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
}

void HeightMap::Render()
{
	D3DXMATRIXA16 worldMat;
	D3DXMatrixIdentity( &worldMat );
	g_pD3DDevice->SetTransform( D3DTS_WORLD, &worldMat );
	g_pD3DDevice->SetMaterial( &mtl );
	g_pD3DDevice->SetTexture( 0, pTexture );
	pMesh->DrawSubset( 0 );
}

bool HeightMap::GetHeight( IN float x, OUT float& y, IN float z )
{
	/*
	* 0---3
	* | \ |
	* 1---2
	*/
	if ( x < 0.0f || z < 0.0f || x >= nTile || z >= nTile )
	{
		y = 0;
		return false;
	}

	int nX = (int)x;
	int nZ = (int)z;

	float deltaX = x - nX;
	float deltaZ = z - nZ;

	int idx0 = (nZ + 0) * (nTile + 1) + nX + 0;
	int idx1 = (nZ + 1) * (nTile + 1) + nX + 0;
	int idx2 = (nZ + 0) * (nTile + 1) + nX + 1;
	int idx3 = (nZ + 1) * (nTile + 1) + nX + 1;

	if ( deltaX + deltaZ < 1.0f )
	{
		D3DXVECTOR3 v01 = vertices[idx1] - vertices[idx0];
		D3DXVECTOR3 v02 = vertices[idx2] - vertices[idx0];
		y = vertices[idx0].y + (v01 * deltaZ + v02 * deltaX).y;
	}
	else
	{
		deltaX = 1.0f - deltaX;
		deltaZ = 1.0f - deltaZ;

		D3DXVECTOR3 v31 = vertices[idx1] - vertices[idx3];
		D3DXVECTOR3 v32 = vertices[idx2] - vertices[idx3];
		y = vertices[idx3].y + (v31 * deltaZ + v32 * deltaX).y;
	}

	return true;
}

void HeightMap::Destroy()
{
	SAFE_RELEASE( pTexture );
	SAFE_RELEASE( pMesh );
}
