    1 wget http://www.ark.cs.cmu.edu/10K/data/"$1".mda.tgz
    2
    3
    4 tar zxf "$1".mda.tgz
    5
    6 cat *.mda | tr '[A-Z]' '[a-z]' | tr ' ' '\n' | tr -c '^[a-z\n^[]]' '\0' |
    7 tr -d '\0 [ ] [] ^' | sed '/^\s*$/d' | sort | uniq -c | awk '$1 > 10 {prin
    8
    9
   10 rm *.mda
   11
   12 rm "$1".mda.tgz
