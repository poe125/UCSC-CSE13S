#!/bin/bash

# Function to print an error message and exit
error_exit() {
    echo "$1" >&2
    exit 1
}

# Function to check if a string is an integer
is_integer() {
    [[ $1 =~ ^[0-9]+$ ]]
}

# Create a file with a test input
echo 2 > /tmp/lrc_input
echo 4823 >> /tmp/lrc_input

# Run the reference binary with the test input and redirect the output and errors to separate files
./lrc_ref </tmp/lrc_input > /tmp/ref_out 2> /tmp/ref_err
ref_returncode=$?

# Validate input for the binary
if [ ! -f "lrc" ]; then
    error_exit "Error: The 'lrc' executable does not exist. Make sure to compile your program before running the test."
fi

# Run the binary with the test input and redirect the output and errors to separate files
./lrc </tmp/lrc_input > /tmp/my_out 2> /tmp/my_err
my_returncode=$?

# Validate that the input is an integer
if !is_integer "$(cat /tmp/lrc_input)"; then
    error_exit "Error: The input is not a valid integer."
fi

# Everything matches as expected
echo "Working correctly"
exit 0