#include "defs.h"
#include "decl.h"

int Line = 0;
FILE *Infile;

char *tokstr[] = {
    "+", "-", "*", "/", "intlit",
};

static void scanfile() {
  struct token T;

  while (scan(&T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == T_INTLIT)
      printf(", value %d", T.value);
    printf("\n");
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(1);
  }

  Infile = fopen(argv[1], "r");
  if (Infile == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  scanfile();
  exit(0);
}
