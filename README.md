# InformedSearch
Informed search using a-star algorithm for  CSCI 4350 Introduction to Artificial Intelligence
Overview

Develop a software agent in C++ to solve the 8-puzzle problem using A* search.
Procedure

    Create a C++ program which uses random actions to generate random starting states for the 8-puzzle problem (random_board.cpp)
        The goal configuration for the 8-puzzle is defined as follows (zero is the "blank" square):

        0 1 2
        3 4 5
        6 7 8

Your random board generator should read the input configuration from standard input, and two command-line arguments (integer: random number generator seed, integer: number of random moves to make), and should print the final configuration to standard output in the same format as the input file format (see above)

    Create a C++ program which performs A* search for the 8-puzzle problem (a-star.cpp)
        Your program should read an 8-puzzle from standard input, and take a single command line argument (integer: heuristic to use)
            0 - h(n) = 0
            1 - h(n) = Number of tiles displaced from the goal
            2 - h(n) = Sum of Manhattan (city-block) distances of all tiles from the goal
            3 - h(n) = A novel heuristic of your own design
        Each node should be given a unique ID number, starting with zero for the root node
        When sorting nodes in the frontier by f(n), ties should be broken by using the node ID number so that newer nodes will be preferred over older nodes
        Your program should output:
            The total number of nodes visited/expanded (V)
            The maximum number of nodes stored in memory (closed list + open list size) (N)
            The depth of the optimal solution (d)
            The -approximate- effective branching factor (b) where N = b^d
            Each state along the optimal path from the starting state to the goal state
