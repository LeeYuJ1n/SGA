#include <iostream>
#include "Josephus.h"
#include "UserCert.h"

using namespace std;

// 문제풀이 + 출력

// 문제풀이에 앞서서 배열 출력
void Josephus::PrintVector(vector<int> data)
{
	// 벡터 크기에 맞추어서 출력
	for (int i = 0; i < data.size(); ++i)
	{
		cout << data[i] << "\t"; // 한 숫자 나오면 탭 띄우기
	}
	cout << endl; // 다 끝나면 줄 바꾸기
}

// 진짜 문제 풀이
void Josephus::Start()
{
	// 입력부터 받기
	cout << "벡터의 크기를 입력해주세요 : ";
	cin >> sizeOfArray;

	cout << "순열 간격을 입력해주세요 : ";
	cin >> interval;

	// 첫 번째 벡터를 만들기
	for (int i = 0; i < sizeOfArray; ++i)
	{
		firstData.push_back(i + 1); // push_back 사용
		// 1부터 정해진 크기까지 숫자가 차례로 들어갈 것
	}

	// 맨 먼저 배열 출력
	cout << "현재 배열 : ";
	PrintVector(firstData);

	cout << "요세푸스 순열 : ";
	PrintVector(answer);

	cout << endl;

	// 이후부터 진짜 계산 시작
	// for (int i = 0; i < sizeOfArray; ++i) // 성립. 한 번 계산에  "첫 배열"에서 숫자 한 개가 반드시 지워지니까
	// {
	// 
	// }

	while (firstData.size() > 0) // 현재 배열에 숫자가 남는 한 무한히 도는 반복문
	{
		// 안내 및 계산 진행

		// 몇 번째 계산인가?
		cout << "<" << count << "번째 계산 >"  << endl;
		cout << endl;

		// int next가 필요한데 헤더에서 만들겠습니다

		// 여기서 next : 다음에 지울 순번
		next = next + interval - 1; // 순번이니까 1을 빼서 계산 (0부터 시작하니까)

		// next가 첫 벡터의 크기보다 커지면, "한 바퀴 돌아서 처음"으로 가야 한다
		// → 첫 벡터의 크기보다 큰 원래 값에서 벡터 크기만큼 빼버리면 된다
		while (next >= firstData.size())
		{
			// 크기 값과 순번이 같다 = 그 자체가 순번이 크기를 넘어갔다는 뜻
			next = next - firstData.size();
		}

		// 다음에 지워질 순번의 데이터를 먼저 답 벡터에 넣자
		// answer.push_back(firstData.at(next)); // 이 쪽이 좀 더 함수를 활용
		answer.push_back(firstData[next]);

		// 이어서 해당 위치를 첫 벡터에서 삭제
		firstData.erase(firstData.begin() + next);

		// * 지우고 → 답 기록이 아니라, 답 기록 후에 지워야 합니다
		// 안 그러면 답을 기록해야 되는데 데이터가 이미 지워져서 없습니다

		// 다 됐으니 출력
		cout << "현재 배열 : ";
		PrintVector(firstData);

		cout << "요세푸스 순열 : ";
		PrintVector(answer);

		// 횟수를 1 올리고 반복
		count++;
	}
}