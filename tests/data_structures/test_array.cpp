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


TEST_F(ArrayTest, Append) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }
    
    int *data = (int *) array_data(array);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(data[i], items[i]);
    }
}

TEST_F(ArrayTest, Length) {
    int items[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        array = array_append(array, &items[i]);
    }

    ASSERT_EQ(array_length(array), 5);
}