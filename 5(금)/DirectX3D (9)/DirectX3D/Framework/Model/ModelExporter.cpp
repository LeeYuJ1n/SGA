#include "Framework.h"

ModelExporter::ModelExporter(string name, string file) : name(name)
{
	importer = new Assimp::Importer(); // 임포터 호출
	importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false); 
	// 자기 객체 내 옵션을 호출해서 설정하는 함수
	// 매개변수 옵션  = "읽으려는 FBX 포맷이 사전에 정의된 회전축 정보가 있나요? / 아니오."
	importer->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS); // 정수값으로 옵션 설정
	// 매개변수 옵션 = "정보를 선별해서 가져와야 하나요? / 화소의 법선보정을 같이 가져와주세요!

	// 에셋 임포트로 호출한 씬을 추가 설정
	scene = importer->ReadFile(file, // 매개변수로 받은 파일을 지정해서 읽기
		aiProcessPreset_TargetRealtime_MaxQuality | // 씬 읽어들이기 과정을 미리 지정한 옵션에서 1차 지정, 지정값 = 최상옵
		aiProcess_Triangulate |                     // 3각형 도형을 기본으로 3D 데이터 연산
		aiProcess_GenSmoothNormals |                // 법선끼리 각도가 너무 커지지 않도록 후처리 연산
		aiProcess_FixInfacingNormals |              // 법선값이 축 (특히 카메라쪽) 방향으로 뻗어나갈 때 빛처리나 법선 자체 계산이 오류나 원하지 않는 결과는 덜 내도록
		aiProcess_RemoveRedundantMaterials |        // 부적절하거나 애초에 지정도 안 된 매티리얼이 있으면 읽기에서 제외
		aiProcess_OptimizeMeshes |                  // 내장된 기능을 사용해서 정점들의 사양 부담을 최적화
		aiProcess_ValidateDataStructure |           // 원형 데이터의 정보 구조체들이 필요한 데이터를 모두 적절히 담았는지 확인하고, 재인증
		aiProcess_ImproveCacheLocality |            // 메모리를 쓸 때 최대한 데이터들이 흩어지지 않게 사용 (안전성 조금 희생, 속도 상승)
		aiProcess_JoinIdenticalVertices |           // 위치상 똑같다고 판단해도 될 정점들이 있으면 나중에 변형이 생겨도 떨어지지 않게 붙이기
		aiProcess_FindInvalidData |                 // 연산 중에 어떤 이유든 부적절한 데이터가 들어오는지 판별
		aiProcess_TransformUVCoords |               // 트랜스폼의 UV 좌표도 같이 계산 (텍스처가 있을 경우 대비)
		aiProcess_FlipUVs |                         // 텍스처의 UV가 방향이 다르다거나, 면 자체가 반대 방향이어도 UV를 뒤집어서 인식
		aiProcess_ConvertToLeftHanded);             // 행렬의 정보를 벡터로 표현할 때, 왼손 좌표계로 바꾼다는 뜻 = DX식 축방향

	assert(scene != nullptr); // 씬을 못 읽으면 강제 종료
	                          // = 이 프레임워크는 FBX 혹은 다른 원형 모델 데이터가 완전할 것을 강요하겠습니다
}

ModelExporter::~ModelExporter()
{
	delete importer;

	// delete scene; // ai에서 따로 관리

	// 다 만든 데이터가 모델 객체로 갈 거기 때문에
	// 지운다면 모델이 지우는 게 맞을 것 : 여기서는 일단 보류
	// vector<Material*> materials;
	// vector<MeshData*> meshes;
	// vector<NodeData*> nodes;
	// vector<BoneData*> bones;
}

// 밖에서 호출하기 위한 기능들
void ModelExporter::ExportMaterial()
{
	// 읽어서 호출하고 저장까지
	ReadMaterial();
	WriteMaterial();
}

void ModelExporter::ExportMesh()
{
	// 관절을 하나씩 읽기
	ReadNode(scene->mRootNode, -1, -1); // root node : 가장 상위에 있는, 개체 그 자체를 총괄하는 노드
	ReadMesh(scene->mRootNode);         // 모양도 읽기
	WriteMesh();
}

void ModelExporter::ExportClip(string clipName)
{
	FOR(scene->mNumAnimations) // 읽어들인 파일에서 수록된 애니메이션의 수 만큼 i가 들어가는 반복문을 돌려서
	{
		Clip* clip = ReadClip(scene->mAnimations[i]); // i번째 애니메이션을 구성하는 프레임을 클립으로 읽기
		WriteClip(clip, clipName, i);
	}
}

