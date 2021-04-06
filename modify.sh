#!/bin/sh

RECURSIVE_MODE=0
MODE=0  
SED_PATTERN=""
SCRIPTNAME=`basename $0`
printHelp(){
        echo "Usage:\n\t$0 [-r] [-l|-u] <dir/file names...>\n\t$0 [-r] <sed pattern> <dir/file names...>\n\t$0 [-h]\n "
        echo "Where:\n\t-l lowerizes specified filenames\n\t-u uppersizes specified filenames"
        echo "\t-r runs the script with recursion\n"
}

if [ $# -eq 0 ]; then
        printHelp
fi
#mode1:change filename from uppercase to lowercase
#mode2: change filename from lower to upper
#mode3: get sed comment from SED_PATTERN 
changeName()
{
                CURRENT_NAME=`basename "$1"`
                case $MODE in
                        "1") NEW_NAME=`echo "$CURRENT_NAME" |  tr [:upper:] [:lower:]` ;;
                        "2") NEW_NAME=`echo "$CURRENT_NAME" |  tr [:lower:] [:upper:]` ;;
                        "3") NEW_NAME=`echo "$CURRENT_NAME" |  sed  $SED_PATTERN` ;;
                esac
                mv "$CURRENT_NAME" "$NEW_NAME"
                echo "The $CURRENT_NAME is rename to $NEW_NAME"
}
# do the recursive or not
travFolder()
{
if [ $RECURSIVE_MODE -eq 1 ] ; then
   if [ -d "$1" ] ; then 
    flist=`ls $1`
    cd $1
    for f in $flist
    do
        if test -d $f
        #if there is folder in $1
        then
            travFolder $f #recursive again to get the filename
              
        else
           
            changeName $f
        fi

    done
    cd ..
    else 
        changeName $1
     fi
else
 changeName $1 
fi
}
while [ "$1" != "" ]; do
        case "$1" in
                "-r")  RECURSIVE_MODE=1 ;;
                "-l")  MODE=1 ;;
                "-u")  MODE=2 ;;
                *)
#$1 can be -l/-u or sed commend
                
                if [ $MODE -eq 0 ]; then
                        MODE=3
                        SED_PATTERN="$1"
                else
                        travFolder "$1"
                fi
                ;;
        esac
shift
done