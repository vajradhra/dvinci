#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100000
#define MAX_LINE 128

typedef struct {
    char *word;
    int count;
} WordCount;

int is_alpha_only(const char *w) {
    for (int i = 0; w[i]; i++) {
        if (!isalpha(w[i])) return 0;
    }
    return 1;
}

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <word_length>\n", argv[0]);
        return 1;
    }
    int want_len = atoi(argv[1]);
    char line[MAX_LINE];
    char *words[MAX_WORDS];
    int word_num = 0;

    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (line[len-1] == '\n') line[len-1] = '\0';
        if ((int)strlen(line) == want_len && is_alpha_only(line)) {
            // 去重
            int found = 0;
            for (int i = 0; i < word_num; i++) {
                if (strcmp(words[i], line) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                words[word_num] = strdup(line);
                word_num++;
            }
        }
    }
    for (int i = 0; i < word_num; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }
    return 0;
}