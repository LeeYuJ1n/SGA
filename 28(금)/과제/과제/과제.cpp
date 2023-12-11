// 2965번 캥거루 세마리
// 1. 캥거루 세 마리가 사막에서 놀고 있다 사막에는 수직선이 하나 있고, 캥거루는 서로 다른 한 좌표 위에 있다
// 2. 한 번 움직일 때, 바깥쪽의 두 캥거루 중 한 마리가 다른 두 캥거루 사이의 정수 좌표로 점프한다
// 3. 한 좌표 위에 있는 캥거루가 두 마리 이상일 수는 없다
// 4. 캥거루는 최대 몇 번 움직일 수 있을까?

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    int a = 0, b = 0, c = 0;
    int maxCount = 0;

    cin >> a >> b >> c;

    while (true) 
    {
        // 두 캥거루 사이의 거리 계산
        int distance_AB = b - a;
        int distance_BC = c - b;

        // 두 캥거루 사이의 거리가 1 이상인 경우
        if (distance_AB >= 1 && distance_BC >= 1) {
            // 한 번의 움직임으로 두 캥거루를 서로 붙임
            a = b;
            b = c - 1;
            maxCount++;
        }
        // 두 캥거루 사이의 거리가 0인 경우 (더 이상 움직일 수 없음)
        else {
            break;
        }
    }

    cout << maxCount << endl;

    return 0;
}