#include "SortingFunctions.h"


std::vector<std::vector<float>> generate_bubble_sort(uint32_t n, std::vector<float>& arr)
{
	std::vector<std::vector<float>> iterations;

	bool swapped;
	for (uint32_t i = 0; i < n - 1; ++i) {
		swapped = false;
		for (uint32_t j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;

		iterations.push_back(arr);
	}
	return iterations;
}

std::vector<std::vector<float>> generate_insertion_sort(uint32_t n, std::vector<float>& arr)
{
	std::vector<std::vector<float>> iterations;

	for (uint32_t i = 1; i < n; ++i)
	{
		float key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;

		iterations.push_back(arr);
	}

	return iterations;
}

std::vector<std::vector<float>> generate_selection_sort(uint32_t n, std::vector<float>& arr)
{
	std::vector<std::vector<float>> iterations;

	for (uint32_t i = 0; i < n - 1; ++i)
	{
		uint32_t minIndex = i;
		for (uint32_t j = i + 1; j < n; ++j)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		if (minIndex != i)
			std::swap(arr[i], arr[minIndex]);

		iterations.push_back(arr);
	}

	return iterations;
}


uint32_t partition(std::vector<float>& arr, uint32_t low, uint32_t high) {
    float pivot = arr[high];
    uint32_t i = low - 1;

    for (uint32_t j = low; j <= high - 1; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<std::vector<float>>& iterations, std::vector<float>& arr, int low, int high) {
    if (low < high) {
        uint32_t pi = partition(arr, low, high);

        quickSort(iterations, arr, low, pi - 1);
        quickSort(iterations, arr, pi + 1, high);

        iterations.push_back(arr);
    }
}

void merge(std::vector<float>& arr, uint32_t left, unsigned mid, uint32_t right)
{
    uint32_t n1 = mid - left + 1;
    uint32_t n2 = right - mid;

    std::vector<float> leftArr(n1);
    std::vector<float> rightArr(n2);

    for (uint32_t i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (uint32_t j = 0; j < n2; ++j) {
        rightArr[j] = arr[mid + 1 + j];
    }

    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        }
        else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<std::vector<float>>& iterations, std::vector<float>& arr, uint32_t left, uint32_t right)
{
    if (left < right) {
        uint32_t mid = left + (right - left) / 2;

        mergeSort(iterations, arr, left, mid);
        mergeSort(iterations, arr, mid + 1, right);

        merge(arr, left, mid, right);

        iterations.push_back(arr);
    }
}


std::vector<std::vector<float>> generate_merge_sort(uint32_t n, std::vector<float>& arr)
{
	std::vector<std::vector<float>> iterations;

	mergeSort(iterations, arr, 0, n - 1);

	return iterations;
}

std::vector<std::vector<float>> generate_quick_sort(uint32_t n, std::vector<float>& arr)
{
	std::vector<std::vector<float>> iterations;

	quickSort(iterations, arr, 0, n - 1);

	return iterations;
}
