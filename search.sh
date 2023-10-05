findthis=$1

tree() {
	for file in *
	do
		if [ -d $file ]
		then
			cd $file
			tree
		else
			if [ $findthis = $file ]
			then
				echo $(pwd)$findthis
				exit 0
			fi
		fi
	done
	cd ..
}
if [[ $# -eq 1 ]]
then
	tree
else
	echo ":("
fi

echo ":("
