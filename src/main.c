#include "defs.h"
#include "decl.h"

struct FileInfo FileInfo;

char *tokstr[] = {
    "+", "-", "*", "/", "intlit",
};

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(1);
    }

    FileInfo.line = 1;
    FileInfo.file = fopen(argv[1], "r");
    if (FileInfo.file == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    FILE *outFile = fopen("main.S", "w");
    // Create the output file
    if (outFile == NULL) {
        fprintf(stderr, "Unable to create main.S: %s\n", strerror(errno));
        exit(1);
    }

    struct Token token;
    nextToken(&token); // get the first token
    while (1) {
        expectToken(&token, T_RETURN, "return");
        struct ASTnode *tree = parse(&token, 0);
        genCode(outFile, tree);
        printf("%d\n", dumpAST(tree));
        expectToken(&token, T_SEMI, ";");

        if (token.token == T_EOF)
            break;
    }

    exit(0);
}
