import os
import subprocess

def read_board_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    N, M, D = map(int, lines[0].strip().split())
    start = tuple(map(int, lines[1].strip().split()))
    goal = tuple(map(int, lines[2].strip().split()))
    board = [list(line.strip()) for line in lines[3:3+N]]
    
    return N, M, D, start, goal, board

def validate_path(board, start, goal, path):
    current_pos = start
    directions = {
        'U': (-1, 0),
        'D': (1, 0),
        'L': (0, -1),
        'R': (0, 1)
    }

    for move in path:
        if move not in directions:
            return False
        delta = directions[move]
        next_pos = (current_pos[0] + delta[0], current_pos[1] + delta[1])
        if (next_pos[0] < 0 or next_pos[0] >= len(board) or
                next_pos[1] < 0 or next_pos[1] >= len(board[0]) or
                board[next_pos[0]][next_pos[1]] == '#'):
            return False
        current_pos = next_pos

    return current_pos == goal

def main():
    folder_path = "tableros"
    program_path = "./programa_astar"

    for file_name in os.listdir(folder_path):
        if file_name.endswith(".txt"):
            file_path = os.path.join(folder_path, file_name)
            N, M, D, start, goal, board = read_board_file(file_path)
            
            result = subprocess.run([program_path, file_path], capture_output=True, text=True)
            path = result.stdout.strip()
            
            if validate_path(board, start, goal, path):
                pass#print(f"Test {file_name}: PASSED")
            else:
                print(f"Test {file_name}: FAILED")

if __name__ == "__main__":
    main()
