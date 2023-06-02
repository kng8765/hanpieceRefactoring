#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LUF_ATTACK 1
#define LUF_HOLD 2

#define CRO_ATTACK 1
#define CRO_HOLD 2 // 모래
#define CRO_NONE 3 // 여유

typedef struct Player {
    int hp;
    int atk;
    int state;
}Player;

Player luffy, crocodile;

int RandomNumber(int, int);
void intro();
void init();
void print_player_status();
int luffy_action();
void luffy_attack(int);
int crocodile_action();
void crocodile_attack(int);
int check_hp();
void battle();
int regame();

int RandomNumber(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void intro() {
    printf("==========한피스 시작==========\n");
    printf("해적왕이 될 사나이 루피는 \n고잉 메리호를 타고 길을 떠난다.\n\n바다를 떠돌던 중\n칠무해 크로커다일을 만나 전투가 벌어지는데...\n강적을 만난 루피!\n과연 이길 수 있을 것인가?\n두둥!\n\n");
    printf("Press <Enter> to continue...\n");
    getchar();
}

void init() {
    srand(time(NULL));
    luffy.hp = RandomNumber(20, 40);
    luffy.atk = RandomNumber(5, 15);
    crocodile.hp = RandomNumber(30, 50);
    crocodile.atk = RandomNumber(15, 25);
}

void print_player_status() {
    printf("==============================\n");
    printf("Luffy      HP: %d, 공격력: %d", luffy.hp < 0 ? 0 : luffy.hp, luffy.atk, (int)pow(2, luffy.state));
    if (luffy.state > 0)
        printf(" (기 x %d배 증가) = %d", (int)pow(2, luffy.state), luffy.atk * (int)pow(2, luffy.state));
    printf("\nCrocodile  HP: %d, 공격력: %d", crocodile.hp < 0 ? 0 : crocodile.hp, crocodile.atk);
    if (crocodile.state > 0)
        printf(" (모래 상태)");
    printf("\n");
}

int luffy_action() {
    int action;

    printf("==========루피 차례===========\n");
    while (1) {
        printf("1. 공격 !\n2. 기 모으기\n==============================\n");
        printf("\n루피가 할 행동을 선택하세요(1 or 2) >>>> ");
        if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // 입력값 예외 처리
            printf("\n");
            getchar();
            printf("잘못된 입력입니다. 다시 입력하세요.\n=========================\n");
            continue;
        }
        break;

    }
    return action;
}

void luffy_attack(int action) {
    int damage;
    switch (action) {
    case LUF_ATTACK:
        damage = luffy.atk;
        printf("\n루피의 공격 : '고무고무 총!' x %d\n", (int)pow(2, luffy.state));
        printf("루피 atk : %d\n\n", luffy.atk);
        damage = damage * (int)pow(2, luffy.state);
        // 방어력 반감 시킬것인지
        if (crocodile.state > 0) {
            damage = damage / 2;
            printf("크로커다일의 방어로 데미지가 반감됩니다. (데미지 %d)\n", damage);
        }
        printf("크로커다일 %d - %d = %d\n", crocodile.hp, damage, crocodile.hp - damage);
        // 피깍음
        crocodile.hp -= damage;
        // 루피 배수 줄이기
        luffy.state = 0;
        break;
    case LUF_HOLD:
        printf("\n루피가 기를 모으고 있습니다...\n");
        luffy.state += 1;
        printf("루피 atk : %d\n\n", luffy.atk * (int)pow(2, luffy.state));
        break;
    }
    print_player_status();
}

int crocodile_action() {
    int action = RandomNumber(1, 3);
    crocodile.state = 0;

    if (action == CRO_HOLD) {
        printf("=======크로커다일 차례========\n");
        printf("\n크로커다일이 몸을 모래로 바꿉니다.\n\n");
        crocodile.state = 1;
    }
    else if (action == CRO_NONE) {
        printf("=======크로커다일 차례========\n");
        printf("\n크로커다일이 여유를 부립니다:'니가 칠무해가 뭔지 알어?!\n\n");
    }
    return action;
}

void crocodile_attack(int action) {
    if (action == CRO_ATTACK) {
        printf("=======크로커다일 차례========\n");
        printf("\n크로커다일의 공격 : '사막의 폭풍!'\n");
        if (luffy.state > 0) {
            printf("크로커다일의 공격으로 루피의 모든 기가 사라집니다\n");
            printf("루피 atk : %d\n\n", luffy.atk);
        }
        int damage;
        damage = crocodile.atk;
        printf("루피 %d - %d = %d\n", luffy.hp, damage, luffy.hp - damage);
        luffy.hp -= damage;
        luffy.state = 0;
    }
    print_player_status();
}

int check_hp() {
    if (luffy.hp <= 0) {
        printf("=============================\n");
        printf("칠무해의 벽은 너무 높았다ㅠ^ㅠ(루피의 패배) \n\n");
        return 0;
    }
    else if (crocodile.hp <= 0) {
        printf("=============================\n");
        printf("루피가 크로커다일을 쓰러뜨렸다!!(루피의 승리)\n\n");
        return 0;
    }
    else if (luffy.hp <= 0 && crocodile.hp <= 0) {
        printf("무승부입니다.");
    }
    return 1;
}

void battle() {
    print_player_status();
    do {
        int luffy_act = luffy_action();
        luffy_attack(luffy_act);
        if (!check_hp()) {
            break;
        }
            
        int cro_act = crocodile_action();
        crocodile_attack(cro_act);
    } while (check_hp());
}

int regame() {
    int restart;
    printf("\n재시작하시겠습니까? (1: 재시작 / 0: 종료) >>> ");
    scanf("%d", &restart);

    if (restart == 1) { // 다시 시작
        printf("게임을 다시 시작합니다.\n");
        system("cls");
        return 1;
    }
    else { // 종료
        printf("게임을 종료합니다.\n");
        return 0;
    }
}

int main() {
    do {
        intro();
        init();
        battle();
    } while (regame());
    return 0;
}