#ifndef RULE_H
#define RULE_H
#include<QList>


class Rule
{
public:
    char *left;
    QList<char> *right;
    Rule(char *left, QList<char>*right);
};

#endif // RULE_H
