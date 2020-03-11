#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <queue>

/*
 * #######################################################################################
 *                                 N-Queens Problem
 * This program uses a breadth first search implementation to solve the N-Queens problem
 *
 * Created by ~ Caleb Howard
 *#######################################################################################
 */


// 2D Vector
typedef std::vector<std::vector<int>> chessboard;

// Class that contains a chessboard and an int - will be used to store a board and the current row context
struct State {
    State(chessboard board, const int &row) : board{std::move(board)}, row{row} {}

    // The current board configuration in this state
    chessboard board;

    // The row context of the current state
    const int row;

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

// This function prints a chessboard
void print_solution(const chessboard &board, int &count)
{
    // If the N is less than 7 then print the solution
    if (board.size() < 7) {
        for (const auto &row : board) {
            for (int square : row) {
                std::cout << square << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    // Increase the number of solutions
    count++;
}

// This function takes a parent board, copies the parent into a child and
// places a queen at the next row and given column in the child, then returns that child
State place_queen(State &state, int col)
{
    chessboard childBoard = state.board;

    childBoard[state.row+1][col] = 1;

    return State(childBoard, state.row+1); // The new state's context is on the row below the parent
}

// This method will check if a placement is valid, if it is not we will stop exploring that path in the BFS
bool isValid_placement(State &state, int col)
{
    int row = state.row + 1; // We are checking the placement on row after the current state

    // Because each state will only ever have one queen on a row and we work from top down,
    // we only need to check diagonals-up and straight up

    // Start at the potential placement and check all values above
    // start at the row above
    for (int r = row; r >= 0; r --) {
        if (state.board[r][col])
            return false;
    }

    // Start at the potential placement and check all values above-diagonally-to-the-left
    // formula is repetitively accessing [row-1][col-1] until we hit a wall/ceiling
    int r = row-1; int c = col-1; // start at the square up-and-to-the-left
    while (r >= 0 && c >= 0) {
        if (state.board[r][c])
            return false;
        r--;
        c--;
    }

    // Start at the potential placement and check all values above-diagonally-to-the-right
    // formula is repetitively accessing [row-1][col+1] until we hit a wall/ceiling
    r = row-1; c = col+1; // start at the square up-and-to-the--right
    while (r >= 0 && c < state.board.size()) {
        if (state.board[r][c])
            return false;
        r--;
        c++;
    }

    return true;
}

// This function runs the BFS on the chess boards and solves for N queens
// Returns a list of solutions - using a List as it has O(1) insertion and non-linear access does not matter
void solve_bfs(int &n)
{
    // Count of solutions
    int solutionCount= 0;

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

                State childState = place_queen(currentState, col);

                // If the row = N, we are that the end of the board, meaning we placed N queens which are all in valid states
                // else push it to the queue as we can explore further
                if (childState.row == n-1)
                    print_solution(childState.board, solutionCount);
                else
                    queue.push(place_queen(currentState, col));
            }
        }

    }

    // Print the number of solutions
    std::cout << "\nNumber of Solutions for " << n << " Queens: " << solutionCount << std::endl;

}


int main() {

    // N-Queens
    int n;

    std::cout<< "How many Queens should I solve?: "; std::cin >> n;
    std::cout<< std::endl;

    clock_t start_t, end_t;
    double cpu_time_used;

    start_t = clock();

    // Solve for n Queens
    solve_bfs(n);

    end_t = clock();
    cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

    std::cout << "\nI have slept for " << cpu_time_used << " seconds."  << std::endl;

    return 0;
}
