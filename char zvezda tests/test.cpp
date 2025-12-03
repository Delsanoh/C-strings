#include "pch.h"

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdint>
#include "../Строки С/string_func.cpp"

TEST(StringUtilsTest, IsDelimiterTest) {
    const char* delimiters = " ,.!?";

    EXPECT_TRUE(isDelimiter(' ', delimiters));
    EXPECT_TRUE(isDelimiter(',', delimiters));
    EXPECT_TRUE(isDelimiter('.', delimiters));
    EXPECT_TRUE(isDelimiter('!', delimiters));
    EXPECT_TRUE(isDelimiter('?', delimiters));

    EXPECT_FALSE(isDelimiter('a', delimiters));
    EXPECT_FALSE(isDelimiter('1', delimiters));
    EXPECT_FALSE(isDelimiter('@', delimiters));
}

TEST(StringUtilsTest, IsDigitWordTest) {
    EXPECT_TRUE(isDigitWord("123"));
    EXPECT_TRUE(isDigitWord("0"));
    EXPECT_TRUE(isDigitWord("999"));

    EXPECT_FALSE(isDigitWord(""));
    EXPECT_FALSE(isDigitWord("12a3"));
    EXPECT_FALSE(isDigitWord("abc"));
    EXPECT_FALSE(isDigitWord("12.3"));
    EXPECT_FALSE(isDigitWord(" 123"));
    EXPECT_FALSE(isDigitWord("123 "));
}

TEST(StringUtilsTest, SumOfDigitsTest) {
    EXPECT_EQ(sumOfDigits("123"), 6);    
    EXPECT_EQ(sumOfDigits("0"), 0);        
    EXPECT_EQ(sumOfDigits("999"), 27);  
    EXPECT_EQ(sumOfDigits(""), 0);
    EXPECT_EQ(sumOfDigits("5"), 5);       
    EXPECT_EQ(sumOfDigits("1111"), 4);    
}

TEST(StringUtilsTest, ExtractWordsWithDigitsTest) {
    const char* str = "test 123 abc 456";
    const char* delimiters = " ";

    char words[MAX_LENGTH][MAX_LENGTH];
    bool isDigitWordFlags[MAX_LENGTH];
    char delimitersBefore[MAX_LENGTH][MAX_LENGTH];
    char delimitersAfter[MAX_LENGTH][MAX_LENGTH];
    int32_t wordCount = 0;

    extractWords(str, delimiters, words, wordCount, isDigitWordFlags,
        delimitersBefore, delimitersAfter);

    EXPECT_EQ(wordCount, 4);
    EXPECT_STREQ(words[0], "test");
    EXPECT_STREQ(words[1], "123");
    EXPECT_STREQ(words[2], "abc");
    EXPECT_STREQ(words[3], "456");

    EXPECT_FALSE(isDigitWordFlags[0]);
    EXPECT_TRUE(isDigitWordFlags[1]);
    EXPECT_FALSE(isDigitWordFlags[2]); 
    EXPECT_TRUE(isDigitWordFlags[3]);
}
TEST(StringUtilsTest, ExtractWordsMultipleDelimitersTest) {
    const char* str = "hello, world! test?";
    const char* delimiters = " ,.!?";

    char words[MAX_LENGTH][MAX_LENGTH];
    bool isDigitWordFlags[MAX_LENGTH];
    char delimitersBefore[MAX_LENGTH][MAX_LENGTH];
    char delimitersAfter[MAX_LENGTH][MAX_LENGTH];
    int32_t wordCount = 0;

    extractWords(str, delimiters, words, wordCount, isDigitWordFlags,
        delimitersBefore, delimitersAfter);

    EXPECT_EQ(wordCount, 3);
    EXPECT_STREQ(words[0], "hello");
    EXPECT_STREQ(words[1], "world");
    EXPECT_STREQ(words[2], "test");

    EXPECT_STREQ(delimitersAfter[0], ", ");
    EXPECT_STREQ(delimitersAfter[1], "! ");
    EXPECT_STREQ(delimitersAfter[2], "?");
}

TEST(StringUtilsTest, SortDigitWordsTest) {
    char words[][MAX_LENGTH] = { "hello", "123", "abc", "456", "test" };
    bool isDigitWordFlags[] = { false, true, false, true, false };
    char delimitersBefore[][MAX_LENGTH] = { "", " ", " ", " ", " " };
    char delimitersAfter[][MAX_LENGTH] = { " ", " ", " ", " ", "" };
    int32_t wordCount = 5;
    sortDigitWords(words, isDigitWordFlags, delimitersBefore, delimitersAfter, wordCount);

    EXPECT_STREQ(words[0], "hello"); 
    EXPECT_STREQ(words[1], "456");    
    EXPECT_STREQ(words[2], "abc");    
    EXPECT_STREQ(words[3], "123");    
    EXPECT_STREQ(words[4], "test");  
}
