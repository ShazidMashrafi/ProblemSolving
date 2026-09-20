g++ correct.cpp -o correct -std=c++20
g++ gen.cpp -o gen -std=c++20
g++ wrong.cpp -o wrong -std=c++20

for ((i = 1; ; ++i)); do
    ./gen $i > in
    ./correct < in > ok || break
    ./wrong < in > wa || break
    diff -w ok wa > /dev/null || break
    echo "Passed test: $i"
done

echo "WA / RE on test:"
cat in
echo "Your answer:"
cat wa
echo "Correct answer:"
cat ok