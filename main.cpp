#include <iostream>
#include <utility>
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

// Class that contains a chessboard and an int - will be used to store a board and the current row context
class State {
public:

    // The current board configuration in this state
    chessboard board;

    // The row context of the current state
    const int row;

    State(chessboard board, const int &row) : board{std::move(board)}, row{row} {}
};

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
State place_queen(State &state, int col)
{
    chessboard childBoard = state.board;
    childBoard[state.row+1][col] = 1;
    return State(childBoard, state.row+1);
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
bool isValid_placement(State &state, int col)
{
    int row = state.row + 1;
    // Because each state will only ever have one queen on a row and we work from top down,
    // we only need to check diagonals up and straight up

    // Start at the potential placement and check all values above
    // start at the row above
    for (int r = row; r >= 0; r --) {
        if (state.board[r][col])
            return false;
    }

    // Start at the potential placement and check all values above-diagonally-to-the-left
    // formula is incrementing [row-1][col-1]
    int r = row-1; int c = col-1; // start at the square up-to-left
    while (r >= 0 && c >= 0) {
        if (state.board[r][c])
            return false;
        r--;
        c--;
    }

    // Start at the potential placement and check all values above-diagonally-to-the-right
    // formula is incrementing [row-1][col+1]
    r = row-1; c = col+1; // start at the square up-to-right
    while (r >= 0 && c < state.board.size()) {
        if (state.board[r][c])
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
    std::queue<State> queue;

    // Push the initial empty board state
    queue.push(State(board,-1)); // initially at row 0

    // Run BFS
    while (!queue.empty())
    {
        // pop from the queue
        State currentState = queue.front();
        queue.pop();


        for (int col=0; col<n; col++) {
            // Only explore the path if the placement is valid
            if (isValid_placement(currentState, col)) {
                // place the valid child board with the current row context at parent row + 1
                queue.push(place_queen(currentState, col));
            }
        }

        // If row = N, we are that the end of the board, meaning we placed N queens which are all in valid states
        // add it to the solutions, else discard it
        if (currentState.row == n) {
            solutions.push_back(currentState.board);
        }
    }
}





int main() {

    int n;

    std::cout<< "Input N: "; std::cin >> n;
    std::cout<< std::endl;

    solve_bfs(n);

    return 0;
}
