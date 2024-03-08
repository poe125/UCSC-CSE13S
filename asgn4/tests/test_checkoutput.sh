cd ..
./xd > tests/output.txt

echo "Output has been redirected to output.txt"

cd tests/

diff output.txt testcase.txt
if [ $? -ne 0 ]; then
    echo "wrong output"
    rm output.txt
    exit 0
else
    echo "correct output"
    rm output.txt
    exit 1
fi

rm output.txt
exit 0
