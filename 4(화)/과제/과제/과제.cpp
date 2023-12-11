#include <iostream>
#include "header_1.h" // 헤더

int main()
{
    // header_1.h 전역변수 "loop"호출
    while (loop)
    {
        std::cout << "캐릭터 시뮬레이터에 오신 것을 환영합니다" << std::endl;
        std::cout << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "1. 도화가" << std::endl;
        std::cout << "2. 기상술사" << std::endl;
        std::cout << "3. 프로그램 종료" << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "캐릭터를 선택해주세요" << std::endl;
        std::cout << "입력 : ";
        inputSelect = _getch();

        // header_1.h 전역변수 "inputSelect"호출
        switch (inputSelect)
        {
        case 49: // 1번을 누를경우 "Character_1" 함수 호출
            system("cls");
            std::cout << "[ 1번 도화가 ] 캐릭터 선택이 완료되었습니다" << std::endl;
            std::cout << std::endl;
            std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
            std::cout << "레벨 : " << Cha_1.level << std::endl; // 레벨
            std::cout << "경험치 : " << Cha_1.experience << std::endl; // 경험치
            std::cout << "체력 : " << Cha_1.strength << std::endl; // 체력
            std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
            std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
            std::cout << "재련 재화 : " << Cha_1.gold << std::endl; // 재련 재화
            
            // header_1.h 함수 "Character_1_LevelUp()"호출
            Character_1_SpecUp();

            system("cls");
            break;

        case 50: // 2번을 누를경우 "Character_2" 함수 호출
            system("cls");
            std::cout << "[ 2번 기상술사 ] 캐릭터 선택이 완료되었습니다" << std::endl;
            std::cout << std::endl;
            std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
            std::cout << "레벨 : " << Cha_2.level << std::endl; // 레벨
            std::cout << "경험치 : " << Cha_2.experience << std::endl; // 경험치
            std::cout << "체력 : " << Cha_2.strength << std::endl; // 체력
            std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
            std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
            std::cout << "재련 재화 : " << Cha_2.gold << std::endl; // 재련 재화

            // header_1.h 함수 "Character_2_LevelUp()"호출
            Character_2_SpecUp();

            system("cls");
            break;

        default:
            system("cls"); // 콘솔 화면 초기화
            std::cout << "잘못된 입력입니다" << std::endl;

            // 3초 딜레이
            for (int i = 0; i < 3; i++)
            {
                std::cout << i + 1 << " ";
                Sleep(1000); // 1초 딜레이
            }
            system("cls");
            break;
        }
        continue;
    }
}

