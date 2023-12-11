#include "Character.h"

//�Լ� ����

void Character::Init(int _id, float _hp, int _atk)
{
	id = _id;
	hitPoint = _hp;
	attack = _atk;
	dead = false; // ���� ���������� �׾��� ���� ������, �Ű����� �ʿ� ���� �׳� ���� false��
}

void Character::Attack(Character* target, float attackMullt)
{
	//������, �ǰ��� ���� Ȯ��

	int _attacker = this->id;
	int _target = target->id;

	// �� �ڵ忡�� ���� this : �� �ν��Ͻ����� �ڱ� �ڽ��� ����Ű�� ������
	// ���� �� �Լ��� this : �����ϴ� ���� id�� ����Ų��

	//���� ǥ�� (�ؽ�Ʈ��)

	std::cout << _attacker << "�� �ι��� " << _target << "�� �ι����� " << this->attack * attackMullt << "�� �������� Ÿ��!" << std::endl;

	// ���� ���
	target->ApplyDamage(this->attack * attackMullt);
	// ������ �޴� �ʵ� �ϴ��� ���� Ŭ������ �����ϴ� �ٸ� �ν��Ͻ�.
	// �׷��Ƿ� main������ ������ �Լ� ������ �� �� ������, Ŭ������� ���� ���赵 �ȿ�����
	// �������� private ���� �Լ��� �����Ӱ� �� �� �ֽ��ϴ�!!

	//�� �ٲٰ� ���

	std::cout << std::endl;

	std::cout << "���� ��ǥ�� ����" << std::endl;
	target->PrintMe();

	std::cout << "���� ������ ���� ����" << std::endl;
	this->PrintMe();
}

void Character::ApplyDamage(float amount)
{
	this->hitPoint -= amount;

	//this �� ������ �Լ�(�� ����)�� ȣ���ϴ� ��ü
	//���� �� �Լ����� ���� this�� �� Attack���� ������ �޾Ҵ�, ǥ���� ���Ѵ� (ǥ��"�� �ڱ⿡��" ���ظ� ����)

	if (this->hitPoint <= 0)
	{
		this->dead = true; //ü���� 0 ���̸� ��

		this->WhenDead();
	}
}

void Character::PrintMe()
{
	std::cout << "< " << id << " �� �ι��� ���� �ɷ�ġ >" << std::endl;
	std::cout << std::endl;

	std::cout << id << "�� �ι��� ������ : " << hitPoint << std::endl;
	std::cout << id << "�� �ι��� ���� ���ݷ� : " << attack << std::endl;
	std::cout << std::endl;

	// ��� �̴ϼȶ����� ���� ������� ���� ���� �ڷ�
	if (id2 != 0)
	{
		std::cout << "< " << id << " �� �ι��� ���� �ɷ�ġ >" << std::endl;
		std::cout << std::endl;

		std::cout << id << "�� �ι��� �����1 : " << id2 << std::endl;
		std::cout << id << "�� �ι��� �����2 : " << f2 << std::endl;
		std::cout << std::endl;
	}
}


void Character::WhenDead()
{
	std::cout << id << "�� �ι��� ���������ϴ�." << std::endl;
	std::cout << std::endl;

	//this�� ���������� ���� ����. (id��, this->id�� �Ȱ���)
	//���� �� �Լ��� �ҷ����� �ʹ��� ������ϸ� this�� �׳� �� �ᵵ �ƹ� ������ ����
}