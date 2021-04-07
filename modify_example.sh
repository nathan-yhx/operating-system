#!/bin/sh

echo"
  testcase a) uppercasing the file [-u]

  testcase b) lowerizing the file [-l]

  tetscase c) calling the sed command to modify the folder, you canc change the name as you wish.
  
  testcase d) calling the sed command to change the postfix. like txt->doc

  you can have more options it's up to you. here is a example --./modify.sh -r sed 's/file/File/g' folder 

  "




	case "$1" in
		-a) ./modify.sh -r -u folder;;
		-b) ./modify.sh -r -l folder;;
		-c) ./modify.sh -r $sed 's/file/File/g' folder;;
		-d )./modify.sh -r $sed 's/txt/doc/g' folder;;
		*) echo " testcase $1 is wrong";;
       esac
	

