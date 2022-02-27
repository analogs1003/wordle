#ifndef WORD_LIST_HPP_
#define WORD_LIST_HPP_

#include <stdio.h>

class WordList {
   private:
    int word_size_ = 0;
    char *word_list_ = NULL;

   public:
    WordList(const char *filename) {
        FILE *fp = fopen(filename, "r");
        char buff[7];
        while (fgets(buff, 7, fp)) {
            if (strlen(buff) == 1) {
                continue;
            } else {
                word_size_++;
            }
        }

        word_list_ = new char[6 * word_size_];
        fseek(fp, 0, SEEK_SET);
        char *pp = word_list_;
        while (fgets(buff, 7, fp)) {
            if (strlen(buff) == 1) {
                continue;
            } else {
                strncpy(pp, buff, 5);
                pp[5] = '\0';
                pp += 6;
            }
        }
        fclose(fp);
    }
    WordList(int word_size) {
        word_size_ = 0;
        word_list_ = new char[6 * word_size];
    }
    ~WordList() { delete[] word_list_; }
    int GetWordSize() { return word_size_; }
    char *GetWord(int pos) { return &word_list_[pos * 6]; }
    void SetWord(char *word) {
        strcpy(&word_list_[word_size_ * 6], word);
        word_size_++;
    }
    void Print() {
        for (int ii = 0; ii < word_size_; ii++) {
            printf("%s ", GetWord(ii));
        }
        printf("\n");
    }
};
#endif  // WORD_LIST_HPP_
