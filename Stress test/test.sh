set -e
g++ correct.cpp -o correct
g++ gen.cpp -o gen
g++ wrong.cpp -o wrong
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./correct < input_file > wrongAnswer
    ./wrong < input_file > correctAnswer
    diff -Z wrongAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat wrongAnswer
echo "Correct answer is:"
cat correctAnswer