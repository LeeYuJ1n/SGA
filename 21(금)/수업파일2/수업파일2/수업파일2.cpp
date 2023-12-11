#include <iostream>
#include <vector> // 벡터, C++에서 가장 흔한 동적 배열

using namespace std;


int main()
{
    // std::string의 특징과 원리
    // 1. 바뀔 수 있는 문자열, 내용도 길이도, 특히 길이!
    // 2. 경우에 따라서 전체 내용도(어쩌면 메모리 구성도) 바꿀 만한 아주 쎈 함수들

    // 위 문자열 클래스를 배열에 대입해서 생각해보면?
    // : 따지고 보면 문자열이 바로 배열의 한 종류

    // 배열도 내부에서 지원만 잘 되면 내용도 길이도 바뀔 수 있어야 하지 않을까

    // → 그래서 등장한 C, C++의 배열 지원 기능(정확히는 이쪽이 먼저 string보다)

    // : 이 배열 지원 기능, 다시 말해 마음대로 바꿀 수 있는 배열을 "동적 배열"이라고 한다

    // ----------------------------------------

    // 오늘의 동적 배열 : 벡터

    // 벡터(vector) : 배열인데 크기가 개발자 마음대로인 것
    //                → 기본적으로는 배열과 형태가 거의 같다. 중간 취급만 다를 뿐
    //                → 가장 널리 쓰이고, 가장 단순하고, 가장 속 편한데
    //                → 동시에 가장 내부가 복잡하고, 가장 귀찮은 동적 배열

    // -----------------------------------------

    // 벡터를 쓰는 방법 : 벡터 선언
    vector<int> vec; // using namespace로 std 생략 가능
    // vector 다음의 <int> : "어떤 자료형의"배열인지를 지정하는 것
    // int arr[10]하고 비슷한 의미

    // 벡터에 숫자 추가하기
    vec.push_back(1); // push_back : 배열의 마지막에 추가 구성요소를 더하는 함수
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    // 출력
    cout << vec[0] << endl; // 배열하고 형태가 같으니 [] 사용 가능
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    cout << vec[3] << endl;
    cout << vec[4] << endl;

    // 마지막 구성요소를 삭제
    vec.pop_back();
    vec.pop_back();

    // 출력
    cout << vec[0] << endl; // 배열하고 형태가 같으니 [] 사용 가능
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    // cout << vec[3] << endl; ← 지워져서 출력 불가능
    // cout << vec[4] << endl; ← 지워져서 출력 불가능

    // 출력
    cout << "숫자 : " << vec[0] << endl; // 배열하고 형태가 같으니 [] 사용 가능
    cout << "숫자 : " << vec[1] << endl;
    cout << "숫자 : " << vec[2] << endl;

    // begin : 벡터의 시작 데이터를 컴퓨터에게 전달하는 함수
    vec.begin(); // 호출할 수 있는데, 호출만 해서는 쓸 데가 없고
    // cout << vec.begin << endl; ← 출력 불가능
    // 출력이 안 되는 이유 : 벡터는 데이터가 숫자 하나 같은 식으로 단순하게 있는 식이 아니다
    // 숫자를 출력하기도, 숫자가 있는 메모리 주소를 그대로 주기도 애매

    // begin을 제대로 쓰는 방법 : 오늘 말도 다음주에 보여드리도록 하겠습니다
    vec.end(); // "벡터 데이터의 마지막"을 컴퓨터에게 전달하는 함수
    // begin과 한 쌍

    // begin, end 대신에 쓸 수 있는 다른 접근 방법

    // at : 벡터의 특정 순번을 호출하는 함수. []와 기본적으로 같다
    // 차이점은 포인터인 []와 달리, at 함수는 "이 메모리가 정말 벡터의 일부인가?"를 염격히 검사한다
    cout << vec.at(0) << endl;
    cout << vec.at(1) << endl;
    cout << vec.at(2) << endl;
    // cout << vec.at(3) << endl;
    // cout << vec.at(4) << endl;

    // 똑같은 벡터의 "실제로는 없는 구성요소"를 참조할래도
    // []를 쓰면 : 일단은 그 메모리에서 값을 찾아보려고 용을 쓴다
    //             → 그 결과, 아무튼 실행은 되거나(대신 의도치 않은 값이 나온다)
    //             → 일정 시간 동안 애를 쓰다가 다운되거니
    //             → (운 나쁜 옛날 컴퓨터는) 그 시간을 못 견뎌서 컴퓨터가 다운되거나

    // 반면 at을 쓰면 : 오류 메시지가 뜬 후, 사용자가 대답을 뭐라고 하든 말든
    //                 "유효하지 않다"는 결과에 따라 즉시 앱을 꺼버린다
    //                 사용자 입장에서는 오류 날 상황에서 빨리 꺼지니 좋고
    //                 컴퓨터 입장에서는 안전
    //                 ...대신 []보다는 느리다(유효성 검사를 꼭 하니까)

    // ------------------------------------------

    // 벡터가 자유롭게 값을 넣었다 뺐다 할 수 있다면
    // 중간에도 값을 넣을 수 있어야 한다

    // 벡터에 구성요소 삽입하기

    // insert : 벡터의 중간에 값 삽입하기
    // vec.insert(1, 100); ← 오류
    vec.insert(vec.begin() + 1, 100); // 1순번(2번째 위치)에 100을 추가
    // 벡터의 insert는 string처럼 순번 번호를 바로 쓸 수는 없다
    // 대신 벡터의 데이터 정보를 기준으로 순번 위치를 다시 지정해줘야 한다
    // = 위에서 살펴본 vec.begin을 여기서 사용
    // 순번 번호인 1대신 "vec.begin() + 1"을 삽입 위치 자리에 넣어줘야 한다

    // 출력
    cout << vec[0] << endl;
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    cout << vec[3] << endl;

    // 한번 더 써보기 : 3번 순번에 (4번째에) 300 추가하기
    vec.insert(vec.begin() + 3, 300);

    // 출력
    cout << vec[0] << endl;
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    cout << vec[3] << endl;
    cout << vec[4] << endl;
    
    // insert와 같은 역할을 하는 다른 함수
    vec.emplace(vec.begin() + 3, 78654);

    // 출력
    cout << vec[0] << endl;
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    cout << vec[3] << endl;
    cout << vec[4] << endl;
    cout << vec[5] << endl;

    // erase : 벡터 중간의 한 구성요소를 지우는 함수
    // insert, emplace와 마찬가지로 vec.begin()을 기준으로 삼아야 한다
    // +0은 [0], +3은 [3]이라는 뜻
    vec.erase(vec.begin() + 1); // 제 1순번(2번째) 구성요소 삭제

    // 출력
    cout << vec[0] << endl;
    cout << vec[1] << endl;
    cout << vec[2] << endl;
    cout << vec[3] << endl;
    cout << vec[4] << endl;

    vec.insert(vec.begin(), 999);
    vec.insert(vec.begin(), 888);
    vec.insert(vec.begin(), 777);

    cout << endl;

    // size : 벡터의 길이를 숫자로 나타내는 함수
    cout << vec.size() << endl;

    cout << endl;

    // 벡터도 배열이라고 했는데, 반복문이 적용되는가? 적용된다!
    // + 더불어서 벡터의 크기를 for문에 넣어서 벡터 크기에 유연하게 대응하게 만들 수 있다
    for (int i = 0; i < vec.size(); ++i) // i가 있는 for문이 돌아갈 횟수는 벡터의 크기만큼
    {
        cout << vec[i] << "\t";
    }
    cout << endl;

    vec.clear(); // ← 벡터 다 지우기

    // 다시 반복문을 돌려도...
    for (int i = 0; i < vec.size(); ++i) // i가 있는 for문이 돌아갈 횟수는 벡터의 크기만큼
    {
        cout << vec[i] << "\t";
    }
    cout << endl;
}