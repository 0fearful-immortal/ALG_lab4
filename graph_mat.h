#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <cctype>
#include <string>
#include <queue>

using namespace std;

const int MaxV = 26;

class GR {
    private:
    int num, n, m, maxv_, num_v;
    vector <list<int>> LIST;
    vector <int> NUM, L;
    stack<pair<int, int>> STACK;
    vector<bool> exists;
    void BFSDistance(int start);
    char Ch(int c) { return c + 'a'; }
public:
    GR(int);
    void Create_manually();
    void Create_auto();
    void CheckDistance();
    ~GR() = default;
};

GR::GR(int maxv) : num(0), n(0), m(0), maxv_(maxv), num_v(0), exists(maxv_, false){}

void GR::Create_manually() {
    int G[MaxV][MaxV];
    for (int i = 0; i < maxv_; ++i)
        for (int j = 0; j < maxv_; ++j) G[i][j] = 0;
    string s;
    cout << "\nВведите мн-ва смежности (строки букв a до z), 'ENTER' чтобы пропустить вершину и '1' чтобы завершить построение графа\n";
    do {
        cout << "v[" << Ch(n) << "]=";
        getline(cin, s);
        if (s == "1") break;
        exists[n] = true;
        for (auto i : s)
            if (isalpha(i)) {
                int j = (tolower(i) - 'a');
                if (j < maxv_) {
                    G[n][j] = 1;
                    exists[j] = true;
                }
            }
        ++n;
    } while (n < maxv_);
    for (bool val : exists) if (val) ++num_v;
    n = m = 0;
    LIST.resize(maxv_);
    for (int i = 0; i < maxv_; ++i) {
        int f = 0;
        cout << '\n' << Ch(i) << ": ";
        for (int j = 0; j < maxv_; ++j)
            if (G[i][j]) {
                ++f;
                LIST[i].push_back(j);
                cout << Ch(j) << ' ';
            } else cout << "- ";
        m += f;
        if (f) ++n;
    }
    cout << "\n|V|=" << n << " |E|=" << m; 
    
}

void GR::Create_auto() {
    int G[MaxV][MaxV] = {0};
    
    string s;
    cout << "Сгенерированный граф:\n";
    int current_n = 0;
    do {
        for (int i = 0; i < maxv_; ++i)
            if (i != current_n && rand() % 100 < 10) {
                G[current_n][i] = 1;
            }
        ++current_n;
    } while (current_n < maxv_);
    
    num_v = maxv_;
    for (int i = 0; i < maxv_; ++i) exists[i] = true;
    LIST.resize(maxv_);
    for (int i = 0; i < maxv_; ++i) {
        for (int j = 0; j < maxv_; ++j) {
            if (G[i][j]) {
                LIST[i].push_back(j);
            }
        }
    }
    
    int n_vertices = 0;
    int n_edges = 0;
    for (int i = 0; i < maxv_; ++i) {
        int f = 0;
        cout << '\n' << Ch(i) << ": ";
        for (int j = 0; j < maxv_; ++j) {
            if (G[i][j]) {
                ++f;
                cout << Ch(j) << ' ';
            } else {
                cout << "- ";
            }
        }
        n_edges += f;
        if (f) ++n_vertices;
    }
    n = n_vertices;
    m = n_edges;
    cout << "\n|V|=" << num_v << " |E|=" << m;
}

void GR::BFSDistance(int start) {
    vector<int> dist(maxv_, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : LIST[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    cout << "\nРасстояния от вершины " << Ch(start) << " до всех остальных вершин:\n";
    for (int i = 0; i < maxv_; ++i) {
        if (exists[i] && i != start) {  // Выводим только для существующих вершин, кроме самой себя
            if (dist[i] != -1) {
                cout << Ch(i) << ": " << dist[i] << "\n";
            } else {
                cout << Ch(i) << ": inf\n";
            }
        }
    }
}

void GR::CheckDistance(){
    char letter;
    cout << "\nВведите букву вершины (a-z) для подсчёта расстояний: ";
    cin >> letter;
    int index = tolower(letter) - 'a';
    if (index < 0 || index >= maxv_ || !exists[index]) {  // Проверяем, что вершина существует
        cout << "Неверная буква. Допустимы существующие вершины.\n";
    }
    else {
        BFSDistance(index);
    }
}
