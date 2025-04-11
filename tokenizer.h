#pragma once
#include "common.h"

enum class TokenKind
{
    TK_RESERVED,
    TK_NUM,
    TK_EOF,
};



struct Token
{
    TokenKind kind;
    Token* next;
    
    union
    {
        struct {int val;} property_of_num;
        struct {char* str; int strlen;} property_of_string;
    } property;


    static bool consume_if(const char op);

    static void expect(const char op);

    static int expect_number();

    static bool at_eof();

    static void tokenize(char* input_string);
    static inline Token* current_token = reinterpret_cast<Token*>(0x01234);
};
