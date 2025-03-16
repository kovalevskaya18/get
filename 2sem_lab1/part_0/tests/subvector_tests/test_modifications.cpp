TEST(SubvectorTest, PushBack) {
    subvector<int> vec;
    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.Capacity(), 1);
    EXPECT_EQ(vec[0], 1);

    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.Capacity(), 2);
    EXPECT_EQ(vec[1], 2);
}

TEST(SubvectorTest, PopBack) {
    subvector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.pop_back(), 2);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.pop_back(), 1);
    EXPECT_EQ(vec.size(), 0);
}

TEST(SubvectorTest, Resize) {
    subvector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.resize(4);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.Capacity(), 4);
}

TEST(SubvectorTest, Clear) {
    subvector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TEST(SubvectorTest, ShrinkToFit) {
    subvector<int> vec = {1, 2, 3, 4, 5};
    vec.resize(10);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.Capacity(), 5);
}