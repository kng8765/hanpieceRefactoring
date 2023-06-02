#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LUF_ATTACK 1
#define LUF_HOLD 2

#define CRO_ATTACK 1
#define CRO_HOLD 2 // ��
#define CRO_NONE 3 // ����

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
    printf("==========���ǽ� ����==========\n");
    printf("�������� �� �糪�� ���Ǵ� \n���� �޸�ȣ�� Ÿ�� ���� ������.\n\n�ٴٸ� ������ ��\nĥ���� ũ��Ŀ������ ���� ������ �������µ�...\n������ ���� ����!\n���� �̱� �� ���� ���ΰ�?\n�ε�!\n\n");
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
    printf("Luffy      HP: %d, ���ݷ�: %d", luffy.hp < 0 ? 0 : luffy.hp, luffy.atk, (int)pow(2, luffy.state));
    if (luffy.state > 0)
        printf(" (�� x %d�� ����) = %d", (int)pow(2, luffy.state), luffy.atk * (int)pow(2, luffy.state));
    printf("\nCrocodile  HP: %d, ���ݷ�: %d", crocodile.hp < 0 ? 0 : crocodile.hp, crocodile.atk);
    if (crocodile.state > 0)
        printf(" (�� ����)");
    printf("\n");
}

int luffy_action() {
    int action;

    printf("==========���� ����===========\n");
    while (1) {
        printf("1. ���� !\n2. �� ������\n==============================\n");
        printf("\n���ǰ� �� �ൿ�� �����ϼ���(1 or 2) >>>> ");
        if (scanf("%d", &action) != 1 || (action != 1 && action != 2)) { // �Է°� ���� ó��
            printf("\n");
            getchar();
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n=========================\n");
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
        printf("\n������ ���� : '���� ��!' x %d\n", (int)pow(2, luffy.state));
        printf("���� atk : %d\n\n", luffy.atk);
        damage = damage * (int)pow(2, luffy.state);
        // ���� �ݰ� ��ų������
        if (crocodile.state > 0) {
            damage = damage / 2;
            printf("ũ��Ŀ������ ���� �������� �ݰ��˴ϴ�. (������ %d)\n", damage);
        }
        printf("ũ��Ŀ���� %d - %d = %d\n", crocodile.hp, damage, crocodile.hp - damage);
        // �Ǳ���
        crocodile.hp -= damage;
        // ���� ��� ���̱�
        luffy.state = 0;
        break;
    case LUF_HOLD:
        printf("\n���ǰ� �⸦ ������ �ֽ��ϴ�...\n");
        luffy.state += 1;
        printf("���� atk : %d\n\n", luffy.atk * (int)pow(2, luffy.state));
        break;
    }
    print_player_status();
}

int crocodile_action() {
    int action = RandomNumber(1, 3);
    crocodile.state = 0;

    if (action == CRO_HOLD) {
        printf("=======ũ��Ŀ���� ����========\n");
        printf("\nũ��Ŀ������ ���� �𷡷� �ٲߴϴ�.\n\n");
        crocodile.state = 1;
    }
    else if (action == CRO_NONE) {
        printf("=======ũ��Ŀ���� ����========\n");
        printf("\nũ��Ŀ������ ������ �θ��ϴ�:'�ϰ� ĥ���ذ� ���� �˾�?!\n\n");
    }
    return action;
}

void crocodile_attack(int action) {
    if (action == CRO_ATTACK) {
        printf("=======ũ��Ŀ���� ����========\n");
        printf("\nũ��Ŀ������ ���� : '�縷�� ��ǳ!'\n");
        if (luffy.state > 0) {
            printf("ũ��Ŀ������ �������� ������ ��� �Ⱑ ������ϴ�\n");
            printf("���� atk : %d\n\n", luffy.atk);
        }
        int damage;
        damage = crocodile.atk;
        printf("���� %d - %d = %d\n", luffy.hp, damage, luffy.hp - damage);
        luffy.hp -= damage;
        luffy.state = 0;
    }
    print_player_status();
}

int check_hp() {
    if (luffy.hp <= 0) {
        printf("=============================\n");
        printf("ĥ������ ���� �ʹ� ���Ҵ٤�^��(������ �й�) \n\n");
        return 0;
    }
    else if (crocodile.hp <= 0) {
        printf("=============================\n");
        printf("���ǰ� ũ��Ŀ������ �����߷ȴ�!!(������ �¸�)\n\n");
        return 0;
    }
    else if (luffy.hp <= 0 && crocodile.hp <= 0) {
        printf("���º��Դϴ�.");
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
    printf("\n������Ͻðڽ��ϱ�? (1: ����� / 0: ����) >>> ");
    scanf("%d", &restart);

    if (restart == 1) { // �ٽ� ����
        printf("������ �ٽ� �����մϴ�.\n");
        system("cls");
        return 1;
    }
    else { // ����
        printf("������ �����մϴ�.\n");
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