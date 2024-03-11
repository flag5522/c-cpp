#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

// Define the objective function
double objectiveFunction(double x, double y)
{
    return pow(pow(x, 2) + y - 11, 2) + pow(x + pow(y, 2) - 7, 2);
}

// Define a structure for a point in 2D space
struct Point
{
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

// Define a structure for the result of the optimization
struct OptimizationResult
{
    Point point;
    int iterations;
    double finalValue;
};

// Function to generate a random point within a given range
Point generateRandomPoint(double minX, double maxX, double minY, double maxY)
{
    double x = (maxX - minX) * ((double)rand() / RAND_MAX) + minX;
    double y = (maxY - minY) * ((double)rand() / RAND_MAX) + minY;
    return Point(x, y);
}

// Function to perform First Choice Hill Climbing Search
OptimizationResult firstChoiceHillClimbing(Point start, double stepSize, int maxIterations)
{
    Point current = start;
    int iterations = 0;

    while (iterations < maxIterations)
    {
        double currentValue = objectiveFunction(current.x, current.y);

        // Check neighbors
        Point next = current;
        for (double dx = -stepSize; dx <= stepSize; dx += stepSize)
        {
            for (double dy = -stepSize; dy <= stepSize; dy += stepSize)
            {
                Point neighbor(current.x + dx, current.y + dy);
                double neighborValue = objectiveFunction(neighbor.x, neighbor.y);

                if (neighborValue < currentValue)
                {
                    next = neighbor;
                }
            }
        }

        if (current.x == next.x && current.y == next.y)
        {
            // No improvement found
            break;
        }

        current = next;
        iterations++;
    }

    return {current, iterations, objectiveFunction(current.x, current.y)};
}

// Function to perform Random Restart Hill Climbing Search
OptimizationResult randomRestartHillClimbing(Point start, double stepSize, int maxRestarts, int maxIterations)
{
    Point bestPoint = start;
    double bestValue = objectiveFunction(start.x, start.y);
    int totalIterations = 0;

    for (int restart = 0; restart < maxRestarts; restart++)
    {
        Point current = start;
        int iterations = 0;

        while (iterations < maxIterations)
        {
            double currentValue = objectiveFunction(current.x, current.y);

            // Check neighbors
            Point next = current;
            for (double dx = -stepSize; dx <= stepSize; dx += stepSize)
            {
                for (double dy = -stepSize; dy <= stepSize; dy += stepSize)
                {
                    Point neighbor(current.x + dx, current.y + dy);
                    double neighborValue = objectiveFunction(neighbor.x, neighbor.y);

                    if (neighborValue < currentValue)
                    {
                        next = neighbor;
                    }
                }
            }

            if (current.x == next.x && current.y == next.y)
            {
                // No improvement found
                break;
            }

            current = next;
            iterations++;
        }

        totalIterations += iterations;

        // Update best point and value
        double currentBestValue = objectiveFunction(current.x, current.y);
        if (currentBestValue < bestValue)
        {
            bestPoint = current;
            bestValue = currentBestValue;
        }
    }

    return {bestPoint, totalIterations, bestValue};
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    double minX = -5.0, maxX = 5.0;
    double minY = -5.0, maxY = 5.0;

    // User input for starting point and step size
    std::cout << "Enter the starting point (x y): ";
    double startX, startY;
    std::cin >> startX >> startY;

    std::cout << "Enter the step size (between 0.1 and 0.5): ";
    double stepSize;
    std::cin >> stepSize;

    // User input for random restarts
    std::cout << "Enter the number of random restarts: ";
    int maxRestarts;
    std::cin >> maxRestarts;

    // User input for maximum iterations per restart
    std::cout << "Enter the maximum iterations per restart: ";
    int maxIterations;
    std::cin >> maxIterations;

    Point startPoint(startX, startY);

    // First Choice Hill Climbing Search
    OptimizationResult firstChoiceResult = firstChoiceHillClimbing(startPoint, stepSize, maxIterations);
    std::cout << "\nFirst Choice Hill Climbing Search Result:\n";
    std::cout << "Optimal Point: (" << firstChoiceResult.point.x << ", " << firstChoiceResult.point.y << ")\n";
    std::cout << "Iterations: " << firstChoiceResult.iterations << "\n";
    std::cout << "Final Value: " << firstChoiceResult.finalValue << "\n\n";

    // Random Restart Hill Climbing Search
    OptimizationResult randomRestartResult =
        randomRestartHillClimbing(startPoint, stepSize, maxRestarts, maxIterations);
    std::cout << "Random Restart Hill Climbing Search Result:\n";
    std::cout << "Optimal Point: (" << randomRestartResult.point.x << ", " << randomRestartResult.point.y << ")\n";
    std::cout << "Total Iterations: " << randomRestartResult.iterations << "\n";
    std::cout << "Best Value: " << randomRestartResult.finalValue << "\n";

    return 0;
}
