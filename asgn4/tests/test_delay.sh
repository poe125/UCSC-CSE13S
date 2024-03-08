cd ..
./xd > output.txt

exec 3<output.txt
exec 4<tests/testcase.txt

while read -r line <&3 && read -r line2 <&4; do
    echo "$line"
    echo "$line2"
    sleep 1
done

rm output.txt
exit 0