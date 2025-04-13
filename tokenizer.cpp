#include "tokenizer.h"


void print_error_info(char* input_string, char* location, const char* fmt, ...)
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

void print_error_info(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

bool Token::consume_if(const char *op)
{
    if (current_token->kind != TokenKind::TK_RESERVED 
        || current_token->property.property_of_reserved.strlen != strlen(op)
        || memcmp(current_token->property.property_of_reserved.str, op, strlen(op)))   
    {
        return false;
    }

    current_token = current_token->next;
    return true;
}

bool Token::consume_if(const char op)
{
    if (current_token->kind != TokenKind::TK_RESERVED || current_token->property.property_of_reserved.str[0] != op)   
    {
        return false;
    }

    current_token = current_token->next;
    return true;
}

void Token::expect(const char op)
{
    if (current_token->kind != TokenKind::TK_RESERVED || current_token->property.property_of_reserved.str[0] != op)
    {
        print_error_info("%cではありません", op);
    }

    current_token = current_token->next;
}

int Token::expect_number()
{
    if (current_token->kind != TokenKind::TK_NUM)
    {
        print_error_info("数ではありません");
    }

    int val = current_token->property.property_of_num.val;
    current_token = current_token->next;
    return val;
}

bool Token::at_eof()
{
    return current_token->kind == TokenKind::TK_EOF;
}




Token* create_new_token(TokenKind kind, Token* current_token, char* str, int strlen)
{
    Token* new_token = new Token;
    new_token->kind = kind;
    new_token->property.property_of_reserved.str = str;
    new_token->property.property_of_reserved.strlen = strlen;
    current_token->next = new_token;

    return new_token;
}

/// @brief 文字列pが文字列qから始まっているかを確認する。qは終端文字列を持っていることが前提となっているので注意。
/// @param p 
/// @param q 
/// @return 
bool isStartFrom(const char* p, const char* q)  
{
    //fprintf(stderr, "len(p) = %d, len(q) = %d\n", strlen(p), strlen(q));
    return memcmp(p, q, strlen(q)) == 0;
}

void Token::tokenize(char* input_string)
{
    Token head;
    head.next = nullptr;
    Token* current_token_tmp = &head; 

    char* p = input_string;

    while(*p)
    {
        if (isspace(*p))
        {
            p++;
            continue;
        }
        
        
        if (isStartFrom(p, "==") || isStartFrom(p, "!=") || isStartFrom(p, ">=") || isStartFrom(p, "<="))
        {
#if DEBUG
            fprintf(stderr, "_%c%c_",*p, *(p + 1));
#endif
            current_token_tmp = create_new_token(TokenKind::TK_RESERVED, current_token_tmp, p, 2);
            p += 2;
            continue;
        }

        if (strchr("+-*/()<>=", *p))
        {
#if DEBUG
            fprintf(stderr, "_%c_",*p);
#endif
            current_token_tmp = create_new_token(TokenKind::TK_RESERVED, current_token_tmp, p, 1);
            p++;
            continue;
        }


        if (isdigit(*p))
        {
#if DEBUG
            fprintf(stderr, "_%c_",*p);
#endif
            current_token_tmp = create_new_token(TokenKind::TK_NUM, current_token_tmp, p, 0);
            current_token_tmp->property.property_of_num.val = strtol(p, &p, 10);
            continue;
        }

        print_error_info(input_string, p, "トークナイズ出来ません : %c\n", *p);
    }

    create_new_token(TokenKind::TK_EOF, current_token_tmp, p, 0);

#if DEBUG
    fprintf(stderr, "\n");
#endif
    current_token = head.next;
}