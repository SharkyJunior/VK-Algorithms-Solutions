// 5_4. Закраска прямой 2.
// На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.


#include <iostream>
#include <vector>
#include <algorithm>

struct Line {
    int left, right;

    Line() : left(0), right(0) {};

    Line(int left, int right) : left(left), right(right) {}
};

bool compare_lines(const Line& line1, const Line& line2) {
    if (line1.left != line2.left)
        return line1.left < line2.left;
    else return line1.right < line2.right;
}

template <typename T, bool (*cmp)(const T&, const T&)>
void merge_sort(std::vector<T>& arr, int left, int right) {
    if (left >= right) return;

    // запускаем сорт для двух половинок массива рекурсивно
    int mid = left + (right - left) / 2;
    merge_sort<T, cmp>(arr, left, mid);
    merge_sort<T, cmp>(arr, mid + 1, right);

    // сливаем два подмассива в один отсортированный массив
    int len_left = mid - left + 1;
    int len_right = right - mid;

    std::vector<T> L(len_left), R(len_right);

    for (int i = 0; i < len_left; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < len_right; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int cur = left;

    while (i < len_left && j < len_right) {
        if (cmp(L[i], R[j]))
            arr[cur] = L[i++];
        else
            arr[cur] = R[j++];
        ++cur;
    }

    while (i < len_left)
        arr[cur++] = L[i++];
    while (j < len_right)
        arr[cur++] = R[j++];
}

int main() {
    int line_count;
    std::cin >> line_count;

    auto lines = std::vector<Line>();

    for (int i = 0; i < line_count; ++i) {
        int left, right;
        std::cin >> left >> right;
        lines.push_back(Line(left, right));
    }

    merge_sort<Line, compare_lines>(lines, 0, lines.size());

    for (const auto& line: lines) {
        std::cout << line.left << ' ' << line.right << std::endl;
    }

    // int total_length = 0;
    // int active = 0;
    // int prev_end = INT32_MIN;
    // int prev_start = -1;

    // for (const auto& line : lines) {
    //     if (line.left > prev_end) {
    //         if (active == 1) {
    //             total_length += (line.left - prev_start);
    //         }
    //         active = 1;
    //     }
    //     if (line.left < prev_end) {
    //         active++;
    //     }
    //     if (line.right )
    //     prev_start = line.left;
    //     prev_end = line.right;
    // }
    // if (active == 1) {
    //     total_length += (prev_end - prev_start);
    // }

    // std::cout << total_length << std::endl;

    return 0;
}