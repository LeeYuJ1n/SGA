﻿#include <iostream>

int main()
{
    // 부분의 합이 100 이상인 쌍이나 원소 찾기

    // 10개짜리 배열 중에서, 부분의 합이 100 이상인 조합이 어떻게 나오는지 검출

    // 10개짜리 배열
    int data[10] = {30, 30, 40, 60, 70, 30, 90, 50, 80, 30};

    // 부분의 합을 최대로 맞출 수 있는 (부분의 합을 구하기 위해 최소로 필요한) 전체 쌍 개수
    // → 최소 조합(시작과 동시에 초기화)
    int  answer = 0;

    // 문제 접근 방법 : 
    // 1. 첫 원소부터 시작해서 자기 다음 칸과 합계 비교
    // 2. 합계가 100 이하가 되면 바로 얘들을 쌍으로 지정하고 배열(의 탐색)에서 제외
    // 3. 합계가 100을 넘으면 다시 다음 칸과 비교
    // 4. 중간에 합계가 맞춰지면 걔들을 쌍으로 지정
    // 5. 끝까지 합계가 안 맞춰지면 쌍이 불가능하니까 자기 칸만 혼자 지정, 그 후 배열에서 제외
    // 6. 다음 순서로 넘어가되, 다음 순서가 배열에서 제외돼 있으면 다시 또 다음 순서로
    // 7. 이 과정을 끝까지 반복

    // while을 쓴다면 index = 0; 아마 필요할 것(index가 끝까지 가나 안 가나 보려고)
    // 혹은 for문이라도 가능(배열에서 크기만큼 각 순번마다 한 번 이상은 봐야 하니까)
    
    // 여기서는 배열에서 제외한다고 할 경우, 해당 원소의 값을 -1로 지정하는 것으로 정하겠습니다

    // 최초 출력 1번
    for (int i = 0; i < 10; ++i)
    {
        std::cout << data[i] << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        if (data[i] == -1) continue; // 배열에서 제외됐으면 검색 중단 후 차례 건너뛰기

        // 다음 칸부터 다른 배열 원소와 쭉 비교
        for (int j = i + 1; j < 10; ++j)
        {
            // 여기서도 제외된 칸이 있으면 검색 중단
            if (data[j] == -1) continue;

            // continue가 안 되고 여기까지 왔으면, i, j 모두 합계 비교 가능
            if (data[i] + data[j] <= 100)// 합계가 100 이하가 맞으면
            {
                answer++; // 답을 하나 올리고

                data[i] = -1;
                data[j] = -1; // 두 원소를 배열에서 제외

                // 합계가 다 맞춰졌으니까 이후의 검색은 의미가 없다 → break
                break;
            }
            // 여기까지 왔다면 아직 합계가 안 맞춰져다 → 작은 반복문 다시(++j)
        }
        // 여기로 나왔으면 경우의 수는 둘
        // 데이터[j]는 둘째치고 데이터[i]의 입장에서 보이는 배열에서

        // 1. 지워졌거나, 2. 안 지워졌거나
        if (data[i] != -1)
        {
            // 데이터[i]가 아직 안 지워진 경우, 따라서 자기 짝이 없다
            // 그래도 쌍은 필요하니까(배 탈출 시나리오라면 1인용 구명보트 하나는 필요하니까)
            // 정답을 1 올리고 자기를 배열에서 제외
            data[i] = -1;
            answer++;
        }
        // 여기까지 오면, 자기는 어쨌든 지워졌고, 쌍은 어쨌든 하나는 나왔고,
        // 차이는 자기 포함 원소가 +1인가, 아니면 혼자인가

        // 검색 다 했으니 i를 1 올리고 계속 반복

        // ...하기 전에, 출력
        for (int k = 0; k < 10; ++k)
        {
            std::cout << data[k] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << answer << std::endl; // 최종 정답
}