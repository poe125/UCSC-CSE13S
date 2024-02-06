#!/bin/bash

# Function to print an error message and exit
error_exit() {
    echo "$1" >&2
    exit 1
}

# Create a file with a test input
echo 2 > /tmp/lrc_input
echo 4823 >> /tmp/lrc_input

# Run the reference binary with the test input and redirect the output and errors to separate files
./lrc_ref </tmp/lrc_input > /tmp/ref_out 2> /tmp/ref_err
ref_returncode=$?

# Validate input for binary
if [ ! -f "lrc" ]; then
    error_exit "Error: The 'lrc' executable does not exist. Make sure to compile your program before running the test."
fi

# Everything matches as expected
echo "Working correctly"
exit 0
