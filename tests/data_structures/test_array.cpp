#include "../../data_structures/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gtest/gtest.h>


TEST(ArrayTest, Init) {
    void *array = array_init(sizeof(int), 0);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(array_length(array), 0);
    EXPECT_EQ(array_capacity(array), 0);
    array_destroy(array);
}

TEST(ArrayTest, Append) {
    void *array = array_init(sizeof(int), 0);
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    ASSERT_EQ(array_length(array), 5);
    
    int *data = (int *) array;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(data[i], items[i]);
    }

    array_destroy(array);
}

TEST(ArrayTest, RawToArray) {
    int items[] = {1, 2, 3, 4, 5};
    int *array_from_raw = (int *)raw_to_array(items, sizeof(int), 5);

    ASSERT_EQ(array_length(array_from_raw), 5);
    
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(array_from_raw[i], items[i]);
    }

    array_destroy(array_from_raw);
}

TEST(ArrayTest, AppendAndPop) {
    void *array = array_init(sizeof(int), 0);
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

    array_destroy(array);
}

TEST(ArrayTest, Length) {
    void *array = array_init(sizeof(int), 0);
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    ASSERT_EQ(array_length(array), 5);

    array_destroy(array);
}

TEST(ArrayTest, BasicGet) {
    void *array = array_init(sizeof(int), 0);
    int items[] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    int item;
    for (int i = 0; i < 5; i++) {
        array_get(array, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    array_destroy(array);
} 

TEST(ArrayTest, Resize) {
    void *array = array_init(sizeof(int), 0);
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

    array_destroy(array);
}

TEST(ArrayTest, Copy) {
    void *array = array_init(sizeof(int), 0);
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
    array_destroy(array);
}

TEST(ArrayTest, Array2D) {
    int items1[] = {1, 2, 3, 4, 5};
    int items2[] = {6, 7, 8, 9, 10};
    int items3[] = {11, 12, 13, 14, 15};

    int **array2D = (int **)array_init(sizeof(void *), 0);

    void *array1 = raw_to_array(items1, sizeof(int), 5);
    void *array2 = raw_to_array(items2, sizeof(int), 5);
    void *array3 = raw_to_array(items3, sizeof(int), 5);

    array2D = (int **) array_append(array2D, &array1);
    array2D = (int **) array_append(array2D, &array2);
    array2D = (int **) array_append(array2D, &array3);

    ASSERT_EQ(array_length(array2D), 3);

    // Iterate over the 2D array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            int item = array2D[i][j];

            if (i == 0) {
                EXPECT_EQ(item, items1[j]);
            } else if (i == 1) {
                EXPECT_EQ(item, items2[j]);
            } else {
                EXPECT_EQ(item, items3[j]);
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        array_destroy(array2D[i]);
    }

    array_destroy(array2D);
}

TEST(ArrayTest, Floats) {
    float items[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    void *array = raw_to_array(items, sizeof(float), 5);

    ASSERT_EQ(array_length(array), 5);
    EXPECT_EQ(array_item_size(array), sizeof(float));

    float item;
    for (int i = 0; i < 5; i++) {
        array_get(array, i, &item);
        EXPECT_FLOAT_EQ(item, items[i]);
    }

    array_destroy(array);
}

TEST(ArrayTest, Chars) {
    char items[] = {'a', 'b', 'c', 'd', 'e'};
    void *array = raw_to_array(items, sizeof(char), 5);

    ASSERT_EQ(array_length(array), 5);
    EXPECT_EQ(array_item_size(array), sizeof(char));

    char item;
    for (int i = 0; i < 5; i++) {
        array_get(array, i, &item);
        EXPECT_EQ(item, items[i]);
    }

    array_destroy(array);
}


struct Point {
    int x;
    int y;
};

TEST(ArrayTest, Structs) {
    struct Point items[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    void *array = raw_to_array(items, sizeof(struct Point), 5);

    ASSERT_EQ(array_length(array), 5);
    EXPECT_EQ(array_item_size(array), sizeof(struct Point));

    struct Point item;
    for (int i = 0; i < 5; i++) {
        array_get(array, i, &item);
        EXPECT_EQ(item.x, items[i].x);
        EXPECT_EQ(item.y, items[i].y);
    }

    array_destroy(array);
}