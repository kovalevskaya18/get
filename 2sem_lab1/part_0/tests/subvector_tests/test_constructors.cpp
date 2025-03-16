TEST(SubvectorTest, DefaultConstructor) {
    subvector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.Capacity(), 0);
}

TEST(SubvectorTest, ConstructorWithCountAndValue) {
    subvector<int> vec(5U, 10);
    ASSERT_EQ(vec.size(), 5);
    for (unsigned int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 10);
    }
}

TEST(SubvectorTest, ConstructorWithCountAndDefaultValue) {
    subvector<int> vec(5);
    ASSERT_EQ(vec.size(), 5);
    for (unsigned int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 0);
    }
}

TEST(SubvectorTest, InitializerListConstructor) {
    subvector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.Capacity(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(SubvectorTest, CopyConstructor) {
    subvector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    subvector<int> vec2 = vec1;
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}

TEST(SubvectorTest, MoveConstructor) {
    subvector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    subvector<int> vec2 = std::move(vec1);
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec1.size(), 0);
}