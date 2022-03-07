// ПиАА 2022, Обрубов Илья Игоревич, БПИ208.
// Среда разработки Clion
// Реализованы все 12 сортировок, все 4 вида массивов, все их длины. Есть массив указателей на
// функции и эксперимент включающий в себя разные виды массива и методы сортировки, т.е. с 4-мя
// вложенными циклами. Есть проверка на отсортированность и вывод в файлы. Все графики есть.
// Т.е. все, что было описано - сделано, кроме создания CSV файла в самом коде. Таблицы создавались
// вручную и экспортировались из Excel.

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <ctime>
#include <string>

// 1) Сортировка выбором:
void selectionSort(int32_t *array, int32_t n) {
    int min;
    for (int i = 0; i < n - 1; ++i) {
        min = i;
        for (int j = i + 1; j < n; ++j) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        std::swap(array[i], array[min]);
    }
}

// 2) Сортировка пузырьком:
void bubbleSort(int32_t *array, int32_t n) {
    for (int i = 0; i <= n - 2; ++i) {
        for (int j = 0; j <= n - i - 2; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

// 3) Сортировка пузырьком с условием Айверсона 1:
void bubbleSortIverson1(int32_t *array, int32_t n) {
    int i = 0;
    bool iverson_flag = true;
    while (iverson_flag) {
        iverson_flag = false;
        for (int j = 0; j <= n - i - 2; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                iverson_flag = true;
            }
        }
        i += 1;
    }
}

// 4) Сортировка пузырьком с условием Айверсона 1+2:
void bubbleSortIverson12(int32_t *array, int32_t n) {
    int32_t t = n - 2;
    for (int i = 0; i <= t; ++i) {
        t = 0;
        for (int j = 0; j <= n - i - 2; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                t = j + 1;
            }
        }
        if (t == 0) {
            return;
        }
    }
}

// 5) Сортировка простыми вставками:
void insertionSort(int32_t *array, int32_t n) {
    int32_t key;
    int32_t j;
    for (int index = 1; index < n; ++index) {
        key = array[index];
        j = index - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j -= 1;
        }
        array[j + 1] = key;
    }
}

// 6) Сортировка бинарными вставками:
void binaryInsertionSort(int32_t *array, int32_t n) {
    int32_t mid;
    int32_t left;
    int32_t right;
    int32_t key;
    for (int index = 1; index < n; ++index) {
        if (array[index - 1] > array[index]) {
            key = array[index];
            left = 0;
            right = index - 1;
            do {
                mid = left + (right - left) / 2;
                if (array[mid] < key) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } while (left <= right);
            for (int j = index - 1; j >= left; --j) {
                array[j + 1] = array[j];
            }
            array[left] = key;
        }
    }
}

