'''
    Часть 11: базовые структуры данных pandas.

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

        -> другой объект типа Series
            first = pd.Series([3, 4, 8, 5])
            second = pd.Series(first)
            third = pd.Series(first, index=[0, 2, 3])
        Аргумнент *index* в данном контексте задаёт те индексы, которые будут взяты из исходного набора данных
'''
# Для примера, пусть есть список со значениями:
some_list = ['AB', 'CD', 'WX', 'QN']
print(f"[Шаг 1] Данные для примера: {some_list}\n")

# Создаём объект Series
first_series = pd.Series(some_list)
print(f"[Шаг 2] серия:\n{first_series}\n")

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
    аттрибут *index*. В данном случае, тип индекса будет - RangeIndex, который представляет собой простой
    целочисленный диапазон с шагом 1.
'''
print(f"[Шаг 3] индекс созданной серии: {first_series.index}\n")

'''
    Поскольку серия представляет собой одномерный массив, ей доступен оператор индексации для получения/изменения
    значений набора данных. В качестве индекса, как и со стандартными перечислимыми объектами python'а, может 
    выступать либо значение конкретной метки, либо срез (slice).
'''
print(f"[Шаг 4] третий элемент first_series: {first_series[2]}\n")

'''
    Для демонстрации работы со срезами, создадим ещё один объект Series и вручную зададим индексы, на этот раз -
    строковые. При создании серии из стандартного python'ого списка количество элементов в нём и в списке 
    для индексации должны совпадать.
'''
second_series = pd.Series([5.5, 1.5, 4.5, 3.7, 9.95], index=['a', 'b', 'c', 'd', 'e'])
print(f"[Шаг 5] ещё одна серия:\n{second_series}\n")

'''
    Теперь к элементам серии *second_series* можно обращаться через оператор индексации ("[]", он же - 
    квадратные скобки) используя и целочисленный, и строковый индексы.

    Плюс нюанс индексации: если индекс набора данных выбран библиотекой pandas по умолчанию (RangeIndex выше),
    то к нему невозможно применить отрицательную индексацию (как в стандартном списке в python). А вот для
    примера со строковым индексом - можно.
'''
print(f"[Шаг 6] доступ по строковому индексу: {second_series['d']}")
print(f"[Шаг 6] доступ по целочисленному индексу: {second_series[2]}\n")
print(f"[Шаг 6] последний элемент second_series: {second_series[-1]}\n")

'''
    Для получения нескольких значений серии применяются срезы (ака диапазоны). Значениями индексов среза
    выступают как целые числа, так и значения меток набора данных. 

    Основные особенности: 
        -> для целочисленных срезов правая граница не включается в получающийся набор данных, 
        для остальных типов значений - включается;

        -> если используются нецелочисленные индексы, то порядок их следования должен соблюдаться.
'''
print(f"[Шаг 7] целочисленный срез:\n{first_series[0:3]}\n===========")
print(f"[Шаг 7] снова он:\n{second_series[0:3]}\n===========")
print(f"[Шаг 7] строковый срез:\n{second_series['a':'d']}\n===========")
print(f"[Шаг 7] срез [-3:-1]:\n{second_series[-3:-1]}\n===========")
print(f"[Шаг 7] срез ['d':'a']:\n{second_series['d':'a']} (пустая серия, не содержащая ни одного элемента)\n")

'''
    С помощью индексации по меткам/целочисленным_индексам меняются или добавляются в наборе данных.

    Стоит заметить, что pandas достаточно гибко подходит к наборам данных и тем операциям, что с ними происходят.
    Так, после следующих изменений, объект *first_series* "поменяет"" самостоятельно тип индекса.
'''
first_series[5] = 'QQ'
print(f"[Шаг 8] индекс first_series теперь:\n{first_series.index}")
print(f"[Шаг 8] опять срез:\n{first_series[0:5]}")
 
second_series['c'] = -2.3 # поменяли значение в рамках сохранённого набора данных
second_series['g'] = 0.58 # добавили новый элемент в набор данных
print(f"[Шаг 8] second_series:\n{second_series}\n")

'''
    К объектам Series применяются векторизованные вычисления. Под таковыми понимают ситуации, когда применение 
    некоторых функций и/или математических операторов к некоторому объекту, представляющим собой набор данных,
    приводит к поэлементному выполнению этих самых функций и/или операторов.

    На практике, для объектов типа Series векторизованные вычисления применяются к каждой метке исходного набора
    данных. Если для какой-то метки невозможно выполнить требуемую операцию, то в итоговой серия соответствующей 
    метке будет проставлено значение NaN (изначально - "not-a-number", но в контексте pandas может означать и 
    значение, полученное в результате недопустимой операции, и отсутствующие данные).
'''
# ещё одна серия для примеров
third_series = pd.Series([4.4, -2.3, -1.5], index=['b', 'd', 'e'])
print(f"[Шаг 9] сумма серии (сама с собой):\n{second_series + second_series}")
print(f"[Шаг 9] сумма серий (разные индексы):\n{second_series + third_series}")
print(f"[Шаг 9] сумма серий (строковые значения):\n{first_series + first_series}\n===========")
exp_values = np.exp(second_series)
print(f"[Шаг 9] вычисление экспоненты на наборе:\n{exp_values}")
exp_values = np.sin(second_series)
print(f"[Шаг 9] или какая-нибудь тригонометрия:\n{exp_values}")