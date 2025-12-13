#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdint>
#include "string_func.h"

bool isDelimiter(char c, const char* delimiters) {
    for (size_t i = 0; delimiters[i] != '\0'; i++) {
        if (c == delimiters[i]) {
            return true;
        }
    }
    return false;
}

bool isDigitWord(const char* word) {
    if (word[0] == '\0') {
        return false;
    }

    for (size_t i = 0; word[i] != '\0'; i++) {
        if (word[i] < '0' || word[i] > '9') {
            return false;
        }
    }
    return true;
}

int32_t sumOfDigits(const char* word) {
    int32_t sum = 0;
    for (size_t i = 0; word[i] != '\0'; i++) {
        sum += word[i] - '0';
    }
    return sum;
}

void extractWords(const char* str, const char* delimiters, char words[][MAX_LENGTH],
    int32_t& wordCount, bool isDigitWordFlags[], char delimitersBefore[][MAX_LENGTH],
    char delimitersAfter[][MAX_LENGTH]) {

    wordCount = 0;
    size_t len = std::strlen(str);
    size_t i = 0;

    // Инициализируем массивы
    for (int32_t k = 0; k < MAX_LENGTH; k++) {
        words[k][0] = '\0';
        delimitersBefore[k][0] = '\0';
        delimitersAfter[k][0] = '\0';
        isDigitWordFlags[k] = false;
    }

    // Обрабатываем начальные разделители
    if (len > 0) {
        size_t j = 0;
        while (i < len && isDelimiter(str[i], delimiters)) {
            if (j < MAX_LENGTH - 1) {
                delimitersBefore[wordCount][j++] = str[i];
            }
            i++;
        }
        delimitersBefore[wordCount][j] = '\0';
    }

    // Основной цикл извлечения слов
    while (i < len) {
        // Извлекаем слово
        size_t j = 0;
        while (i < len && !isDelimiter(str[i], delimiters)) {
            if (j < MAX_LENGTH - 1) {
                words[wordCount][j++] = str[i];
            }
            i++;
        }
        words[wordCount][j] = '\0';

        // Устанавливаем флаг для слова
        if (j > 0) {
            isDigitWordFlags[wordCount] = isDigitWord(words[wordCount]);
        }

        // Извлекаем разделители после слова
        j = 0;
        while (i < len && isDelimiter(str[i], delimiters)) {
            if (j < MAX_LENGTH - 1) {
                delimitersAfter[wordCount][j++] = str[i];
            }
            i++;
        }
        delimitersAfter[wordCount][j] = '\0';

        // Если слово не пустое, увеличиваем счетчик
        if (words[wordCount][0] != '\0') {
            wordCount++;
        }

        // Подготавливаем разделители для следующего слова
        if (i < len) {
            j = 0;
            while (i < len && isDelimiter(str[i], delimiters)) {
                if (j < MAX_LENGTH - 1) {
                    delimitersBefore[wordCount][j++] = str[i];
                }
                i++;
            }
            delimitersBefore[wordCount][j] = '\0';
        }
    }
}

void sortDigitWords(char words[][MAX_LENGTH], bool isDigitWordFlags[],
    char delimitersBefore[][MAX_LENGTH], char delimitersAfter[][MAX_LENGTH],
    int32_t wordCount) {

    if (wordCount <= 1) return;

    // Создаем массив индексов цифровых слов
    int32_t digitIndices[MAX_LENGTH];
    int32_t digitCount = 0;

    // Находим все цифровые слова
    for (int32_t i = 0; i < wordCount; i++) {
        if (isDigitWordFlags[i] && words[i][0] != '\0') {
            digitIndices[digitCount++] = i;
        }
    }

    if (digitCount <= 1) return;

    // Пузырьковая сортировка цифровых слов по сумме цифр (по убыванию)
    for (int32_t i = 0; i < digitCount - 1; i++) {
        for (int32_t j = 0; j < digitCount - i - 1; j++) {
            int32_t idx1 = digitIndices[j];
            int32_t idx2 = digitIndices[j + 1];

            int32_t sum1 = sumOfDigits(words[idx1]);
            int32_t sum2 = sumOfDigits(words[idx2]);

            if (sum1 < sum2) {
                std::swap(digitIndices[j], digitIndices[j + 1]);
            }
        }
    }

    // Восстанавливаем позиции цифровых слов
    char tempWords[MAX_LENGTH][MAX_LENGTH];
    char tempDelimitersBefore[MAX_LENGTH][MAX_LENGTH];
    char tempDelimitersAfter[MAX_LENGTH][MAX_LENGTH];
    bool tempFlags[MAX_LENGTH];

    // Копируем все в временные массивы
    for (int32_t i = 0; i < wordCount; i++) {
        std::strcpy(tempWords[i], words[i]);
        std::strcpy(tempDelimitersBefore[i], delimitersBefore[i]);
        std::strcpy(tempDelimitersAfter[i], delimitersAfter[i]);
        tempFlags[i] = isDigitWordFlags[i];
    }

    // Проходим по всем словам и для цифровых слов используем отсортированный порядок
    int32_t sortedDigitIdx = 0;
    for (int32_t i = 0; i < wordCount; i++) {
        if (tempFlags[i]) {
            // Это цифровое слово - берем следующее из отсортированного списка
            int32_t sortedIdx = digitIndices[sortedDigitIdx];
            std::strcpy(words[i], tempWords[sortedIdx]);
            std::strcpy(delimitersBefore[i], tempDelimitersBefore[sortedIdx]);
            std::strcpy(delimitersAfter[i], tempDelimitersAfter[sortedIdx]);
            sortedDigitIdx++;
        }
        else {
            std::strcpy(words[i], tempWords[i]);
            std::strcpy(delimitersBefore[i], tempDelimitersBefore[i]);
            std::strcpy(delimitersAfter[i], tempDelimitersAfter[i]);
        }
    }
}

void buildString(char* result, char words[][MAX_LENGTH],
    char delimitersBefore[][MAX_LENGTH], char delimitersAfter[][MAX_LENGTH],
    int32_t wordCount) {

    result[0] = '\0';

    for (int32_t i = 0; i < wordCount; i++) {
        std::strcat(result, delimitersBefore[i]);
        std::strcat(result, words[i]);
        std::strcat(result, delimitersAfter[i]);
    }
}