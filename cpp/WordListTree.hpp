#ifndef WORD_LIST_TREE_HPP_
#define WORD_LIST_TREE_HPP_

#include <stdio.h>

#include "RuleList.hpp"
#include "WordList.hpp"
class WordListTree;
WordListTree *GetMaxEntropy(WordList *all_word_list, WordList *hidden_word_list,
                            int max_level, int level);

class WordListTree {
   private:
    char *word_;
    // word_list = NULL when separating word_list_tree
    // word_list_tree = NULL when don't separating word_list_tree
    WordList *word_list_[273];  // 3*3*3*3*3
    WordListTree *word_list_tree_[273];

   public:
    WordListTree(char *word, WordList *word_list) {
        word_ = word;
        // init
        int word_size = word_list->GetWordSize();
        for (int ii = 0; ii < 273; ii++) {
            word_list_[ii] = new WordList(word_size);
            word_list_tree_[ii] = NULL;
        }
        // separate word_list
        for (int ii = 0; ii < word_size; ii++) {
            char *tmp_word = word_list->GetWord(ii);
            int rule_number = CalcRuleNum(tmp_word, word_);
            word_list_[rule_number]->SetWord(tmp_word);
        }
    }
    ~WordListTree() {
        for (int ii = 0; ii < 273; ii++) {
            delete word_list_[ii];
            delete word_list_tree_[ii];
        }
    }
    char *GetWord() { return word_; }
    int CalcSum() {
        int sum = 0;
        for (int ii = 0; ii < 273; ii++) {
            if (word_list_[ii] != NULL) {
                sum += word_list_[ii]->GetWordSize();
            } else {
                sum += word_list_tree_[ii]->CalcSum();
            }
        }
        return sum;
    }
    double CalcEntropy(int sum) {
        double entropy = 0.0;
        for (int ii = 0; ii < 273; ii++) {
            if (word_list_[ii] != NULL) {
                if (word_list_[ii]->GetWordSize() != 0) {
                    double prob = (double)word_list_[ii]->GetWordSize() / sum;
                    entropy -= prob * log(prob);
                }
            } else {
                entropy += word_list_tree_[ii]->CalcEntropy(sum);
            }
        }
        return entropy;
    }
    // create subtree to max_level
    void CreateSubTree(WordList *all_wl, int max_level, int level) {
        for (int ii = 0; ii < 273; ii++) {
            int word_size = word_list_[ii]->GetWordSize();
            // don't create subtree when word_size = 0 or 1
            if (word_size == 0 || word_size == 1) {
                continue;
            }
            // create subtree using max_entropy
            word_list_tree_[ii] =
                GetMaxEntropy(all_wl, word_list_[ii], max_level, level + 1);
            // delete word_list when separating subtree
            delete word_list_[ii];
            word_list_[ii] = NULL;
        }
    }
    int GetMaxWordSize() {
        int max_word_size = 0;
        int word_size = 0;
        for (int ii = 0; ii < 273; ii++) {
            if (word_list_[ii] != NULL) {
                word_size = word_list_[ii]->GetWordSize();
            } else {
                word_size = word_list_tree_[ii]->GetMaxWordSize();
            }
            if (word_size > max_word_size) {
                max_word_size = word_size;
            }
        }
        return max_word_size;
    }
    void PrintJson() {
        printf("{");
        printf("\"word\": \"%s\", ", GetWord());
        printf("\"tree\": [");
        bool has_element = false;
        for (int ii = 0; ii < 273; ii++) {
            if (word_list_[ii] != NULL) {
                int word_size = word_list_[ii]->GetWordSize();
                if (word_size != 0) {
                    if (has_element) {
                        printf(", ");
                    }
                    printf("{\"rule_string\": \"%s\", ", RuleNum2Str(ii));
                    printf("\"word_size\": %d, ", word_size);
                    printf("\"word_list\": [");
                    bool has_word = false;
                    for (int jj = 0; jj < word_size; jj++) {
                        if (has_word) {
                            printf(", ");
                        }
                        printf("\"%s\"", word_list_[ii]->GetWord(jj));
                        has_word = true;
                    }
                    printf("]}");
                    has_element = true;
                }
            } else {
                int word_size = word_list_tree_[ii]->CalcSum();
                if (has_element) {
                    printf(", ");
                }
                printf("{\"rule_string\": \"%s\", ", RuleNum2Str(ii));
                printf("\"word_size\": %d, ", word_size);
                printf("\"tree\": ");
                word_list_tree_[ii]->PrintJson();
                printf("}");
                has_element = true;
            }
        }
        printf("]");
        printf("}\n");
    }
};

#endif  // WORD_LIST_TREE_HPP_
