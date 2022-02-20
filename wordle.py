import math
import sys

# input_wordを入力したときanswer_wordに対する結果を求める
def calc_rule_type(answer_word, input_word):
    char_list = list(answer_word)
    rule_type = ['W','W','W','W','W']
    # green
    for ii in range(5):
        if input_word[ii] == char_list[ii]:
            rule_type[ii] = 'G'
            char_list[ii] = '-'  # 正解で使った文字は使用不可
    # yellow
    for ii in range(5):
        for jj in range(5):
            if rule_type[ii] != 'G' and input_word[ii] == char_list[jj]:
                rule_type[ii] = 'Y'
                char_list[jj] = '-'  # 正解で使った文字は使用不可
                break
    rule_type = ''.join(rule_type)
    return rule_type

# wordがrule_listすべてを満たしているか確認する
def check_rule_list(word, rule_list):
    for rule in rule_list:
        rule_word = rule[0]
        rule_type = rule[1]
        if calc_rule_type(word, rule_word) != rule_type:
            return False
    return True

# word_listからrule_listを満たすword_listを得る
def get_word_list(word_list, rule_list):
    tmp_word_list = []
    for word in word_list:
        if check_rule_list(word, rule_list):
            tmp_word_list.append(word)
    return tmp_word_list

# rule_typeごとのhidden_wordを数える
def get_word_count_dict(word, hidden_word_list):
    word_count_dict = {}
    for hidden_word in hidden_word_list:
        # 正解がhidden_wordだったときwordを入力したときのrule_typeを求める
        rule_type = calc_rule_type(hidden_word, word)
        # rule_type別にword数を数える
        word_count_dict[rule_type] = word_count_dict.get(rule_type, 0) + 1
    return word_count_dict

# word_count_dictからエントロピー（hidden_word_listのばらけぐあい）を求める
def calc_entropy(word_count_dict):
    value_list = word_count_dict.values()
    # hidden_word_listの合計値
    sum = 0
    for value in value_list:
        sum += value
    # 確率を求めてエントロピーを求める
    entropy = 0.0
    for value in value_list:
        prob = value / sum
        entropy -= prob * math.log(prob)
    return entropy

# all_word_listの中でentropyが最も大きくなる（hidden_word_listがばらける）単語を得る
def get_max_entropy_word(all_word_list, hidden_word_list):
    max_entropy = 0.0
    max_word = ""
    max_word_count_dict = ()
    for word in all_word_list:
        word_count_dict = get_word_count_dict(word, hidden_word_list)
        entropy = calc_entropy(word_count_dict)
        # print("get_max_entropy", entropy, word)
        if entropy > max_entropy:
            max_entropy = entropy
            max_word = word
            max_word_count_dict = word_count_dict
    return (max_word, max_entropy, max_word_count_dict)

def main(all_word_list, hidden_word_list, rule_list):
    # rule_listを満たすhidden_word_listを得る
    hidden_word_list = get_word_list(hidden_word_list, rule_list)
    hidden_word_list_len = len(hidden_word_list)
    if hidden_word_list_len == 0:
        print("None")
    elif hidden_word_list_len == 1:
        print(hidden_word_list[0])
    else:
        # print(' '.join(hidden_word_list))
        # entropyが最も大きくなる単語を得る
        print(len(hidden_word_list), "candidates remain")
        (word, entropy, word_count_dict) = get_max_entropy_word(all_word_list, hidden_word_list)
        # 残りのばらつき具合を表示
        # for rule_type in word_count_dict:
        #     print(rule_type, word_count_dict[rule_type])
        print(word, entropy)
    return

def load_word_list(filename):
    word_list = []
    ff = open(filename, 'r')
    for line in ff:
        if (line[0] == "#"):
            continue
        word_list.append(line.rstrip("\n"))
    ff.close()
    return word_list

# 引数からrule_listを得る
def get_rule_list():
    rule_list = []
    size = len(sys.argv) - 1
    for ii in range(int(size / 2)):
        rule = (sys.argv[2 * ii + 1], sys.argv[2 * ii + 2])
        rule_list.append(rule)
    return rule_list

if __name__ == "__main__":
    # ALL_WORD_LIST = load_word_list("pokemon5.txt")
    # HIDDEN_WORD_LIST = load_word_list("pokemon5.txt")
    ALL_WORD_LIST = load_word_list("wordlist_all")
    HIDDEN_WORD_LIST = load_word_list("wordlist_hidden")
    main(ALL_WORD_LIST, HIDDEN_WORD_LIST, get_rule_list())
