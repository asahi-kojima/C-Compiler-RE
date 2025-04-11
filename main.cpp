#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "tokenizer.h"
#include "code-generator.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません : 引数の数=%d\n", argc);
    }

#if DEBUG
    fprintf(stderr, "Start tokenize\n");
#endif
    Token::tokenize(argv[1]);
#if DEBUG
    fprintf(stderr, "Finish Parse\n");
#endif

#if DEBUG
    fprintf(stderr, "Start Parse\n");
#endif
    ASTNode* node = Parser::expr();
#if DEBUG
    fprintf(stderr, "Finish Parse\n");
#endif

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    
#if DEBUG
    fprintf(stderr, "Start Code Genaration\n");
#endif
    codeGenerator(node);
#if DEBUG
    fprintf(stderr, "Finish Code Generation\n");
#endif

    printf("    pop rax\n");
    printf("    ret\n");
    return 0;
}