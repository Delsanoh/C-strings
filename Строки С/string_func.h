#ifndef STRING_FUNC_H
#define STRING_FUNC_H

#include <cstdint>

const int MAX_LENGTH = 301;

bool isDelimiter(char c, const char* delimiters);
bool isDigitWord(const char* word);
int32_t sumOfDigits(const char* word);
void extractWords(const char* str, const char* delimiters, char words[][MAX_LENGTH],
    int32_t& wordCount, bool isDigitWordFlags[], char delimitersBefore[][MAX_LENGTH],
    char delimitersAfter[][MAX_LENGTH]);
void sortDigitWords(char words[][MAX_LENGTH], bool isDigitWordFlags[],
    char delimitersBefore[][MAX_LENGTH], char delimitersAfter[][MAX_LENGTH],
    int32_t wordCount);
void buildString(char* result, char words[][MAX_LENGTH],
    char delimitersBefore[][MAX_LENGTH], char delimitersAfter[][MAX_LENGTH],
    int32_t wordCount);

#endif 