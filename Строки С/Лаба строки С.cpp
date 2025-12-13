#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <locale>
#include "string_func.h"

int main() {
    std::setlocale(LC_ALL, "Russian");

    char input[MAX_LENGTH];
    char delimiters[MAX_LENGTH];
    char result[MAX_LENGTH * 2];

    std::cout << "Введите строку (не более " << (MAX_LENGTH - 1) << " символов): ";
    std::cin.getline(input, MAX_LENGTH);

    std::cout << "Введите символы-разделители: ";
    std::cin.getline(delimiters, MAX_LENGTH);

    if (std::strlen(input) == 0) {
        std::cout << "Ошибка: строка пуста!" << std::endl;
        return 1;
    }

    if (std::strlen(delimiters) == 0) {
        std::cout << "Ошибка: не указаны разделители!" << std::endl;
        return 1;
    }

    char words[MAX_LENGTH][MAX_LENGTH];
    bool isDigitWordFlags[MAX_LENGTH];
    char delimitersBefore[MAX_LENGTH][MAX_LENGTH];
    char delimitersAfter[MAX_LENGTH][MAX_LENGTH];
    int32_t wordCount = 0;

    extractWords(input, delimiters, words, wordCount, isDigitWordFlags, delimitersBefore, delimitersAfter);

    if (wordCount == 0) {
        std::cout << "Ошибка: в строке нет слов!" << std::endl;
        return 1;
    }

    std::cout << "\nИсходная строка: '" << input << "'" << std::endl;

    bool hasDigitWords = false;
    for (int32_t i = 0; i < wordCount; i++) {
        if (isDigitWordFlags[i] && words[i][0] != '\0') {
            hasDigitWords = true;
            break;
        }
    }

    if (!hasDigitWords) {
        std::cout << "\nВ строке нет слов, состоящих только из цифр!" << std::endl;
        std::cout << "Результат без изменений: '" << input << "'" << std::endl;
        return 0;
    }

    sortDigitWords(words, isDigitWordFlags, delimitersBefore, delimitersAfter, wordCount);

    buildString(result, words, delimitersBefore, delimitersAfter, wordCount);

    std::cout << "\nРезультат: '" << result << "'" << std::endl;

    return 0;
}