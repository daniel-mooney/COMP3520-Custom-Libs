#include "../../data_structures/deque.h"
#include <gtest/gtest.h>


TEST(Deque, init) {
    deque_t deque;
    deque_init(&deque, sizeof(int));

    EXPECT_EQ(deque_length(&deque), 0);
    EXPECT_EQ(deque_item_size(&deque), sizeof(int));

    deque_destroy(&deque);
}

TEST(Deque, push_pop_front) {
    deque_t deque;
    deque_init(&deque, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        deque_push_front(&deque, &items[i]);
    }

    EXPECT_EQ(deque_length(&deque), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        deque_pop_front(&deque, &item);
        EXPECT_EQ(item, items[i]);
    }

    deque_destroy(&deque);
}

TEST(Deque, push_pop_back) {
    deque_t deque;
    deque_init(&deque, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        deque_push_back(&deque, &items[i]);
    }

    EXPECT_EQ(deque_length(&deque), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        deque_pop_back(&deque, &item);
        EXPECT_EQ(item, items[i]);
    }

    deque_destroy(&deque);
}

TEST(Deque, from_raw) {
    deque_t deque;
    int items[] = {1, 2, 3, 4, 5};

    deque_from_raw(&deque, sizeof(int), 5, items);

    EXPECT_EQ(deque_length(&deque), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        deque_pop_front(&deque, &item);
        EXPECT_EQ(item, items[i]);
    }

    deque_destroy(&deque);
}

TEST(Deque, front_back) {
    deque_t deque;
    deque_init(&deque, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        deque_push_back(&deque, &items[i]);
    }

    int item;
    deque_front(&deque, &item);
    EXPECT_EQ(item, items[0]);

    deque_back(&deque, &item);
    EXPECT_EQ(item, items[4]);

    deque_destroy(&deque);
}

TEST(Deque, basic_1) {
    deque_t deque;
    int items[] = {1, 2, 3, 4, 5};

    deque_from_raw(&deque, sizeof(int), 5, items);

    int item;
    deque_pop_front(&deque, &item);
    EXPECT_EQ(item, 1);

    deque_pop_back(&deque, &item);
    EXPECT_EQ(item, 5);

    deque_push_back(&deque, &items[2]);
    deque_push_front(&deque, &items[1]);

    deque_front(&deque, &item);
    EXPECT_EQ(item, 2);

    deque_back(&deque, &item);
    EXPECT_EQ(item, 3);

    deque_pop_back(&deque, &item);
    EXPECT_EQ(item, 3);

    EXPECT_EQ(deque_length(&deque), 4);

    deque_pop_back(&deque, &item);
    deque_pop_back(&deque, &item);

    EXPECT_EQ(deque_length(&deque), 2);
    EXPECT_EQ(item, 3);

    deque_destroy(&deque);
}

TEST(Deque, empty) {
    deque_t deque;
    deque_init(&deque, sizeof(int));

    EXPECT_EQ(deque_empty(&deque), 1);

    int item = 1;
    EXPECT_EQ(deque_pop_back(&deque, &item), 1);

    deque_push_back(&deque, &item);
    EXPECT_EQ(deque_empty(&deque), 0);

    deque_destroy(&deque);
}