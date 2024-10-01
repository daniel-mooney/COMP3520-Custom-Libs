#include "../../data_structures/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gtest/gtest.h>


TEST(QueueTest, Init) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    EXPECT_EQ(queue_capacity(&queue), capacity);
    EXPECT_EQ(queue_item_size(&queue), sizeof(int));
    EXPECT_EQ(queue_length(&queue), 0);
    EXPECT_EQ(queue_is_empty(&queue), 1);

    queue_destroy(&queue);
}

TEST(QueueTest, PushAndPop) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }
    
    ASSERT_EQ(queue_length(&queue), 5);

    // Pop all items
    for (int i = 0; i < 5; i++) {
        int item;
        queue_pop(&queue, &item);
        EXPECT_EQ(item, items[i]);
    }

    queue_destroy(&queue);
}

TEST(QueueTest, Full) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    for (int i = 0; i < capacity; i++) {
        queue_push(&queue, &i, NULL);
    }

    int item = 100;
    EXPECT_EQ(queue_push(&queue, &item, NULL), 1);
    EXPECT_EQ(queue_length(&queue), capacity);

    queue_destroy(&queue);
}

TEST(QueueTest, HeadAndTail) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    int item;
    queue_head(&queue, &item);
    EXPECT_EQ(item, items[0]);

    queue_tail(&queue, &item);
    EXPECT_EQ(item, items[4]);

    queue_destroy(&queue);
}

TEST(QueueTest, PopEmpty) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int item;
    EXPECT_EQ(queue_pop(&queue, &item), 1);

    queue_destroy(&queue);
}

TEST(QueueTest, HeadEmpty) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int item;
    EXPECT_EQ(queue_head(&queue, &item), 1);

    queue_destroy(&queue);
}

TEST(QueueTest, TailEmpty) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int item;
    EXPECT_EQ(queue_tail(&queue, &item), 1);

    queue_destroy(&queue);
}

TEST(QueueTest, Length) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    ASSERT_EQ(queue_length(&queue), 5);

    queue_destroy(&queue);
}

TEST(QueueTest, Capacity) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    ASSERT_EQ(queue_capacity(&queue), capacity);

    queue_destroy(&queue);
}

TEST(QueueTest, ItemSize) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    ASSERT_EQ(queue_item_size(&queue), sizeof(int));

    queue_destroy(&queue);
}

TEST(QueueTest, IsEmpty) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(int), capacity);

    ASSERT_EQ(queue_is_empty(&queue), 1);

    queue_destroy(&queue);
}

TEST(QueueTest, CharTest) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(char), capacity);

    ASSERT_EQ(queue_capacity(&queue), capacity);
    ASSERT_EQ(queue_length(&queue), 0);

    EXPECT_EQ(queue_is_empty(&queue), 1);
    EXPECT_EQ(queue_item_size(&queue), sizeof(char));

    char items[] = {'a', 'b', 'c', 'd', 'e'};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    ASSERT_EQ(queue_length(&queue), 5);

    char item;

    queue_head(&queue, &item);
    EXPECT_EQ(item, items[0]);

    queue_tail(&queue, &item);
    EXPECT_EQ(item, items[4]);

    for (int i = 0; i < 5; i++) {
        char item;
        queue_pop(&queue, &item);
        EXPECT_EQ(item, items[i]);
    }

    EXPECT_EQ(queue_is_empty(&queue), 1);
    queue_destroy(&queue);
    
}

struct Point {
    int x;
    int y;
};

TEST(QueueTest, StructTest) {
    queue_t queue;
    int capacity = 20;
    queue_init(&queue, sizeof(struct Point), capacity);

    ASSERT_EQ(queue_capacity(&queue), capacity);
    ASSERT_EQ(queue_length(&queue), 0);

    EXPECT_EQ(queue_is_empty(&queue), 1);
    EXPECT_EQ(queue_item_size(&queue), sizeof(struct Point));

    struct Point items[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    ASSERT_EQ(queue_length(&queue), 5);

    struct Point item;

    queue_head(&queue, &item);
    EXPECT_EQ(item.x, items[0].x);
    EXPECT_EQ(item.y, items[0].y);

    queue_tail(&queue, &item);
    EXPECT_EQ(item.x, items[4].x);
    EXPECT_EQ(item.y, items[4].y);

    for (int i = 0; i < 5; i++) {
        struct Point item;
        queue_pop(&queue, &item);
        EXPECT_EQ(item.x, items[i].x);
        EXPECT_EQ(item.y, items[i].y);
    }

    EXPECT_EQ(queue_is_empty(&queue), 1);
    queue_destroy(&queue);
}