# handle input
with open('puzzleinput.txt', 'r') as puzzle_input:
    content = [line.rstrip('\n') for line in puzzle_input.readlines()]

def hand(items):
    possible_hand = True
    break_flag = 0
    for group in items.split(';'):
        if break_flag:
            break
        for item in group.split(','):
            quantity, color = item.split()
            if color == "red" and int(quantity) > 12:
                possible_hand = False
                break_flag = 1
                break
            elif color == "green" and int(quantity) > 13:
                possible_hand = False
                break_flag = 1
                break
            elif color == "blue" and int(quantity) > 14:
                possible_hand = False
                break_flag = 1
                break
            else:
                possible_hand = True

    return possible_hand
def main():
    possible_games = 0
    for line in content:
        game_id, items_str = line.split(":")
        game_id = game_id.strip('Game')
        if hand(items_str):
            possible_games += int(game_id)

    print(possible_games)

if __name__ == "__main__":
    main()