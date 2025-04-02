#pragma once

using u8 = unsigned char;
using s8 = char;

using u32 = unsigned int;
using s32 = int;

using f32 = float;
using f64 = double;


enum class TokenKind
{
    TK_RESERVED,
    TK_NUM,
    TK_EOF,
};

struct Token;

class Tokenizer
{
public:
    Tokenizer(char* input_string)
    : input_string(input_string)
    , current_token(nullptr)
    {
       current_token = tokenize();
    }

    bool consume_if(const char op);

    void expect(const char op);

    int expect_number();

    bool at_eof();
    
private:
    Token* tokenize();
    void print_error_info(const char* fmt, ...);
    void print_error_info(char* location, const char* fmt, ...);
    void print_tokenized_result();

    char* input_string;
    Token* current_token;
};