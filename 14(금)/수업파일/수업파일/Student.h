#pragma once
#include "Human.h"

// �л��� ��Ÿ���� Ŭ����

// Ű�� ���� �Ű� ü�ߵ� ���� �Ű� ���

// "�л��� �ΰ��̴�"�� �ڵ�� ������ ���� ������? �� �����ϴ�! C++�̶��

// Ŭ������ ���

class Student : public Human // class Ŭ������ : public Ŭ������
	// ������ ���� public ��� private�� �͵� ������, ���������� public�� ���� ���δ�
	// ���� : ���⼭ private�� ����, �������� public�̾��� �� ���⼭ private�� �ȴ�
	// 		  �� ������ �ִ� ���� ��� �����͸�(�ڱ� �ǵ���) �ڱⰡ �� �θ��� �Ǵϱ�
{
	// ��ó�� ������ Student�� Human�� ��� �Ӽ��� �����ϴ� �Ļ� Ŭ����(breached)�� �ȴ�
	// �ڽ� Ŭ����(child), ��ӵ� Ŭ����(inherited), ���� Ŭ����(slave)�����ε� �Ҹ���

private:
	// �л��� ��Ÿ���� ����
	// ���� ���� �ʴ´�(�Ļ� Ŭ������ ���� Ŭ������ ��� �����͸� ���� ���´�)
	
	
	// �л� ������ ����(�ΰ����� ���� �л��̾�� ������ ����)
	int schoolCode; // �ڵ�� ��Ÿ�� �б���
	int grade; // �г�
	float averageScore; // �������

public:
	// �⺻ ������
	Student()
	{
		Human(); // �ΰ� �亻 ������ ���
		schoolCode = 0;
		grade = 0;
		averageScore = 0;
	}

	// ������
	Student(int _age, int _gender, float _height, float _weight, int _hobby, int _school, int _grade, float _score)
		: Human(_age, _gender, _height, _weight, _hobby)
	{
		// �л��� �α�ƴ�, ����(Ȥ�� ����)�ΰ��� ��������� �Ѵ�
		// Human(_age, _gender, _height, _weight, _hobby);

		schoolCode = _school;
		grade = _grade;
		averageScore = _score;
	}

	// �л� ��¿� �Լ�
	void PrintMe()
	{
		// �� �ڵ� ó�� �ۼ� �� ������ �� ������ : age�� private�̶� 
		std::cout << "�� ���̴� : " << age << ", �׸��� �� �г��� : " << grade << "�г� �Դϴ�" << std::endl;
		// this->GetAge() ��밡��, Human�� protected�� ����Ǹ� age ���� ����
		// �̰��� Ŭ���� �ܺ� ������, ����� ���� ū ����

		// �л��� �ΰ��̴ϱ� Human�� protected�� ����� ��,
		// Human�� ������� ��� �Լ����� ���⼭ ȣ�� ����

		this->ImOut();
		this->PrivateLife();
	}

	// private : �ڱ� Ŭ���� �ٱ��� ��� ������ �� �� ���� ������
	//			 �Ļ� Ŭ������ ���� ���ܰ� �ƴϴ�
	 
	// �׷��� �Ļ� Ŭ������ �����͸� ���� �ִ� ��ŭ�� ������ ������?

	// �׷��� �Ļ� Ŭ������ ���� Ŭ������ �����Ϳ� ������ �� �ֵ��� �ϴ�, 3���� ���� �����ڰ� �ִ�
	// -> Human.h�� ����
};