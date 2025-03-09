#pragma once

#define FOOD_NAME_MAX 50
#define CATEGORY_MAX 50
#define ID_MAX 10
#define USER_NAME_MAX 50
#define NOTE_MAX 100

struct Food
{
    char name[FOOD_NAME_MAX];
    int price;
    char category[CATEGORY_MAX];
    bool available;
};

struct Order
{
    char id[ID_MAX];
    char name[USER_NAME_MAX];
    char food_name[FOOD_NAME_MAX];
    int amount;
    int total_price;
    char note[NOTE_MAX];
};
