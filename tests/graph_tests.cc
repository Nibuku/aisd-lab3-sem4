#include <gtest/gtest.h>
#include <graph/graph.h>
#include <iostream>
using namespace std;

TEST(Graph, constructor) {
	Graph<int, double>::Edge my_graph= Graph<int, double>::Edge(0, 1, 10);
	EXPECT_TRUE(my_graph.distance == 10);
};

TEST(Graph, add_vertex) {
	Graph<int, double> my_graph;
	EXPECT_TRUE(my_graph.add_vertex(0)==true);
	EXPECT_TRUE(my_graph.add_vertex(1) == true);
	EXPECT_TRUE(my_graph.add_vertex(1) == false);
};

TEST(Graph, has_vertex) {
	Graph<int, double> my_graph;
	my_graph.add_vertex(0);
	my_graph.add_vertex(1);
	my_graph.add_vertex(7);
	EXPECT_TRUE(my_graph.has_vertex(1) == true);
	EXPECT_TRUE(my_graph.has_vertex(0) == true);
	EXPECT_TRUE(my_graph.has_vertex(12) == false);

};

TEST(Graph, vector_vertex) {
	Graph<int, double> my_graph;
	my_graph.add_vertex(0);
	my_graph.add_vertex(1);
	my_graph.add_vertex(7);
	cout << "Vector of vertices: ";
	std::vector<int> vector = my_graph.vertices();
	for (int i = 0; i < vector.size(); ++i)
		cout << vector[i] << " ";
}

TEST(Graph, remove_vertex) {
	Graph<int, double> my_graph;
	my_graph.add_vertex(0);
	my_graph.add_vertex(1);
	my_graph.add_vertex(7);
	EXPECT_TRUE(my_graph.remove_vertex(1) == true);
	EXPECT_TRUE(my_graph.remove_vertex(0) == true);
	EXPECT_TRUE(my_graph.remove_vertex(12) == false);
	cout << "Vector of vertices after remove: ";
	std::vector<int> vector = my_graph.vertices();
	for (int i = 0; i < vector.size(); ++i)
		cout << vector[i] << " ";
};

TEST(Graph, add_edge) {
	Graph<int, double> my_graph;
	EXPECT_TRUE(my_graph.add_edge(0, 1, 10) == true);
	EXPECT_TRUE(my_graph.add_edge(0, 1, 5) == true);
	EXPECT_TRUE(my_graph.add_edge(0, 2, 15) == true);
	EXPECT_TRUE(my_graph.add_edge(0, 1, 10) == false);
	cout << "Vector of vertices after add edges: ";
	std::vector<int> vector = my_graph.vertices();
	for (int i = 0; i < vector.size(); ++i)
		cout << vector[i] << " ";
}

TEST(Graph, remove_edge) {
	Graph<int, double> my_graph;
	Graph<int, double>::Edge my_edge = Graph<int, double>::Edge(3, 2, 30);
	Graph<int, double>::Edge my_edge_two = Graph<int, double>::Edge(3, 2, 8);
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	EXPECT_TRUE(my_graph.remove_edge(0, 1) == true);
	EXPECT_TRUE(my_graph.remove_edge(2, 1) == true);
	EXPECT_TRUE(my_graph.remove_edge(0, 1) == false);
	EXPECT_TRUE(my_graph.remove_edge(my_edge) == true);
	EXPECT_TRUE(my_graph.remove_edge(my_edge_two) == false);
	std::vector<Graph<int, double>::Edge> vector = my_graph.edges(0);
	for (int i = 0; i < vector.size(); ++i)
		cout << "(" << vector[i].from << "," << vector[i].to << "," << vector[i].distance << ")" << " ";

}

TEST(Graph, vector_edge) {
	Graph<int, double> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	std::vector<Graph<int, double>::Edge> vector = my_graph.edges(3);
	cout << "Exiting edges: ";
	for (int i = 0; i < vector.size(); ++i)
		cout << "("<<vector[i].from<<","<< vector[i].to<< "," << vector[i].distance << ")"<<" ";
}

TEST(Graph, vector_new_edge) {
	Graph<int, double> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 3, 25);
	cout << "Exiting and incoming edges: ";
	std::vector<Graph<int, double>::Edge> vector = my_graph.edges_new(3);
	for (int i = 0; i < vector.size(); ++i)
		cout << "(" << vector[i].from << "," << vector[i].to << "," << vector[i].distance << ")" << " ";
}

TEST(Graph, vector_degree) {
	Graph<int, double> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 3, 25);
	cout<<"Degree of vertex: "<< my_graph.degree(3)<<endl;
}

TEST(Graph, walk) {
	Graph<int, int> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 5, 30);
	my_graph.add_edge(4, 3, 5);
	my_graph.add_edge(5, 6, 12);

	vector<int> expected = { 3, 2, 1, 5, 6 };

	vector<int> actual = my_graph.walk(3);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); ++i) {
		EXPECT_EQ(expected[i], actual[i]);
	}
	cout << "Result the walk test: ";
	for (size_t i = 0; i < actual.size(); ++i) {
		cout<< actual[i];
	}
	
}

TEST(Graph, dejstra_test) {
	Graph<int, int> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 5, 30);
	my_graph.add_edge(4, 3, 5);
	my_graph.add_edge(5, 6, 12);

	cout << "Result the shortest_path test: ";
	vector<Graph<int, int>::Edge> actual = my_graph.shortest_path(3,5);
	for (int i = 0; i < actual.size(); ++i)
		cout << "(" << actual[i].from << "," << actual[i].to << "," << actual[i].distance << ")" << " ";

}

TEST(Graph, print_walk) {
	Graph<int> graph;
	graph.add_edge(1, 2, 2);
	graph.add_edge(1, 3, 7);
	graph.add_edge(2, 4, 8);
	graph.add_edge(3, 5, 12);
	graph.add_edge(3, 6, 7);

	cout << "Result of walk with print: ";
	graph.new_print(3);
}

TEST(Graph, vector_walk) {
	Graph<int> graph;
	graph.add_edge(1, 2, 2);
	graph.add_edge(1, 3, 7);
	graph.add_edge(2, 4, 8);
	graph.add_edge(3, 5, 12);
	graph.add_edge(3, 6, 7);
	graph.vector_walk(3);

}

TEST(Graph, task_test) {
	Graph<int, int> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 5, 30);
	my_graph.add_edge(4, 3, 5);
	my_graph.add_edge(5, 6, 12);
	// для вершины 0: 10
	// для вершины 1: 15
	// для вершины 2: 16
	// для вершины 3: 16
	// для вершины 4: 5
	// для вершины 5: 21
	pair<int, int> avg=my_graph.avg_of_distance(0);
	cout << "The most far away vertex: " << avg.first<<endl;
	cout << "Avg distance: " << avg.second << endl;
}