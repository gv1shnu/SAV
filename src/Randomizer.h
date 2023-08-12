#pragma once

#include <random>
#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iomanip> // Include this for std::setprecision

std::vector<float> randomArrayGenerator(int length, float minRange, float maxRange)
{
    // Create a random number generator
    std::random_device rd;   // Obtain a random seed from hardware
    std::mt19937 eng(rd());  // Seed the generator

    // Define the range of random integers for generating 1 decimal point
    int intMin = static_cast<int>(minRange * 10);
    int intMax = static_cast<int>(maxRange * 10);
    std::uniform_int_distribution<int> intDistr(intMin, intMax);

    // Create the vector and populate it with random floats
    std::vector<float> randomArray;
    for (int i = 0; i < length; ++i) {
        int intValue = intDistr(eng);
        randomArray.push_back(static_cast<float>(intValue) / 10.0f);
    }

    // Print the generated vector
    std::cout << "Random vector of length " << length << ":\n";
    for (float num : randomArray) {
        std::cout << std::fixed << std::setprecision(1) << num << " ";
    }
    std::cout << std::endl;

    return randomArray;
}

glm::vec4 generateRandomVec4(float minVal, float maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(minVal, maxVal);

    float x = dis(gen);
    float y = dis(gen);
    float z = dis(gen);
    float w = dis(gen);

    return glm::vec4(x, y, z, w);
}