void Character_1_SpecUp()
{
    bool loop = true;
    int levelUpGlod = 500;

    while (loop)
    {
        int inputSelect = 0;
        std::cout << "메뉴를 선택해주세요" << std::endl;
        std::cout << std::endl;
        std::cout << "1. 레벨업(+1)" << std::endl;
        std::cout << "2. 경험치 구매(+50)" << std::endl;
        std::cout << "3. 체력 업그레이드(+100)" << std::endl;
        std::cout << "4. 메인화면" << std::endl;

        inputSelect = _getch();

        switch (inputSelect)
        {
        case 49:
            inputSelect = _getch();
            std::cout << "레벨업 비용 : " << levelUpGlod << std::endl;
            std::cout << std::endl;

            switch (inputSelect)
            {
            case 49: // 1번 레벨업
                if (Cha_1.gold >= 100)
                {
                    std::cout << "레벨업 진행중" << std::endl;

                    // 3초 딜레이
                    for (int i = 0; i < 3; i++)
                    {
                        std::cout << i + 1 << " ";
                        Sleep(1000); // 1초 딜레이
                    }
                    std::cout << std::endl;
                    system("cls");
                    std::cout << "레벨업이 완료되었습니다" << std::endl;

                    std::cout << std::endl;
                    std::cout << "--------------------------------------------------------------" << std::endl;
                    std::cout << "강화 전 프로필" << std::endl;
                    std::cout << std::endl;
                    std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
                    std::cout << "레벨 : " << Cha_1_Level << std::endl; // 레벨
                    std::cout << "경험치 : " << Cha_1.experience << std::endl; // 경험치
                    std::cout << "체력 : " << Cha_1.strength << std::endl; // 체력
                    std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
                    std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
                    std::cout << "재련 재화 : " << Cha_1.gold << std::endl; // 재련 재화
                    std::cout << "--------------------------------------------------------------" << std::endl;

                    Cha_1_Level = Cha_1.level;
                    Cha_1.level = Cha_1.level + 1;
                    Cha_1.gold = Cha_1.gold - 100;

                    std::cout << std::endl;

                    std::cout << "--------------------------------------------------------------" << std::endl;
                    std::cout << "강화 후 프로필" << std::endl;
                    std::cout << std::endl;
                    std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
                    std::cout << "★ 레벨 : " << Cha_1.level << "( "<< Cha_1_Level << " → " << Cha_1.level << " )" << std::endl; // 레벨
                    std::cout << "경험치 : " << Cha_1.experience << std::endl; // 경험치
                    std::cout << "체력 : " << Cha_1.strength << std::endl; // 체력
                    std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
                    std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
                    std::cout << "★ 재련 재화 : " << Cha_1.gold << "(-100)" << std::endl; // 재련 재화
                    std::cout << "--------------------------------------------------------------" << std::endl;
                    std::cout << "Enter키를 누르시면 메인화면으로 돌아갑니다" << std::endl;
                    std::cout << "--------------------------------------------------------------" << std::endl;
                    inputSelect = _getch();

                    switch (inputSelect)
                    {
                    case 13:
                        std::cout << "메인화면으로 이동합니다" << std::endl;

                        // 3초 딜레이
                        for (int i = 0; i < 3; i++)
                        {
                            std::cout << i + 1 << " ";
                            Sleep(1000); // 1초 딜레이
                        }
                        system("cls");
                        main();
                        break;
                    }
                }
                else
                {
                    std::cout << "골드가 부족합니다" << std::endl;
                }
                break;
            }
            break;

        case 50: // 2번 경험치 구매
            if (Cha_1.gold >= 100)
            {
                std::cout << "경험치 구매중" << std::endl;

                // 3초 딜레이
                for (int i = 0; i < 3; i++)
                {
                    std::cout << i + 1 << " ";
                    Sleep(1000); // 1초 딜레이
                }
                std::cout << std::endl;
                system("cls");
                std::cout << "경험치 구매가 완료되었습니다" << std::endl;

                std::cout << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 전 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_1_Level << std::endl; // 레벨
                std::cout << "경험치 : " << Cha_1.experience << std::endl; // 경험치
                std::cout << "체력 : " << Cha_1.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
                std::cout << "재련 재화 : " << Cha_1.gold << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;

                Cha_1_experience = Cha_1.experience;
                Cha_1.experience = Cha_1.experience + 50;
                Cha_1.gold = Cha_1.gold - 100;

                std::cout << std::endl;

                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 후 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_1.level << std::endl; // 레벨
                std::cout << "★ 경험치 : " << Cha_1.experience << "(+50)" << std::endl; // 경험치
                std::cout << "체력 : " << Cha_1.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
                std::cout << "★ 재련 재화 : " << Cha_1.gold << "(-100)" << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "Enter키를 누르시면 메인화면으로 돌아갑니다" << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                inputSelect = _getch();

                switch (inputSelect)
                {
                case 13:
                    std::cout << "메인화면으로 이동합니다" << std::endl;

                    // 3초 딜레이
                    for (int i = 0; i < 3; i++)
                    {
                        std::cout << i + 1 << " ";
                        Sleep(1000); // 1초 딜레이
                    }
                    system("cls");
                    main();
                    break;
                }
            }
            else
            {
                std::cout << "골드가 부족합니다" << std::endl;
            }
            break;

        case 51: // 3번 체력 업그레이드
            if (Cha_1.gold >= 100)
            {
                std::cout << "체력 업그레이드 중..." << std::endl;

                // 3초 딜레이
                for (int i = 0; i < 3; i++)
                {
                    std::cout << i + 1 << " ";
                    Sleep(1000); // 1초 딜레이
                }
                std::cout << std::endl;
                system("cls");
                std::cout << "경험치 구매가 완료되었습니다" << std::endl;

                std::cout << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 전 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_1_Level << std::endl; // 레벨
                std::cout << "경험치 : " << Cha_1.experience << std::endl; // 경험치
                std::cout << "체력 : " << Cha_1.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
                std::cout << "재련 재화 : " << Cha_1.gold << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;

                Cha_1_strength = Cha_1.strength;
                Cha_1.strength = Cha_1.strength + 100;
                Cha_1.gold = Cha_1.gold - 100;

                std::cout << std::endl;

                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 후 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_1.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_1.level << std::endl; // 레벨
                std::cout << "경험치 : " << Cha_1.experience << "(+50)" << std::endl; // 경험치
                std::cout << "★ 체력 : " << Cha_1.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_1.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_1.defensive << std::endl; // 방어력
                std::cout << "★ 재련 재화 : " << Cha_1.gold << "(-100)" << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "Enter키를 누르시면 메인화면으로 돌아갑니다" << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                inputSelect = _getch();

                switch (inputSelect)
                {
                case 13:
                    std::cout << "메인화면으로 이동합니다" << std::endl;

                    // 3초 딜레이
                    for (int i = 0; i < 3; i++)
                    {
                        std::cout << i + 1 << " ";
                        Sleep(1000); // 1초 딜레이
                    }
                    system("cls");
                    main();
                    break;
                }
            }
            else
            {
                std::cout << "골드가 부족합니다" << std::endl;
            }
            break;

        case 52:
            system("cls");
            main();
            break;

        default:
            system("cls");
            std::cout << "ERROR CODE" << std::endl;

            // 3초 딜레이
            for (int i = 0; i < 3; i++)
            {
                std::cout << i + 1 << " ";
                Sleep(1000); // 1초 딜레이
            }
            break;
        }
    }
}

