import os
import subprocess
import filecmp
subprocess.run(["g++", "correct.cpp", "-o", "correct"], check=True)
subprocess.run(["g++", "gen.cpp", "-o", "gen"], check=True)
subprocess.run(["g++", "wrong.cpp", "-o", "wrong"], check=True)

i = 1
while True:
    with open("input_file", "w") as input_file:
        subprocess.run(["./gen", str(i)], stdout=input_file, check=True)
    with open("input_file", "r") as input_file, open("correctAnswer", "w") as correct_output:
        subprocess.run(["./correct"], stdin=input_file, stdout=correct_output, check=True)
    with open("input_file", "r") as input_file, open("myAnswer", "w") as wrong_output:
        subprocess.run(["./wrong"], stdin=input_file, stdout=wrong_output, check=True)
    if not filecmp.cmp("myAnswer", "correctAnswer", shallow=False):
        print("\nWA on the following test:")
        with open("input_file", "r") as f:
            print(f.read())
        print("Your answer is:")
        with open("myAnswer", "r") as f:
            print(f.read())
        print("\nCorrect answer is:")
        with open("correctAnswer", "r") as f:
            print(f.read())
        break
    print(f"Passed test: {i}")
    i += 1