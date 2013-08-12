#include "../Interfaces/ResourceService.h"

#include "../../Graphics/Model3D.h"
#include "../../Helpers/BinaryReader.h"

template<> unique_ptr<Model3D> ResourceService::LoadResource<Model3D>(std::tstring filePath)
{
	auto pModel = new Model3D();
	BinaryReader meshFile(filePath);
	unsigned int inputLayoutID = 0;

	auto versionNumber = meshFile.Read<unsigned short>();

	auto vertexFormat = meshFile.Read<unsigned char>();
	auto nrOfTexCoordChannels = meshFile.Read<unsigned char>();

	unsigned int* nrOfTexCoordsArr;
	unsigned int nrOfPositions=0, nrOfNormals=0, nrOfTangents=0, nrOfBinormals=0, nrOfVertexColors=0;//, nrOfAnimData=0;
	
	nrOfPositions = meshFile.Read<unsigned int>();

	if(nrOfTexCoordChannels > 0){
		nrOfTexCoordsArr = new unsigned int[nrOfTexCoordChannels];
		meshFile.ReadArray<unsigned int>(nrOfTexCoordsArr, nrOfTexCoordChannels);
	}
	if(vertexFormat & 1)
		nrOfNormals = meshFile.Read<unsigned int>();
	if(vertexFormat & 2)
		nrOfTangents = meshFile.Read<unsigned int>();
	if(vertexFormat & 4)
		nrOfBinormals = meshFile.Read<unsigned int>();
	if(vertexFormat & 8)
		nrOfVertexColors = meshFile.Read<unsigned int>();
	//if(vertexFormat & 16)
		//nrOfAnimData = meshFile.Read<unsigned int>();
	
	auto nrOfVertices = meshFile.Read<unsigned int>();
	auto nrOfIndices = meshFile.Read<unsigned int>();

	//Read vertex positions
	for(unsigned int i=0; i < nrOfPositions; ++i){
		auto x = meshFile.Read<float>();
		auto y = meshFile.Read<float>();
		auto z = meshFile.Read<float>();

		pModel->m_Positions.data.push_back(D3DXVECTOR3(x,y,z));
	}
	
	//Read texture coordinates
	if(nrOfTexCoordChannels > 0){
		pModel->m_TexCoords.resize(nrOfTexCoordChannels);
		for(unsigned short channel = 0; channel < nrOfTexCoordChannels; ++channel){
			for(unsigned int i = 0; i < nrOfTexCoordsArr[channel]; ++i){
				auto u = meshFile.Read<float>();
				auto v = meshFile.Read<float>();

				pModel->m_TexCoords[channel].data.push_back(D3DXVECTOR2(u,v));
			}
		}
		delete[] nrOfTexCoordsArr;
	}

	//Read vertex normals
	if(vertexFormat & 1){
		for(unsigned int i=0; i < nrOfNormals; ++i){
			auto x = meshFile.Read<float>();
			auto y = meshFile.Read<float>();
			auto z = meshFile.Read<float>();

			pModel->m_Normals.data.push_back(D3DXVECTOR3(x,y,z));
		}
	}
	
	//Read vertex tangents
	if(vertexFormat & 2){
		for(unsigned int i=0; i < nrOfTangents; ++i){
			auto x = meshFile.Read<float>();
			auto y = meshFile.Read<float>();
			auto z = meshFile.Read<float>();

			pModel->m_Tangents.data.push_back(D3DXVECTOR3(x,y,z));
		}
	}
	
	//Read vertex binormals
	if(vertexFormat & 4){
		for(unsigned int i=0; i < nrOfBinormals; ++i){
			auto x = meshFile.Read<float>();
			auto y = meshFile.Read<float>();
			auto z = meshFile.Read<float>();

			pModel->m_Binormals.data.push_back(D3DXVECTOR3(x,y,z));
		}
	}
	
	//Read vertex color
	if(vertexFormat & 8){
		for(unsigned int i=0; i < nrOfVertexColors; ++i){
			auto r = meshFile.Read<float>();
			auto g = meshFile.Read<float>();
			auto b = meshFile.Read<float>();
			auto a = meshFile.Read<float>();

			pModel->m_Colors.data.push_back(D3DXCOLOR(r,g,b,a));
		}
	}
	/*
	if(vertexFormat & 16){
	//Read blend indices
		for(unsigned int i=0; i < nrOfAnimData; ++i){
			auto x = meshFile.Read<float>();
			auto y = meshFile.Read<float>();
			auto z = meshFile.Read<float>();
			auto w = meshFile.Read<float>();

			pModel->m_BlendIndices.push_back(D3DXVECTOR4(x,y,z,w));
		}
		inputLayoutID += 100000;

		//Read blend weights
		for(unsigned int i=0; i < nrOfVertices; ++i){
			auto x = meshFile.Read<float>();
			auto y = meshFile.Read<float>();
			auto z = meshFile.Read<float>();
			auto w = meshFile.Read<float>();

			pModel->m_BlendWeights.push_back(D3DXVECTOR4(x,y,z,w));
		}
	}
	*/
	
	pModel->m_TexCoords.resize(nrOfTexCoordChannels);
	
	//Read vertices
	for(unsigned int i=0; i < nrOfVertices; ++i)
	{
		auto iPos = meshFile.Read<unsigned int>();
		pModel->m_Positions.indices.push_back(iPos);

		if(nrOfTexCoordChannels > 0){
			auto iTexCoordArr = new unsigned int[nrOfTexCoordChannels];
			meshFile.ReadArray<unsigned int>(iTexCoordArr, nrOfTexCoordChannels);

			for(unsigned int channel=0; channel < nrOfTexCoordChannels; ++channel)
				pModel->m_TexCoords[channel].indices.push_back(iTexCoordArr[channel]);
								
			delete[] iTexCoordArr;
		}
		if(nrOfNormals > 0){
			auto iNormal = meshFile.Read<unsigned int>();
			pModel->m_Normals.indices.push_back(iNormal);
		}
		if(nrOfTangents > 0){
			auto iTangent = meshFile.Read<unsigned int>();
			pModel->m_Tangents.indices.push_back(iTangent);
		}
		if(nrOfBinormals > 0){
			auto iBinormal = meshFile.Read<unsigned int>();
			pModel->m_Binormals.indices.push_back(iBinormal);
		}
		if(nrOfVertexColors > 0){
			auto iVertexColor = meshFile.Read<unsigned int>();
			pModel->m_Colors.indices.push_back(iVertexColor);
		}/*
		if(nrOfAnimData > 0){
			auto iAnimData = meshFile.Read<unsigned int>();
			pModel->m_BlendIndices.indices.push_back(iAnimData);
			pModel->m_BlendWeights.indices.push_back(iAnimData);
		}*/
	}

	//Read indices
	for(unsigned int i=0; i < nrOfIndices; ++i)
		pModel->m_Indices.push_back(meshFile.Read<unsigned int>());

	return std::unique_ptr<Model3D>(pModel);
}