void Character_2_SpecUp()
{
    bool loop = true;
    int levelUpGlod = 500;

    while (loop)
    {
        int inputSelect = 0;
        std::cout << "메뉴를 선택해주세요" << std::endl;
        std::cout << std::endl;
        std::cout << "1. 레벨업(+1)" << std::endl;
        std::cout << "2. 경험치 구매(+50)" << std::endl;
        std::cout << "3. 체력 업그레이드(+100)" << std::endl;
        std::cout << "4. 메인화면" << std::endl;

        inputSelect = _getch();

        switch (inputSelect)
        {
        case 49:
            inputSelect = _getch();
            std::cout << "레벨업 비용 : " << levelUpGlod << std::endl;
            std::cout << std::endl;

            switch (inputSelect)
            {
            case 49: // 1번 레벨업
                if (Cha_2.gold >= 100)
                {
                    std::cout << "레벨업 진행중" << std::endl;

                    // 3초 딜레이
                    for (int i = 0; i < 3; i++)
                    {
                        std::cout << i + 1 << " ";
                        Sleep(1000); // 1초 딜레이
                    }
                    std::cout << std::endl;
                    system("cls");
                    std::cout << "레벨업이 완료되었습니다" << std::endl;

                    std::cout << std::endl;
                    std::cout << "--------------------------------------------------------------" << std::endl;
                    std::cout << "강화 전 프로필" << std::endl;
                    std::cout << std::endl;
                    std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
                    std::cout << "레벨 : " << Cha_2_Level << std::endl; // 레벨
                    std::cout << "경험치 : " << Cha_2.experience << std::endl; // 경험치
                    std::cout << "체력 : " << Cha_2.strength << std::endl; // 체력
                    std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
                    std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
                    std::cout << "재련 재화 : " << Cha_2.gold << std::endl; // 재련 재화
                    std::cout << "--------------------------------------------------------------" << std::endl;

                    Cha_2_Level = Cha_2.level;
                    Cha_2.level = Cha_2.level + 1;
                    Cha_2.gold = Cha_2.gold - 100;

                    std::cout << std::endl;

                    std::cout << "--------------------------------------------------------------" << std::endl;
                    std::cout << "강화 후 프로필" << std::endl;
                    std::cout << std::endl;
                    std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
                    std::cout << "★ 레벨 : " << Cha_2.level << "( " << Cha_2_Level << " → " << Cha_2.level << " )" << std::endl; // 레벨
                    std::cout << "경험치 : " << Cha_2.experience << std::endl; // 경험치
                    std::cout << "체력 : " << Cha_2.strength << std::endl; // 체력
                    std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
                    std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
                    std::cout << "★ 재련 재화 : " << Cha_2.gold << "(-100)" << std::endl; // 재련 재화
                    std::cout << "--------------------------------------------------------------" << std::endl;
                    std::cout << "Enter키를 누르시면 메인화면으로 돌아갑니다" << std::endl;
                    std::cout << "--------------------------------------------------------------" << std::endl;
                    inputSelect = _getch();

                    switch (inputSelect)
                    {
                    case 13:
                        std::cout << "메인화면으로 이동합니다" << std::endl;

                        // 3초 딜레이
                        for (int i = 0; i < 3; i++)
                        {
                            std::cout << i + 1 << " ";
                            Sleep(1000); // 1초 딜레이
                        }
                        system("cls");
                        main();
                        break;
                    }
                }
                else
                {
                    std::cout << "골드가 부족합니다" << std::endl;
                }
                break;
            }
            break;

        case 50: // 2번 경험치 구매
            if (Cha_2.gold >= 100)
            {
                std::cout << "경험치 구매중" << std::endl;

                // 3초 딜레이
                for (int i = 0; i < 3; i++)
                {
                    std::cout << i + 1 << " ";
                    Sleep(1000); // 1초 딜레이
                }
                std::cout << std::endl;
                system("cls");
                std::cout << "경험치 구매가 완료되었습니다" << std::endl;

                std::cout << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 전 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_2_Level << std::endl; // 레벨
                std::cout << "경험치 : " << Cha_2.experience << std::endl; // 경험치
                std::cout << "체력 : " << Cha_2.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
                std::cout << "재련 재화 : " << Cha_2.gold << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;

                Cha_2_experience = Cha_2.experience;
                Cha_2.experience = Cha_2.experience + 50;
                Cha_2.gold = Cha_2.gold - 100;

                std::cout << std::endl;

                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 후 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_2.level << std::endl; // 레벨
                std::cout << "★ 경험치 : " << Cha_2.experience << "(+50)" << std::endl; // 경험치
                std::cout << "체력 : " << Cha_2.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
                std::cout << "★ 재련 재화 : " << Cha_2.gold << "(-100)" << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "Enter키를 누르시면 메인화면으로 돌아갑니다" << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                inputSelect = _getch();

                switch (inputSelect)
                {
                case 13:
                    std::cout << "메인화면으로 이동합니다" << std::endl;

                    // 3초 딜레이
                    for (int i = 0; i < 3; i++)
                    {
                        std::cout << i + 1 << " ";
                        Sleep(1000); // 1초 딜레이
                    }
                    system("cls");
                    main();
                    break;
                }
            }
            else
            {
                std::cout << "골드가 부족합니다" << std::endl;
            }
            break;

        case 51: // 3번 체력 업그레이드
            if (Cha_2.gold >= 100)
            {
                std::cout << "체력 업그레이드 중..." << std::endl;

                // 3초 딜레이
                for (int i = 0; i < 3; i++)
                {
                    std::cout << i + 1 << " ";
                    Sleep(1000); // 1초 딜레이
                }
                std::cout << std::endl;
                system("cls");
                std::cout << "경험치 구매가 완료되었습니다" << std::endl;

                std::cout << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 전 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_2_Level << std::endl; // 레벨
                std::cout << "경험치 : " << Cha_2.experience << std::endl; // 경험치
                std::cout << "체력 : " << Cha_2.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
                std::cout << "재련 재화 : " << Cha_2.gold << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;

                Cha_2_strength = Cha_2_strength;
                Cha_2.strength = Cha_2.strength + 100;
                Cha_2.gold = Cha_2.gold - 100;

                std::cout << std::endl;

                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "강화 후 프로필" << std::endl;
                std::cout << std::endl;
                std::cout << "닉네임 : " << Cha_2.chaName << std::endl; // 캐릭터 이름
                std::cout << "레벨 : " << Cha_2.level << std::endl; // 레벨
                std::cout << "경험치 : " << Cha_2.experience << "(+50)" << std::endl; // 경험치
                std::cout << "★ 체력 : " << Cha_2.strength << std::endl; // 체력
                std::cout << "공격력 : " << Cha_2.power << std::endl; // 공격력
                std::cout << "방어력 : " << Cha_2.defensive << std::endl; // 방어력
                std::cout << "★ 재련 재화 : " << Cha_2.gold << "(-100)" << std::endl; // 재련 재화
                std::cout << "--------------------------------------------------------------" << std::endl;
                std::cout << "Enter키를 누르시면 메인화면으로 돌아갑니다" << std::endl;
                std::cout << "--------------------------------------------------------------" << std::endl;
                inputSelect = _getch();

                switch (inputSelect)
                {
                case 13:
                    std::cout << "메인화면으로 이동합니다" << std::endl;

                    // 3초 딜레이
                    for (int i = 0; i < 3; i++)
                    {
                        std::cout << i + 1 << " ";
                        Sleep(1000); // 1초 딜레이
                    }
                    system("cls");
                    main();
                    break;
                }
            }
            else
            {
                std::cout << "골드가 부족합니다" << std::endl;
            }
            break;

        case 52:
            system("cls");
            main();
            break;

        default:
            system("cls");
            std::cout << "ERROR CODE" << std::endl;

            // 3초 딜레이
            for (int i = 0; i < 3; i++)
            {
                std::cout << i + 1 << " ";
                Sleep(1000); // 1초 딜레이
            }
            break;
        }
    }
}