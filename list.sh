# tree-search root

bold=$(tput bold)
norm=$(tput sgr0)

tree_all() {
	for file in *
	do
		if [ -d $file ]
		then
			if [ $file != localauthority ]
			then
				cd $file
				tree_all
			else
				echo "Avoid localauthority"
			fi
		else
			if [ $file == X11 ]
			then
				echo "Ignore X11"
			else
				if [ $1=="all" ]
				then
					#echo "meta:"
					echo "$file in $(pwd)"
					#echo "print file contents:"
					#cat $file
					#echo "continue"
				else 
					echo "$file in $(pwd)"
				fi
			fi
		fi
	done
	cd ..
}

cd $1

tree_all
