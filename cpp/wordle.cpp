#include <math.h>
#include <stdio.h>
#include <string.h>

#include "RuleList.hpp"
#include "WordList.hpp"
#include "WordListTree.hpp"

class WordList;
class WordListTree;

// select WordListTree using max entropy
WordListTree *GetMaxEntropy(WordList *all_word_list, WordList *hidden_word_list,
                            int max_level, int level) {
    double max_entropy = 0.0;
    WordListTree *max_wlt = NULL;
    for (int ii = 0; ii < all_word_list->GetWordSize(); ii++) {
        // create WordListTree
        char *word = all_word_list->GetWord(ii);
        WordListTree *tmp_wlt = new WordListTree(word, hidden_word_list);
        if (level < max_level) {
            tmp_wlt->CreateSubTree(all_word_list, max_level, level);
        }
        // calc entropy
        int tmp_sum = tmp_wlt->CalcSum();
        double tmp_entropy = tmp_wlt->CalcEntropy(tmp_sum);
        // select WordListTree by max_entropy
        if (tmp_entropy > max_entropy) {
            max_entropy = tmp_entropy;
            delete max_wlt;
            max_wlt = tmp_wlt;
        } else {
            delete tmp_wlt;
        }
        if (level == 1) {
            printf("%s: entropy = %f, max_word = %s, max_entropy = %f\n", word,
                   tmp_entropy, max_wlt->GetWord(), max_entropy);
        }
        // finish when all word_list separate word_list_size = 1
        if (max_wlt != NULL && max_wlt->GetMaxWordSize() == 1) {
            break;
        }
    }
    return max_wlt;
}

// mask word_list using rule_list
WordList *MaskWordList(WordList *word_list, RuleList *rule_list) {
    int word_size = word_list->GetWordSize();
    WordList *masked_word_list = new WordList(word_size);
    for (int ii = 0; ii < word_size; ii++) {
        char *word = word_list->GetWord(ii);
        if (rule_list->Check(word)) {
            masked_word_list->SetWord(word);
        }
    }
    return masked_word_list;
}

int GetMaxLevel(int argc, char *argv[]) {
    if (argc % 2 == 1) {
        return 1;
    }
    return atoi(argv[argc - 1]);
}

int main(int argc, char *argv[]) {
    WordList all_word_list("wordlist_all");
    WordList hidden_word_list("wordlist_hidden");
    RuleList rule_list(argc, argv);
    int max_level = GetMaxLevel(argc, argv);

    // mask word_list using rule_list
    WordList *masked_word_list = MaskWordList(&hidden_word_list, &rule_list);
    int word_size = masked_word_list->GetWordSize();
    if (word_size == 0) {
        printf("None\n");
    } else if (word_size == 1) {
        printf("%s\n", masked_word_list->GetWord(0));
    } else {
        printf("%d candidates remain\n", masked_word_list->GetWordSize());
        // get WordListTree using max_entropy
        WordListTree *wlt =
            GetMaxEntropy(&all_word_list, masked_word_list, max_level, 1);
        printf("%s\n", wlt->GetWord());
        wlt->PrintJson();
        delete wlt;
    }
    delete masked_word_list;
    return 0;
}
