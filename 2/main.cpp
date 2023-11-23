#include<iostream>
#include<chrono>
#include<vector>
#include<thread>
using namespace std;
using namespace std::chrono;

void matrix_multiple(std::vector<std::pair <double, double> >& a, std::vector<std::pair <double, double> >& b, 
                    std::vector<std::pair <double, double> >& ans, size_t start, size_t end, int m, int n, int k){
    for (size_t i = start; i < end; i++){
        for (size_t j = 0; j < n; j++){
            double d_ans = 0.0; double m_ans = 0.0;
            for (size_t l = 0; l < k; l++){
                std::pair pair1 = a[m*i+l];
                std::pair pair2 = b[n*l+j];
                d_ans += pair1.first * pair2.first - pair1.second * pair2.second;
                m_ans += pair1.first * pair2.second + pair1.second * pair2.first;
            }
            ans.push_back(make_pair(d_ans,m_ans)); 
        }
    }
}

int main(int argc, char* argv[]) {
    
    if (argc != 2){
        cout << "Incorrect usage. Arguments are not instantiated" << endl;
        cout << "Usage: ./lr2 number_of_treads" << endl;
        exit(1);
    }

    size_t num_threads = atoi(argv[1]);

    //Матрица хранится в векторы пары. В первой ячейке действительная часть, во второй мнимая
    //Пример a + b*i, arr.first = a, arr.second = b
    //Умножение таких чисел: (a+bi)*(c+di) = ac+adi+bci-bd, тогда результат: res.first=ac-bd, res.second=ad+bc

    cout << "Enter the dimension of the matrices to be multiplied to fill them with random numbers" << endl;
    cout << "Matrix format: m*n, n*k, enter 3 natural numbers" << endl;
    int m,n,k; cin >> m >> n >> k; cout << endl;
    if (m < num_threads){
        cout << "No need for treads. Parameter m is less then number of threads" << endl;
        exit(1);
    }
    if (m < 0 || n < 0 || k < 0){
        cout << "Incorrect values of matrix dimensions. Values should be natural" << endl;
        exit(1);
    }
    // Первая матрица
    vector <pair <double, double> > matr1;
    for (int i = 0; i < m*n; i++){
        double a,b;
        a = rand() % 100;
        b = rand() % 100;
        matr1.push_back(make_pair(a,b));
    }
    // Вторая матрица
    vector <pair <double, double> > matr2;
    for (int i = 0; i < k*n; i++){
        double a,b;
        a = rand() % 100;
        b = rand() % 100;
        matr2.push_back(make_pair(a,b));
    }
    // Формирование ответа
    vector <pair <double, double> > answer(n*k);
    

    vector<thread> threads(num_threads);

    size_t block_size = m / num_threads;
    size_t remainder = m % num_threads;

    // Начинаем считать время выполнения
    auto begining = std::chrono::high_resolution_clock::now();

    // Создание потоков для обработки блоков
    size_t start = 0;
    for (int i = 0; i < num_threads; i++) {
        size_t end = start + block_size;
        if (i < remainder) {
            end++;
        }
        threads[i] = thread( matrix_multiple, ref(matr1), ref(matr2), ref(answer), start, end, m, n, k); 
        //ref - передача по ссылке
        start = end;
    }

    // Ожидание завершения потоков
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }

    // Заканчиваем измерять время выполнения
    auto ending = std::chrono::high_resolution_clock::now();

    duration<double> sec = ending - begining;
    cout << "Result: ";
    cout << sec.count() << " s" << std::endl;
    answer.clear(); matr1.clear(); matr2.clear();

    return 0;
}
