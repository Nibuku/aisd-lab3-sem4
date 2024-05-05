#pragma once
#include <iostream>
#include<set>
#include<list>
#include<stack>
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
    set<Vertex> _vertices;
    unordered_map <Vertex, list<Edge>> _edge;
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
        _edge.emplace(v, list<Edge>());
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
        std::vector<Edge> edge;
        if (!has_vertex(vertex))
            return edge;
        for (auto& e : _edge[vertex])
            edge.push_back(e);
        return edge;
    }

    size_t order() const {
        return _vertices.size();
    }; //порядок 

    size_t degree(const Vertex& v) const {
        return edges(v).size();
    }; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        enum class Colors {
            White,
            Grey,
            Black
        };

        std::vector<Vertex> vertices;
        std::stack<Vertex> stack;
        std::unordered_map<Vertex, Colors> color;
        if (_vertices.find(start_vertex) == _vertices.end()) {
            return vertices;
        }
        for (const auto& v : _vertices) {
            color.emplace(v, Colors::White);
        }
        color[start_vertex] = Colors::Grey;
        stack.push(start_vertex);
        while (!stack.empty()) {
            Vertex curr = stack.top();
            stack.pop();
            vertices.push_back(curr);
            for (const auto& e : _edge.at(curr)) {
                if (color[e.to] == Colors::White) {
                    stack.push(e.to);
                    color[e.to] = Colors::Grey;
                }
            }
            color[curr] = Colors::Black;
        }
        return vertices;
    }
    
};
