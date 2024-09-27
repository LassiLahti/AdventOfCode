# handle input
with open('puzzleinput.txt', 'r') as puzzle_input:
    content = [line.rstrip('\n') for line in puzzle_input.readlines()]

def hand(items):
    red = 0
    green = 0
    blue = 0
    for group in items.split(';'):
        for item in group.split(','):
            quantity, color = item.split()
            if color == "red" and int(quantity) > red:
                red = int(quantity)
            if color == "green" and int(quantity) > green:
                green = int(quantity)
            if color == "blue" and int(quantity) > blue:
                blue = int(quantity)

    return red, green, blue

def main():
    total = 0
    for line in content:
        game_id, items_str = line.split(":")
        game_id = game_id.strip('Game')
        red, green, blue = hand(items_str)
        total += red * green * blue
    print(total)

if __name__ == "__main__":
    main()