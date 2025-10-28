// 4.3 Планировщик процессов
// В операционной системе Technux есть планировщик процессов. 
// Каждый процесс характеризуется: приоритетом, временем, которое он уже отработал t,
// временем, которое необходимо для завершения работы процесса T 
// Планировщик процессов выбирает процесс с минимальным значением P * (t + 1), выполняет его время P и кладет обратно в очередь процессов.
// Если выполняется условие t >= T, то процесс считается завершенным и удаляется из очереди.

#include <iostream>
#include <algorithm>

template <typename T, bool (*cmp)(const T&, const T&)>
class Heap {
    public:

        Heap() : size(0), capacity(16) {
            arr = new T[capacity];
        }

        Heap(T* array, int size) : capacity(size), size(size) {
            arr = new T[capacity];
            std::copy(array, array + size, arr);
            heapify();
        }

        Heap(const Heap<T, cmp>& other) : size(other.size), capacity(other.capacity) {
            arr = new T[capacity];
            std::copy(other.arr, other.arr + size, arr);
        }

        Heap(Heap<T, cmp>&& other) : size(other.size), capacity(other.capacity), arr(other.arr) {
            other.arr = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        ~Heap() {
            delete[] arr;
        }

        void insert(T value) {
            if (size == capacity) {
                auto new_arr = new T[capacity * 2];
                for (int i = 0; i < size; ++i) {
                    new_arr[i] = arr[i];
                }
                delete[] arr;
                arr = new_arr;
                capacity *= 2;
            }
            arr[size++] = value;
            siftUp(size - 1);
        }

        T getRoot() {
            if (isEmpty())
                throw std::out_of_range("Heap is empty!");
            return arr[0];
        }

        T popRoot() {
            if (isEmpty())
                throw std::out_of_range("Heap is empty!");
            T root = arr[0];
            arr[0] = arr[--size];
            siftDown(0);
            return root;
        }

        bool isEmpty() {
            return size == 0;
        }

    private:
        T* arr;
        int size, capacity;
        
        // функция для построения кучи
        void heapify() {
            for (int i = size / 2 - 1; i >= 0; --i) {
                siftDown(i);
            }
        }
        void siftUp(int index) {
            while (index > 0) {
                int parent = (index - 1) / 2;
                if (cmp(arr[index], arr[parent])) {
                    std::swap(arr[parent], arr[index]);
                    index = parent;
                }
                else break;
            }
        }
        void siftDown(int index) {
            int smallest = index;
            while (smallest < size) {
                smallest = index;
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                
                if (left < size && cmp(arr[left], arr[smallest]))
                    smallest = left;
                if (right < size && cmp(arr[right], arr[smallest]))
                    smallest = right;

                // если какой-то из дочерних узлов меньше родительского
                if (smallest != index) {
                    std::swap(arr[index], arr[smallest]);
                    index = smallest;
                } else break; // если ни один из дочерних узлов меньше родительского, то это значит, что дальше опускаться не надо
            }
        }
};

struct Process {
    long long priority, time_working, time_required;
    
    public: 
        Process() : priority(0), time_working(0), time_required(0) {}

        Process(long long priority, long long time_required) 
        : priority(priority), time_working(0), time_required(time_required) {}
};

bool compare(const Process& a, const Process& b) {
    long long va = 1LL * a.priority * (a.time_working + 1);
    long long vb = 1LL * b.priority * (b.time_working + 1);
    return va < vb;   
}

int main() {
    int proc_count;
    std::cin >> proc_count;

    auto heap = Heap<Process, compare>();

    for (int i = 0; i < proc_count; ++i) {
        long long priority, time_required; 
        std::cin >> priority >> time_required;
        Process p = Process(priority, time_required);
        heap.insert(p);
    }

    int switch_count = 0;
    std::string s;
    while (!heap.isEmpty()) {
        Process p = heap.popRoot();
        // дебаг для выбранного процесса
    //     std::cout << "run " << switch_count << ": P=" << p.priority << " t_after=" << p.time_working 
    //  << " T=" << p.time_required << " val=" << p.priority*(p.time_working+1) << "\n";
    //     std::getline(std::cin, s);
        ++switch_count;
        p.time_working += p.priority;
        if (p.time_working >= p.time_required)
            continue;
        heap.insert(p);
    }

    std::cout << switch_count << std::endl;

    return 0;
}