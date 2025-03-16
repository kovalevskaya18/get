TEST(SubvectorTest, CopyAssignment) {
    subvector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    subvector<int> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}

TEST(SubvectorTest, MoveAssignment) {
    subvector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    subvector<int> vec2;
    vec2 = std::move(vec1);
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec1.size(), 0);
}

TEST(SubvectorTest, Swap) {
    subvector<int> vec1 = {1, 2, 3};
    subvector<int> vec2 = {4, 5};
    vec1.swap(vec2);
    EXPECT_EQ(vec1.size(), 2);
    EXPECT_EQ(vec1[0], 4);
    EXPECT_EQ(vec1[1], 5);
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
}

TEST(SubvectorTest, SelfAssignment) {
    subvector<int> vec = {1, 2, 3};
    vec = vec;
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(SubvectorTest, SelfMoveAssignment) {
    subvector<int> vec = {1, 2, 3};
    vec = std::move(vec);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}