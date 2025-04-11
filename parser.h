#pragma once
#include "common.h"
#include "tokenizer.h"

enum class ASTNodeKind
{
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_NUM,
};


//struct ASTNode;


struct ASTNode
{
    ASTNodeKind kind;
    ASTNode* lhs;
    ASTNode* rhs;
    union
    {
        struct
        {
            int value;
        } property_of_num;
        
    } property;  
};


class Parser
{
public:
    static ASTNode* expr();
    static ASTNode* mul();
    static ASTNode* unary();
    static ASTNode* primary();
};