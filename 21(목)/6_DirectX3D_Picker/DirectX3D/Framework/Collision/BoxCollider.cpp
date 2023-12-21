#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size)
{
    //�ӽ� �ڵ� : ����� ������ �� �ǳ׿�...
    this->size = Vector3(1, 1, 1);


    //���� �̳� ����
    type = Type::BOX;

    MakeMesh(); // ó�� ������ �� �������̾��� �޽� ��� ���
    mesh->CreateMesh(); //�޽� ��� ���� ����
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
    // �浹 ��Ȳ ��ÿ� ����� OBB ���� ���

    obbDesc.pos = GlobalPos(); // (�浹�� �Ͼ �浹ü��) ���� �� ���� ��ġ�� �ݿ�

    obbDesc.axis[0] = Right(); // �⺻ ������ �ֱ�. Right�� �¿� = X
    obbDesc.axis[1] = Up();    // ���Ʒ� = Y
    obbDesc.axis[2] = Forward(); // �յ� = Z

    //��� ���Ǹ� ���� ���� ũ�� �̸� ���ϱ�
    obbDesc.halfSize = size * 0.5f * GlobalScale(); // ������ ������ ���� �� ũ�⸦ �ݿ�

}

//������ �ڽ� �浹ü�� �ε�ģ �⺻ ��Ȳ
// * 12.15 : �Ű������� ����Ʈ ���� ���ǿ����� �ۼ����� �ʽ��ϴ�!
bool BoxCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{

    ObbDesc box;
    GetObb(box);

    Vector3 min = box.halfSize * -1.0f;
    Vector3 max = box.halfSize;

    Vector3 delta = box.pos - ray.pos;

    Vector3 D = ray.dir.GetNormalized();

    float tMin = 0.0f;
    float tMax = FLT_MAX;

    for (int i = 0; i < 3; i++)
    {
        Vector3 axis = box.axis[i];
        float e = Dot(axis, delta);
        float f = Dot(D, axis);

        if (NearlyEqual(f, 0.0f))//���̿� ���� ������ ��Ȳ
        {
            if (min[i] > e || max[i] < e) return false;
        }
        else
        {
            float t1 = (e + min[i]) / f;
            float t2 = (e + max[i]) / f;

            if (t1 > t2) swap(t1, t2);

            if (t2 < tMax) tMax = t2;
            if (t1 > tMin) tMin = t1;
            if (tMin > tMax) return false;
        }
    }

    if (contact != nullptr)
    {
        contact->tag = tag;
        contact->distance = tMin;
        contact->hit = ray.pos + ray.dir * tMin;
    }

    return true;
    
}

bool BoxCollider::IsSphereCollision(class SphereCollider* collider)
{
    // ��ü�� �ڽ��� �浹

    ObbDesc box;
    GetObb(box);

    Vector3 closestPointToSphere = box.pos;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 direction = collider->GlobalPos() - box.pos;

        float length = Dot(box.axis[i], direction);

        float mult = (length < 0.0f) ? -1.0f : 1.0f;

        length = min(abs(length), box.halfSize[i]);

        closestPointToSphere += box.axis[i] * length * mult;
    }

    float distance = Distance(collider->GlobalPos(), closestPointToSphere);

    return distance <= collider->Radius();
}

bool BoxCollider::IsBoxCollision(class BoxCollider* collider)
{
    // �ڽ������� �浹

    ObbDesc box1, box2;
    GetObb(box1);
    collider->GetObb(box2);

    Vector3 D = box2.pos - box1.pos;

    for (UINT i = 0; i < 3; i++)
    {
        if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
        if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
    }

    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            if (box1.axis[i] == box2.axis[j]) return true;
        }
    }

    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            Vector3 cross = Cross(box1.axis[i], box2.axis[j]);
            if (IsSeperateAxis(D, cross, box1, box2)) return false;
        }
    }

    return true;
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, BoxCollider::ObbDesc box1, BoxCollider::ObbDesc box2)
{
    //���� �ڽ����� �ٸ� �����ΰ�?

    float distance = abs(Dot(D, axis));

    float a = 0.0f;
    float b = 0.0f;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 temp = box1.axis[i] * box1.halfSize[i];
        a += abs(Dot(temp, axis));
        temp = box2.axis[i] * box2.halfSize[i];
        b += abs(Dot(temp, axis));
    }

    return distance > a + b;
}

void BoxCollider::MakeMesh()
{
    //Draw �Ű����� ������ ���� �޽� ����� �ٸ���

    if (!isRenderAsLine) // �⺻ ���� (�ؽ�ó �ִ� ť��� ����) : �� ��� ���´� �Ʒ��ʿ�
    {
        // * ������ ������ 8���� �־ ������, UV ť�긦 �������� ������� �ߺ� ��ǥ ����

        Vector3 half = size * 0.5f;

        //�⺻(�Ű����� ����, ����Ʈ) ���� �޽� ����
        vector<Vertex>& vertices = mesh->GetVertices();

        //Front
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, -half.z);
        //Up                   
        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        //Left               
        vertices.emplace_back(+half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);
        //Right              
        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        //Back               
        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);
        //Down
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);

        vector<UINT>& indices = mesh->GetIndices();

        indices = {
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
    }
    else
    {
        Vector3 half = size * 0.5f;

        //�⺻(�Ű����� ����, ����Ʈ) ���� �޽� ����
        vector<Vertex>& vertices = mesh->GetVertices();

        // D3D11_PRIMITIVE_TOPOLOGY_LINELIST ������ ���

        // 1. ������ �����ϰ� 8���� ���� ����
        // 2. �ش� 8���� ��ǥ�� ����.....

        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, -half.z);
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);

        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);

        vector<UINT>& indices = mesh->GetIndices();

        // 3. "���� ����" -> "���� ��" ������ ���Ϳ� �߰��� ���鼭 �ε��� ���͸� ä���
        //    (A �𼭸� ���� -> A �𼭸� �� -> (A �𼭸� ���� ��ǥ�� ����) B �𼭸� ���� -> B �𼭸� ��....)
        //    (������ ���÷� ���, 0 -> 1 -> 1 -> 3 -> 3 -> 2 -> 2 -> 0 -> 0�̳� 4....)

        indices = {
            0, 1, 1, 3, 3, 2, 2, 0,
            4, 5, 5, 7, 7, 6, 6, 4,
            0, 4, 1, 5, 2, 6, 3, 7
        };

        int a = 10;
    }
}