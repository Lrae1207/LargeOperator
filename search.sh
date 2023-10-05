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
				echo $findthis found at $(pwd)
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
	echo "This command requires and handles only one parameter/argument"
fi

echo "	$findthis not found"
