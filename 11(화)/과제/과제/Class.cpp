#include <iostream>
#include <Windows.h>
#include "Class.h"

void Class::print()
{
    // ĳ����1 ����
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "ĳ���� �̸� : ��ȭ��" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "���̵� : " << id() << std::endl;
    std::cout << "ü�� : " << strength() << std::endl;
    std::cout << "���ݷ� : 1 ~ 10" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    // �˾ƺ��� �����ϱ� ���� �ٹٲ�
    std::cout << std::endl;

    // ĳ����2 ����
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "ĳ���� �̸� : ������" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    std::cout << "���̵� : " << id2() << std::endl;
    std::cout << "ü�� : " << strength2() << std::endl;
    std::cout << "���ݷ� : 1 ~ 10" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
}

void Class::pvpsystem()
{
    bool loop = true;

    srand(GetTickCount64());

    system("cls");

    std::cout << "pvp�� �����մϴ�" << std::endl;
    std::cout << std::endl;
    std::cout << "������ �ڵ����� ����˴ϴ�" << std::endl;

    while (loop)
    {
        chara.attack = rand() % 10 + 1;
        chara2.attack = rand() % 10 + 1;

        if (chara.strength > 0 && chara2.strength > 0)
        {
            Sleep(1000);
            system("cls");

            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "��ȭ��(����) �� ������(����)" << std::endl;
        
            // ������ ���
            chara2.strength -= chara.attack;

            std::cout << "��ȭ�� ü�� : " << chara.strength << std::endl;
            std::cout << "������ ü�� : " << chara2.strength << "(-" << chara.attack << ")" << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;

            Sleep(1000);

            std::cout << "---------------------------------------------------------------" << std::endl;
            std::cout << "������(����) �� ��ȭ��(����)" << std::endl;
            
            // ������ ���
            chara.strength -= chara2.attack;

            std::cout << "������ ü�� : " << chara2.strength << std::endl;
            std::cout << "��ȭ�� ü�� : " << chara.strength << "(-" << chara2.attack << ")" << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;
        }
        if(chara.strength <= 0)
        {
            std::cout << "��ȭ�� �й�" << std::endl;
            loop = false;
        }
        else if (chara2.strength <= 0)
        {
            std::cout << "������ �й�" << std::endl;
            loop = false;
        }
    }
}