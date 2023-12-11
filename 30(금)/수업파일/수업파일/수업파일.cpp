﻿#include <iostream>
#include <stdlib.h>
#include <Windows.h>

int main()
{
    // 배열
    // = (컴퓨터에서의 정의) 복수의 동일한 자료형을 메모리에 연속 할당한 것.....
    // = 자료형이 똑같고, 서로 연관성이 추축되는 여러 개의 변수 하나의 이름으로 싸잡는 것

    // 대표적인 사례 : "학생부를 학생 순번만 가지고 작성한다면?"

    // 실제 작성 사례(가장 단순한 형태)

    // 학생번호라는 이름을 공유하는 10개의 정수를 만들고, 첫 번째 순서부터 각각 1, 2, 3....10의 숫자를 부여
    int studentNumber[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // 배열의 값을 넣을 때는 {}뒤에 ; 기호를 붙인다 중요!!!

    // 배열의 구체적인 작성 방법 = 자료형에 이어 변수명을 적은 후(여기까지는 다른 변수와 동일)
    // 변수명 뒤에[]를 붙인다. [] 안에 들어가는 숫자가 배열의 크기, 즉 그룹의 구성요소(원소) 개수

    // 배열의 사용 방법 : 변수와 똑같이(배열도 변수니까)변수명을 적고, 그 뒤에 []를 붙인다

    // **작성하는 코드에서 변수명 뒤의 []는 배열의 크기
    
    // *** 호출하는 코드에서 변수명의 뒤의 [] 속 숫자 : 불러오려는 배열의 순번 *** 중요!!!

    // 직접 호출 사례
    studentNumber[0]; // 이렇게 호출(호출만 했고 아무 것도 안 해서 사용자는 확인 불가능)
    std::cout << studentNumber[1] << std::endl; // "1번 순번"을 호출해서 출력

    // 배열은 0번 순번이 첫 번째 순서 / 1번이 두 번째 순서... "배열 크기 -1이 마지막 순서"
    // 다른 말로 "배열 크기"를 순번으로 쓰면 배열의 범위를 벗어나서 의도치 않은 겨과가 생긴다

    std::cout << studentNumber[10] << std::endl; // 의도치 않은 결과 발생

    // 배열을 순번으로 호출할 수 있고 쓸 수 있으니 수정도 할 수 있음을 확인

    studentNumber[5] = 777; // 6번째 숫자, 즉 6을 777로 수정

    std::cout << studentNumber[5] << std::endl;

    // ------------------------------------------
    
    // 배열의 개념은 매우 간단 응용에 활용하는 것이 조금 귀찮을 뿐 그나마 익숙해지면 똑같이 간단

    // --------------------------------------------

    // 배열을 좀 더 응용하는 방법

    // 문자열 : 여러 개의 문자를 이어붙여서 하나의 단어로 구성한 것, 혹은 "문자로 만든 배열"

    // 문자열의 사용 예시

    char word[64] = "나랏말싸미 동귁에말아";
    // 문자열을 입력할 때는 문자를 큰따옴표로 표현(문자 하나는 작은따옴표)
    // 배열의 크기가 64인 문자열 : 최대 63바이트까지 입력 가능(64번쨰 글자는 입력 불가능) : C++의 경우
    // 이유 : 문자가 배열일 경우, 맨 마지막에 글자가 무조건 고정되기 때문("여기서 문자열이 끝났다"는 뜻의 특수문자)

    std::cout << word << std::endl; // 문자열은 다른 배열과는 호출 및 표현이 조금 문법이 다르다
    // 이 부분은 별 수 없이 암기, 혹은 그냥 체독하는 편이 빠르다

    // char word2[5] = "apple"; → 배열크기가 5인 문자열에는 5글자 입력 불가능

    // --------------------------------------------

    // 문자열의 추가 응용 및 주의점

    // 한 번 만들어진 문자열을 코딩에서 수정할 경우

    char word3[9] = "computer";

    // word3 = "bibimbap"; // 한 번 만들어진 문자열은 배열의 이름을 써서 수정 불가능(**문법적인 이유가 있는데... 다음 기회에 설명드리겠습니다**)

    word3[0] = 'p'; // 배열의 원소를 순번으로 호출해서 수정하는 건 된다(정수에서도 된다)

    std::cout << word3 << std::endl;

    // cin을 사용해서 word3에 수동으로 문자를 입력해보고 출력해보기
    std::cin >> word3;
    std::cout << word3 << std::endl;

    // 결과 : cin를 사용하면 word3에 수정된 결과 입력 가능(이유 : 비트 연산으로 그냥 자료를 떺어씌웠기 때문)

    // ----------------------------------------

    // 돌아거서, 정수(혹은 소수) 등 일반적인 자료를 다루는 배열의 응용법

    // 1. 배열은 크기가 있다(유한하다)
    // 2. 배열은 순번이 있다(원소마다 순서가 다르다)
    // 3. 배열의 순번은 정진적이다(다른 말로 순서가 다르게 올라간다, 혹은 "0부터 끝까지 차례대로 1씩 올라간다")

    // 위 배열의 문법적 특징을 활용해서 배열을 반복문에 활용 가능

    int testNumber[100]; // 원소 100개까지 배열을 만든 후, 선언만 하고 값 미리 안 주기

    // 배열의 일괄 처리(반복문으로 같은 작업을 한 번에 처리)

    for (int i = 0; i < 100; ++i) // 0부터, 배열 크기 직전까지, 배열 크기만큼 반복하는 for문
    {
        testNumber[i] = i + 1; // i번째(0~99순번) 배열 속 원소를 하나씩 불러내서 값을 수정
        std::cout << testNumber[i] << std::endl;
    }

    // 반복문에 숫자 계산 등을 적용하면 배열을 좀 더 다양하게 일괄 처리 가능
    int testNumber2[50];

    for (int i = 0; i < 50; ++i) // 반복문이 어떻게 돌아가는지를 정하는 것, 따라서 굳이 수정할 필요 없음(배열크기만 빼고)
    {
        testNumber2[i] = (2 * i) + 1; // 들어가는 수의 다른 산술 계산식을 적용해봅시다
        std::cout << testNumber2[i] << std::endl;
    }

    // 각자 생각나는 배열을 만들어보시고, 여러 산수 식 등을 원소에 일괄적으로 넣어봅시다

    // ---------------------------------------

    // 배열의 다른 응용법
    // = 무엇을 할 수 있고, 무엇을 할 수 없는가?(C++의 배열은 조금 제약이 심해서... 체독으로 익혀야 되는 것들도 있다)

    // 1. cin과 원소를 조합 가능
    int inputArray[3];
    std::cin >> inputArray[0]; // cin에서 배열의 각 원소를 호출 가능
    std::cin >> inputArray[1];
    std::cin >> inputArray[2];

    for (int i = 0; i < 3; ++i)
    {
        std::cout << inputArray[i] << std::endl;
    }

    // 2. 정수 변수를 배열의 순번에 사용할 수 있다(for문에서 짐작 가능했던 부분)
    int varArray[3] = { 901, 802, 703 }; // 정수 세 개짜리 배열
    int indexfix = 2; // 0, 1, 2를 넣으면 밑에서 해당 순번의 varArray 값이 출력

    std::cout << varArray[indexfix] << std::endl;

    // 3. 배열의 값은 결국 각 순번에 들어간 *개발자가 지정한 자료형의 데이터*
    // = 그 데이터가 정수일 경우, 한 배열의 값이 순번으로 쓰여도 괜찮다(같은 변수니까)
    // 단, 그 값이 다른 배열의 크기를 넘지는 말 것
    int compArr_1[3] = { 1, 2, 3 };
    int compArr_2[3] = { 1, 2, 3 };
    std::cout << compArr_1[ compArr_2[0] ] << std::endl;
    // compArr_2의 0번 순번, 다시 말해 첫 번째 순서 int가 먼저 호출 : 1
    // 이렇게 나온 값 1을 compArr_1의 순번에 대입하고 결과를 사용

    // --------------이 다음부터는 할 수 없는 것

    // 4. 배열의 이름을 출력해서 안에 있는 원소들을 확인할 수는 없다

    // 위에서 만든 varArray를 출력에 사용
    std::cout << varArray << std::endl;
    // 출력 결과 : varArray라는 배열이 위치하는 컴퓨터 내 메모리 위치(주소) - 지금은 암기할 필요x
    // 지금 중요한 건 아무튼 이 결과는 원소 목록이 아니라는 것

    // 5. 한 번 작성된 배열의 크기를(다른 꼼수나 나중에 배울 고급 기능 없이)그냥 바꿀 수 없다
    int ugul[10]; // 원소 10개짜리 배열 작성
    // ugul[100]; // 이건 호출(100순번 사용하기)
    // ugul[10] = ugul[100]; // 코드의 의도 : 10개까지 배열을 100개 바꾸겠다 → 작동 안 함

    // 억울한데, C++은 원래 그렇다

    // 6. 배열의 크기를 변수로 지정할 수 없다. 반드시 상수만(그냥 숫자) 써야 한다
    // int size = 100; // 변수를 만들고...
    // int arrayBySize[size]; // 그 변수를 크기로 사용해서 배열을 작성할 수가 없다

    // 진짜 억훌하고 말도 안 되는데...c++는 그냥 그렇다

    // ----------------------------

    // 배열에서 쓸 수 있는 추가 응용 팁

    // 1. 배열의 위치 서로 바꾸기
    int order[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 위에서 만든 "순서 배열의 3번째와 7번째 위치를 바꿔보기
    int tmp = order[2];
    order[2] = order[6];
    order[6] = tmp;
    
    // 임시로 쓰기 위한 정수 tmp를 만들고, 그 자리에 order의 2순번 값(3)을 할당한 후
    // order[2]의 값을 order[6]의 값(7)으로 수정하고, 다시 order[6]값은
    // 윗줄에서 저장된 tmp의 값(3, 원래는 order[2]여 였던 값)으로 또 수정

    for (int i = 0; i < 10; ++i)
    {
        std::cout << order[i] << std::endl;
    }

    // 2. 배열을 랜덤 순서로 헝클어뜨리기
    
    // 원리 : 무작위 순서 들을 뽑아서 서로 위치를 바꾸게 하는데, 그 횟수를 아주 많이 반복
    srand(GetTickCount64());

    for (int i = 0; i < 1000; ++i) // 1000번 반복하기 위한 조건
    {
        // 위에 만든 order 배열 사용
        // 랜덤 순서들을 a, b로 지칭
        int a = rand() % 10;
        int b = rand() % 10;

        int temp = order[a];
        order[a] = order[b];
        order[b] = temp;

        // temp를 새로 만들고, a와 b의 위치를 랜덤으로 뽑아서 바꾸기 x 1,000
        // 여기서는 std::cout 사용불가, 사용 의미 없음
    }

    // 1,000번동안 반복문을 반복한 그 다음에, 10번짜리 반복문으로 배열을 출력
    for (int i = 0; i < 10; ++i)
    {
        std::cout << order[i] << std::endl;
    }

    // 3. 배열의 속 배열 : 다차원 배열
    int axis[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // 순번 0-0부터 0-2까지 한 번 돌고
    // 왼쪽 순번이 1로 올라서 1-0부터 1-2까지 또 돌고
    // 왼쪽 순번이 2로 올라서 2-0부터 2-2까지 또 도는

    // 0-0, 0-1, 0-2
    // 1-0, 1-1, 1-2
    // 2-0, 2-1, 2-2

    // 2차원 스타이르이 배열이 만들어진다
    // 그리고 C++ 콘솔 환경이 가로 출력 후 세로 출력 스타일이라서
    // 먼저 돌아가는 순번(=오른쪽)이 가로 출력을 담당하는 경우가 대부분(x축)

    // 3-1. 다차원 배열의 중복 허용 범위
    int triDim[3][3][3]; // 3차원 배열, 가능
    int quaDim[4][4][4][4]; // 4차원 배열, 가능
    // int comDim[17][17][17][17][17][17][17][17][17][17][17][17][17][17][17][17][17];
    // 위 배열은 메모리가 딸려서 불가능

    // 결론 : 다차원 배열은 이론적으로 어디까지나 중복 가능
    // 단, 배열의 크기가 너무 커지면 메모리의 영역이 감당을 못하기 때문에 현실적으로는 배열의 차원 수가 무한은 아니다
    // 좀 더 현실적으로 이야기 : 보통 배열은 2차원까지가 많고, 4차원까지가 드물게 쓰이고, 5차원 이상은 거의 안 쓴다

    // 3.2 다차원 배열도 배열이기 때문에, 순번에는 변수를 사용할 수 있다
    // 위에 만든 axis 배열을 사용
    int x = 1; // 0부터 2까지 가능
    int y = 2; // 0부터 2까지 가능

    std::cout << axis[y][x] << std::endl;
    // 1, 2, 3
    // 4, 5, 6
    // 7, 8, 9

    // 순번에 각각 x, y를 넣으면 (출력 방식 때문에 순서는 반대지만)
    // 그 위치에 있는 axis 배열의 값을 호출해서 출력 가능
}
