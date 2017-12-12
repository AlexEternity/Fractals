#include "rule.h"

Rule::Rule(char *left,QList<char>*right)
{
    this->left = left;
    this->right = new QList<char>(*right);
}
