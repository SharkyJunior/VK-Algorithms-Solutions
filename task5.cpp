// 5_4. Закраска прямой 2.
// На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.


#include <iostream>
#include <vector>
#include <algorithm>

struct Pair {
    int left, right;

    Pair() : left(0), right(0) {};

    Pair(int left, int right) : left(left), right(right) {}
};

bool compare_lines(const Pair& pair1, const Pair& pair2) {
    if (pair1.left != pair2.left)
        return pair1.left < pair2.left;
    else return pair1.right < pair2.right;
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

    auto pairs = std::vector<Pair>();

    for (int i = 0; i < line_count; ++i) {
        int left, right;
        std::cin >> left >> right;
        pairs.push_back(Pair(left, right));
    }

    std::vector<Pair> events;
    for (auto& pair : pairs) {
        events.push_back({pair.left, 1});   
        events.push_back({pair.right, -1}); 
    }
    
    merge_sort<Pair, compare_lines>(events, 0, events.size() - 1);
    
    int coverage = 0;
    int last_pos = events[0].left;
    int total_length = 0;
    
    for (auto& event : events) {
        int pos = event.left;
        int type = event.right;
        
        if (coverage == 1) {
            total_length += (pos - last_pos);
        }
        
        coverage += type;
        last_pos = pos;
    }
    
    std::cout << total_length << std::endl;

    return 0;
}