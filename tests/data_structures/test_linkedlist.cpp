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

TEST(LinkedList, Char) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(char));

    char items[] = {'a', 'b', 'c', 'd', 'e'};

    linkedlist_from_raw(&list, sizeof(char), 5, items);

    EXPECT_EQ(linkedlist_length(&list), 5);

    char item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

struct Point {
    int x;
    int y;
};

TEST(LinkedList, Struct) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(Point));

    Point items[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};

    linkedlist_from_raw(&list, sizeof(Point), 5, items);

    EXPECT_EQ(linkedlist_length(&list), 5);

    Point item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item.x, items[i].x);
        EXPECT_EQ(item.y, items[i].y);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedListIterator, Init) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    linkedlist_iterator_t iter;
    linkedlist_iter_init(&iter, &list, 0, 0);

    EXPECT_EQ(iter.next, list.head);
    EXPECT_EQ(iter.reverse, 0);

    linkedlist_destroy(&list);
}

TEST(LinkedListIterator, Next) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    linkedlist_iterator_t iter;
    linkedlist_iter_init(&iter, &list, 0, 0);

    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_iter_next(&iter, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedListIterator, Reverse) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    linkedlist_iterator_t iter;
    linkedlist_iter_init(&iter, &list, -1, 1);

    int item;
    for (int i = 4; i >= 0; i--) {
        linkedlist_iter_next(&iter, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, SortAscending) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {5, 3, 1, 4, 2};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    linkedlist_sort(&list, [](const void *a, const void *b) -> int {
        return *(int *)a - *(int *)b;
    });

    int sorted[] = {1, 2, 3, 4, 5};
    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, sorted[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, SortDescending) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {5, 3, 1, 4, 2};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    linkedlist_sort(&list, [](const void *a, const void *b) -> int {
        return *(int *)b - *(int *)a;
    });

    int sorted[] = {5, 4, 3, 2, 1};
    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&list, i, &item);
        EXPECT_EQ(item, sorted[i]);
    }

    linkedlist_destroy(&list);
}

TEST(LinkedList, Head) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    int head;
    linkedlist_head(&list, &head);

    EXPECT_EQ(head, 1);

    linkedlist_destroy(&list);
}

TEST(LinkedList, Tail) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    int tail;
    linkedlist_tail(&list, &tail);

    EXPECT_EQ(tail, 5);

    linkedlist_destroy(&list);
}

TEST(LinkedList, Copy) {
    linkedlist_t list;
    linkedlist_init(&list, sizeof(int));

    int items[] = {1, 2, 3, 4, 5};

    linkedlist_from_raw(&list, sizeof(int), 5, items);

    linkedlist_t copy;
    linkedlist_copy(&copy, &list);
    linkedlist_destroy(&list);

    EXPECT_EQ(linkedlist_length(&copy), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        linkedlist_get(&copy, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    linkedlist_destroy(&copy);
}