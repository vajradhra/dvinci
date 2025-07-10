#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 128

// 检查单词是否包含指定字母
int contains_any(const char *word, const char *letters) {
    for (int i = 0; word[i]; i++) {
        for (int j = 0; letters[j]; j++) {
            if (tolower(word[i]) == tolower(letters[j])) {
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <letters>\n", argv[0]);
        return 1;
    }
    const char *letters = argv[1];
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (line[len-1] == '\n') line[len-1] = '\0';
        if (!contains_any(line, letters)) {
            printf("%s\n", line);
        }
    }
    return 0;
}