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

TEST(Graph, remove_vertex) {
	Graph<int, double> my_graph;
	my_graph.add_vertex(0);
	my_graph.add_vertex(1);
	my_graph.add_vertex(7);
	EXPECT_TRUE(my_graph.remove_vertex(1) == true);
	EXPECT_TRUE(my_graph.remove_vertex(0) == true);
	EXPECT_TRUE(my_graph.remove_vertex(12) == false);
};

TEST(Graph, vector_vertex) {
	Graph<int, double> my_graph;
	my_graph.add_vertex(0);
	my_graph.add_vertex(1);
	my_graph.add_vertex(7);
	std::vector<int> vector = my_graph.vertices();
	for (int i = 0; i < vector.size(); ++i)
		cout << vector[i] << " ";
}

TEST(Graph, add_edge) {
	Graph<int, double> my_graph;
	EXPECT_TRUE(my_graph.add_edge(0, 1, 10) == true);
	EXPECT_TRUE(my_graph.add_edge(0, 1, 5) == true);
	EXPECT_TRUE(my_graph.add_edge(0, 2, 15) == true);
	EXPECT_TRUE(my_graph.add_edge(0, 1, 10) == false);
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
	std::cout << __cplusplus << std::endl;
	std::vector<Graph<int, double>::Edge> vector = my_graph.edges(3);
	for (int i = 0; i < vector.size(); ++i)
		cout << "("<<vector[i].from<<","<< vector[i].to<< "," << vector[i].distance << ")"<<" ";
}

TEST(Graph, vector_walk) {
	Graph<int, int> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 5, 30);
	my_graph.add_edge(4, 3, 5);
	my_graph.add_edge(5, 6, 12);

	std::vector<int> expected = { 3, 2, 1, 5, 6 };

	std::vector<int> actual = my_graph.walk(3);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); ++i) {
		EXPECT_EQ(expected[i], actual[i]);
	}
	for (size_t i = 0; i < actual.size(); ++i) {
		cout<< actual[i];
	}
	
}

TEST(Graph, SimplePath) {
	Graph<int, int> my_graph;
	my_graph.add_edge(0, 1, 10);
	my_graph.add_edge(2, 1, 5);
	my_graph.add_edge(3, 2, 15);
	my_graph.add_edge(3, 2, 30);
	my_graph.add_edge(1, 5, 30);
	my_graph.add_edge(4, 3, 5);
	my_graph.add_edge(5, 6, 12);


	std::vector<Graph<int, int>::Edge> actual = my_graph.shortest_path(3,5);
	for (int i = 0; i < actual.size(); ++i)
		cout << "(" << actual[i].from << "," << actual[i].to << "," << actual[i].distance << ")" << " ";

}