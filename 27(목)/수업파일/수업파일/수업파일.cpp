#include <iostream>

using namespace std;

// 페어(pair)와 맵(map)

// 일반적인 데이터 명명법(a는 10이다) : 컴퓨터에게 a라고 말하면, 10이라는 숫자가 돌아오는 방식
//                                    컴파일러에게 일방적으로 데이터를 전달, 지정

// 일반적인 데이터 명명법 대신, 데이터에게 이름과 실제를 각각 따로 주기로 한다
// → 데이터의 이름, 데이터의 실제
//   그리고 두 "이름과 실제"를 묶어서 한 번 더 만든 컴퓨터용 이름

// 이런 식으로 만든 데이터를 데이터쌍이라고 한다 (data pair)
// 그리고 데이터 페어를 C++에서 다루기 위해서 만든 두 기능이 pair와 map

// 페어와 맵을 사용하기 위해서는 (다른 기능과 마찬가지로) 그에 맞는 기능을 include
#include <utility>          // ← pair를 사용하기 위한 include
#include <map>              // ← 이건 map
#include <vector>           // ← 벡터 로딩도 미리
#include <string.h>         // ← string 로딩

int main()
{
    // pair
    // pair의 선언 도식 : pair<type1('key'), type2('value')> dataName;
    // * type1의 다른 이름은 key : 식별 자료
    // * type2의 다른 이름은 value : 실체 자료
    // → pair를 말로 풀어서 표현하면 "Key는 Value다"라는 의미

    pair<int, int> pr;          // pr이라는 이름의 데이터쌍, 두 정수를 받는다
    pair<char*, int> human;     // human이라는 이름의 데이터쌍은 문자열과 정수를 받는다

    // 선언된 pair에 값을 넣는 방법

    pr.first = 1;          // ← 페어의 첫 번째 데이터에(key에) 1이라는 숫자를 넣었다
    pr.second = 2;         // ← 두 번째 데이터에(value에) 2라는 숫자를 넣었다

    // 이제 pr이라는 데이터의 쌍은 "1은 2다"라는 의미를 가지게 되었다
    // (물론 비현실적인 이야기지만, 아무튼 컴퓨터에게는 그렇게 전달했다)

    char name[9] = "사람이름";
    human.first = name;
    human.second = 40;

    // 위 코드로 human이라는 데이터 그룹에서 "사람이름이라는 이름의 인간은 40이다"
    // ...라는 의미를 컴퓨터에게 전달했다
    
    // 그러면 컴퓨터는 (늘 하던 대로 ) 전달받은 데이터를 처리를 해준다
    // → 중요한 건 개발자

    // 만약 개발자가 저 위의 데이터 쌍에 각각 미리 의미를 부여했다고 생각해보자
    // 예를 들어서 human의 first가 정말로 사람 이름을 뜻하는 데이터라면?
    // 그리고 human의 second가 사람의 나이를 뜻하는 데이터라면?
    
    // 그러면 human이라는 페어에서 개발자는 사람 이름으로 나이를 도출할 수 있다
    // → 이런 이유로 pair를 사용

    // 사실 pair도 구조체인데, 사용자가 만든 구조체와 뭐가 다른가?
    // 1. 기본으로 주어져 있다 (누구나 쓸 수 있다)
    // 2. 형태가 정해져 있다 (어떤 코드에든 갖다붙일 수 있다)
    // 3. 대신 변수의 개수는 항상 2개

    // → 데이터를 단순하게 도식화하고 싶을 때, pair를 유용하게 쓸 수 있다

    // --------------------------------------------------------------------------------

    // 한편 pair에는 위에 적은 1, 2, 3 장단점 외에 추가로 한 가지 한계점이 있다
    // → 변수 하나가 한 번에 하나의 실체밖에 표현하지 못한다
    //   (이를테면 숫자 value 한 개, 혹은 "사람 한 명")

    // 그래서 pair를 보통 사용할 때는 배열과 같이 쓰는 경우가 많다

    pair<int, char*> studentList[10];          // ← 학생이 10명 있는 반의 학생부
                                               // 1번 학생 아무개, 2번 학생 김이박 등

    // 더불어서 이 배열이 동적으로 제어되어야 할 경우에는 동적 배열도 사용

    vector<pair<char*, char*>> privateDic;          // 개인 사전
    vector<pair<float, float>> privatePasscode;     // 개인용 암호표

    // 학생부를 직접 채워보기
    // (한 명 한 명이 달라야 하니까 아쉽게도 반복문을 100% 쓰기는 힘들지도)

    // 숫자만 반복문

    for (int i = 0; i < 10; ++i)
    {
        studentList[i].first = i + 1;          // 학생 10명에게 일괄 학생 번호 부여
    }
    char name0[9] = "학생1";
    char name1[9] = "학생2";
    char name2[9] = "학생3";
    char name3[9] = "학생4";
    char name4[9] = "학생5";
    char name5[9] = "학생6";
    char name6[9] = "학생7";
    char name7[9] = "학생8";
    char name8[9] = "학생9";
    char name9[9] = "학생10";
    studentList[0].second = name0;
    studentList[1].second = name1;
    studentList[2].second = name2;
    studentList[3].second = name3;
    studentList[4].second = name4;
    studentList[5].second = name5;
    studentList[6].second = name6;
    studentList[7].second = name7;
    studentList[8].second = name8;
    studentList[9].second = name9;          // 길어졌지만, 학생에게 이름을 부여

    // 학생들의 이름을 일괄 출력

    for (int i = 0; i < 10; ++i)
    {
        cout << "학생 번호 : " << studentList[i].first << ", ";
        cout << "이름 : " << studentList[i].second << endl;
    }

    // pair의 (잘 쓰이지는 않는) 편리한 응용법
    // : pair도 구조체 → pair에도 생성자가 있다

    pair<int, int> testPair(2, 3);                                         // ← 선언과 동시에 값을 부여할 수도 있다
    pair<int, int>* testPair2 = new pair<int, int>(3, 10);                 // ← 동적할당 가능

    // 다만 구조체이고, 또 배열로 자주 쓰다 보니 생성자까지 동원하는 경우가 흔치 않다
    // (배열로 만든다 = 만들 때 이미 선언 끝났다, 구조체 = 포인터 인스턴스를 자주 쓰진 않는다)

    // -----------------------------------------------------------------------------------------------

    // 데이터 쌍을 다루는 C++의 또 다른 기능

    // map (대응하기) : 간단하게 말하면, pair의 강화판
    // map의 정의 : 복수의 key와 그에 대응하는 value로 이루어진 데이터쌍의 트리
    //              (동적배열과 비슷한 자료의 집합)
    //              (쉽게 말하면, pair를 vector처럼 쓸 수 있게 만든 것)

    // 맵 선언

    map<int, int> mapList;                   // 맵핑의 목록
    
    // 맵에 값을 실제로 주기

    // 실제로 맵에 값을 주는 방법 : insert (vector의 그것)

    mapList.insert({ 1, 2 });                // 1 : key, 2 : value
    mapList.insert({ 3, 4 });                // 3 : key, 4 : value
    mapList.insert({ 5, 6 });                // 5 : key, 6 : value
    mapList.insert({ 7, 8 });                // 7 : key, 8 : value
    mapList.insert({ 9, 10 });               // 9 : key, 10 : value
    mapList.insert({ 6, 11 });               // ← Vector였으면 이 요소는 9, 10 다음에 와야 한다
                                             // 그러나 맵에서 이 요소의 위치는 key의 값에 따라 컴퓨터가 다시 판단한다

    mapList.insert({ 1, 222 });              // ← 이 요소의 위치는? 지구에는 없다
                                             // map에 key가 1인 요소가 이미 있기 때문에, insert 코드가 무시된 것

    mapList.insert({ 10, 10 });              // 9, 10과 value가 중복, key는 중복 아님

    // 맵 출력하기 : 반복자를 사용해서 한다 (List와 Vector의 그것)

    for (map<int, int>::iterator it = mapList.begin();
        it != mapList.end();
        ++it)
    {
        cout << "키 : " << it->first << ", ";
        cout << "자료 값 : " << it->second << endl;
    }

    // 여기서 map이 Vector와 다른 문법 사용 방법이 있다
    // 1. insert에 위치를 지정하지 않아도 된다 (원칙적으로 가능은 한데 무의미)
    //    왜 map에서 위치가 무의미한가? → map에서는 각 pair를 자동 정렬을 해줘서
    // 2. insert 사용시 주의점, key를 중복시키면 안 된다
    //    다른 동적 배열과 다르게, map은 각 원소가 (정확히는 각 key) 중복이 있으면 안 된다
    //    왜냐면 A는 B다, 는 의미의 쌍을 목록한 것이기 때문에 (A는 B고 A는 C다? 오류!)
    //    value는 중복되어도 되는가? value는 괜찮다

    // -----------------------------------------------------------------

    // map의 다른 기능 : find (현 단계에선 map에만 있는 것)
    // : map의 각 원소 중에서 주어진 매개변수가 key가 같은 쌍을 (원소를) 찾아주는 기능
    // : 이를테면 학생부에서 학생 번호로 이름을 찾거나, 인명부에서 이름으로 나이를 찾거나
    //   할 때 유리!

    cout << mapList.find(3)->first << endl;            // first : key
    cout << mapList.find(3)->second << endl;           // second : value

    // * find를 잘 쓸 수 있으면 map의 중요한 용도는 거의모두 사용할 수 있다

    // -----------------------------------------------------------------

    // map에서 구성요소를 삭제

    // mapList.erase(mapList.begin() + 3); ← 안 먹힌다 (인덱스가 없어서)
    // map은 Vector는 아니라는 것을 확인

    map<int, int>::iterator iter = mapList.begin();
    iter++;
    iter++;
    iter++;                          // 순번 3 (즉 4번째)

    mapList.erase(iter);             // 반복자로는 지울 수 있다

    for (map<int, int>::iterator it = mapList.begin();
        it != mapList.end();
        ++it)
    {
        cout << "키 : " << it->first << ", ";
        cout << "자료 값 : " << it->second << endl;
    }

    // ** erase를 key로 쓸 수도 있다

    // ** 짜투리 : swap 함수 = 집합 내 구성요소를 서로 바꾸는 기능을 하긴 합니다
    //             다만 어차피 잘 안 씁니다
    //             다만 코딩 테스트 등에서 코드 길이 줄이려고 쓰는 경우가 간혹 있습니다
    //             관심 있는 분들은 한번 개인적으로 검색을 해보시길 바랍니다
  
    // -----------------------------------------------------------------

    // 실습, 직접 해봅시다 : map으로 인명장부 작성하기

    // key는 (가상의) 인명, value : (가상의) 전화번호
    // key로 find하면 전화번호를 알 수 있도록...

    cout << endl;
    cout << "실습 : map으로 인명장부 작성하기" << endl;

    map<string, string> testList;                    // 맵핑의 목록

    testList.insert({ "도화가", "010-0000-0000" });               // key : 도화가, value : 010-0000-0000
    testList.insert({ "기상술사", "010-1111-1111"});              // key : 기상술사, value : 010-1111-1111
    testList.insert({ "캐릭터1", "010-2222-2222" });              // key : 캐릭터1, value : 010-2222-2222
    testList.insert({ "캐릭터2", "010-3333-3333" });              // key : 캐릭터2, value : 010-3333-3333

    string nameToFind;

    // find 후에 전화번호 알기
    
    cout << "찾으려는 사람 이름 : ";
    cin >> nameToFind;

    cout << endl;
    cout << "이름 : " << testList.find(nameToFind)->first << endl;
    cout << "전화번호 : " << testList.find(nameToFind)->second << endl;
    cout << endl;

    // -----------------------------------------------------------------

    // 맵을 좀 더 폭 넓게 쓸수 있는 방법
    // key혹은 value쪽을 구성하는 데이터 역시 복수로 구성하는 것

    // 사례

    map<int, pair<int, int>> IDnAxis;

    // key는 정수 한 개, value가 정수 두 개로 이루어진 쌍
    // key가 사람의 id를 나타내고, value가 각각 x축과 y축을 이룬다고 가정할 경우
    
    // 위 map의 의미는 "각 사람이 자리한 위치"를 나타내게 된다

    IDnAxis.insert({ 0, { 0, 0 } });                      // 0번 사람은 원점
    IDnAxis.insert({ 1, { 2, 3 } });                      // 1번 사람은 x2 y3 위치에
    IDnAxis.insert({ 2, { -5, 10 } });                    // 2번 사람은 x-5 y10 위치에 있다는 뜻이 될 것
                                                          // → 여러 사람의 위치관계를 한 번에 나타내고자 할 때 위와 같은 map은 유용

    // 반대로
    
    map<pair<int, int>, int> worldMap;

    // x, y로 이루어진 데이터의 pair가 key를 담당하고, value가 다른 단일 변수라면
    // → "이 위치에는 어떤 의미가 있느냐?"를 나타내는 데이터가 되고,
    //   보물지도, 세계지도... 등을 나타내기에 좋은 코드가 된다

    // 그리고... key도 value도 모두 페어!

    map<pair<int, int>, pair<int, int>> portalMap;          // * 오류 : 위에 worldMap가 동일한 변수명일 때 발생 → 변수명 교체후 해결

    // key도 xy위치, value도 마찬가지로 할 때...
    //위 map은 두 지점의 연관성 (두 지점이 연결됨)을 뜻하는 자료가 될 수 있을 것

    // → 만지면 순간이동하는 포탈 등을 만들 때 유용 (오버워치의 시메트라 포털처럼)

    // 위 처럼 map에 단일 데이터만 쓰는 것이 아니라, 다른 구조체(pair등) 혹은 Class...
    // ...와 조합해서 더 많은 의미를, 컴퓨터만이 아니라 인간이 검색할 수 있는 형태로 만든다

    // → map의 강점이자, 용도, 존재의의

    // ---------------------------------------------------------------------------

    // 위처럼 map이 점점 복잡해질 때, key도 점점 복잡해지는 경향이 있다
    // 이럴 때 map을 반복자로 지우는 게 더 편할 때도 있고, 더 불편할 때도 있다

    // 그럴 때 erase를 key로 쓸 수도 있다

    testList.erase("기상술사");                                    // ← 이름을 써서 바로 원소 삭제 가능
    cout << testList.find("기상술사") -> second << endl;           // 출력가능? 불가능!
    
    // ---------------------------------------------------------------------------
}