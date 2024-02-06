#This is a program to check if the file includes an integer, and not strings.
#Citation: I got the hints from the link: (https://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash)
#This should fail as 7.txt is a string.

echo "seven" > 7.txt
./calc 3 4 > 3.4.txt

filename = "3.4.txt"

# Ensures exit code is Zero
if [ ! -f "$filename" ]; then
	echo "File not found: "$filename"
	exit 1
fi

#returns an error if 3.4.txt is not integer
content = $(<"$filename")
if [[ $content =~ ^[0-9]+$ ]]; then
	echo "The input of 3.4.txt is not an integer"
	rm 3.4.txt
	rm 7.txt
	exit 1
fi

# returns an error if 7.txt is not integer
filename = "7.txt"
content = $(<"$filename")
if [[ $content =~ ^[0-9]+$ ]]; then
        echo "The input of 7.txt is not an integer"
	rm 3.4.txt
	rm 7.txt
	exit 1
fi


# Prints a message on success
echo "Test does not find an integer error: PASS"

# Cleans up files created
rm 3.4.txt
rm 7.txt
exit 0
