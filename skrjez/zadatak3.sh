for file in $(find ~/ -regex ".*localhost_access_log.[0-9][0-9][0-9][0-9]-02-[0-9][0-9].*.txt")
do
	echo $file |sed -r 's/.*\.([0-9][0-9][0-9][0-9])-([0-9][0-9])-([0-9][0-9]).*/datum: \3-\2-\1/'
	echo "---------------------------------------------"
	sudo cut -d '"' -f 2 $file | sort -b | uniq -c | sort -n -r
done
