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
    bool add_edge(const Vertex& from, const Vertex& to,
        const Distance& d) {
        Edge new_edge(from, to, d);
        if (has_edge(new_edge))
            return false;
        if (!has_vertex(from))
            _vertices.insert(from);
        if (!has_vertex(to))
            _vertices.insert(to);
        _edge[from].push_back(new_edge);
        return true;
    };

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_edge(from, to))
            return false;
        auto& list = _edge[from];
        for (auto it=list.begin(); it != list.end(); ++it) {
            if (it->to == to) {
                list.erase(it);
                return true;
            }
        }
        return false;
    };

    bool remove_edge(const Edge& e) {
        if (!has_edge(e))
            return false;
        auto& list = _edge[e.from];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->to == e.to && it->distance == e.distance) {
                list.erase(it);
                return true;
            }
        }
        return false;
    };//c учетом расстояния

    bool has_edge(const Vertex& from, const Vertex& to) const {
        auto it = _edge.find(from);
        if (it == _edge.end())
            return false;
        auto& edge_list = it->second;
        for (auto& e : edge_list) {
            if (e.to == to)
                return true;
        }
        return false;
    };

    bool has_edge(const Edge& e) const {
        if (!has_edge(e.from, e.to))
            return false;
        auto it = _edge.find(e.from);
        auto& edge_list = it->second;
        for (auto& edge : edge_list) {
            if (edge.to == e.to) {
                if (e.distance == edge.distance)
                    return true;
            }
        }
        return false;
    }; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex) {
        if (!has_vertex(vertex))
            throw std::invalid_argument("not vertex!");
        std::vector<Edge> result(_edge.at(vertex).begin(), _edge.at(vertex).end());

        return result;
    }

    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};
