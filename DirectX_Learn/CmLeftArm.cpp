#include "framework.h"
#include "CmLeftArm.h"

void CmLeftArm::Setup()
{
	CubeManBodyParts::Setup( { sizeX, sizeY, sizeZ }, { axisX, axisY, axisZ }, { 0.0f, localPosY, 0.0f } );
	{
		vertices[0].t.x = (float)44 / 64; vertices[0].t.y = (float)32 / 32;
		vertices[1].t.x = (float)44 / 64; vertices[1].t.y = (float)20 / 32;
		vertices[2].t.x = (float)48 / 64; vertices[2].t.y = (float)20 / 32;  //¾Õ¸é À­»ï°¢ 
		 //0,1,2vertices[3].t.x = (float)44 / 64; vertices[3].t.y = (float)32 / 32;
		vertices[4].t.x = (float)48 / 64; vertices[4].t.y = (float)20 / 32;
		vertices[5].t.x = (float)48 / 64; vertices[5].t.y = (float)32 / 32;  //¾Õ¸é ¾Æ·§»ï°¢
		 //0,2,3
		vertices[6].t.x = (float)56 / 64; vertices[6].t.y = (float)32 / 32;
		vertices[7].t.x = (float)52 / 64; vertices[7].t.y = (float)20 / 32;
		vertices[8].t.x = (float)56 / 64; vertices[8].t.y = (float)20 / 32;  //µÞ¸é À­»ï°¢
		 //4,6,5
		vertices[9].t.x = (float)56 / 64; vertices[9].t.y = (float)32 / 32;
		vertices[10].t.x = (float)52 / 64; vertices[10].t.y = (float)32 / 32;
		vertices[11].t.x = (float)52 / 64; vertices[11].t.y = (float)20 / 32;  //µÞ¸é ¾Æ·§»ï°¢
		 //4,7,6
		vertices[12].t.x = (float)40 / 64; vertices[12].t.y = (float)32 / 32;
		vertices[13].t.x = (float)40 / 64; vertices[13].t.y = (float)20 / 32;
		vertices[14].t.x = (float)44 / 64; vertices[14].t.y = (float)20 / 32;  //¿ÞÂÊ¸é À­»ï°¢
		 //4,5,1
		vertices[15].t.x = (float)40 / 64; vertices[15].t.y = (float)32 / 32;
		vertices[16].t.x = (float)44 / 64; vertices[16].t.y = (float)20 / 32;
		vertices[17].t.x = (float)44 / 64; vertices[17].t.y = (float)32 / 32;  //¿ÞÂÊ¸é ¾Æ·§»ï°¢
		 //4,1,0
		vertices[18].t.x = (float)48 / 64; vertices[18].t.y = (float)32 / 32;
		vertices[19].t.x = (float)48 / 64; vertices[19].t.y = (float)20 / 32;
		vertices[20].t.x = (float)52 / 64; vertices[20].t.y = (float)20 / 32;  //¿À¸¥¸é À­»ï°¢
		 //3,2,6
		vertices[21].t.x = (float)48 / 64; vertices[21].t.y = (float)32 / 32;
		vertices[22].t.x = (float)52 / 64; vertices[22].t.y = (float)20 / 32;
		vertices[23].t.x = (float)52 / 64; vertices[23].t.y = (float)32 / 32;  //¿À¸¥¸é ¾Æ·§»ï°¢
		 //3,6,7
		vertices[24].t.x = (float)44 / 64; vertices[24].t.y = (float)20 / 32;
		vertices[25].t.x = (float)44 / 64; vertices[25].t.y = (float)16 / 32;
		vertices[26].t.x = (float)48 / 64; vertices[26].t.y = (float)16 / 32;  //À­¸é À­»ï°¢
		 //1,5,6
		vertices[27].t.x = (float)44 / 64; vertices[27].t.y = (float)20 / 32;
		vertices[28].t.x = (float)48 / 64; vertices[28].t.y = (float)16 / 32;
		vertices[29].t.x = (float)48 / 64; vertices[29].t.y = (float)20 / 32;  //À­¸é ¾Æ·§»ï°¢
		 //1,6,2
		vertices[30].t.x = (float)48 / 64; vertices[30].t.y = (float)16 / 32;
		vertices[31].t.x = (float)48 / 64; vertices[31].t.y = (float)20 / 32;
		vertices[32].t.x = (float)52 / 64; vertices[32].t.y = (float)20 / 32;  //¾Æ·§¸é À­»ï°¢
		 //4,0,3
		vertices[33].t.x = (float)48 / 64; vertices[33].t.y = (float)16 / 32;
		vertices[34].t.x = (float)52 / 64; vertices[34].t.y = (float)20 / 32;
		vertices[35].t.x = (float)52 / 64; vertices[35].t.y = (float)16 / 32;  //¾Æ·§¸é ¾Æ·§»ï°¢
	}
}
