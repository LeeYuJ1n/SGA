#include <iostream>
#include <vector>      // 1302번 문제는 벡터가 필요
#include <string.h>    // 문자열을 쓸 생각입니다
// + 알고리즘 스타일에 따라선 각 정보에 "해시 태그"가 필요할 수 있습니다
// 해시 태그 : 각 정보에 붙이는 부가 정보를 고유화한 것 (A = 1 등의 등식, 혹은 #안녕세상아)
// → C++이라면 해시 태그를 map으로 구현 가능하다 (map은 key가 중복되면 안 되니까!)
// #include <map> ← 충분히 가능한 선택지

using namespace std;

// 1302번 문제 : 목록에서 가장 빈도가 높은 요소 찾아내기 (최빈도 검색)

int main()
{
    // 문제 요약 : 
    // 1. 문자열 벡터를 입력 ( * 코딩테스트의 경우, 대부분 변수를 cin 등으로 입력을 받으라고도 한다)
    // 2. 가장 많이 중복된 문자열을 찾아내기
    // 2-1. 정복 빈도가 똑같은 문자열이 여러 개면 사전상 가장 먼저 오는 문자열 찾기

    // 변수로 벡터와 크기 필요 (몇 개짜리 목록인가)
    int length;                                 // 길이(벡터의 크기)
    vector<string> titles;                      // 제목들(문자열 벡터)

    // 곧바로 벡터를 정하도록 하겠습니다
    cin >> length;
    titles.resize(length);                   // 입력받은 길이를 벡터 크기에 곧바로 반영

    for (int i = 0; i < length; ++i)
    {
        cin >> titles[i];                   // ← i번째 제목도 입력을 받겠습니다
        // push_back, insertm emplace 등이 쓰여도 됩니다만...
        // 벡터에서 이렇게 추가를 하다 보면 사본이 여러 번 나올 수 있고 (insert는 100%)
        // 그렇게 사본이 나오면 그게 다~ 메모리 크기가 되고, 시간 지연이 됩니다
        // 일반 상황이면 문제거리가 아니지만, 코딩 테스트니까요 (제한 시간, 제한 메모리)
    }

    // 문자열 벡터는 다 받았으니, 이번에는 기록용 (최빈도 검색 결과 저장용)
    // 가장 많이 들어온 문자열
    string mostPick = titles[0];                   // 일단 제일 처음에 들어온 값을 임시 지정
    int mostCount = 1;                             // 임시 문자열의 현재 빈도 (아무리 적어도 1번은 들어왔으니까)

    // 빈도 검출 반복문
    for (int i = 0; i < length; ++i)
    {
        // 이 반복문 안에서, 모든 문자열 내용을 한 번씩 돌려보겠습니다
        int currentCount = 1;             // ← 자기 자신의 빈도 (최소 1번은 확보)

        // (옵션) 불필요한 계산을 뛰어넘을 수도 있다 (이 대목 자체가 살짝 불필요하지만)
        if (titles[i].compare(mostPick) == 0)
        {
            continue;     // 검사할 문자열이 이미 최빈도 문자열이면 검사 생략
        }

        for (int j = 0; j < length; ++j)
        {
            // 이 반복문에서 titles[i]를 나머지 모든 문자열 요소를 비교해봅니다

            // 자기 자신과는 비교할 필요 없음
            if (i == j) continue;

            // 문자열이 같으면 현재 자신의 빈도를 +1
            if (titles[i].compare(titles[j]) == 0)               // 비교 함수 결과가 0 : 동일
            {
                currentCount++;
            }
        }

        // 작은 반복문이 끝났을 때, titles[i]는 목록 내의 다른 모든 구성요소와 비교가 끝난 상태

        // 이 때, titles[i]가 기록을 갱신했으면 결과를 반영
        if (currentCount > mostCount)
        {
            mostPick = titles[i];
            mostCount = currentCount;
        }

        // + 기록이 똑같은데, 사전상으로 더 먼저 나온 단어라면?
        // 결과를 반영할 필요 있음 (2-1)
        else if (currentCount == mostCount &&         // 같은 기록
            titles[i].compare(mostPick) < 0)          // 비교 결과가 음수 : 이 단어가
        {
            mostPick = titles[i];
            mostCount = currentCount;           // 확인차 넣었지만, 필요는 없다
        }

        // * 다소 코딩테스트, 그리고 이론에 치우친 팁 : 코딩 테스트 상황이라면 주의 필요!
        // if와 else if는 엄연히 다릅니다
        // if : 다른 조건문과 별개로 동작
        // else if : 위에 있는 if가 틀렸다는 것을 전제

        // 앞뒤로 늘어진 두 if가 서로  겹치지 않는다면 실제로는 뒤의 if가 else if나 마찬가지
        // 이론상의 의미가 엄연히 뒤의 if가 앞의 if를 부정하지 않기 때문에
        // → "둘 중 무조건 한 가지 경우만"이라는 의도를 전하고 싶을 때는 (혹은 그런 조건이 문제의 문맥에 숨겨졌을 경우)
        // else if를 꼭 써줘야 합니다
    }

    // 반복문이 끝나고 나오면 문자열 비교가 끝나고 최빈도 결과도 나온 상황
    // 출력
    cout << mostPick;
}