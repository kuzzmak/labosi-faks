proba="Ovo je proba"
echo $proba
lista_datoteka=$(ls)
echo $lista_datoteka
proba3="$proba. $proba. $proba. "
a=4
b=3
c=7
d=$((($a+4)*($b%$c)))
echo $d
broj_rijeci=$(cat *.txt | wc -w)
echo $broj_rijeci
ls ~
cut -d ":" -f 1,6,7 /etc/passwd
ps -ef | tr -s ' ' | cut -d ' ' -f 3,4,5,6,7