/*
file layout:

//----------------
// metadata
//----------------

2 bytes: version number

1 byte: vertex format

1 << #
     1 normal
     2 tangent
     3 normal
	 4 color
     5 animdata

1 byte: # of uv channels

4 bytes					 : nrOfPositions
4 bytes * nrOfUVChannels : nrOfTexcoords (per uv channel))
4 bytes					 : nrOfNormals
4 bytes					 : nrOfTangents
4 bytes					 : nrOfBinormals
4 bytes					 : nrOfAnimData

4 bytes					 : nrOfVertices
4 bytes					 : nrOfIndices

//------------------
// vertex attributes
//------------------

12 bytes * nrOfPositions						: positions
8 bytes  * (nrOfTexcoords0 + nrOfTexcoords1...)	: texcoords (channel 0, ..., channel 9)
12 bytes * nrOfNormals							: normals
12 bytes * nrOfTangents							: tangents
12 bytes * nrOfBinormals						: binormals
16 bytes * nrOfVertColors						: colors
16 bytes * nrOfBlendindices						: blendindices
16 bytes * nrOfBlendweights						: blendweights

//---------
// vertices
//---------
4 bytes : posIndex	
4 bytes : UVIndex		
4 bytes : normalIndex	
4 bytes : tangentIndex
4 bytes : binormalIndex
4 bytes : colorIndex	
4 bytes : animDataIndex

^-- * nrOfVertices

//--------
// indices
//--------
4 bytes * nrOfIndices : indices

EOF
*/