// 세부 기능들
void ModelExporter::ReadMaterial()
{
	FOR(scene->mNumMaterials) // 씬에 수록된 매티리얼 수만큼 반복
	{
		aiMaterial* srcMaterial = scene->mMaterials[i]; // srcMaterial = source 매티리얼
		Material* material = new Material();

		material->GetName() = srcMaterial->GetName().C_Str(); // 소스 매티리얼의 이름을 스트링으로 적용

		aiColor3D color; // 색 받아오기
		Material::MaterialBuffer::Data& data = material->GetData(); // 매티리얼 데이터 받아오기

		// 소스의 색 정보를 받아서 적용하기
		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);    // 디퓨즈를 컬러에 적용하기 (매개변수는 원본->출력 순서)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // 디퓨즈를 알파 포함해서 데이터에 적용해가ㅣ

		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);   // 반사정도를 컬러에 적용하기 (매개변수는 원본->출력 순서)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // 반사정도를 알파 포함해서 데이터에 적용해가ㅣ

		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);    // 어두움 범위를 컬러에 적용하기 (매개변수는 원본->출력 순서)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // 어두움 범위를 알파 포함해서 데이터에 적용해가ㅣ

		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);   // 밝음 범위를 컬러에 적용하기 (매개변수는 원본->출력 순서)
		data.diffuse = Float4(color.r, color.g, color.b, 1); // 밝음 범위를 알파 포함해서 데이터에 적용해가ㅣ

		srcMaterial->Get(AI_MATKEY_SHININESS, data.shininess); // 빛을 받아들이는 정도를 적용

		aiString file;
		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);        // 파일에서 텍스처의 정보 얻기 (디퓨즈맵)
		material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // 파일의 이름에서 텍스처를 추출해서 매티리얼에 적용
		
		file.Clear(); // 파일 읽기 메모리 초기화

		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);       // 파일에서 텍스처의 정보 얻기 (디퓨즈맵)
		material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // 파일의 이름에서 텍스처를 추출해서 매티리얼에 적용

		file.Clear(); // 파일 읽기 메모리 초기화

		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file); // 파일에서 텍스처의 정보 얻기 (디퓨즈맵)
		material->SetDiffuseMap(ToWString(CreateTexture(file.C_Str()))); // 파일의 이름에서 텍스처를 추출해서 매티리얼에 적용
		file.Clear(); // 파일 읽기 메모리 초기화

		materials.push_back(material); // 벡터에 넣기
	}
}

void ModelExporter::WriteMaterial()
{
	// 파일 쓰기 : 여기서 쓰기 위한 파일을 만드는 것이 목적
	// * 호환성 있는 포맷이 필요하면 그때 관련 클래스를 불러도 무관

	string savePath = "Models/Materials/" + name + "/";
	string fileName = name + ".mats"; // .mats : 매티리얼 정보들을 저장할 때 쓰는 확장자 (여기선 내부 포맷은 다르지만)

	CreateFolders(savePath);

	BinaryWriter* writer = new BinaryWriter(savePath + fileName);

	writer->UInt(materials.size()); // 일겅야 할 매티리얼 수를 미리 지정

	for (Material* material : materials)
	{
		string path = savePath + material->GetName() + ".mat";
		material->Save(path);

		writer->String(path); // 파일에 정보와 경로, 이름 모두 저장

		delete material; // 지금은 읽고 쓰기가 목적이니 매티리얼 다 쓴 건 하나씩 지우기
	}

	materials.clear(); // 다 저장했으니 벡터도 용도 다 함
	
	delete writer;
}

string ModelExporter::CreateTexture(string file)
{
	if (file.length() == 0)
	{
		return ""; // 아무것도 없는 것을 리턴
	}

	string fileName = GetFileNameWithoutExtension(file) + ".png"; // 파일 이름 준비
	string savePath = "Textures/Model/" + name + "/" + fileName;

	CreateFolders(savePath);

	const aiTexture* texture = scene->GetEmbeddedTexture(file.c_str()); // 파일이름에서 FBX 내장 텍스처 가져오기

	if (texture == nullptr) // 그런 내장 텍스처가 없다면 또 종료
	{
		return "";
	}

	if (texture->mHeight < 1)
	{
		BinaryWriter writer(savePath);
		writer.Byte(texture->pcData, texture->mWidth);
	}
	else
	{
		// 텍스처 정보를 C++의 Image 클래스에 옮겨담기
		Image image;
		image.width      = texture->mWidth;
		image.height     = texture->mHeight;
		image.pixels     = (uint8_t*)(texture->pcData); // 8바이트 int : 요즘 그림 특성상 정보량이 너무 많을 수도 있으니까
		image.rowPitch   = image.width * 4;
		image.slicePitch = image.width * image.height * 4;

		// 기록하기 ( = 그림에 넣기) : 추가옵션 없음, PNG, 위치는 정해진 문자열에 따라
		SaveToWICFile(image, 
			WIC_FLAGS_NONE,
			GetWICCodec(WIC_CODEC_PNG), 
			ToWString(savePath).c_str());
	}

	// 기록 끝난 경로를 반환
	return savePath;
}

