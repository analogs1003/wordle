import sys

# input_wordを入力したときanswer_wordに対する結果を求める
def calc_rule_type(answer_word, input_word):
    rule_type = ['W','W','W','W','W']
    for ii in range(5):
        if answer_word[ii] == input_word[ii]:
            rule_type[ii] = 'G'
        else:
            for jj in range(5):
                if answer_word[jj] == input_word[ii]:
                    rule_type[ii] = 'Y'
    rule_type = ''.join(rule_type)
    return rule_type

def main(answer_word, input_word):
    rule_type = calc_rule_type(answer_word, input_word)
    print(rule_type)
    return

def load_word_list(filename):
    word_list = []
    ff = open(filename, 'r')
    for line in ff:
        word_list.append(line.rstrip("\n"))
    return word_list

main(sys.argv[1], sys.argv[2])