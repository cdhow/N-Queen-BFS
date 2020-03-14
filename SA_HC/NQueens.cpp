//
// Created by caleb on 12/3/20.
//


#include "NQueens.h"


std::vector<int> NQueens::createBoard()
{

    // Problem will not work for N < 1
    if (n_queens < 1) {
        std::cout << "The N-Queens Problem will not work for 3, 2, and values less than 1."
                     "\nDefaulting to N=8.\n" << std::endl;
        n_queens = 8;
    }

    std::random_device rd;
    std::mt19937 v(rd());

    std::vector<int> chessboard;

    // Create a chess board where the indexes are the rows and the values are the columns
    chessboard.reserve(n_queens);
    for (int i = 0; i < n_queens; i++) {
        chessboard.emplace_back(i);
    }

    // Randomise the board
    std::shuffle(chessboard.begin(), chessboard.end(), v);

    return chessboard;
}

int NQueens::cost(std::vector<int> &chessboard)
{
    int cost = 0;
    // Loop and check how many pairs of conflicts are in the current configuration
    for (int i=0; i<chessboard.size(); i++) {
        for (int j=i+1; j<chessboard.size(); j++) {
            if (chessboard[i] == chessboard[j] || abs(i-j) == abs(chessboard[i]-chessboard[j])) // conflict found
                cost++;
        }
    }
    return cost;
}

void NQueens::random_swap(std::vector<int> &chessboard)
{
    int rand_row1 = 0; int rand_row2 = 0;

    // Choose two random queens
    while (rand_row1 == rand_row2) {
        rand_row1 = (int)random() % n_queens;
        rand_row2 = (int)random() % n_queens;
    }

    // Swap the column positions
    std::swap(chessboard[rand_row1], chessboard[rand_row2]);
}

void NQueens::printBoard(std::vector<int> &chessboard)
{
    for (int queen = 0; queen < chessboard.size(); queen++) {
        for (int row = 0; row < chessboard.size(); row++) {
            if (chessboard[queen] == row)
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void NQueens::solve_simulated_annealing(const int &n, double t, const double &cooling_factor)
{
    srand((unsigned int) time(nullptr));

    this->n_queens = n;

    // Initial board
    std::vector<int> best_board(createBoard());

    // Initial cost
    int cost_best = cost(best_board);

    // simulated annealing
    std::vector<int> successor;
    successor.reserve(n_queens);

    while (t > 0)
    {
        t *= cooling_factor;
        successor = best_board;

        // Alter the success by swapping random queens
        random_swap(successor);

        double delta = cost(successor) - cost_best;

        // If successor cost is less than the current best cost
        if (delta < 0) {
            best_board = successor;
            cost_best = cost(best_board);
        } else {
            // Else calculate a probability and update the board based on that probability
            double p = exp(-delta / t);

            if (random() / double(RAND_MAX) < p) {
                best_board = successor;
                cost_best = cost(best_board);
            }
        }

        // Best board found - print
        if (cost_best == 0) {
            printBoard(best_board);
            break;
        }
    }
}

void NQueens::solve_hill_climbing(const int &n)
{
    // Set n_queens
    this->n_queens = n;

    std::vector<int> best_board(createBoard());
    int best_cost = cost(best_board);

    std::vector<int> successor;
    successor.reserve(n_queens);

    // Run until the best cost (heuristic) = 0
    while (best_cost)
    {
        successor = best_board;

        // Swap the the column positions of two random random queens
        random_swap(successor);

        // If the successor has a better cost, update the best_board and it's cost
        if (cost(successor) < best_cost) {
            best_board = successor;
            best_cost = cost(best_board);
        }

        // If the cost is 0 we have found a solution
        if (best_cost == 0) {
            // Print board
            printBoard(best_board);
            break;
        }

    }
}
