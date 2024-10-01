#include "../../data_structures/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gtest/gtest.h>


class QueueTest: public ::testing::Test {
    protected:
        queue_t queue;
        int capacity = 20;

        virtual void SetUp() override {
            queue_init(&queue, sizeof(int), capacity);
        }

        virtual void TearDown() override {
            queue_destroy(&queue);
        }
};

TEST_F(QueueTest, Init) {
    EXPECT_EQ(queue_capacity(&queue), capacity);
    EXPECT_EQ(queue_item_size(&queue), sizeof(int));
    EXPECT_EQ(queue_length(&queue), 0);
    EXPECT_EQ(queue_is_empty(&queue), 1);
}


TEST_F(QueueTest, PushAndPop) {
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
}

TEST_F(QueueTest, Full) {
    for (int i = 0; i < capacity; i++) {
        queue_push(&queue, &i, NULL);
    }

    int item = 100;
    EXPECT_EQ(queue_push(&queue, &item, NULL), 1);
    EXPECT_EQ(queue_length(&queue), capacity);
}

TEST_F(QueueTest, HeadAndTail) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    int item;
    queue_head(&queue, &item);
    EXPECT_EQ(item, items[0]);

    queue_tail(&queue, &item);
    EXPECT_EQ(item, items[4]);
}

TEST_F(QueueTest, PopEmpty) {
    int item;
    EXPECT_EQ(queue_pop(&queue, &item), 1);
}

TEST_F(QueueTest, HeadEmpty) {
    int item;
    EXPECT_EQ(queue_head(&queue, &item), 1);
}

TEST_F(QueueTest, TailEmpty) {
    int item;
    EXPECT_EQ(queue_tail(&queue, &item), 1);
}

TEST_F(QueueTest, Length) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    ASSERT_EQ(queue_length(&queue), 5);
}

TEST_F(QueueTest, Capacity) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        queue_push(&queue, &items[i], NULL);
    }

    ASSERT_EQ(queue_capacity(&queue), capacity);
}

TEST_F(QueueTest, ItemSize) {
    ASSERT_EQ(queue_item_size(&queue), sizeof(int));
}

TEST_F(QueueTest, IsEmpty) {
    ASSERT_EQ(queue_is_empty(&queue), 1);
}