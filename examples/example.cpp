#include <chrono>
#include <chrono>
#include <iostream>
#include <string>

#include <min2phase/min2phase.h>  // Solver
#include <min2phase/tools.h>      // For randomCube(), setRandomSeed()

int main(int argc, char *argv[]) {
    uint8_t movesUsed;

    // Set a random seed using current time
    min2phase::tools::setRandomSeed(time(nullptr));

    // Step 1: Initialize solver from precomputed file (faster than full init)
    auto start = std::chrono::high_resolution_clock::now();
    // min2phase::init();               // Full initialization (slow)
    min2phase::loadFile("coords.m2pc"); // Load precomputed coordinates from file
    // min2phase::writeFile("coords.m2pc"); // Optional: write precomputed coordinates to file
    auto end = std::chrono::high_resolution_clock::now();

    // Step 2: Print time taken for initialization
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    // Step 3: Generate a random cube and solve it
    start = std::chrono::high_resolution_clock::now();
    std::cout << min2phase::solve(
        min2phase::tools::randomCube(),       // Random valid cube scramble
        21,                                   // Max number of moves (God's number is 20)
        1000000,                              // Max number of nodes to explore
        0,                                    // Timeout in milliseconds (0 = no timeout)
        min2phase::APPEND_LENGTH              // Show move count at end
        | min2phase::USE_SEPARATOR            // Add space between moves
        | min2phase::INVERSE_SOLUTION,        // Show inverse solution
        &movesUsed                            // Output: number of moves used
    ) << std::endl;
    end = std::chrono::high_resolution_clock::now();

    // Step 4: Print time taken to solve the cube
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    return 0;
}
