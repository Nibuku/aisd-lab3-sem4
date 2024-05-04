#pragma once
#include <iostream>
#include<set>
#include<list>
#include<unordered_map>

using namespace std;

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from, to;
        Distance distance;
        Edge(Vertex from, Vertex to, Distance distance) : from(from), to(to), distance(distance) {};
    };
private:  
    std::set<Vertex> _vertices;
    std::unordered_map <Vertex, std::list<Edge>> _edge;
public:

    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const {
        if (_vertices.find(v) != _vertices.end())
            return true;
        return false;
    };

    bool add_vertex(const Vertex& v) {
        if (has_vertex(v))
            return false;
        _vertices.insert(v);
        _edge.emplace(v, std::list<Edge>());
        return true;
    };

    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v))
            return false;
        _vertices.erase(v);
        _edge.erase(v);
        for (auto& ver : _vertices) {
            auto& e = _edge[ver];
            for(auto it = e.begin(); it != e.end(); ) {
                if (it->to == v) {
                    it = e.erase(it);
                };
                
            };
        }
        return true;
    }
    std::vector<Vertex> vertices() const {
        std::vector<Vertex> vertices;
        for (auto& v : _vertices)
            vertices.push_back(v);
        return vertices;
    }

    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to,
        const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e) const; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};
