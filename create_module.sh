#!/bin/bash

SRC_DIR=src
INC_DIR=inc

mkdir -p $SRC_DIR $INC_DIR

for var in "$@"
do
	
	SRC_FILE="$var.c"
	INC_FILE="$var.h"
	
    INC_GUARD="${var^^}_H"
	
	CREATE=true
	
	if [ -e "$SRC_DIR/$SRC_FILE" ]
	then
		echo "$SRC_FILE already exists in $SRC_DIR."
		CREATE=false
	fi
	
	if [ -e "$INC_DIR/$INC_FILE" ]	
	then
		echo "$INC_FILE already exists in $INC_DIR."
		CREATE=false
	fi
	
	if [ "$CREATE" = true ]	
	then
		echo -e "#include \"$INC_FILE\" \n\n" > $SRC_DIR/$SRC_FILE
		echo -e "#ifndef $INC_GUARD\n#define $INC_GUARD\n\n\n\n#endif /* $INC_GUARD */\n" > $INC_DIR/$INC_FILE
		echo "Created $SRC_DIR/$SRC_FILE and $INC_DIR/$INC_FILE."
	fi
	
done