// 7) Сортировка подсчетом (устойчивая):
void countingSort(int32_t *array, int32_t n) {
    int32_t max = array[0];
    for (int i = 1; i < n; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    int32_t c[max + 1];
    for (int i = 0; i <= max; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        c[array[i]]++;
    }
    for (int i = 0, j = 0; i <= max; i++) {
        while (c[i] > 0) {
            array[j] = i;
            j++;
            c[i]--;
        }
    }
}

// Цифровая сортировка:
void radixSort(int32_t *array, int32_t n) {
    int32_t max = array[0];
    int32_t exp = 1;
    for (int i = 1; i < n; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    int32_t *result = array;
    while (max / exp > 0) {
        int output[n];
        int i, count[10] = {0};
        for (i = 0; i < n; i++) {
            count[(array[i] / exp) % 10]++;
        }
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            output[count[(array[i] / exp) % 10] - 1] = array[i];
            count[(array[i] / exp) % 10]--;
        }
        for (i = 0; i < n; i++) {
            array[i] = output[i];
        }
        exp = exp * 10;
    }
    array = result;
}

// Сортировка слиянием:
void mergeLists(int32_t *array, int32_t left, int32_t right, int32_t middle) {
    int32_t i, j, k;
    int32_t *c = array;
    i = left;
    k = left;
    j = middle + 1;
    while (i <= middle && j <= right) {
        if (array[i] < array[j]) {
            c[k] = array[i];
            k++;
            i++;
        } else {
            c[k] = array[j];
            k++;
            j++;
        }
    }
    while (i <= middle) {
        c[k] = array[i];
        k++;
        i++;
    }
    while (j <= right) {
        c[k] = array[j];
        k++;
        j++;
    }
    for (i = left; i < k; i++) {
        array[i] = c[i];
    }
}

void recursiveMergeSort(int32_t *array, int32_t left, int32_t right) {
    int middle;
    if (left < right) {
        middle = left + (right - left) / 2;
        recursiveMergeSort(array, left, middle);
        recursiveMergeSort(array, middle + 1, right);
        mergeLists(array, left, right, middle);
    }
}

void mergeSort(int32_t *array, int32_t n) {
    return recursiveMergeSort(array, 0, n - 1);
}

// 10.1) Быстрая сортировка (разбиением Хоара):
void recursiveQuickSortHoar(int32_t *array, int32_t first, int32_t last) {
    int32_t mid, count;
    int32_t f = first, l = last;
    mid = array[first + (last - first) / 2];
    do {
        while (array[f] < mid) {
            f++;
        }
        while (array[l] > mid) {
            l--;
        }
        if (f <= l) {
            count = array[f];
            array[f] = array[l];
            array[l] = count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) {
        recursiveQuickSortHoar(array, first, l);
    }
    if (f < last) {
        recursiveQuickSortHoar(array, f, last);
    }
}

void quickSortHoar(int32_t *array, int32_t n) {
    return recursiveQuickSortHoar(array, 0, n - 1);
}

// 10.2) Быстрая сортировка (разбиение Ломуто):
void recursiveQuickSortLomuto(int32_t *array, int32_t low, int32_t high) {
    if (low < high) {
        int32_t pivot = array[high];
        int32_t i = low - 1;
        for (int j = low; j < high; ++j) {
            if (array[j] <= pivot) {
                std::swap(array[++i], array[j]);
            }
        }

        if (array[high] < array[i + 1]) {
            std::swap(array[i + 1], array[high]);
        }

        int32_t partition = i + 1;
        recursiveQuickSortLomuto(array, low, partition - 1);
        recursiveQuickSortLomuto(array, partition + 1, high);
    }
}

void quickSortLomuto(int32_t *array, int32_t n) {
    return recursiveQuickSortLomuto(array, 0, n - 1);
}

// 11) Пирамидальная сортировка:
void heapify(int32_t *array, int32_t length, int32_t index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    if (right < length && array[right] > array[largest]) {
        largest = right;
    }
    if (left < length && array[left] > array[largest]) {
        largest = left;
    }
    if (largest != index) {
        std::swap(array[index], array[largest]);
        heapify(array, length, largest);
    }
}

void heapSort(int32_t *array, int32_t n) {
    for (int32_t i = n / 2 - 1; i != -1; --i) {
        heapify(array, n, i);
    }
    for (int32_t i = n - 1; i > 0; --i) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

int main() {
    srand(std::clock());
    void (*functions[12])(int32_t *, int32_t) = {
        selectionSort, bubbleSort,          bubbleSortIverson1, bubbleSortIverson12,
        insertionSort, binaryInsertionSort, countingSort,       radixSort,
        mergeSort,     quickSortHoar,       quickSortLomuto,    heapSort};

    std::vector<std::string> function_names = {"Выбором",
                                               "Пузырек",
                                               "Пузырек + Айверсон 1",
                                               "Пузырек + Айверсон 1 + 2",
                                               "Простыми вставками",
                                               "Бинарными вставками",
                                               "Подсчетом",
                                               "Цифровая",
                                               "Слиянием",
                                               "Быстрая + Хоара",
                                               "Быстрая + Ломуто",
                                               "Пирамидальная"};

    std::vector<std::string> array_names = {"Случайные 0-5", "Случайные 0-4000",
                                            "Почти отсортированный", "Обратный порядок"};
    // Вывод отсортированного и исходного массива в файлы
    std::ofstream out_input_array;
    out_input_array.open("input.txt");
    std::ofstream out_output_array;
    out_output_array.open("output.txt");
    int32_t *array = new int32_t[4100];
    // Прогон функций в холостую
    for (auto function : functions) {
        for (int i = 0; i < 4100; ++i) {
            array[i] = static_cast<int32_t>(random()) % 4001;
        }
        function(array, 4100);
    }
    bool is_sorted = false;
    // Заполнение эталонного массива
    for (int array_type = 0; array_type < 4; ++array_type) {
        if (array_type == 0) {
            // Массив заполненныйы случайными значениями от 0 до 5
            for (int i = 0; i < 4100; ++i) {
                array[i] = static_cast<int32_t>(random()) % 6;
            }
        } else if (array_type == 1) {
            // Массив заполненныйы случайными значениями от 0 до 4000
            for (int i = 0; i < 4100; ++i) {
                array[i] = static_cast<int32_t>(random()) % 4001;
            }
        } else if (array_type == 2) {
            // Отсортированный массив в котором N пар элементов в каждой тысяче поменяли местами
            for (int i = 0; i < 4100; ++i) {
                array[i] = i;
            }
            int n = 50;
            for (int i = 1; i < 5; ++i) {
                for (int j = 0; j < n; ++j) {
                    int32_t index1 = i * static_cast<int64_t>(random()) % 1001;
                    int32_t index2 = i * static_cast<int64_t>(random()) % 1001;
                    std::swap(array[index1], array[index2]);
                }
            }
        } else {
            // Массив отсортированный в обратном порядке
            for (int i = 0; i < 4100; ++i) {
                array[i] = 4099 - i;
            }
        }
        int function_id = 0;
        // Цикл по массиву указателей на функцию
        for (auto function : functions) {
            int32_t *new_array;
            out_input_array << "Сортировка: " << function_names[function_id] << '\n';
            out_output_array << "Сортировка: " << function_names[function_id] << '\n';
            // Сортировка массивов длины [50, 300] с шагом 10
            for (int i = 50; i <= 300; i += 10) {
                new_array = new int32_t[i];
                u_int64_t sum = 0;
                // Копирование элементов из эталонного массива
                for (int j = 0; j < i; ++j) {
                    new_array[j] = array[j];
                }
                std::string array_string;
                for (int j = 0; j < i; ++j) {
                    array_string += std::to_string(new_array[j]) + ' ';
                }
                out_input_array << "Тип массива: " << array_names[array_type] << ". Длина: " << i
                                << ". " << array_string << '\n';
                for (int j = 0; j < 12; ++j) {
                    // Пропуск пары прогонов
                    if (j < 2) {
                        function(new_array, i);
                        delete[] new_array;
                        new_array = new int32_t[i];
                        for (int k = 0; k < i; ++k) {
                            new_array[k] = array[k];
                        }
                        continue;
                    }
                    delete[] new_array;
                    new_array = new int32_t[i];
                    for (int k = 0; k < i; ++k) {
                        new_array[k] = array[k];
                    }
                    auto start = std::chrono::high_resolution_clock::now();
                    function(new_array, i);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    int64_t microseconds =
                        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

                    sum += microseconds;
                }
                u_int64_t result_time = sum / 10;
                // Проверка на отсортированность
                is_sorted = true;
                for (int j = 0; j < i - 1; ++j) {
                    if (new_array[j + 1] < new_array[j]) {
                        is_sorted = false;
                        break;
                    }
                }
                array_string = "";
                for (int j = 0; j < i; ++j) {
                    array_string += std::to_string(new_array[j]) + ' ';
                }
                out_output_array << "Тип массива: " << array_names[array_type] << ". Длина: " << i
                                 << ". " << array_string << '\n';
                std::cout << "Тип массива: " << array_names[array_type] << ". Размер массива: " << i
                          << ". Сортировка " << function_names[function_id]
                          << " Отсортировано: " << is_sorted << ". Время: " << result_time
                          << " microseconds." << '\n';
                delete[] new_array;
            }
            std::cout << '\n';
            // Сортировка массивов длины [100, 4100] с шагом 100
            for (int i = 100; i <= 4100; i += 100) {
                u_int64_t sum = 0;
                new_array = new int32_t[i];
                for (int j = 0; j < i; ++j) {
                    new_array[j] = array[j];
                }
                std::string array_string;
                for (int j = 0; j < i; ++j) {
                    array_string += std::to_string(new_array[j]) + ' ';
                }
                out_input_array << "Тип массива: " << array_names[array_type] << ". Длина: " << i
                                << ". " << array_string << '\n';
                for (int j = 0; j < 12; ++j) {
                    // Пропуск пары прогонов
                    if (j < 2) {
                        function(new_array, i);
                        delete[] new_array;
                        new_array = new int32_t[i];
                        for (int k = 0; k < i; ++k) {
                            new_array[k] = array[k];
                        }
                        continue;
                    }

                    delete[] new_array;
                    new_array = new int32_t[i];
                    for (int k = 0; k < i; ++k) {
                        new_array[k] = array[k];
                    }
                    auto start = std::chrono::high_resolution_clock::now();
                    function(new_array, i);
                    auto elapsed = std::chrono::high_resolution_clock::now() - start;
                    int64_t microseconds =
                        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

                    sum += microseconds;
                }
                u_int64_t result_time = sum / 10;
                // Проверка на отсортированность
                is_sorted = true;
                for (int j = 0; j < i - 1; ++j) {
                    if (new_array[j + 1] < new_array[j]) {
                        is_sorted = false;
                        break;
                    }
                }
                array_string = "";
                for (int j = 0; j < i; ++j) {
                    array_string += std::to_string(new_array[j]) + ' ';
                }
                out_output_array << "Тип массива: " << array_names[array_type] << ". Длина: " << i
                                 << ". " << array_string << '\n';
                std::cout << "Тип массива: " << array_names[array_type] << ". Размер массива: " << i
                          << ". Сортировка " << function_names[function_id]
                          << " Отсортировано: " << is_sorted << ". Время: " << result_time
                          << " microseconds." << '\n';
                delete[] new_array;
            }
            out_input_array << "\n\n";
            out_output_array << "\n\n";
            std::cout << '\n';
            function_id += 1;
        }
    }
    out_input_array.close();
    out_output_array.close();
    delete[] array;
    return 0;
}
