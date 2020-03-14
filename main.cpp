#include <iostream>
#include "BFS/BFS_NQueens.h"
#include "SA_HC/NQueens.h"

/*
 * #######################################################################################
 *                                 N-Queens Problem
 * This program can use the following algorithms to solve the N-Queens problem:
 * - a breadth first search implementation to find ALL solutions
 * - a Hill Climbing implementation to find a SINGLE solution
 * - a Simulated Annealing algorithm to find a SINGLE solution
 *
 * Created by ~ Caleb Howard
 *#######################################################################################
 */

// Takes an option and the N value and runs an algorithm based on the option
void run(const uint32_t &opt, int &n) {

    clock_t start_t, end_t;
    double cpu_time_used;

    switch (opt) {
        case 1:
            start_t = clock(); // track time
            solve_bfs(n);
            end_t = clock();
            break;
        case 2:
            start_t = clock(); // track time
            NQueens().solve_hill_climbing(n);
            end_t = clock();
            break;
        case 3:
            start_t = clock(); // track time
            NQueens().solve_simulated_annealing(n, 4000, 0.99);
            end_t = clock();
            break;
        default: std::cout << opt << " is not a valid option, please try again.\n" << std::endl;
    }

    cpu_time_used = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

    std::cout << "\nAlgorithm run time: " << cpu_time_used << " seconds.\n"  << std::endl;
}

int main() {

    std::cout<< "Welcome to the N-Queens Solver ~ Created by Caleb Howard.\n" << std::endl;

    // Program loop
    int opt = 0;
    while (true)
    {
        // N-Queens
        int n;

        // Choose Algorithm
        std::cout << "Choose from the following algorithms:\n1. BFS (all solutions).\n2. Hill Climbing (single solution).\n"
                     "3. Simulated Annealing (single solution).\n4. Exit program." << std::endl;
        std::cin >> opt;

        if (opt == 4) {
            std::cout<< "\nBye!";
            break;
        }

        // Choose the number of Queens
        std::cout<< "\nHow many Queens should be solved?: "; std::cin >> n;
        std::cout << std::endl;

        // run algorithm
        run(opt, n);

    }



    return 0;
}


//#include <iostream>
//#include <random>
//#include <vector>
//#include <algorithm>
//#define TEMPERATURE 4000
//
//void print_chessboard(std::vector<int> chess_board) { // print the chessboard
//    for (int queen = 0; queen < chess_board.size(); queen++) {
//        for (int row = 0; row < chess_board.size(); row++) {
//            if (chess_board[queen] == row)
//                std::cout << "1 ";
//            else
//                std::cout << "0 ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << std::endl;
//}
//
//int threat_calculate(int n) { // combination formula for calculate number of pairs of threaten queens
//    if (n < 2) return 0;
//    if (n == 2) return 1;
//    return (n - 1) * n / 2;
//}
//
//int cost(std::vector<int> chess_board) { // cost function to count total of pairs of threaten queens
//    unsigned long size = chess_board.size();
//    int threat = 0;
//    int m_chessboard[size];
//    int a_chessboard[size];
//
//    for (int i = 0; i < size; i++) {
//        a_chessboard[i] = i + chess_board[i];
//        m_chessboard[i] = i - chess_board[i];
//    }
//
//    std::sort(m_chessboard, m_chessboard + size);
//    std::sort(a_chessboard, a_chessboard + size);
//
//    int m_count = 1;
//    int a_count = 1;
//
//    for (int i = 0; i < size - 1; i++) {
//        int j = i + 1;
//        if (m_chessboard[i] == m_chessboard[j]) m_count += 1;
//        else {
//            threat += threat_calculate(m_count);
//            m_count = 1;
//        }
//        if (a_chessboard[i] == a_chessboard[j]) a_count += 1;
//        else {
//            threat += threat_calculate(a_count);
//            a_count = 1;
//        }
//        if (j == size - 1) {
//            threat += threat_calculate(m_count);
//            threat += threat_calculate(a_count);
//            break;
//        }
//    }
//
//    return threat;
//}
//
//int main() {
//    clock_t start = clock();
//    srand((unsigned int) time(nullptr));
//    std::random_device rd;
//    std::mt19937 g(rd());
//
//    std::vector<int> answer;
//    unsigned int n_queens; // number of queens
//
//    std::cout << "Number of queens: ";
//    std::cin >> n_queens;
//
//    // create a chess board
//    answer.reserve(n_queens);
//    for (int i = 0; i < n_queens; i++) { // create a vector from 0 to N_QUEENS - 1
//        answer.emplace_back(i);
//    }
//    std::shuffle(answer.begin(), answer.end(), g); //shuffle chess board to make sure it is random
//    int cost_answer = cost(answer); // To avoid recounting in case can not find a better state
//
//    // simulated annealing
//    std::vector<int> successor;
//    successor.reserve(n_queens);
//    double t = TEMPERATURE;
//    double sch = 0.99;
//    while (t > 0) {
//        int rand_col_1;
//        int rand_col_2;
//        t *= sch;
//        successor = answer;
//        while (true) { // random 2 queens
//            rand_col_1 = (int) random() % n_queens;
//            rand_col_2 = (int) random() % n_queens;
//            if (successor[rand_col_1] != successor[rand_col_2]) break;
//        }
//        std::swap(successor[rand_col_1], successor[rand_col_2]); // swap two queens chosen
//        double delta = cost(successor) - cost_answer;
//        if (delta < 0) {
//            answer = successor;
//            cost_answer = cost(answer);
//        } else {
//            double p = exp(-delta / t);
//            if (random() / double(RAND_MAX) < p) {
//                answer = successor;
//                cost_answer = cost(answer);
//            }
//        }
//        if (cost_answer == 0) {
//            print_chessboard(answer);
//            break;
//        }
//    }
//
//    clock_t stop = clock();
//    std::cout << "Runtime: " << (float) (stop - start) / 1000000 << " seconds" << std::endl;
//
//    return 0;
//}
