# wordle

wordle を（最適に？）解くツール

## usage

### format

```
$ python3 wordle.py word1 colors1 word2 colors2 ...
```

### colors format

```
G: GREEN
Y: YELLOW
W: WHITE
```

### samples

```
$ python3 wordle.py
soare 4.079836655397409
```

```
$ python3 wordle.py soare WWWYY
tined 3.0408279545988806
```

```
$ python3 wordle.py soare WWWYY tined WWWGW
flump 2.6015683031684986
```

## data

使用しているデータ

- 登録されている単語一覧  
  https://github.com/alex1770/wordle/blob/main/wordlist_all
- 答えとして選ばれる単語一覧  
  https://github.com/alex1770/wordle/blob/main/wordlist_hidden

## 解き方

`登録されれている単語一覧`から 1 つの単語を選ぶときに、結果(colors)ごとの`答えとして選ばれる単語一覧`の単語の数がばらつくように選択する

※ばらつく = エントロピーが高い状態

### エントロピーが高い単語

```
soare: 4.079836655397409
roate: 4.07763190248932
raise: 4.0742565297788875
raile: 4.06580014743624
reast: 4.0656250812699835
slate: 4.058914192529379
crate: 4.044426464977779
salet: 4.044223734400918
irate: 4.042016375718313
trace: 4.04142840212909
```

### エントロピーが低い単語

```
qajaq: 1.226389003745831
immix: 1.3742681392190257
jujus: 1.4054629353905606
xylyl: 1.444289343089728
jaffa: 1.4515950547067338
yukky: 1.500730704836311
zoppo: 1.504932453667627
pzazz: 1.5316354583246432
jeeze: 1.540163122342829
fuffy: 1.5463245016289733
kudzu: 1.5508245252798494
```

### 1 手目が`qajaq`のときのばらつき結果

「登録されている単語一覧」から`qajaq`を選んだときに、「答えとして選ばれる単語一覧」の単語が、colors ごとに何語ずつにわかれるか

```
WYWYW: 449
WYWGW: 142
WGWYW: 282
WGWGW: 17
WGYYW: 3
WWWWW: 1369
WWYWW: 19
WWGWW: 1
YYWGY: 3
YWWWY: 3
WYYYW: 2
WGGYW: 1
GYWYY: 9
GWWWY: 14
WGGGW: 1
```

上記から 1 手目に`qajaq`を入れると、ほとんどの答えで`WWWWW`が返ってきて、最終結果にたどり着くまでに手数がかかってしまいそうなことがわかる

### 1 手目が`soare`のときのばらつき結果

```
WWGWW: 40
YWGWG: 7
WWGWG: 28
WWYWY: 68
WYYWW: 44
WYYYW: 27
WWYWG: 40
WYYWG: 8
WYYGW: 6
YWYWG: 15
YWYWW: 23
WWYYW: 42
WWYWW: 138
WYYGG: 1
WWYGG: 2
WWYYY: 61
WWYYG: 7
WWGGW: 13
WWYGY: 5
YWGWW: 14
WWYGW: 11
WGYYW: 8
YWYYG: 3
YYYYG: 1
YYYYW: 1
YWYYW: 4
YYYWW: 3
YWYWY: 5
WWGGG: 4
WWGWY: 21
WWGGY: 9
YWGWY: 5
WWWWY: 120
WWWWG: 79
WYWWY: 25
WWWYY: 117
WWWGY: 14
YWWWY: 19
WWWWW: 183
WYWWW: 56
WYWWG: 20
WWWYW: 57
YYWWW: 7
YWWWW: 33
WWWGW: 13
WGGGW: 2
YGGWW: 3
WGWWW: 87
WGWWY: 26
YGWWW: 15
WGWWG: 10
WGWYG: 9
WGWYY: 22
WWGYG: 19
WWGYW: 40
YWGYW: 7
WYGYW: 1
WWWYG: 39
YWWYW: 16
WYWYW: 59
WYWYG: 14
WYYWY: 4
YYGWW: 1
WYWGW: 8
WYWGG: 2
YYWWG: 5
WGGWW: 5
WGYGW: 1
WGYWW: 21
WGWYW: 26
YGWWG: 11
WGWGW: 6
WYWYY: 13
YWWYY: 15
YYWYW: 5
YWWYG: 7
YWWWG: 8
YWGYG: 1
YYWWY: 3
WWWGG: 4
YGWYG: 3
YGWYY: 2
WYWGY: 3
YGWWY: 2
WYYGY: 1
WYGGW: 1
WYGWG: 1
WYGWW: 1
YYWYG: 1
WWGYY: 4
WGGYW: 1
YGGYW: 1
YGWYW: 4
GWYWW: 19
GWYYY: 6
GYYWW: 4
GWYWG: 3
GWYYW: 8
GYYYW: 1
GWGWW: 41
GWGWG: 19
GWGGG: 5
GWGGW: 11
GWWWG: 23
GWWWY: 35
GYWWW: 37
GYWWG: 12
GYWGG: 6
GYWGW: 10
GYWYW: 1
GWWYG: 4
GWWYY: 13
GWWYW: 9
GWYWY: 9
GWWWW: 63
GWWGG: 2
GWWGW: 8
GGGWW: 1
GGWYY: 2
GGWWW: 7
GGYYW: 2
GGWWG: 1
GGWGW: 1
GWWGY: 2
GWGYW: 1
YWWGW: 1
YYWYY: 1
```

`qajaq`よりも`soara`の方がばらついていることがわかり、1 手目に`qajaq`よりも`soara`を入力した方が早く正解にたどりつけそうなことがわかる

## tests

```
$ python3 -m unittest tests/test_wordle.py
```

## おまけ

[POKEMON WORDLE](https://wordle.mega-yadoran.jp/)用の[データ](https://github.com/analogs1003/wordle/blob/main/pokemon5.txt)をつくってみました。
データを差し替えることで POKEMON WORDLE に対応できます。
