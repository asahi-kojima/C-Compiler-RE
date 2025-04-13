#include "code-generator.h"


using Node = ASTNode;
using NodeKind = ASTNodeKind;

void codeGenerator(Node* node)
{
    if (node->kind == NodeKind::ND_NUM)
    {
        printf("    push %d\n", node->property.property_of_num.value);
        return;
    }


    codeGenerator(node->lhs);
    codeGenerator(node->rhs);

    printf("    pop rdi\n");
    printf("    pop rax\n");

    switch (node->kind)
    {
    case NodeKind::ND_ADD:
        printf("    add rax, rdi\n");
        break;
    case NodeKind::ND_SUB:
        printf("    sub rax, rdi\n");
        break;
    case NodeKind::ND_MUL:
        printf("    imul rax, rdi\n");
        break;
    case NodeKind::ND_DIV:
        printf("    cqo\n");
        printf("    idiv rdi\n");
        break;
    
    case NodeKind::ND_EQ:
        printf("    cmp rax, rdi\n");
        printf("    sete al\n");
        printf("    movzb rax, al\n");
        break;
    case NodeKind::ND_NE:
        printf("    cmp rax, rdi\n");
        printf("    setne al\n");
        printf("    movzb rax, al\n");
        break;
    case NodeKind::ND_LT:
        printf("    cmp rax, rdi\n");
        printf("    setl al\n");
        printf("    movzb rax, al\n");
        break;
    case NodeKind::ND_LE:
        printf("    cmp rax, rdi\n");
        printf("    setle al\n");
        printf("    movzb rax, al\n");
        break;
        
    default:
        fprintf(stderr, "can't reach here\n");
        exit(1);
    }

    printf("    push rax\n");
}