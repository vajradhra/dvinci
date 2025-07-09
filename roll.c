#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PINK    "\033[38;5;210m"
#define RESET   "\033[0m"
#define MAX_WORDS 1000000
#define WORD_LEN 128

int find_word(char **wordlist, int wordcount, const char *word) {
    for (int i = 0; i < wordcount; ++i) {
        if (strcmp(wordlist[i], word) == 0) return 1;
    }
    return 0;
}

// 判断word是否包含substr所有字母（不区分大小写，顺序不限，且数量要够）
int contains_all_letters_case_insensitive(const char *word, const char *substr) {
    int need[256] = {0}, have[256] = {0};
    for (int i = 0; substr[i]; ++i) {
        need[(unsigned char)tolower(substr[i])]++;
    }
    for (int i = 0; word[i]; ++i) {
        have[(unsigned char)tolower(word[i])]++;
    }
    for (int i = 0; i < 256; ++i) {
        if (need[i] > have[i]) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(PINK"usage: %s <letter> *.txt\n"RESET, argv[0]);
        return 1;
    }
    const char *substr = argv[1];
    const char *filepath = argv[2];
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror("cannot open");
        return 1;
    }
    char line[4096];
    while (fgets(line, sizeof(line), fp)) {
        char *saveptr;
        char *token = strtok_r(line, " \t\r\n,.;:!?()[]{}<>\"'", &saveptr);
        while (token) {
            if (contains_all_letters_case_insensitive(token, substr)) {
                printf(PINK "%s" RESET "\n", token);
            }
            token = strtok_r(NULL, " \t\r\n,.;:!?()[]{}<>\"'", &saveptr);
        }
    }
    fclose(fp);
    return 0;
}