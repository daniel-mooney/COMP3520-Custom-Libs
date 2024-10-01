#include "../../data_structures/linkedlist.h"

#include <gtest/gtest.h>


TEST(LinkedList, Init) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    EXPECT_EQ(linkedlist_length(&list), 0);
    EXPECT_EQ(linkedlist_item_size(&list), sizeof(int));

    linkedlist_destroy(&list);
}

TEST(LinkedList, Append) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        linkedlist_append(&list, &items[i]);
    }

    EXPECT_EQ(linkedlist_length(&list), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, Insert) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        linkedlist_insert(&list, i, &items[i]);
    }

    EXPECT_EQ(linkedlist_length(&list), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, Remove) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        linkedlist_append(&list, &items[i]);
    }

    int rm_item;
    linkedlist_remove(&list, 2, &rm_item);

    EXPECT_EQ(rm_item, 3);
    EXPECT_EQ(linkedlist_length(&list), 4);

    int item;
    for (int i = 0; i < 4; i++) {
        linkedlist_get(&list, i, &item);
        if (i < 2) {
            EXPECT_EQ(item, items[i]);
        } else {
            EXPECT_EQ(item, items[i + 1]);
        }
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, Pop) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        linkedlist_append(&list, &items[i]);
    }

    int rm_item;
    linkedlist_pop(&list, &rm_item);

    EXPECT_EQ(rm_item, 5);
    EXPECT_EQ(linkedlist_length(&list), 4);

    int item;
    for (int i = 0; i < 4; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, FromRaw) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    EXPECT_EQ(linkedlist_length(&list), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, Get) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}