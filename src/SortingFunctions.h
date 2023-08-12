
#include <vector>


std::vector<std::vector<float>> generate_bubble_sort(uint32_t n, std::vector<float>& barHeights);
std::vector<std::vector<float>> generate_quick_sort(uint32_t n, std::vector<float>& barHeights);
std::vector<std::vector<float>> generate_merge_sort(uint32_t n, std::vector<float>& barHeights);
std::vector<std::vector<float>> generate_insertion_sort(uint32_t n, std::vector<float>& barHeights);
std::vector<std::vector<float>> generate_selection_sort(uint32_t n, std::vector<float>& barHeights);

uint32_t partition(std::vector<float>& arr, uint32_t low, uint32_t high);

void quickSort(std::vector<std::vector<float>>& iterations, std::vector<float>& arr, int low, int high);

void merge(std::vector<float>& arr, uint32_t left, unsigned mid, uint32_t right);

void mergeSort(std::vector<std::vector<float>>& iterations, std::vector<float>& arr, uint32_t left, uint32_t right);
