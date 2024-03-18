#pragma once
#ifndef SUBSETSUM_H
#define SUBSETSUM_H

#include <vector>

class SubsetSumSolver {
public:
    SubsetSumSolver(const std::vector<int>& set, int targetSum);
    bool existsSubset();
    double getElapsedTime() const; // Método para obtener el tiempo de ejecución en segundos

private:
    const std::vector<int>& set;
    int targetSum;
    bool subsetSum(int n, int sum);
    double elapsedTime; // Almacenar el tiempo de ejecución
};

#endif // SUBSETSUM_H

