# Сравнение основных алгоритмов сортировок на языке C++
Проведение экспериментов – измерение времени выполнения 12 алгоритмов сортировки

Алгоритмы сортировок:

1) выбором
2) пузырьком
3) пузырьком с условием Айверсона 1
4) пузырьком с условием Айверсона 1+2
5) простыми вставками
6) бинарными вставками
7) подсчетом (устойчивая)
8) цифровая
9) слиянием
10) быстрая (разбиение Хоара и разбиение Ломуто)
11) пирамидальная

Измерения проводятся для размеров массива (включительно)

   • от 50 до 300, шаг 10

   • от 100 до 4100 , шаг 100

Для массивов, заполненных целыми неотрицательными числами:

   • случайными значениями от 0 до 5

   • случайными значениями от 0 до 4000

   • «Почти» отсортированными в требуемом порядке числами (например, в каждой тысяче элементов поменять местами N пар элементов отсортированного массива)

   • Отсортированными в обратном порядке (по убыванию) числами от 4100 до 1
  
  Основной отчет находится в файле comparison.pdf
  
  Код в файлу main.cpp
  
  Таблицы с временем работы алгоритмов и графики в файлах формата .xls и .csv
