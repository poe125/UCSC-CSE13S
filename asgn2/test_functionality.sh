#this tests the functionality of test_helpers.c
#compile the file
cc -o helpers test_helpers.c hangman_helpers.c

# Function to print an error message and exit
error_exit() {
    echo "$1" >&2
    exit 1
}

#run the test cases

#if the input is a lowercase in the string
./helpers <<EOF
t
EOF

#lowercase but not in the string
./helpers <<EOF
a
EOF

#a number
./helpers <<EOF
3
b
EOF

#a special key
./helpers <<EOF
&
c
EOF

#a capital alphabet
./helpers <<EOF
D
d
EOF

rm helpers