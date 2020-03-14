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