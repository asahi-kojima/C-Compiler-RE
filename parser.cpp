#include "parser.h"


using ASTNode = ASTNode;
using ASTNodeKind = ASTNodeKind;
ASTNode* create_new_node(ASTNodeKind kind, ASTNode* lhs, ASTNode* rhs)
{
    ASTNode* node = reinterpret_cast<ASTNode*>(calloc(1, sizeof(ASTNode)));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

ASTNode* create_new_node_num(int val)
{
    ASTNode* node = reinterpret_cast<ASTNode*>(calloc(1, sizeof(ASTNode)));
    node->kind = ASTNodeKind::ND_NUM;
    node->property.property_of_num.value = val;
    return node;
}

ASTNode* Parser::expr()
{
    return equality();
}

ASTNode* Parser::equality()
{
    ASTNode* node = relational();
    
    while(true)
    {
        if (Token::consume_if("=="))
        {
            node = create_new_node(ASTNodeKind::ND_EQ, node, relational());
        }
        else if (Token::consume_if("!="))
        {
            node = create_new_node(ASTNodeKind::ND_NE, node, relational());
        }
        else
        {
            return node;
        }
    }
}


ASTNode* Parser::relational()
{
    ASTNode* node = add();
    
    while(true)
    {
        if (Token::consume_if("<"))
        {
            node = create_new_node(ASTNodeKind::ND_LT, node, add());
        }
        else if (Token::consume_if("<="))
        {
            node = create_new_node(ASTNodeKind::ND_LE, node, add());
        }
        else if (Token::consume_if(">"))
        {
            node = create_new_node(ASTNodeKind::ND_LT, add(),node);
        }
        else if (Token::consume_if(">="))
        {
            node = create_new_node(ASTNodeKind::ND_LE, add(), node);
        }
        else
        {
            return node;
        }
    }
}

ASTNode* Parser::add()
{
    ASTNode* node = mul();
    
    while(true)
    {
        if (Token::consume_if("+"))
        {
            node = create_new_node(ASTNodeKind::ND_ADD, node, mul());
        }
        else if (Token::consume_if("-"))
        {
            node = create_new_node(ASTNodeKind::ND_SUB, node, mul());
        }
        else
        {
            return node;
        }
    }
}


ASTNode* Parser::mul()
{
    ASTNode* node = unary();
    
    while(true)
    {
        if (Token::consume_if('*'))
        {
            node = create_new_node(ASTNodeKind::ND_MUL, node, unary());
        }
        else if (Token::consume_if('/'))
        {
            node = create_new_node(ASTNodeKind::ND_DIV, node, unary());
        }
        else
        {
            return node;
        }
    }
}

ASTNode* Parser::unary()
{
    if (Token::consume_if('+'))
    {
        return primary();
    }
    
    if (Token::consume_if('-'))
    {
        return create_new_node(ASTNodeKind::ND_SUB, create_new_node_num(0),primary());
    }

    return primary();
}

ASTNode* Parser::primary()
{
    if (Token::consume_if('('))
    {
        ASTNode* node = expr();
        Token::expect(')');
        return node;
    }
    
    return create_new_node_num(Token::expect_number());
}