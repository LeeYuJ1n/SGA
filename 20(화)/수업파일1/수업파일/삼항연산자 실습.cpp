#include <iostream>

int main()
{
	int inputGameNumber;   
	std::cout << "���ڸ� �Է����ּ���" << std::endl;
	std::cin >> inputGameNumber;

	switch (inputGameNumber)
	{
	case 1:
		std::cout << "�ν�Ʈ��ũ" << std::endl;
		break;

	case 2:
		std::cout << "������ġ" << std::endl;
		break;

	case 3:
		std::cout << "�߷ζ�Ʈ" << std::endl;
		break;

	case 4:
		std::cout << "Ŭ������" << std::endl;
		break;

	case 5:
		std::cout << "�ر� : ��Ÿ����" << std::endl;
		break;
		
	case 6:
		std::cout << "ī���¶���" << std::endl;
		break;

	case 7:
		std::cout << "����Ʈ 4 ���� 2" << std::endl;
		break;

	case 8:
		std::cout << "����������" << std::endl;
		break;

	case 9:
		std::cout << "�����ý��丮" << std::endl;
		break;
	}
}