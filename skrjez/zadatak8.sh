file="$1"

if [ "$#" -ne 1 ];
then 
	echo "Wrong number of arguments."
fi

if [ -r "$file" ];then
	echo "File not readable"
	exit 1
fi

sudo cut -d '"' "$file" -f 1 | sort | cut -d ':' -f 2 | sort | uniq -c | cut -d ' ' -f 7,6,5 | sed -E 's/(.*[0-9]*) ([0-9]*)/\2 \1/'
