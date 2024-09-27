
import re

# handle input
with open('puzzleinput.txt', 'r') as puzzle_input:
    content = [line.rstrip('\n') for line in puzzle_input.readlines()]

# Testing
exampleList = [
        "two1nine",
        "eightwothree",
        "abcone2threexyz",
        "xtwone3four",
        "4nineeightseven2",
        "zoneight234",
        "7pqrstsixteen"]

decodeDict = {
        'one' : '1',
        'two' : '2',
        'three': '3',
        'four': '4',
        'five': '5',
        'six': '6',
        'seven': '7',
        'eight': '8',
        'nine' : '9'}


def decoder(calibration_values):
    res = 0
    for line in calibration_values:
        tmp = []
        for string in decodeDict:
            tmp += [(r.start(), decodeDict[r.group()]) for r in re.finditer(string, line)]
            tmp += [(r.start(), r.group()) for r in re.finditer('\d', line)]
        if tmp:
            tmp.sort()
            res += int(tmp[0][1] + tmp[-1][1])
    print(res)

decoder(content)
