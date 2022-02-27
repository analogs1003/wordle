#include "RuleList.hpp"

int main(int argc, char *argv[]) {
    char *answer = argv[1];
    char *input = argv[2];

    int rule_number = CalcRuleNum(answer, input);
    printf("%03d %s\n", rule_number, RuleNum2Str(rule_number));
    return 0;
}
