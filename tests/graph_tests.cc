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
