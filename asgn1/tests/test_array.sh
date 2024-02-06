#!/bin/bash

# Function to print an error message and exit
error_exit() {
    echo "$1" >&2
    exit 1
}

# Function to check if an array is within its valid length
check_array_length() {
    local array=("$@")
    local max_length=$1

    # Check if the array length exceeds the specified maximum length
    if [ "${#array[@]}" -gt "$max_length" ]; then
        error_exit "Error: Array length exceeds the specified maximum length."
    fi
}

insertData() {
    local array=$1     
    local element=$2

    # Insert the element into the array
    array+=("$element")
}

# Test the insertData function
max_length=5
declare -a myArray

# Call the insertData function with a reference to myArray
insertData myArray element1
insertData myArray element2
insertData myArray element3
insertData myArray element4
insertData myArray element5
insertData myArray element6
insertData myArray element7

# Check if the array is within its valid length
check_array_length "$max_length" "${myArray[@]}"

# If everything is as expected, print a success message
echo "Test passed: Array length is within the valid range."

# Exit with success status
exit 0
