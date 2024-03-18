#include "subsetsum.h"
#include <chrono>

SubsetSumSolver::SubsetSumSolver(const std::vector<int>& set, int targetSum) : set(set), targetSum(targetSum), elapsedTime(0) {}

bool SubsetSumSolver::existsSubset() {
    auto start = std::chrono::high_resolution_clock::now();

    bool result = subsetSum(set.size(), targetSum);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    elapsedTime = elapsed_seconds.count(); // Almacenar el tiempo de ejecución en segundos

    return result;
}

bool SubsetSumSolver::subsetSum(int n, int sum) {
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(sum + 1, false));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= sum; ++j) {
            if (set[i - 1] > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
        }
    }

    return dp[n][sum];
}

double SubsetSumSolver::getElapsedTime() const {
    return elapsedTime;
}

