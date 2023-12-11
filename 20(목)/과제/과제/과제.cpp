#include <iostream>
#include <string.h> // 문자열을 쓰기 위한 기능 포함

int main()
{
    // 문자열 5가지

    // 문자열 선언
    char word[101] = "안녕하세요";

    // C스타일로 문자열 출력(printf)
    printf("%s", word); // "안녕하세요"라는 글자 출력
    printf("\n"); // std::endl;

    // 1. 문자 뒤에 다른 문자 이어서 적기 strcat_s사용
    strcat_s(word, " [ 이어서 붙이기 사용 ] \n");

    // 2. 문자열 수정(복제)하기 strcpt_s사용
    strcpy_s(word, "도화가!\n");
    printf("%s", word); // "도화가!"라는 글자 출력

    // 3. 문자열 길이 파악하기 strlen사용
    int length = strlen(word);
    // strlen : 바이트 수 단위로 계산한 길이

    //출력
    printf("%s의 길이는 %d입니다\n", word, length);

    // 4. 문자열 변환하기(문자형 → 자료형) ato사용
    char textData1[20] = "12345";
    char textData2[20] = "1234.5";
    char textData3[20] = "1234567890";

    // 변환
    int inform1 = atoi(textData1); // 정수 : atoi
    float inform2 = atof(textData2); // 소수 : atof
    long long int inform3 = atoll(textData3); // 길고 긴 정수 : atoll

    // 출력
    printf("%d\n", inform1); // 정수 출력 : %d
    printf("%f\n", inform2); // 소수 출력 : %f
    printf("%d\n", inform3); // 긴 정수 출력 : %d

    // 5. 문자열 자르기 cut, strtok_s사용
    char list[100] = "도화가, 기상술사, 소울이터, 슬레이어";

    char* cut = NULL;
    char* result = NULL;

    cut = strtok_s(list, ", ", &result);

    printf("%s || %s", cut, result);

    cut = strtok_s(result, ", ", &result);

    printf("%s || %s", cut, result);

    cut = strtok_s(result, ", ", &result);

    printf("%s || %s", cut, result);

    cut = strtok_s(result, ", ", &result);

    printf("%s || %s", cut, result);

    // 6. (옵션)
    // strtok : 내부적으로 정적 변수를 사용하여 이전 호출에서 찾은 위치를 추적하여 이러한 특성으로 인해 다중 스레드 환경에서 안전하지 않을 수 있다
    // strtok_s : 문자열을 변경하지 않고도 토큰 분리 작업을 수행하며, 토큰 분리를 위해 사용자에게 버퍼의 주소와 길이를 제공받아서 작업한다. 이러한 방식으로 인해 다중 스레드 환경에서 더 안전하다
}