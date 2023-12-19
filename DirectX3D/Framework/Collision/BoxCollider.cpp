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
// * 12.19 : VS �ּ� ����ó�� ������ ���� �Ʒ� �Լ����� �ۼ��ߴ�
//           �ּ��� ��� �����մϴ� (15�� �����ڷ�)

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

        if (NearlyEqual(f, 0.0f))
        {
            if (min[i] > e || max[i] < e) return false;
            // "e"��� ���ڰ� ������ �Ǹ� �� �ȴ�
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

    // �浹 ������ ������ ����� �ʱ�ȭ (�ڱ�� box1, �ε�ģ �ʵ� box2)
    ObbDesc box1, box2;
    GetObb(box1);
    collider->GetObb(box2);

    // �� D ��� : ���⼭�� �� ť�� �浹ü ������ �������迡�� ��ٷ� ���
    Vector3 D = box2.pos - box1.pos;

    for (UINT i = 0; i < 3; i++)
    {
        // �ೢ�� �м��� ��߳�(���۷��̼�)�� �ִ°�? �� ����ϰ�,
        // * ( �ش� �Լ��� ��� ) ���Ҿ �� ť�� ���̿� �Ÿ��� ����ġ�� ������ �ִ°��� ���
        // �ش� ����� x, y, z ������ �����Ƽ� �Ѵ� ( Vector3�� [] ������ ���� )
        // * ȣ���ؼ� ���͸� ������� ��� ( DX, UE, Unity ) -> �׳� ���ٿ����ڳ� ��� �����ڸ� �ᵵ ����
        // -> ���ǹ��� ���̶��, �൵ ������ �ְų� �Ÿ��� �ִ� ( Ȥ�� �� �ٴ� )
        if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
        if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
    }
    // �� ����� �� ť�꿡�� ȸ�� ������ �ؽ����� �ʾҴٴ� ���� �Ͽ�
    // X�ೢ��, Y�� ����, Z�ೢ�� ���ϴ� ��
    
    // ������ ť��� ������ �ٸ��� ���� ���� ( ���̳� �麸�ٴ� ) ���� ( = 3���� )

    // �׷��Ƿ� �ؿ� 3x3���� ���� ��� �ٽ� �� ����
    // -> �׷��� x, y, z���� ���ϸ� ����� Ȯ���� ��쵵 ���� ���� ���� ���ǹ����� ����
    // �������� �ݺ������� ����

    // ���� ���� = ��ġ, ���� ���� ��� ���̵� �ٸ� ť��� ������ ���� ���� �ִ�
    //          = �ش� ������ ������ ��ģ�� = ���� ��ġ ( Ȥ�� ���� ��ġ�� ���� ������ �ֺ� )
    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            if (box1.axis[i] == box2.axis[j]) return true;
        }
    }

    // ����� ���� �Ǹ� �ϴ� ���� �� ���� = ��ġ, ������ �ٸ��ٴ� ��
    // �׷��Ƿ� ���� ��� ���� ��� ��� �ٽ� ��߳����� ( �׸��� �Ÿ��� ���� ) ��� ���
    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            // �� ���� ������ ũ�ν��� ( ��������, ������ ���Ͱ� ���� ã�� ) 
            Vector3 cross = Cross(box1.axis[i], box2.axis[j]);

            // ������ ��D ( ��ġ���� ) ���� �ٽ� ��߳� �ִ��� �� ���
            // Ȥ�� "��D�� ���Ͱ��� ������� ������ ���� �� �ִ°�?"
            // ��� ����� �� = �� ���� ��߳� �� = ���� �� ���� = �浹 �ƴ�
            if (IsSeperateAxis(D, cross, box1, box2)) return false;
        }
    }

    // ������� ���� �� �� �ִ� ���
    // �� ť��� x, y, z���� ������ ������ ������ ������,
    // �� ������ ������ ��߳� ���� ���� 
    // = �ణ �߶Ѹ��� �� ���Ƶ�, ���������� ( ������ ���������� ) ħ���� �Ѵ�
    // = �浹 ����
    return true;
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, BoxCollider::ObbDesc box1, BoxCollider::ObbDesc box2)
{
    //���� �ڽ����� �ٸ� �����ΰ�?

    // �� ť���� ��ġ����� ���� ������ �޾Ƽ� ���� ��, ���밪 ����

    float distance = abs(Dot(D, axis));

    // �Լ��� ����� a, b��� �Ҽ��� �ʱ�ȭ

    float a = 0.0f;
    float b = 0.0f;

    for (UINT i = 0; i < 3; i++)
    {
        // a�� ��� �� �浹�� ���� ��, �ڽ�1�� ����� ������ �������� ����
        // b�� ��� �� �浹�� ���� ��, �ڽ�2�� ����� ������ �������� ����

        // �׷��� �ؼ�, �ڽ�1�� 2�� ( ���� �Ҹ��� ) �浹��� 
        // �Ű������� ���� ������ (�� �ڽ��� �ೢ�� ������ �� ��)
        // ���ʷ� ��� �ȴ�

        Vector3 temp = box1.axis[i] * box1.halfSize[i];
        a += abs(Dot(temp, axis));
        temp = box2.axis[i] * box2.halfSize[i];
        b += abs(Dot(temp, axis));
    }

    // ���� �浹�� �Ͼ ������ �� ���ڷκ����� ���� ( ���� = ������ ��ü�� ��ġ ) ������
    // ���� �� �Ÿ��� ��� ���� ����� �Ϲ� ���� ( ��Į�� ) �� ���� ��

    // �ش� ������� ���ڳ����� �Ÿ��� �� �� �ִٸ�
    // �൵ �������� �ش� �����κ��� ���� ������ ���� "�����" �������� �̵��� ���� ������ ���Ѵ�
    // = �浹 �� ���ٴ� �� ( �Լ��� True, �ֳĸ� "������ ����"�� ���� ���� )

    return distance > a + b;

    // * ����������, �׷��� ���Ͱ� �浹 ��꿡 ���̱� �����ϸ�
    //   �ᱹ ��� ����� �⺻������ �Ÿ��� ������ ������ �ٲ�ϴ�
    //   �̹��ϰ� ������ ����ϴ� �Ͱ� ��� �����մϴ�
    //   �׷��� ��¼�� ������ �� ���� ���� �ִ�
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

        // int a = 10; // �ε��� �˻�� �ߴ��� Ȱ��ȭ�� ���ؼ� ���� �����ڵ�
    }
}