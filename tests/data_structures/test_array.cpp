#include "../../data_structures/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gtest/gtest.h>


// Test the array_append function
class ArrayTest: public ::testing::Test {
    protected:
        void *array;

        virtual void SetUp() override {
            array = array_init(sizeof(int), 0);
        }

        virtual void TearDown() override {
            array_destroy(array);
        }
};


TEST_F(ArrayTest, Init) {
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(array_length(array), 0);
    EXPECT_EQ(array_capacity(array), 0);
}


TEST_F(ArrayTest, Append) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    ASSERT_EQ(array_length(array), 5);
    
    int *data = (int *) array;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(data[i], items[i]);
    }
}

TEST_F(ArrayTest, RawToArray) {
    int items[] = {1, 2, 3, 4, 5};
    int *array_from_raw = (int *)raw_to_array(items, sizeof(int), 5);

    ASSERT_EQ(array_length(array_from_raw), 5);
    
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(array_from_raw[i], items[i]);
    }

    array_destroy(array_from_raw);
}

TEST_F(ArrayTest, AppendAndPop) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    for (int i = 4; i >= 0; i--) {
        int item;
        array = array_pop(array, &item);
        EXPECT_EQ(item, items[i]);
    }

    // Try to pop from an empty array
    array_pop(array, NULL);
    ASSERT_EQ(array_length(array), 0);
}

TEST_F(ArrayTest, Length) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    ASSERT_EQ(array_length(array), 5);
}

TEST_F(ArrayTest, BasicGet) {
    int items[] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    int item;
    for (int i = 0; i < 5; i++) {
        array_get(array, i, &item);
        EXPECT_EQ(item, items[i]);
    }
} 

TEST_F(ArrayTest, Resize) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    array = array_resize(array, 10);
    ASSERT_EQ(array_capacity(array), 10);

    int item;
    for (int i = 0; i < 5; i++) {
        array_get(array, i, &item);
        EXPECT_EQ(item, items[i]);
    }
}

TEST_F(ArrayTest, Copy) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    int *copy = (int *)array_copy(array);
    ASSERT_NE(copy, nullptr);

    ASSERT_EQ(array_length(copy), 5);

    int item;
    for (int i = 0; i < 5; i++) {
        array_get(copy, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    array_destroy(copy);
}