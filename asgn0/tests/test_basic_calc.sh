#This is a program to check whether 3+4=7 or not.
#This should pass.

# Creates the example output
echo 7 > 7.txt

# Runs the program
./calc 3 4 > 3.4.txt

# Ensure that exit code is 0
diff 3.4.txt 7.txt
if [ $? -ne 0 ]; then
    echo "invalid exit code"$?
    rm 3.4.txt
    rm 7.txt
    exit 0
fi

# Ensures differences are not found for 3+4 and 7
diff 3.4.txt 7.txt
if [ $? -ne 0 ]; then
    echo "Somehow, 3+4 does not equal 7"
    rm 3.4.txt
    rm 7.txt
    exit 0
fi

# Prints a message on success
echo "Test calculates correctly; 3+4=7: PASS"

# Cleans up files created
rm 3.4.txt
rm 7.txt
exit 0
