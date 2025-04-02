#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <map>
#include "common.h"

struct Token
{
    TokenKind kind;
    Token* next;
    
    union
    {
        struct {int val;} property_of_num;
        struct {char* str; int strlen;} property_of_string;
    } property;
};