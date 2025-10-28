// 2.2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, 
// а на интервале [m, n-1] строго убывают. Найти m за O(log m). 
// Требования:  Время работы O(log m). Внимание! В этой задаче сначала нужно определить диапазон для 
// бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.


#include <iostream>

int main() {
    int len;
    std::cin >> len;

    int* arr = new int[len];
    for (int i = 0; i < len; ++i) {
        std::cin >> arr[i];
    }

    int max = arr[0];
    int left = 0, right = 1;
    while (right < len - 1) {
        if (arr[left] < arr[right]) {
            left = right;
            right = std::min(right * 2, len - 1);
        }
        else break;
    }
    

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < arr[mid + 1])
            left = mid + 1;
        else 
            right = mid;
    }

    std::cout << left << std::endl;

    delete[] arr;

    return 0;
}