args="$@"
length=$(($#-1))
files=${@:1:$length}
backup_directory="${@: $#}"
coppied=0
#echo "args: "$args
#echo "files: "$files
#echo "backup_directory: "$backup_directory

if ! [ -d "$backp_directory" ];then
	echo "Making backup directory..."
	sudo mkdir $backup_directory
	echo "Done making directory "$backup_directory
fi

for file in $files;do
	if [[ -a "$file" && -r "$file" ]];then
		sudo cp $file $backup_directory
		((coppied++))
	else
		echo "File "$file does not exist or is not readable.
	fi
done

echo "Succesfully coppied files: "$coppied
