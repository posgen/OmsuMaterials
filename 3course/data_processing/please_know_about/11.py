'''
    Часть 18: базовые структуры данных pandas.

    pandas - библиотека для обработки и анализа двумерных (табличных) данных. Для примера, рассмотрим набор:
        
        | 4 | 3.5 | "AB" | 2022-02-09 |
        | 6 | 1.8 | "CD" | 2022-02-13 |
        | 7 | 8.4 | "WX" | 2022-02-13 |
        | 8 | 2.5 | "QN" | 2022-02-26 |

    Простая таблица из четырёх столбцов и четырёх строк, которая может создана программным образом, храниться в Excel-подобных 
    табличных редакторах, загружаться из баз данных. pandas даёт инструменты для выборки части данных из исходного набора, их группировки,
    их расширения, проведения статистических расчётов. Предоставляются функции для различных типов данных - численных, строковых, дат, 
    временных меток (дата + время) и прочих. И даже визуализация, встроенная в библиотеку, прилагается.

    Для удобства работы, pandas ко всем строкам и столбцам применяет концепцию расширенной индексации: каждая строка или столбец получает 
    свою метку (label). Структура исходных данных в рамках логики pandas становится:

                            столбец
                               |
                               v
                          __________
                         /          \  
                        |[label_col1]|   [label_col2] [label_col3]  [label_col4]
        { [label_row1] ||      4     | |     3.5     |     "AB"   |  2022-02-09  | } <- строка 
          [label_row2] ||      6     | |     1.8     |     "CD"   |  2022-02-13  |
          [label_row3] ||      7     | |     8.4     |     "WX"   |  2022-02-13  |
          [label_row4] ||      8     | |     2.5     |     "QN"   |  2022-02-26  |
                         \___________/

          \______________________________________________________________________/
                                            |
                                            v
                    объект типа DataFrame (pandas.DataFarame, с учётом имени модуля)

    Метками также могут быть различные типы данных. Технически говоря, метки индексируют столбцы
    и строки какими-то значениями.

    Исходные данные + два набора меток (для строки и столбцов, соответственно) в рамках библиотеки 
    представляются объектом типа - DataFrame. Это как раз представление 2D структуры данных с индексами 
    по обоим направлениям.

    Каждый столбец исходных данных представлен в виде объекта типа Series - одномерного проиндексированного 
    массива. На примере исходных данных, графически объект Series для третьей колонки можно изобразить как:

        [label_row1] | "AB" |
        [label_row2] | "CD" |
        [label_row3] | "WX" |
        [label_row4] | "QN" |
        \___________________/
                  |
                  v
      объект типа Series (pandas.Series)

    Для третьего столбца такой объект хранит 4 значения (строки а-ля "AB", ... выше) и позволяет обращаться
    к ним не только с помощью целочисленных индексов, но и с помощью соответствующих меток.

    Далее идут детали работы с объектами Series и DateFrame. Для начала, загружаем нужные пакеты Python'а
'''
import numpy as np # необязятелен, используется для примеров
import pandas as pd

'''
    Работа с объектом Series.

    Вручную объект типа Series создаётся путём передачи в конструктор типа некоторых данных. Общая форма:
        
        pd.Series(data, index=index)

    Аргумент с именем *index* является опциональным. *data* может быть объектом различных типов данных:
        -> обычный питоновский список
            pd.Series([3, 4, 8, 5])

        -> словарь
            pd.Series({'a': 4.5, 'b': -3.5, 'c': 6.7})
        !! при таком способе создания серии, ключи словаря становятся - метками, а значения - элементами хранимого 
        массива !!

        -> массивом ndarray из библиотеки numpy
            pd.Series(np.randn(5, dtype=float), index=['col1', 'col2', 'col3', 'col4', 'col5'])
            pd.Series(np.random.randn(3), index=['energy', 'mass', 'density'])

        -> объект, представляющий скаляр (единственное значение):
            pd.Series(78)
            pd.Series('my talk to world')
'''
# Для примера, пусть есть список со значениями:
some_list = ['AB', 'CD', 'WX', 'QN']
print(f"[Шаг 1] Данные для примера: {some_list}\n")

# Создаём объект Series
first_series = pd.Series(some_list)
print(f"[Шаг 2] серия: {first_series}\n")
'''
    При создании объекта не был задан опциональный аргумент *index*. В этом случае, pandas создаёт целочисленный
    индекс для переданного набора данных. Метки получают значения 0, 1, 2, ... и так далее с шагом 1. 
    Схематично выглядит так:

        0 | "AB" |
        1 | "CD" |
        2 | "WX" |
        3 | "QN" |
        \________/
            |
            v
        first_series

    Узнать, что за тип используется в качестве индекса (да и значения подсмотреть), можно запросив у объекта 
    следующий аттрибут:
'''
print(f"[Шаг 3] индекс созданной серии: {first_series.index}\n")
'''
    Поскольку серия представляет собой одномерный массив, ей доступен оператор индексации для получения/изменения
    значений набора данных. В качестве индекса, как и со стандартными перечислимыми объектами python'а, может 
    выступать либо значение конкретной метки, либо срез (slice).
'''
print(f"[Шаг 4] третий элемент first_series: {first_series[2]}\n")


