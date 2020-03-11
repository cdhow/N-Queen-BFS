#include <iostream>
#include <vector>
#include <list>
#include <queue>

// TODO : intro comment

/*   0 1 2 3
 * 0 0 0 0 0
 * 1 0 0 0 0
 * 2 0 0 0 0
 * 3 0 0 0 0
 */


// 2D Vector
typedef std::vector<std::vector<int>> chessboard;

// Takes a dimension ( width = height ) and returns a n*n 2D vector with all values = 0, ( initial empty board )
chessboard setup_board(int &n)
{
    // Problem will not work for N < 1
    if (n < 1) {
        std::cout << "The N-Queens Problem will not work for N values less than 1.\nDefaulting to N=8.\n" << std::endl;
        n = 8;
    }

    return chessboard (n, std::vector<int>(n, 0));
}

// This function takes a parent board, copies the parent into a child and
// places a queen at the corresponding row, col in the child, then returns that child
chessboard place_queen(chessboard &parentBoard, int row, int col)
{
    chessboard childBoard = parentBoard;
    childBoard[row][col] = 1;
    return childBoard;
}

// This function updates the solution list containing the goal boards
void update_solution(const chessboard &goalBoard, std::list<chessboard> &solutions, const int &n)
{

    // If the N is less than 7 then print the solution
    if (n < 7) {
        for (const auto &row : goalBoard) {
            for (int square : row) {
                std::cout << square << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    solutions.push_back(goalBoard);
}

// This method will check if a placement is valid, if it is not we will stop exploring that path in the BFS
bool isValid_placement(chessboard &board, int row, int col)
{
    // Because each state will only ever have one queen on a row and we work from top down,
    // we only need to check diagonals up and straight up

    // Start at the potential placement and check all values above
    // start at the row above
    for (int r = row; r <=0; r --) {
        if (board[r][col])
            return false;
    }

    // Start at the potential placement and check all values above-diagonally-to-the-left
    // formula is incrementing [row-1][col-1]
    int r = row-1; int c = col-1; // start at the square up-to-left
    while (r >= 0 && c >= 0) {
        if (board[r][c])
            return false;
        r--;
        c--;
    }

    // Start at the potential placement and check all values above-diagonally-to-the-right
    // formula is incrementing [row+1][col+1]
    r = row=+1; c = col+1; // start at the square up-to-right
    while (r <= board.size() && c <= board.size()) {
        if (board[r][c])
            return false;
        r--;
        c--;
    }

    return true;
}

// This function runs the BFS on the chess boards and solves for N queens
// Returns a list of solutions - using a List as it has O(1) insertion and non-linear access does not matter
std::list<chessboard> solve_bfs(int &n)
{
    // List of solutions
    std::list<chessboard> solutions;

    // Initial empty board
    chessboard board = setup_board(n);

    // BFS queue
    std::queue<chessboard> queue;

    // Push the initial empty board state
    queue.push(board); // initially at row 0

    // Run BFS
    int row = 0;
    while (!queue.empty())
    {
        // pop from the queue and push boards with queen on each col in the current row
        chessboard parentBoard = queue.front();
        queue.pop();


        for (int col=0; col<n; col++) {
            // Only explore the path if the placement is valid
            if (isValid_placement(parentBoard, row, col)) {
                // place the valid child board
                queue.push(place_queen(parentBoard, row, col));
            }
        }

        // If row = N, we are that the end of the board, meaning we placed N queens which are all in valid states
        // add it to the solutions, else discard it
        if (row == n) { // TODO : not sure where this belongs
            solutions.push_back(parentBoard);
        }

        row++;
    }
}