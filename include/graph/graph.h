#pragma once
#include <iostream>
#include <functional>
#include<set>
#include<list>
#include<stack>
#include<unordered_map>
#include<queue>

using namespace std;

template<typename Vertex=int, typename Distance = double>
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

    //��������-����������-�������� ������
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
    vector<Vertex> vertices() const {
        vector<Vertex> vertices;
        for (auto& v : _vertices)
            vertices.push_back(v);
        return vertices;
    }

    //��������-����������-�������� �����
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
    };//c ������ ����������

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
    }; //c ������ ���������� � Edge

    //��������� ���� �����, ��������� �� �������
    vector<Edge> edges(const Vertex& vertex) const{
        vector<Edge> edge;
        if (!has_vertex(vertex))
            return edge;
        for (auto& e : _edge.at(vertex))
            edge.push_back(e);
        return edge;
    }

    vector<Edge> edges_new(const Vertex& vertex) {
        vector<Edge> edge;
        if (!has_vertex(vertex))
            return edge;
        for (auto& e : _edge[vertex])
            edge.push_back(e);
        for (auto& v : _vertices) {
            for (auto& e:_edge[v]) {
                if (e.to==vertex)
                    edge.push_back(e);
            }
        }
        return edge;
    }

    size_t order() const {
        return _vertices.size();
    }; //������� 

    size_t degree(const Vertex& v) {
        return edges_new(v).size();
    }; //������� �������


    //����� ����������� ����
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to)) {
            throw std::invalid_argument("Vertex not found in the graph");
        }

        unordered_map<Vertex, Distance> min_weight;
        for (const Vertex& v : _vertices) {
            min_weight[v] = std::numeric_limits<Distance>::max();
        }

        priority_queue<pair<Distance, Vertex>> q;

        q.push({ 0, from });

        min_weight[from] = 0;
        unordered_map<Vertex, Vertex> parent_map;
        while (!q.empty()) {
            pair<Distance, Vertex> temp = q.top();
            q.pop();

            Distance curr_weight = temp.first;
            Vertex curr_vertex = temp.second;

            if (curr_weight > min_weight[curr_vertex]) {
                continue;
            }
            if (_edge.find(curr_vertex) == _edge.end())
                continue;
            for (const Edge& edge : _edge.at(curr_vertex)) {
                Distance new_weight = curr_weight + edge.distance;
                if (new_weight < min_weight[edge.to]) {
                    parent_map[edge.to] = curr_vertex;
                    min_weight[edge.to] = new_weight;
                    q.push({ new_weight, edge.to });
                }
            }
        }
        cout << min_weight[to];
        if (min_weight[to] == std::numeric_limits<Distance>::max()) {
            return {};
        }
        vector<Edge> path;
        Vertex current = to;
        while (current != from) {
            Vertex parent = parent_map[current];
            Distance weight = min_weight[current] - min_weight[parent];
            path.push_back(Edge{ parent, current, weight });
            current = parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }
    //�����
    vector<Vertex> walk(const Vertex& start_vertex) const {
        if (!has_vertex(start_vertex))
            throw std::invalid_argument("��������� ������� �� �������!");
        vector<Vertex> vertices;
        stack<Vertex> stack;
        set<Vertex> visited_set;
        stack.push(start_vertex);
        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();
            if (visited_set.find(current) != visited_set.end()) {
                continue;
            }

            vertices.push_back(current);
            visited_set.insert(current);

            if (_edge.find(current) != _edge.end()) {
                for (auto& edge : _edge.at(current)) {
                    if (visited_set.find(edge.to) == visited_set.end()) {
                        stack.push(edge.to);
                    }
                }
            }
        }

        return vertices;
    }

    void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
        if (!has_vertex(start_vertex))
            throw std::invalid_argument("��������� ������� �� �������!");
        stack<Vertex> stack;
        set<Vertex> visited_set;
        stack.push(start_vertex);
        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();
            if (visited_set.find(current) != visited_set.end()) {
                continue;
            }

            action(current);
            visited_set.insert(current);

            if (_edge.find(current) != _edge.end()) {
                for (auto& edge : _edge.at(current)) {
                    if (visited_set.find(edge.to) == visited_set.end()) {
                        stack.push(edge.to);
                    }
                }
            }
        }
    }

    void print(const Vertex& vertex) const {
        cout << vertex << " ";
    }
    void new_print(const Vertex& start_vertex)const {
        function<void(const Vertex&)> action = [*this](const Vertex& vertex) { print(vertex); };
        walk(start_vertex, action);
    }

    void vector_walk(const Vertex& start_vertex) const{
        vector<Vertex> v;
        function<void(const Vertex&)> action = [this, &v](const Vertex& vertex) { v.push_back(vertex); };
        walk(start_vertex, action);
    }

    pair<Vertex, Distance> avg_of_distance(const Vertex& vertex) {
        if (!has_vertex(vertex))
            return {};
        vector <pair<Vertex, Distance>> avg;
        vector<Vertex> vertices = walk(vertex);
        while (vertices.size() < order()) {
            for (auto& v : _vertices) {
                if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
                    vector<Vertex> additional = walk(v);
                    vertices.insert(vertices.end(), additional.begin(), additional.end());
                }
            }
        }
        for (size_t i = 0; i < vertices.size(); ++i) {
            vector<Edge> edge = edges_new(vertices[i]);
            Distance dist = 0;
            size_t vertex_degree =degree(vertices[i]);
            if (vertex_degree != 0) {
                for (size_t j = 0; j < edge.size(); ++j) {
                    dist += edge[j].distance;
                }
          
                dist=dist/vertex_degree;

                avg.push_back({ vertices[i], dist });
            }
            
            
        }
        pair<Vertex, Distance> max_avg = avg[0];
        for (size_t i = 0; i < avg.size(); ++i) {
            if (max_avg.second < avg[i].second)
                max_avg = avg[i];
        }
        return max_avg;
    }
};
