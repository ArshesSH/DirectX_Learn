#include "framework.h"
#include "ObjLoader.h"
#include "MtlTex.h"
#include "ObjGroup.h"

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::Load( OUT std::vector<ObjGroup*>& pGroups, IN char* szFolder, IN char* szFile )
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;

	std::vector<PNT_VERTEX> vecVertex;

	std::string sFullPath( szFolder );
	sFullPath += (std::string( "/" ) + std::string( szFile ));

	FILE* fp;
	fopen_s( &fp, sFullPath.c_str(), "r" );

	std::string sMtlName;

	while ( true )
	{
		if ( feof( fp ) )
		{
			break;
		}
		char szTemp[1024];
		fgets( szTemp, 1024, fp );
		if ( szTemp[0] == '#' )
		{
			continue;
		}
		else if ( szTemp[0] == 'm' )
		{
			char szMtlFile[1024];
			sscanf_s( szTemp, "%*s %s", szMtlFile, 1024 );
			LoadMtlLib( szFolder, szMtlFile );

		}
		else if ( szTemp[0] == 'g' )
		{
			if ( !vecVertex.empty() )
			{
				ObjGroup* pGroup = new ObjGroup;
				pGroup->SetVertices( vecVertex );
				pGroup->SetMaterialTexture( mtlTexMap[sMtlName] );
				pGroups.push_back( pGroup );
				vecVertex.clear();
			}
		}
		else if ( szTemp[0] == 'v' )
		{
			if ( szTemp[1] == ' ' )
			{
				float x, y, z;
				sscanf_s( szTemp, "%*s %f %f %f", &x, &y, &z );
				vecV.push_back( D3DXVECTOR3( x, y, z ) );
			}
			else if ( szTemp[1] == 't' )
			{
				float u, v;
				sscanf_s( szTemp, "%*s %f %f %*f", &u, &v );
				vecVT.push_back( D3DXVECTOR2( u, v ) );
			}
			else if ( szTemp[1] == 'n' )
			{
				float x, y, z;
				sscanf_s( szTemp, "%*s %f %f %f", &x, &y, &z );
				vecVN.push_back( D3DXVECTOR3( x, y, z ) );
			}
		}
		else if ( szTemp[0] == 'u' )
		{
			char szMtlName[1024];
			sscanf_s( szTemp, "%*s %s", szMtlName, 1024 );
			sMtlName = std::string( szMtlName );
		}
		else if ( szTemp[0] == 'f' )
		{
			int nIndex[3][3];
			sscanf_s( szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]
			);
			for ( int i = 0; i < 3; ++i )
			{
				PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back( v );
			}
		}
	}
	fclose( fp );

	for ( auto it : mtlTexMap )
	{
		SAFE_RELEASE( it.second );
	}
	mtlTexMap.clear();
}

void ObjLoader::LoadMtlLib( char* szFolder, char* szFile )
{
	std::string sFullPath( szFolder );
	sFullPath += (std::string( "/" ) + std::string( szFile ));
	FILE* fp;
	fopen_s( &fp, sFullPath.c_str(), "r" );

	std::string sMtlName;

	while ( true )
	{
		if ( feof( fp ) )
		{
			break;
		}
		char szTemp[1024];
		fgets( szTemp, 1024, fp );
		if ( szTemp[0] == '#' )
		{
			continue;
		}
		else if ( szTemp[0] == 'n' )
		{
			char szMtlName[1024];
			sscanf_s( szTemp, "%*s %s", szMtlName, 1024 );
			sMtlName = std::string( szMtlName );
			if ( mtlTexMap.find( sMtlName ) == mtlTexMap.end() )
			{
				mtlTexMap[sMtlName] = new MtlTex;
			}
		}
		else if ( szTemp[0] == 'K' )
		{
			if ( szTemp[1] == 'a' )
			{
				float r, g, b;
				sscanf_s( szTemp, "%*s %f %f %f", &r, &g, &b );
				mtlTexMap[sMtlName]->GetMaterial().Ambient.r = r;
				mtlTexMap[sMtlName]->GetMaterial().Ambient.g = g;
				mtlTexMap[sMtlName]->GetMaterial().Ambient.b = b;
				mtlTexMap[sMtlName]->GetMaterial().Ambient.a = 0.1f;
			}
			else if ( szTemp[1] == 'd' )
			{
				float r, g, b;
				sscanf_s( szTemp, "%*s %f %f %f", &r, &g, &b );
				mtlTexMap[sMtlName]->GetMaterial().Diffuse.r = r;
				mtlTexMap[sMtlName]->GetMaterial().Diffuse.g = g;
				mtlTexMap[sMtlName]->GetMaterial().Diffuse.b = b;
				mtlTexMap[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if ( szTemp[1] == 's' )
			{
				float r, g, b;
				sscanf_s( szTemp, "%*s %f %f %f", &r, &g, &b );
				mtlTexMap[sMtlName]->GetMaterial().Specular.r = r;
				mtlTexMap[sMtlName]->GetMaterial().Specular.g = g;
				mtlTexMap[sMtlName]->GetMaterial().Specular.b = b;
				mtlTexMap[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if ( szTemp[0] == 'd' )
		{
			float d;
			sscanf_s( szTemp, "%*s %f", &d );
			mtlTexMap[sMtlName]->GetMaterial().Power = d;
		}
		else if ( szTemp[0] == 'm' )
		{
			char szTexFile[1024];
			sscanf_s( szTemp, "%*s %s", szTexFile, 1024 );
			sFullPath = std::string( szFolder );
			sFullPath += (std::string( "/" ) + std::string( szTexFile ));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture( sFullPath );
			mtlTexMap[sMtlName]->SetTexture( pTexture );
		}
	}
	fclose( fp );
}

void ObjLoader::LoadSurface( OUT std::vector<D3DXVECTOR3>& surfaces, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat )
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<PNT_VERTEX> vecVertex;

	std::string sFullPath( szFolder );
	sFullPath += (std::string( "/" ) + std::string( szFile ));

	FILE* fp;
	fopen_s( &fp, sFullPath.c_str(), "r" );

	std::string sMtlName;

	while ( true )
	{
		if ( feof( fp ) )
		{
			break;
		}
		char szTemp[1024];
		fgets( szTemp, 1024, fp );
		if ( szTemp[0] == '#' )
		{
			continue;
		}
		else if ( szTemp[0] == 'v' )
		{
			if ( szTemp[1] == ' ' )
			{
				float x, y, z;
				sscanf_s( szTemp, "%*s %f %f %f", &x, &y, &z );
				vecV.push_back( D3DXVECTOR3( x, y, z ) );
			}
		}
		else if ( szTemp[0] == 'f' )
		{
			int nIndex[3];
			sscanf_s( szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &nIndex[0], &nIndex[1], &nIndex[2]);
			for ( int i = 0; i < 3; ++i )
			{
				surfaces.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}
	fclose( fp );


	if ( pMat )
	{
		for ( size_t i = 0; i < surfaces.size(); ++i )
		{
			D3DXVec3TransformCoord( &surfaces[i], &surfaces[i], pMat );
		}
	}
}