void ModelExporter::ReadMesh(aiNode* node)
{
	FOR(node->mNumMeshes) // 매개변수로 지금 받은 노드의 구성 메시 개수에 따라
	{
		MeshData* mesh = new MeshData();
		mesh->name = node->mName.C_Str();

		UINT index = node->mMeshes[i]; // 현재 보고 있는 i번째 메시에 기록된 인덱스를 가져오기
		aiMesh* srcMesh = scene->mMeshes[index]; // 씬에서 인덱스를 통해 찾아내는 메시

		mesh->materialIndex = srcMesh->mMaterialIndex; // 매티리얼의 인덱스(들) 받아오기

		vector<VertexWeights> vertexWeights(srcMesh->mNumVertices);
		ReadBone(srcMesh, vertexWeights); // 뼈대 만들기를 여기서 호출

		mesh->vertices.resize(srcMesh->mNumVertices);

		for (UINT v = 0; v < srcMesh->mNumVertices; ++v) // 정점의 v
		{
			ModelVertex vertex;
			memcpy(&vertex.pos, &srcMesh->mVertices[v], sizeof(Float3));

			if (srcMesh->HasTextureCoords(0)) // HasTextureCoords : 매개변수로 받은 순번에 텍스처 좌표가 있는가?
				                              // true : 텍스처에 대한 정보가 1개 이상 있음
			{
				memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Float2));
			}

			if (srcMesh->HasNormals()) // 메시가 법선 정보를 같이 갖고 있다면
			{
				memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Float3));
			}

			if (srcMesh->HasTangentsAndBitangents()) // 탄젠트 (법선에 의한 화소 수정 정보)도 갖고 있다면
			{
				memcpy(&vertex.tangent, &srcMesh->mTangents[v], sizeof(Float3));
			}

			// 이렇게 메모리 카피를 통해서 원본 메시의 정보를 메모리로 읽어들인다

			// 그것을 mesh에 적용
			mesh->vertices[v] = vertex;
		}

		// 여기까지 정점
		// 여기부터는 인덱스

		mesh->indices.resize(srcMesh->mNumFaces * 3); // 원본 메시의 면 개수 x3

		for (UINT f = 0; f < srcMesh->mNumFaces; ++f)
		{
			aiFace& face = srcMesh->mFaces[f]; // 면을 하나씩 받아서

			for (UINT k = 0; k < face.mNumIndices; ++k)
			{
				// 면 하나 건너뛸 때마다 인덱스 3씩 건너뛰고, 각 면의 정점 3개의 인덱스 받기
				mesh->indices[f * 3 + k] = face.mIndices[k];
			}
		}

		// 여기까지 오면 메시의 구성 정보가 모두 모인다! (정점, 인덱스)

		meshes.push_back(mesh); // 만든 메시 담기
	}

	// 읽은 정보에 따라서 각 노드 밑에 다른 노드가 있는 경우
	// 해당 자식 노드도 모두 찾아서 메시 읽기를 진행

	for (UINT i = 0; i < node->mNumChildren; ++i)
	{
		ReadMesh(node->mChildren[i]); // 재귀함수로 메시 읽기를 반복
	}

	// 여기까지 오면 최초로 받은 node의 모든 메시 읽기가 끝난다
}

void ModelExporter::ReadNode(aiNode* node, int index, int parent)
{

}

void ModelExporter::ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights)
{

}

void ModelExporter::WriteMesh()
{

}

Clip* ModelExporter::ReadClip(aiAnimation* animation)
{
	return nullptr;
}

void ModelExporter::ReadKeyFrame(Clip* clip, aiNode node, vector<ClipNode>* clipnodes)
{

}

void ModelExporter::WriteClip(Clip* clip, string clipName, UINT index)
{

}
