#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern FILE *yyin;
int yyparse(void);
extern ASTNode *root;

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./parser <input-file>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }

    if (yyparse() == 0) {
        printf("Parsing successful.\n");

        if (root != NULL) {
            printf("AST created successfully.\n");

            printf("\n=== AST OUTPUT ===\n");
            print_ast(root, 0);

            printf("\n=== PRETTY PRINT OUTPUT ===\n");
            print_pretty(root, 0);
        }
    } else {
        printf("Parsing failed.\n");
    }

    fclose(yyin);
    return 0;
}