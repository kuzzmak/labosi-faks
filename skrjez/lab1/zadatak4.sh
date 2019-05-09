if [ "$#" -ne 2 ]; 
then
	echo "Wrong number of arguments."
	#exit 1
fi

# $1 - source
# #2 - destination

if  ! [ -d "$1" ];
then
	echo "You must provide starting directory."
	#exit 1
fi	

if ! [ -d "$2" ];
then
	echo "Making directory $2"
	mkdir "$2"
fi

for picture in $(ls $1); do
	date=$(sudo stat --format "%y" $1/$picture | cut -d "-" -f 1,2)
	if ! [ -d "$2/$date" ];
	then
		mkdir "$2/$date"
		mv "$1/$picture" "$2/$date"
	fi
done	



#stat --format "%y" primjer.txt | cut -d "-" -f 1,2,3 | sed 's/[[:space:]].*//'
