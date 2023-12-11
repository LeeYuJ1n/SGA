#include <iostream>

using namespace std;

int Add(int a, int b) { return a + b; }      // 덧셈 함수
int Sub(int a, int b) { return a - b; }      // 뺄셈 함수
int Mult(int a, int b) { return a * b; }     // 곱셈 함수
int Div(int a, int b) { return a / b; }      // 나눗셈 함수

int main()
{
    int (*fp[4])(int, int);          // 함수 포인터 배열 선언
    fp[0] = Add;                     // 배열[1]에 덧셈 함수의 메모리 주소 저장
    fp[1] = Sub;                     // 배열[2]에 뺄셈 함수의 메모리 주소 저장
    fp[2] = Mult;                    // 배열[3]에 곱셈 함수의 메모리 주소 저장
    fp[3] = Div;                     // 배열[4]에 나눗셈 함수의 메모리 주소 저장

    for (int i = 0; i < 4; ++i)
    {
        cout << "배열 함수의 실행 값 : " << fp[i](20, 10) << endl;
    }
}