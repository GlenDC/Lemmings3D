//====================== #INCLUDES ===================================
#include "HeightmapParser.h"
//--------------------------------------------------------------------
#include "../Lib/LemmingsHelpers.h"
//--------------------------------------------------------------------
#include "Diagnostics/Logger.h"
#include "Helpers/BinaryReader.h"
//--------------------------------------------------------------------
#include <memory>
//====================================================================

bool HeightmapParser::Read(const tstring & file, const UINT width, const UINT height, 
						   const float heightDivider, const float scale, const float texScale)
{
	std::shared_ptr<BinaryReader> binReader(new BinaryReader(file));
	vector<char> heightMap;
	vector<vector<D3DXVECTOR3>> vertexList(height);
    for( UINT r = 0; r < height; r++ )
        vertexList[r] = vector<D3DXVECTOR3>(width);
 
    UINT rows = width;
    UINT cols = height;
    //UINT width = width;
    //UINT height = height;
    //float scale = 1.0f;
    //m_pScale = scale;
    bool isProc = true;
    float maxDistance = 10.0f;
    //m_texScale = texScale;  
    float tdist = static_cast<float>(width/cols)*scale;
    float tdist2 = static_cast<float>(height/rows)*scale;
 
    /*file= fopen(heightMapFilename, "rb");
    if(file==NULL)
        return false;*/
 
	if(width*height == 0) return false; // less than 2 dimensions!

	int size(width*height);
	heightMap.reserve(size * sizeof(char));
	for(int i = 0 ; i < size ; ++i)
	{
		heightMap.push_back(binReader->ReadChar());
	}

    //heightMap= new unsigned char    [width*height];
    //if(heightMap==NULL)
    //    return false;   // didnt allocate
 
 
    //fread(heightMap, 1, width*height, file);
 
    for( UINT r = 0; r < rows; r++ ){
        for( UINT c = 0; c < cols; c++ ) {
            vertexList[r][c].x = r*tdist;
                int a = heightMap[(r*cols)+c];
                vertexList[r][c].y = (float)(a);
            vertexList[r][c].z = c*tdist2;
        }
    }       
 
    /*if(heightMap)
        delete[] heightMap;
 */
     
    return true;
}


bool HeightmapParser::Read(const tstring & file, const UINT width, const UINT height, vector<vector<D3DXVECTOR3>> & vertex2DVec,
						    D3DXVECTOR2 & depthInfo, const float heightDivider, const float scale, const float texScale) 
{
	//std::shared_ptr<BinaryReader> binReader(new BinaryReader(file));
	vector<char> heightMap;

    for( UINT r = 0; r < height; r++ )
		vertex2DVec.push_back(vector<D3DXVECTOR3>(width));
 
    UINT rows = width;
    UINT cols = height;

    bool isProc = true;
    float tdist = static_cast<float>(width/cols)*scale;
    float tdist2 = static_cast<float>(height/rows)*scale;
 
	if(width*height == 0) return false; 

	int size(width*height);
	/*heightMap.reserve(size * sizeof(char));
	for(int i = 0 ; i < size ; ++i)
	{
		heightMap.push_back((float)binReader->ReadChar());
	}*/
	LoadHeightMap(file, width, height, heightMap);

	depthInfo = D3DXVECTOR2(0,0);
 
    for( UINT r = 0; r < rows; ++r)
	{
        for( UINT c = 0; c < cols; ++c) 
		{
            vertex2DVec[r][c].x = r*tdist;
            float a = heightMap[(r*height)+c];
			float depth(a*heightDivider);
			//save min and max depth
			if (depth < depthInfo.x) depthInfo.x = depth;
			else if (depth > depthInfo.y) depthInfo.y = depth;
			vertex2DVec[r][c].y = depth;
            vertex2DVec[r][c].z = c*tdist2;
        }
    }     

	//binReader->Close();
     
    return true;
}

bool HeightmapParser::LoadHeightMap(const tstring & file, const int width, 
									const int height, std::vector<char> & heightmapVec)
{
	int size(width*height);
	//create already sized vector to store height values
	heightmapVec.resize(size, 0 );
	//open binary file 
	std::ifstream inFile;
	inFile.open(GlobalHelpers::ConvertToString(file).c_str(),std::ios_base::binary);
	if ( !inFile )
	{
		tstringstream tstrstr;
		tstrstr << _T("Loading heightmap ") << file << _T(" Failed  !!!");
		ASSERT(false, tstrstr.str().c_str());
		return false;
	}
	//read height info
	inFile.read((char*)&heightmapVec[0], 
		(std::streamsize)(size * sizeof(char)) );	
	inFile.close();

	return true;
}