#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size)
{
	// ���� Ÿ�� ����
	type = Type::BOX;

	MakeMesh();         // ó�� ������ �� �������̾��� �޽� ��� ���
	mesh->CreateMesh(); // �޽� ��� ���� ����
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
    // �浹 ��Ȳ ��ÿ� ����� OBB ���� ���
    obbDesc.pos      = GlobalPos(); // (�浹�� �Ͼ �浹ü��) ���� �� ���� ��ġ�� �ݿ�
    obbDesc.axis[0]  = Right();     // �⺻ �� ���� �ֱ�. Right : �¿�  = X
    obbDesc.axis[1]  = Up();        // ���Ʒ�  = Y
    obbDesc.axis[2]  = Forward();   // �յ�    = Z

    // ��� ���Ǹ� ���� ���� ũ�� �̸� ���ϱ� (half = ����)
    obbDesc.halfSize = size * 0.5f * GlobalScale(); // ������ ������ ���� �� ũ�⸦ �ݿ�
}

// ������ �ڽ� �浹ü�� �ε�ģ �⺻ ��Ȳ
bool BoxCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
	// �浹ü�� ���� ��Ȳ�� ������Ʈ
    UpdateWorld();

    // ��Ͽ� ����ü
    ObbDesc box;
    GetObb(box); // �ʱ�ȭ ����ϱ�

    // ��Ͽ� ����ü���� ����� �浹 ���� �ּ� �ִ� ���ϱ�
    // ��� �ڽ��� �ּ� �ִ� �԰��� ���س��� �ش� �԰ݺ��� �浹 ��� ��Ȳ�� ��� ������ �׳� �浹 �� �� �ɷ� ģ��
    Vector3 min   = box.halfSize * -1.0f;  // �ּ� �԰� ���ϱ�
    Vector3 max   = box.halfSize * 1.0f;   // �ִ� �԰� ���ϱ�

    Vector3 delta = box.pos = ray.pos;       // �浹ü�� ���� �߿����� ���ͻ� (����)����
    Vector3 D     = ray.dir.GetNormalized(); // ���� ������ ����ȭ�� �� : �������
                                             // dir : ����
                                             // GetNormalized() : ����ȭ

    // ����� ��ġ�� �ִ� �ּ� ���ϱ�
    float tMin = 0.0f;
    float tMax = FLT_MAX; // �̰ͺ��� ū ���ڴ� �����Ѵ�
                          // -> unsigned ���� ������ �ڷ����� ���� �ʰ� ������ ���ڴ�

    // ������� ���� ��� ������ �⺻ ���� ���� ���� ��
    // �������� ������ �ڽ��� ��Ȳ�� ����

    // 3�� ������ �ݺ��� : Obb ���ü �� ���ڿ� ���� 
    // �ش� ���ü�� �� �������� ������ ��� �������� �ִ°��� ���� ����
    for (int i = 0; i < 3; ++i)
    {
        // OBB���� �� ������
        Vector3 axis = box.axis[i]; // �ٸ� ������ ���ٸ� x -> y -> z �� ������ ��ġ���� �Ǻ�
        
        // ��� ������ ���� ����
        float e = Dot(axis, delta); // ���ü ��� �ڽ�-���� �������� ����
        float f = Dot(D, axis);     // ���� ��ü�� (�ڽ��ʹ� ����ȯ) ��ü ������ ���ü�� ��� ����
        // ����(D)�������� ������ ���ڵ��̱� ������ ��Ī�� �� e, f�� ��Ī
        // -> �� ������ ���̿��� ���� cos = ������ ������ ������ �� �ִ� ���ڰ� ���´�

        // �׷��� �� ������ ������ �� 
        // 1. �����̴� = ������ ��ü�� ������ �� �Ѵ�

        // if (f == 0)            // <- Į��� ����. �Ǽ��� �����е� ����� ���� �Ͼ�� DirectX Ư���� ���� ���ɼ�
        // if (f <= FLT_EPSILON)  // <- ��ǻ�Ͱ� ������ �Ѿ�� �ʰ� ���� ������ ���� ���� �Ҽ� (�ԽǷ� ����)
                                  // FLT_EPSILON : ��ǻ�Ͱ� ���� ������ ���� ���� �Ҽ�
        if (NearlyEqual(f, 0.0f)) // <- �� �����ӿ�ũ����, �ش� ���ڰ� ���� ���ڿ��� �� ��ŭ�� �ԽǷ� ������ �Ͼ���� (Ȥ�� �� �Ͼ����) �Ǻ� ����
        {
            // ������ Obb �Ƴ� �־����� �ƴϳĸ� �Ǻ�
            // �ƿ� ������ ó������ �浹ü �ȿ��� ���� �Ŷ�� �翬�� �浹 ���ɼ� ����(�̶�⺸��, ����)
            // �ݴ�� ������ �ƿ� ���̰�, �ೢ�� ���� �Ÿ� ����͵� �� �����̸� -> ������ ����

            // ���ü�� x, y, z �࿡ �ٽ� �˻�
            switch (i)
            {
            case 0:
                if (min.x > e || max.x < e) return false;
                break;

            case 1:
                if (min.y > e || max.y < e) return false;
                break;

            case 2:
                if (min.z > e || max.z < e) return false;
                break;
            }

            // ������� ����, �ϴ� ���ɼ��� ��
            // 1. ������ ������ �ƴϴ� (�� if���� ����)
            // 2. ������ �����ε�, ��ġ�� ������ �� �ִ� (switch) �ȿ��� is ���ǹ� ����)
            //    -> �˻�� ��� �Ѵ�
        }
        else
        {
            float raw1;
            float raw2;

            // x, y, z�� ���� ���� ���迡 ���� �� ���� ����
            switch (i)
            {
            case 0:
                raw1 = min.x;
                raw2 = max.x;
                break;

            case 1:
                raw1 = min.y;
                raw2 = max.y;
                break;

            case 2:
                raw1 = min.z;
                raw2 = max.z;
                break;
            }

            // raw�� �̿��ؼ� �񱳿� �Ҽ� t�� ���Ѵ� (���� ������ ����)

            float t1 = (e + raw1) / f; // ���� ����(�Ÿ�)�� �� ������ �ּҰ��� �����ϰ� ������踦 ����Ѵ�
            float t2 = (e + raw2) / f;

            // t1�� t2�� ���� �ٽ� ���ϱ� (������ ���ü�� �Ÿ�����, ������ ���ü�� ũ�����)

            // if (t1 > t2) swap(t1, t2); // �� ū ���� t2�� �ǵ��� ���� ������ �ٲٱ�

            // �� ū ���� ���� ��� �����ΰ�?
            if (t2 < tMax) tMax = t2; // �ִ븦 tMax�� ���Ҵ�
            if (t1 > tMin) tMin = t1; // �ּҵ� ���Ҵ�

            // �� ū ���� �ڷ� ����� �ϴµ� 
            if (tMin > tMax)  // ����� �ּҰ��� �ִ밪�� ������ �Ѿ ��Ȳ = �Ÿ� Ȥ�� ������ ��߳���
                return false;
        }

        // ������� ���� 
        // 1. ������ �浹ü�� ��� ���̿� ������ ���� (���� �鿡�� ���� ���ɼ� ����)
        // 2. ������ �浹ü ���̿�, �Ÿ� - ���� ���迡�� ��߳��� ���� (������ �� ���󰡸� �ݵ�� �ε�ħ)

        // ���� ���� ����ϱ�
        if (contact != nullptr)
        {
            contact->tag      = tag;                        // �浹ü�� �̸��� �±׿� ��� (������ �ε��ƴ°�)
            contact->distance = tMin;                       // ��ϵ� ���� ���� �Ÿ� = �浹�� ���۵� ����
            contact->hit      = ray.pos + (ray.dir * tMin); // ���� �������� �� �浹 ������(�� ����)
        }

        return true; // �������Ƿ� true
    }
}

