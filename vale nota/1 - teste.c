#include <stdio.h>
#include <string.h>
/*
int is_palindrome(char *str, int start, int end) {
    while (start < end) {
        if (str[start] != str[end]) {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

void find_largest_palindrome(char *str, int len, int start, int end, int *max_start, int *max_end) {
    if (start == end || is_palindrome(str, start, end)) {
        if (end - start > *max_end - *max_start) {
            *max_start = start;
            *max_end = end;
        }
    } else {
        find_largest_palindrome(str, len, start+1, end, max_start, max_end);
        find_largest_palindrome(str, len, start, end-1, max_start, max_end);
    }
}
*/
int is_palindrome(char *str, int start, int end) {
    int i;
    for(i=start;i<end;i++){
        if(str[i]!=str[end]){
            return 0;
        }
        end--;
    }
    return 1;
}

int find_largest_palindrome(char *str, int len, int start, int end) {
    if (start == end || is_palindrome(str, start, end)) {
        return end - start + 1;
    } else {
        int len1 = find_largest_palindrome(str, len, start+1, end);
        int len2 = find_largest_palindrome(str, len, start, end-1);
        return len1 > len2 ? len1 : len2;
    }
}




void print_largest_palindrome(char *str) {
    int len = strlen(str);
    int max_len = find_largest_palindrome(str, len, 0, len-1);
    for (int i = 0; i < len; i++) {
        if (is_palindrome(str, i, i + max_len - 1)) {
            for (int j = i; j < i + max_len; j++) {
                printf("%c", str[j]);
            }
            printf("\n");
            break;
        }
    }
}

int main() {
    char str[100];
    scanf("%s", str);
    print_largest_palindrome(str);
    return 0;
}
*/

int main() {
    char *str;
    int tam, max, i, j;

    str = (char*)malloc(sizeof(char));

    scanf("%s", str);

    tam = strlen(str);

    max = maiorPalindromo(str, tam, 0, tam - 1);

    for(i = 0; i < tam; i++) {
        if(palindromo(str, i, i + max - 1))
            for(j = i; j < i + max; j++)
                printf("%c", str[j]);
    }

    free(str);
    return 0;
}



void print_largest_palindrome(char *str) {
    int len = strlen(str);
    int max_len = find_largest_palindrome(str, len, 0, len-1);
    for (int i = 0; i < len; i++) {
        if (is_palindrome(str, i, i + max_len - 1)) {
            for (int j = i; j < i + max_len; j++) {
                printf("%c", str[j]);
            }
            printf("\n");
            break;
        }
    }
}

int main() {
    char str[100];
    scanf("%s", str);
    print_largest_palindrome(str);
    return 0;
}