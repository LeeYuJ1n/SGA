#pragma once

class ModelExporter
{
	// 모델 데이터를 원형 데이터에서 앱 등에서 빠르게 재사용 가능한 포맷으로 변환해줄 클래스

	// 원형 데이터 : FBX, nif, dds, png... 아트 디자인, 키 프레임 등 
	//              기본적인 데이터가 실제로 담긴 진짜 리소스

	// 모델 데이터 : .mesh, .model, .mats, .mat, .prefab
	// 언리얼 엔진 : .mesh, .model, mats
	// 유니티 엔진 : .mat, .prefab
	//              원형 데이터를 통해서 앱이 빠르게 연산을 수행할 수 있도록
	//              용도나 자료형에 따라서 데이터를 다시 정리한 결과

public:
	ModelExporter(string name, string file);
	// 파일에서 지정된 이름을 적용해서, 같은 이름이 적용된 모델의 데이터를 만들기
	~ModelExporter();

	void ExportMaterial(); // 매티리얼
	void ExportMesh();     // 메시
	void ExportClip(string clipName);     // 키 프레임을 읽어서 동작의 데이터로 내보내기 위한 함수

private:
	// 매티리얼
	void ReadMaterial();  // 원형에서 데이터 읽기
	void WriteMaterial(); // 읽은 데이터 적용하거나 쓰기
	
	string CreateTexture(string file);
	// FBX가 안에 프레임, 메시, 텍스처까지 다 갖고 있는 경우
	// 텍스처를 따로 빼기 위한 함수

	// 메시
	// ai가 붙으면 에셋 임포트에서 제공하는 자료형식으로 제공하겠다라는 뜻
	void ReadMesh(aiNode* node); // 전체 모양 읽기
	void ReadNode(aiNode* node, int index, int parent); // 관절 정보 읽기
	void ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights); // 뼈대와 정점의 가중치 적용

	void WriteMesh(); // 다 읽은 데이터로 결과 메시 만들기

	// 동작
	Clip* ReadClip(aiAnimation* animation); // aiAnimation : 에셋 임포트 라이브러리의 애니메이션 관리 클래스

	void ReadKeyFrame(Clip* clip, aiNode node, vector<ClipNode>* clipnodes); // 키 프레임 읽기
	void WriteClip(Clip* clip, string clipName, UINT index);                 // 프레임으로 동작을 구성하기

private:
	// 에셋 임포트 라이브러리 사용 : 읽어들이기 클래스
	Assimp::Importer* importer; // importer : 읽어오기, export : 써서 보내기

	const aiScene* scene; // 임포트용 씬 구성하기 : 다른 제공된 함수를 불러올 수 있게

	string name; // 모델의 이름을 매개변수에서 받을 수 있게

	vector<Material*> materials;
	vector<MeshData*> meshes;
	vector<NodeData*> nodes;
	vector<BoneData*> bones;

	map<string, UINT> boneMap;

	UINT boneCount = 0; // 뼈대 개수 (0에서 초기화로 시작)
};

