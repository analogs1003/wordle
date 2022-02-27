#ifndef RULE_LIST_HPP_
#define RULE_LIST_HPP_

#include <math.h>
#include <stdio.h>
#include <string.h>

int RuleStr2Num(char *rule_string) {
    int rule_number = 0;
    for (int ii = 0; ii < 5; ii++) {
        if (rule_string[ii] == 'G') {
            rule_number += 2 * pow(3, ii);
        } else if (rule_string[ii] == 'Y') {
            rule_number += 1 * pow(3, ii);
        }
    }
    return rule_number;
}
char *RuleNum2Str(int rule_number) {
    char rule_char_list[] = {'W', 'Y', 'G'};
    static char rule_string[6] = "";
    int quotient = rule_number;
    int remainder = 0;
    for (int ii = 0; ii < 5; ii++) {
        remainder = quotient % 3;
        quotient = quotient / 3;
        rule_string[ii] = rule_char_list[remainder];
    }
    return rule_string;
}

int CalcRuleNum(const char *answer_word, const char *input_word) {
    char rule_string[6] = "WWWWW";
    char tmp_answer_word[6] = "";
    strncpy(tmp_answer_word, answer_word, 5);
    // green
    for (int ii = 0; ii < 5; ii++) {
        if (input_word[ii] == tmp_answer_word[ii]) {
            rule_string[ii] = 'G';
            tmp_answer_word[ii] = '-';  // 正解で使った文字は使用不可
        }
    }
    // yellow
    for (int ii = 0; ii < 5; ii++) {
        if (rule_string[ii] == 'G') {
            continue;
        }
        for (int jj = 0; jj < 5; jj++) {
            if (input_word[ii] == tmp_answer_word[jj]) {
                rule_string[ii] = 'Y';
                tmp_answer_word[jj] = '-';  // 正解で使った文字は使用不可
                break;
            }
        }
    }
    return RuleStr2Num(rule_string);
}

class RuleList {
   private:
    int rule_size_ = 0;
    char *rule_word_list_ = NULL;
    int *rule_number_list_ = NULL;

   public:
    RuleList(int argc, char *argv[]) {
        rule_size_ = (argc - 1) / 2;
        rule_word_list_ = new char[rule_size_ * 6];
        rule_number_list_ = new int[rule_size_];
        for (int ii = 0; ii < rule_size_; ii++) {
            strcpy(&rule_word_list_[ii * 6], argv[2 * ii + 1]);
            rule_number_list_[ii] = RuleStr2Num(argv[2 * ii + 2]);
        }
    }
    ~RuleList() {
        delete[] rule_word_list_;
        delete[] rule_number_list_;
    }
    int GetRuleSize() { return rule_size_; }
    char *GetRuleWord(int pos) { return &rule_word_list_[pos * 6]; }
    int GetRuleNum(int pos) { return rule_number_list_[pos]; }
    bool Check(char *word) {
        for (int ii = 0; ii < rule_size_; ii++) {
            if (CalcRuleNum(word, GetRuleWord(ii)) != GetRuleNum(ii)) {
                return false;
            }
        }
        return true;
    }
    void Print() {
        for (int ii = 0; ii < rule_size_; ii++) {
            printf("%s, %d\n", &rule_word_list_[ii * 6], rule_number_list_[ii]);
        }
    }
};

#endif  // RULE_LIST_HPP_
