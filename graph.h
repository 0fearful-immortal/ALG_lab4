#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <cctype>
#include <string>
#include <queue>
using namespace std;





class GR {
    private:
    int num, n, m, maxv_;
    vector <list<int>> LIST;
    vector <int> NUM, L;
    stack<pair<int, int>> STACK;
    const int MaxV = 26;
    void BFSDistance(int start);
    char Ch(int c) { return c + 'a'; }
public:
    GR(int);
    void Create_manually();
    void Create_auto();
    void CheckDistance();
    ~GR() = default;
};




GR::GR(int maxv) : num(0), n(0), m(0), maxv_(maxv){}

void GR:: Create_manually(){
    vector<vector<int>> G(maxv_, vector<int>(maxv_, 0));
    string s;
    cout << "Введите мн-ва смежности (строки букв a до z), 'ENTER' чтобы пропустить вершину и '1' чтобы завершить построение графа.\n";
    int current_n = 0;
    do {
        cout << "v[" << Ch(current_n) << "]=";
        getline(cin, s); 
        if (s == "1") break;
        for (auto i : s)
            if (isalpha(i)) {
                int j = (tolower(i) - 'a');
                if (j < maxv_) {
                    G[current_n][j] = 1;
                }
            }
        ++current_n;
    } while (current_n < maxv_);
    LIST.resize(maxv_);
    int n_vertices = 0;
    int n_edges = 0;
    for (int i = 0; i < maxv_; ++i)
    {
        int f = 0;
        cout << '\n' << Ch(i) << ": ";
        for (int j = 0; j < maxv_; ++j)
            if (G[i][j])
            {
                ++f;
                LIST[i].push_back(j);
                cout << Ch(j) << ' ';
            }
            else cout << "- ";
        n_edges += f;
        if (f) ++n_vertices;
    }
    n = n_vertices;
    m = n_edges;
    cout << "\n|V|=" << n << " |E|=" << m;
}


void GR:: Create_auto(){
    vector<vector<int>> G(maxv_, vector<int>(maxv_, 0));
    string s;
    cout << "Сгенерированный граф:\n";
    int current_n = 0;
    do {
        for (int i = 0; i<maxv_;++i)
            if (i != current_n && rand() % 100 < 10) {
                G[current_n][i] = 1;
            }
        ++current_n;
    } while (current_n < maxv_);
    LIST.resize(maxv_);
    int n_vertices = 0;
    int n_edges = 0;
    for (int i = 0; i < maxv_; ++i)
    {
        int f = 0;
        cout << '\n' << Ch(i) << ": ";
        for (int j = 0; j < maxv_; ++j)
            if (G[i][j])
            {
                ++f;
                LIST[i].push_back(j);
                cout << Ch(j) << ' ';
            }
            else cout << "- ";
        n_edges += f;
        if (f) ++n_vertices;
    }
    n = n_vertices;
    m = n_edges;
    cout << "\n|V|=" << n << " |E|=" << m;
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

    cout << "\nРасстояния от вершины " << Ch(start) << " до связанных вершин:\n";
    bool flag = false;
    for (int i = 0; i < maxv_; ++i) {
        if (dist[i] != -1 && i != start) { 
            cout << Ch(i) << ": " << dist[i] << "\n";
            flag = true;
        }
    }
    if (!flag) {
        cout << "Нет связанных вершин.\n";
    }
}

void GR::CheckDistance(){
    char letter;
    cout << "\nВведите букву вершины (a-z) для подсчёта расстояний: ";
    cin >> letter;
    int index = tolower(letter) - 'a';
    if (index < 0 || index >= maxv_) {
        cout << "Неверная буква. Допустимы a-z.\n";
    }
    else {
        BFSDistance(index);
    }
}
