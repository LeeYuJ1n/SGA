#include <iostream>
#include <vector>
#include <string.h>
#include "UserCert.h"

using namespace std;

void UserCert::Start()
{
	// 첫 번째 인물 명단
	vector<string> firstList = 
	{
		"최복순",
		"이승길",
		"심상출",
		"고은우",
		"마순자",
		"박호칠",
	};

	// 두 번째 명단
	vector<string> secondList = 
	{
		"마순자",
		"김항우",
		"이승길",
		"고동백",
		"오우석",
		"강사흠",
	};

	// 일치하는 명단
	vector<string> matchedList;

	// 일치한 사람 수
	int matched = 0; // 0부터 시작

	// 두 배열을 각각 반복문 돌리기
	for (int i = 0; i < firstList.size(); ++i)
	{
		// 한 명마다 다른 쪽 배열을 다 돌리기 때문에 이중 반복문
		for (int j = 0; j < secondList.size(); ++j)
		{
			// 첫 명단의 i번째와 두 번째 명단의 j번째를 비교
			// *이중배열만 아니라 두 배열도 이런 식으로 비교 가능

			int match = firstList[i].compare(secondList[j]);

			if (match == 0) // ← compare가 "일치"값이 나오면 0이 된다는 점에 주의
			{
				matched++; // 일치 인원 수 +1
				matchedList.push_back(secondList[j]); // 명단에 이름 추가
			}
		}
	}

	// 여기까지 오면 일치하는 사람의 명단과 인원 수가 나올 것

	// 출력
	cout << "일치하는 인원 수 : " << matched << endl;
	cout << "명단 : ";

	for (int i = 0; i < matchedList.size(); ++i)
	{
		cout << matchedList[i] << ", ";
	}
}