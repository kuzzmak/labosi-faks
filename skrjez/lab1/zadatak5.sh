if [ "$#" -ne 2 ] || ! [ -d "$1" ];
then
	echo "You must pass two arguments; first argument must be directory and second search pattern."
	#exit 1
fi

dir="$1"
pattern="$2"

total_words=0
words=0

echo "$@"

for file in $(sudo find "$dir" -name "*$pattern");do
	words=$(sudo wc -l "$file" | cut -d ' ' -f  1)
	temp=$((total_words + words))
	total_words=$temp
done

echo $total_words
