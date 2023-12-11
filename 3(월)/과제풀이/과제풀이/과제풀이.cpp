#include <iostream>
#include <conio.h> // 키 입력을 받기 위한 기능

// 헤더는 없이 진행

// 변수 필요 : 전역 변수로 작성

// 나의 위치
int x; // 가로
int y; // 세로

// 필드(문자 숫자 하나씩 작성)
int filedNum[10][10];
char filedCha[10][10];

// 필드를 문자로 표시할 건지 숫자로 표시할 건지
bool showFiledNumber = false; // 기본값 : 문자로 표시

// 입력을 받거나 하는 부분은 입력할 때만 필요하니까, 전역변수일 필요가 없다

// ---------------------------------------

// 함수 작성(main 위니까 선언만)

// 배열 세팅
void SetArrays();

// 맵 표시
void PrintMap();

// 입력 받아서 컴퓨터에게 전달하기
int GetInput();

// 입력 값에 따라서 움직이기(입력 값은 그때그때 다르니까 매개변수로 그때그때 설정)
void ProcControl(int input);

// -----------------------------------------------

// 옵션 : 가능할까?

int test = 10;

void ChangeTest(int x)
{
    x = 10000;
}

// -----------------------------------------------

int main()
{
    // ---시작 전에 옵션 확인 한번만---
    
    ChangeTest(test); // 기대 결과 : test가 10000으로 변경
    std::cout << test << std::endl;

    // 실제 결과 : 아무 일도 안 일어난다(test에 변화 없음)
    // 뭔가 잘못된 기분이지만 C++에서는 이게 맞다

    // 일단은 이런 식으로 매개변수로 다른 변수를 수정할 수 없다는 데까지 알아둡시다

    // --------------------------------
    // 내 시작위치(0, 0) 정하기
    x = 0;
    y = 0;

    // 배열을 세팅
    SetArrays();

    while (true) // 무한 반복문
    {
        // 표시부터 하고
        PrintMap();

        int input = GetInput(); // 함수를 실행하고 결과를 변수에 저장
        ProcControl(input); // 결과를 사용해서 그때그때 다른 조작을 처리

        // * ProcControl(GetInput())로 작성해도 된다 : 함수 처리 결과 자체를 매개변수로 사용
        
        std::cout << input << std::endl; // 중간 테스트용 : asdw가 값이 뭐였는지 알기 위해(다 알고 나면 주석)
    }
    // 위 반복문으로 움직이고, 움직인 결과를 표시
}

// 여기서 각 함수를 시제로 정의
void SetArrays()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            filedNum[i][j] = 1; // 숫자의 경우, 모든 필드 표시를 0로
            filedCha[i][j] = ' - '; // 문자의 경우, 모든 필드 표시를 하이폰(빼기 기호)으로
        }
    }
}

void PrintMap()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (i != y || j != x) // i, j중 하나라도 내 위치와 다르면
            {
                // = 내 위치 빼고 전부 다
                if (showFiledNumber) std::cout << filedNum[i][j] << "\t";
                else std::cout << filedCha[i][j] << "\t";
            }
            else // i, j 모두 내 위치와 일치 = 여기가 내 위치
            {
                std::cout << "x" << "\t";
            }
        }
        std::cout << std::endl; // 가로 한 줄 끝나면 줄바꿈
    }
}

int GetInput()
{
    // 키 입력을 받아서 컴퓨터에게 전달
    int key = _getch();
    return key;
}


void ProcControl(int input)
{
    // 매개변수로 받은, input 값이 무엇이냐 따라 조작 처리

    switch (input)
    {
        // 먼저 모르는 상태에서 실행해보고, 문자코드를 알아가면서 보강
    case 97: // input이 97일 때 코드 = a를 눌렀을 떄 수행해야 할 일
        // asdw에서 a는 왼쪽, x축 값 -1
        // 단, x가 0일 때는 더 왼쪽으로 가면 안 보일 듯
        if(x > 0) x--; // x가 0보다 클 때만 -1
        break;

    case 115: // input이 115일 때 코드 = s를 눌렀을 때 = 아래쪽
        // y가 제일 아래쪽만 아니면 +1
        // y는 0일 때 0일 때 제일 위니까
        if (y < 9) y++; // y가 9(제일 아랫줄) 아니면 +1
        break;

    case 100: // d = 오른쪽y가 밑으로 가는 것과 원리는 같다
        if (x < 9) x++;
        break;

    case 119: // w = 위쪽. x가 왼쪽 가는 것과 거의 같다
        if (y > 0)y--;
        break;

    case 99: // c = asdw는 아닌데, 누르면 추가 입력을 처리하고 싶다
        showFiledNumber = !showFiledNumber;
        // 위 연산식 : bool 변수를, 지금 있는 값의 반대로 뒤집겠다
        // true는 false, false는 true로
        break;

    default :
        std::cout << input << std::endl; // 뭔지 모르는 키를 받으면, 그 키의 문자코드를 출력
        // 이 코드를 이용해서 asdw도 혹은 나중에라도 추가로 키를 알고 싶을 때 쓸 수 있겠다
        break;
    }
}