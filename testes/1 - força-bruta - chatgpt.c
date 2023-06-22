#include <stdio.h>
#include <string.h>

/*/
int isPalindromo(char str[], int start, int end) {
    if (start >= end) 
        return 1;

    if (str[start] != str[end]) {
        return 0;
    }

    return isPalindromo(str, start + 1, end - 1);
}
*/

int isPalindromo(char *string, int ini, int fim){
    if(ini >= fim)
        return 1;
    if(string[ini] != string[fim])
        return 0;
    return isPalindromo(string, ini + 1, fim - 1);
}

void findLargestPalindromoRecursive(char str[], int start, int end, int* maxLength, int* maxStart) {
    if (start >= end) {
        return 0;
    }

    if (isPalindromo(str, start, end)) {
        int currentLength = end - start + 1;
        if (currentLength > *maxLength) {
            *maxLength = currentLength;
            *maxStart = start;
        }
    }

    findLargestPalindromoRecursive(str, start + 1, end, maxLength, maxStart);
    findLargestPalindromoRecursive(str, start, end - 1, maxLength, maxStart);
}

void findLargestPalindromo(char str[]) {
    int len = strlen(str);
    int maxLength = 1;
    int maxStart = 0;

    findLargestPalindromoRecursive(str, 0, len - 1, &maxLength, &maxStart);

    printf("Maior palindromo: ");
    for (int i = maxStart; i < maxStart + maxLength; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int main() {
    char str[100];

    printf("Digite uma string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    findLargestPalindromo(str);

    return 0;
}
