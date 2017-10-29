#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]){
    int i = 0, j = 0;
    char* s1 = NULL;
    char* s2 = NULL;
    char ch;
    FILE *f1 = fopen(argv[1], "r");
    if (f1 == 0)
        return -1;
    while ((ch = fgetc(f1)) != '\n')
    {
        s1 = (char*)realloc(s1, (i + 1) * sizeof(char));
        s1[i++] = ch;
    }
    while ((ch = getchar()) != '\n')
    {
        s2 = (char*)realloc(s2, (j + 1) * sizeof(char));
        s2[j++] = ch;
    }
    if (j != i)
    {
	    free(s1);
	    free(s2);
        return 1;
    }
    if (strcmp(s1,s2) == 0)
    {
	    free(s1);
	    free(s2);
	    return 0;
	}
    else
    {
	    free(s1);
	    free(s2);
        return 1;
	}
}

