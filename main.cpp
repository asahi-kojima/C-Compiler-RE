#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "引数の個数が正しくありません : 引数の数=%d\n", argc);
    }

    //char *p = argv[1];

    Tokenizer tokenizer(argv[1]);

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    printf("    mov rax, %ld\n", tokenizer.expect_number());

    while (!tokenizer.at_eof())
    {
        if (tokenizer.consume_if('+'))
        {
            printf("    add rax, %ld\n", tokenizer.expect_number());
            continue;
        }
        tokenizer.expect('-');
        printf("    sub rax, %ld\n", tokenizer.expect_number());
    }
    
    printf("    ret\n");
    return 0;
}