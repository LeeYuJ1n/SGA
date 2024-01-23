#pragma once

//글로벌 이벤트 파일
//문자 그대로, "클래스에 국한되지 않고 쓸 수 있는" 이벤트의 작성에 활용 가능
// ->싱글턴 사용, 기본적인 클래스 호출, 단순 연산, 혹은 "피드백이 있는 함수"에 해당할 경우 사용 가능

// -> 특정 씬에 결속된 이벤트라면 이쪽 파일로는 사용 불가능한 점이 한계

//글로벌 이벤트는 클래스가 아닌 구조체(C의 일부, 캡슐화가 안 되어 있고 -> 어디서든 접근 가능)
//보안성이 약해지고(기본 접근권이 전공개) 대신 어디서든 접근할 수 있는 전역 코드가 된다

struct GlobalEvent
{
    // 구조체는 클래스나 함수는 아니다
    // 하지만 연산자 () <- 함수처럼 불러오게 만드는 기호를 부착시켜서 함수처럼 인식시킬 수는 있다
    // 이런 식으로 변형한 코드를 프로그래밍에서는 "호출대상(콜러블)"이라고 한다
    
    void operator()(string keyword); //앞의 괄호는 "()"라는 모양의 연산자를 지정해서 오버라이드한다는 뜻
                                     //뒤의 괄호는 이 연산자를 부를 때 지정해야 할 매개변수

    void operator()(string keyword, string args); // 키워드와 추가변수가 또 있는 경우
};
