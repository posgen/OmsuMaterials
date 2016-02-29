/*
    Одна более-менее реальная программа.
    Задача была следующая: есть некоторый файл, содержащий последовательности чисел
    (в общем случае - действительных). Длина последовательности - известна, но не известно
    количество последовательностей в файле. Кроме всего прочено, есть вероятность появления не
    циферных символов в файле.

    Пример содержимого файла:
        1.3455 -2.2 4.5555 3f
        1.5 -3.4 -5.6 10
        5.6 7.8 -6.5 -8.2

    Тут размер последовательности - 4 числа, количество строк - 3.
    Нужно получить средние по каждой позиции. Вот тут и пригодилось посимвольное чтение.

    После компиляции запускать через командную строку как-то так:
        program.exe 4 to_average.dat
*/

#include <iostream>
#include <fstream>
#include <cctype>

#define FBUFFER 500

using namespace std;

void get_average(long double *array_for_averages, char* file_name, int buf)
{
	ifstream in;
	in.open(file_name, ios::binary);

	if ( !in ) {
	  cout << "Enable to opening file...";
      delete[] array_for_averages;
	  delete[] file_name;
	  exit(1);
	}

	double num;
	int i, n_buf = 0; // n_buf - количество полных последовательностей
	char ch;

	for (i = 0; i < buf; i++) {
        array_for_averages[i] = 0;
    }

	i = 0;
	do {
        // метод peek - считывает следующий символ из входного потока, но не меняет позицию в нём
        // Таким образом, далее мы можем считать тот же символ снова.
		ch = in.peek();

		if ( isdigit(ch) || ch == '-') {
            // Происходит чтение числа начиная с текущей позиции и до первого разделителя (пробел или новая строка)
			in >> num;

			array_for_averages[i] += num;
			i++;

			if (i == buf)
			{
				i = 0;
				++n_buf;
			}

		} else {
            // Если потенциальный симовол - не цифра и не знак отрицания, просто считываем текущий символ и идёт тестировать следующий
			in.get(ch);
		}
	} while( !in.eof() );

	for (i = 0; i < buf; i++) {
        array_for_averages[i] *= (1.0 / static_cast<double>(n_buf));
    }

	in.close();
	cout << "There was " << n_buf << " data sets." << endl;
}

int main(int argc, char* argv[])
{
	long double *av_result;
    int buf;

    if ( argc != 3 ) {
        cout << "Usage: " << argv[0] << " <bufer_size> <input_file>" << endl;
        return 1;
    }

    buf = atoi(argv[1]);

    av_result = new long double[buf];
    if( av_result == nullptr ) {
        cerr << "Error with memory.Exit...";
        return 1;
    }

    get_average(av_result, argv[2], buf);

    ofstream out("output.dat");
    out.precision(12);
    for (int i = 0; i < buf; i++) {
        out << av_result[i] << endl;
    }
    out.close();

	delete[] av_result;
	return 0;
}
