echo 7 > 7.txt
./calc 3 4 > 3.4.txt

# Ensures exit code is Zero

# Check if 3.4.txt is larger than 512 or smaller than -512, return fail
if [ $(<3.4.txt) -gt 512 ] || [ $(<3.4.txt) -lt -512 ]; then
    echo "The number in 3.4.txt is too large or too small"
    rm 3.4.txt
    rm 7.txt
    exit 1
fi

# Check if the number in 7.txt is larger than 512 or smaller than -512, return fail
if [ $(<7.txt) -gt 512 ] || [ $(<7.txt) -lt -512 ]; then
    echo "The number in 7.txt is too large or too small"
    rm 3.4.txt
    rm 7.txt
    exit 1
fi

# Prints a message on success
echo "The numbers are within the valid range: PASS"

# Cleans up files created
rm 3.4.txt
rm 7.txt
exit 0