bool BoxCollider::InSphereCollision(SphereCollider* collider)
{
	
}

bool BoxCollider::IsBoxCollision(BoxCollider* collider)
{
	
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, BoxCollider::ObbDesc box1, BoxCollider::ObbDesc box2)
{
	
}

void BoxCollider::MakeMesh()
{
	// Draw �Ű����� ������ ���� �Ž� ����� �ٸ���

	// �⺻(�Ű����� ����, ����Ʈ) ���� �޽� ����

    vector<Vertex>& vertices = mesh->GetVertices();

    Vector3 half = size * 0.5f;

    // * ������ ������ 8���� �־ ������, UV ť�긦 �������� ������� �ߺ� ��ǥ ����

    //Front
    vertices.emplace_back(-half.x, -half.y, -half.z, 0, 1);
    vertices.emplace_back(-half.x, +half.y, -half.z, 0, 0);
    vertices.emplace_back(+half.x, -half.y, -half.z, 1, 1);
    vertices.emplace_back(+half.x, +half.y, -half.z, 1, 0);
    //Up
    vertices.emplace_back(-half.x, +half.y, -half.z, 0, 1);
    vertices.emplace_back(-half.x, +half.y, +half.z, 0, 0);
    vertices.emplace_back(+half.x, +half.y, -half.z, 1, 1);
    vertices.emplace_back(+half.x, +half.y, +half.z, 1, 0);
    //Left
    vertices.emplace_back(+half.x, +half.y, -half.z, 0, 1);
    vertices.emplace_back(+half.x, +half.y, +half.z, 0, 0);
    vertices.emplace_back(+half.x, -half.y, -half.z, 1, 1);
    vertices.emplace_back(+half.x, -half.y, +half.z, 1, 0);

    //Right
    vertices.emplace_back(-half.x, +half.y, -half.z, 0, 1);
    vertices.emplace_back(-half.x, -half.y, -half.z, 0, 0);
    vertices.emplace_back(-half.x, +half.y, +half.z, 1, 1);
    vertices.emplace_back(-half.x, -half.y, +half.z, 1, 0);

    //Back
    vertices.emplace_back(-half.x, +half.y, +half.z, 0, 1);
    vertices.emplace_back(-half.x, -half.y, +half.z, 0, 0);
    vertices.emplace_back(+half.x, +half.y, +half.z, 1, 1);
    vertices.emplace_back(+half.x, -half.y, +half.z, 1, 0);

    //Down
    vertices.emplace_back(-half.x, -half.y, -half.z, 0, 1);
    vertices.emplace_back(+half.x, -half.y, -half.z, 0, 0);
    vertices.emplace_back(-half.x, -half.y, +half.z, 1, 1);
    vertices.emplace_back(+half.x, -half.y, +half.z, 1, 0);

    vector<UINT>& indices = mesh->GetIndices();
    indices = 
    {
        //Front
        0, 1, 2, 2, 1, 3,
        //Up
        4, 5, 6, 6, 5, 7,
        //Right
        8, 9, 10, 10, 9, 11,
        //Left
        12, 13, 14, 14, 13, 15,
        //Back
        16, 17, 18, 18, 17, 19,
        //Down
        20, 21, 22, 22, 21, 23
    };

    // D3D11_PRIMITIVE_TOPOLOGY_LINELIST ������ ���
    // 1. ������ �����ϰ� 8���� ���� ����
    // 2. �ش� 8���� ��ǥ�� ����
    // 3. "���� ����" -> "���� ��" ������ ���Ϳ� �߰��� ���鼭 �ε��� ���͸� ä���
    //    (A �𼭸� ���� -> A �𼭸� �� -> (A �𼭸� ���� ��ǥ�� ����) B �𼭸� ���� -> B �𼭸� ��)
    //    (������ ���÷� ���, 0 -> 1 -> 1 -> 3 -> 3 -> 2 -> 2 -> 0 -> 0�̳� 4)
}
