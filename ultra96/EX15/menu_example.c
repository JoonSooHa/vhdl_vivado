#include <stdio.h>

int main()
{
    char c;
    char str[100];

    while(1) {
        printf("==== Menu Option ====\n\r");
        printf("a. first menu\n\r");
        printf("b. second menu\n\r");
        printf("s. enter string\n\r");
        printf("x. finish\n\r");
        printf("Select Menu : ");
        c = getchar();

        printf("==> Selected Menu : %c\n\r", c);

        if ((c != 'a') && (c != 'b') && (c != 's') && (c != 'x')) {
            printf("WRONG COMMAND\n\r");
        }

        if (c == 's') {
            printf("enter string : ");
            scanf("%s", str);
            getchar();
            printf("\nstring is %s\n\r", str);
        }

        if (c == 'x') {
            break;
        }
    }

    printf("program finished\n\r");
    return 0;
}
