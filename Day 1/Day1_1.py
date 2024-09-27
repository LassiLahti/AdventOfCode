
# handle input
with open('puzzleinput.txt', 'r') as puzzle_input:
    content = [line.rstrip('\n') for line in puzzle_input.readlines()]
print(content)

# Testing
exampleList = ["1abc2",
    "pqr3stu8vwx",
    "a1b2c3d4e5f",
    "treb7uchet"]

# VITUSTI LISTOJA :)
def decoder(calibration_values):
    numberlist = []

    # PASKA LOOPPI
    for value in calibration_values:
        tmp = []
        for character in value:
            if character.isdigit():
                tmp.append(character)
        numberlist.append(tmp[0])
        numberlist.append(tmp[-1])

    # TOP TIER LIST COMPREHENSION
    joined = [int(''.join(numberlist[i:i+2])) for i in range(0, len(numberlist), 2)]

    # SUMMA
    result = sum(joined)
    print(result)

decoder(content)

