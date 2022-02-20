import sys

# input_wordを入力したときanswer_wordに対する結果を求める
def calc_rule_type(answer_word, input_word):
    char_list = list(answer_word)
    rule_type = ['W','W','W','W','W']
    # green
    for ii in range(5):
        if input_word[ii] == char_list[ii]:
            rule_type[ii] = 'G'
            char_list[ii] = '-'
    # yellow
    for ii in range(5):
        for jj in range(5):
            if rule_type[ii] != 'G' and input_word[ii] == char_list[jj]:
                rule_type[ii] = 'Y'
                char_list[jj] = '-'
                break
    rule_type = ''.join(rule_type)
    return rule_type

def main(answer_word, input_word):
    rule_type = calc_rule_type(answer_word, input_word)
    print(rule_type)
    return

main(sys.argv[1], sys.argv[2])
