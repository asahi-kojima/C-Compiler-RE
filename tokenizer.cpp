#include "tokenizer.h"




bool Tokenizer::consume_if(const char op)
{
    if (current_token->kind != TokenKind::TK_RESERVED || current_token->property.property_of_string.str[0] != op)   
    {
        return false;
    }

    current_token = current_token->next;
    return true;
}

void Tokenizer::expect(const char op)
{
    if (current_token->kind != TokenKind::TK_RESERVED || current_token->property.property_of_string.str[0] != op)
    {
        print_error_info("%cではありません", op);
    }

    current_token = current_token->next;
}

int Tokenizer::expect_number()
{
    if (current_token->kind != TokenKind::TK_NUM)
    {
        print_error_info("数ではありません");
    }

    int val = current_token->property.property_of_num.val;
    current_token = current_token->next;
    return val;
}

bool Tokenizer::at_eof()
{
    return current_token->kind == TokenKind::TK_EOF;
}

void Tokenizer::print_error_info(char* location, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    const int position = location - input_string;
    fprintf(stderr, "%s\n", input_string);
    fprintf(stderr, "%*s", position, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void Tokenizer::print_error_info(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}


Token* create_new_token(TokenKind kind, Token* current_token, char* str, int strlen)
{
    Token* new_token = new Token;
    new_token->kind = kind;
    new_token->property.property_of_string.str = str;
    new_token->property.property_of_string.strlen = strlen;
    current_token->next = new_token;

    return new_token;
}

Token* Tokenizer::tokenize()
{
    Token head;
    head.next = nullptr;
    Token* current_token = &head; 

    char* p = input_string;

    while(*p)
    {
        if (isspace(*p))
        {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-')
        {
            current_token = create_new_token(TokenKind::TK_RESERVED, current_token, p, 1);
            p++;
            continue;
        }

        if (isdigit(*p))
        {
            current_token = create_new_token(TokenKind::TK_NUM, current_token, p, 0);
            current_token->property.property_of_num.val = strtol(p, &p, 10);
            continue;
        }

        print_error_info(p, "トークナイズ出来ません : %c\n", *p);
    }

    create_new_token(TokenKind::TK_EOF, current_token, p, 0);

    return head.next;
}