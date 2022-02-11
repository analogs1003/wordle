import math
import sys

# wordがruleを満たしているか確認する
def check_rule(word, rule):
    rule_word = rule[0]
    rule_type = rule[1]
    for ii in range(5):
        # GREEN: ii番目の文字がrule文字と一致 -> OK
        if rule_type[ii] == 'G':
            if word[ii] != rule_word[ii]:
                return False
        # YELLOW: ii番目の文字がrule文字と一致 -> NG, 他の位置で文字が一致 -> OK, 全位置で文字が不一致 -> NG
        elif rule_type[ii] == 'Y':
            if word[ii] == rule_word[ii]:
                return False
            count = 0
            for jj in range(5):
                if word[jj] == rule_word[ii]:
                    count += 1
            if count == 0:
                return False
        # WHITE: どこかの位置で文字が一致 -> NG
        elif rule_type[ii] == 'W':
            for jj in range(5):
                if word[jj] == rule_word[ii]:
                    return False
        # OTHER: 
        else:
            return False
    return True

# wordがrule_listすべてを満たしているか確認する
def check_rule_list(word, rule_list):
    for rule in rule_list:
        if check_rule(word, rule) == False:
            return False
    return True

# word_listからrule_listを満たすword_listを得る
def get_word_list(word_list, rule_list):
    tmp_word_list = []
    for word in word_list:
        if check_rule_list(word, rule_list):
            tmp_word_list.append(word)
    return tmp_word_list

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

def get_word_count_dict(word, hidden_word_list):
    # rule_typeごとのhidden_wordを数える
    word_count_dict = {}
    for hidden_word in hidden_word_list:
        # 正解がhidden_wordだったときwordを入力したときのrule_typeを求める
        rule_type = calc_rule_type(hidden_word, word)
        # rule_type別にword数を数える
        if rule_type in word_count_dict:
            word_count_dict[rule_type] += 1
        else:
            word_count_dict[rule_type] = 1
    return word_count_dict

# word_count_dictからエントロピー（hidden_word_listのばらけぐあい）を求める
def calc_entropy(word_count_dict):
    # rule_typeごとの確率を求める
    sum = 0
    for rule_type in word_count_dict.keys():
        sum += word_count_dict[rule_type]
    prob = {}
    for rule_type in word_count_dict.keys():
        prob[rule_type] = word_count_dict[rule_type] / sum

    # entropyを求める
    entropy = 0.0
    for rule_type in word_count_dict.keys():
        entropy -= prob[rule_type] * math.log(prob[rule_type])
    return entropy

# all_word_listの中でentropyが最も大きくなる（hidden_word_listがばらける）単語を得る
def get_max_entropy_word(all_word_list, hidden_word_list):
    max_entropy = 0.0
    max_word = ""
    for word in all_word_list:
        word_count_dict = get_word_count_dict(word, hidden_word_list)
        entropy = calc_entropy(word_count_dict)
        print("get_max_entropy", entropy, word)
        if entropy > max_entropy:
            max_entropy = entropy
            max_word = word
    return (max_word, max_entropy)

def main(all_word_list, hidden_word_list, rule_list):
    # rule_listを満たすhidden_word_listを得る
    hidden_word_list = get_word_list(hidden_word_list, rule_list)
    hidden_word_list_len = len(hidden_word_list)
    if hidden_word_list_len == 0:
        print("None")
    elif len(hidden_word_list) == 1:
        print(hidden_word_list[0])
    else:
        if len(hidden_word_list) < 10:
            for hidden_word in hidden_word_list:
                print(hidden_word)
        # entropyが最も大きくなる単語を得る
        (word, entropy) = get_max_entropy_word(all_word_list, hidden_word_list)
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

# ALL_WORD_LIST = load_word_list("pokemon5.txt")
# HIDDEN_WORD_LIST = load_word_list("pokemon5.txt")
ALL_WORD_LIST = load_word_list("wordlist_all")
HIDDEN_WORD_LIST = load_word_list("wordlist_hidden")
main(ALL_WORD_LIST, HIDDEN_WORD_LIST, get_rule_list())