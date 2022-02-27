# wordle.cpp

wordle solver  
wordle を（最適に？）解くツール (c++版)

- 高速化のため c++化
- 1 手だけでなく N 手先まで読む
- 読んだ手を json でツリー表示
- 2 手先以上読むときはとても時間がかかる

## install

```
$ git clone git@github.com:analogs1003/wordle.git
$ cd wordle
$ wget https://raw.githubusercontent.com/alex1770/wordle/main/wordlist_all
$ wget https://raw.githubusercontent.com/alex1770/wordle/main/wordlist_hidden
$ cd cpp
$ g++ wordle.cpp -o ../wordle
$ cd ..
```

## usage

### format

```
$ ./wordle word1 color1 word2 color2 N
```

### colors format

```
G: GREEN
Y: YELLOW
W: WHITE
```

### samples

```
$ ./wordle 1
2315 candidates remain
  :
zymic: entropy = 2.263158, max_word = soare, max_entropy = 4.079837
soare
{"word": "soare", "tree": [{"rule_string": "WWWWW", "word_size": 183, ...
```

```
$ ./wordle soare YWWWW 2
33 candidates remain
  :
album: entropy = 3.496508, max_word = album, max_entropy = 3.496508
album
{"word": "album", "tree": [{"rule_string": "WWWWW", "word_size": 8, ...
```
