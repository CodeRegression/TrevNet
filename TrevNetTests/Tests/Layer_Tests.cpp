//--------------------------------------------------
// Unit Tests for class Layer
//
// @author: Wild Boar
//
// @date: 2023-02-14
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/Layer.h>
using namespace NVL_AI;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that the correct number of nodes are created
 */
TEST(Layer_Test, correct_node_count)
{
	// Setup
	auto layer_1 = Layer(5);
	auto layer_2 = Layer(3);

	// Confirm
	ASSERT_EQ(layer_1.GetNodes().size(), 5);
	ASSERT_EQ(layer_2.GetNodes().size(), 3);
}

/**
 * @brief Verify that the correct number of edges are created
 */
TEST(Layer_Test, correct_edge_count)
{
	// Setup
	auto layer = Layer(5);

	// Execute
	layer.AddEdge(new Edge(0, 1, 0.5));
	layer.AddEdge(new Edge(0, 2, 0.6));
	layer.AddEdge(new Edge(1, 1, 0.3));

	// Confirm
	ASSERT_EQ(layer.GetEdges().size(), 3);

	ASSERT_EQ(layer.GetEdges()[0]->GetSource(), 0);
	ASSERT_EQ(layer.GetEdges()[0]->GetDestination(), 1);
	ASSERT_EQ(layer.GetEdges()[0]->GetWeight(), 0.5);

	ASSERT_EQ(layer.GetEdges()[1]->GetSource(), 0);
	ASSERT_EQ(layer.GetEdges()[1]->GetDestination(), 2);
	ASSERT_EQ(layer.GetEdges()[1]->GetWeight(), 0.6);

	ASSERT_EQ(layer.GetEdges()[2]->GetSource(), 1);
	ASSERT_EQ(layer.GetEdges()[2]->GetDestination(), 1);
	ASSERT_EQ(layer.GetEdges()[2]->GetWeight(), 0.3);
}

/**
 * @brief Determine that we are able to retrieve the valid source edges
 */
TEST(Layer_Test, source_edge_retrieval)
{
	// Setup
	auto layer = Layer(5);

	layer.AddEdge(new Edge(0, 1, 0.5));
	layer.AddEdge(new Edge(0, 2, 0.6));
	layer.AddEdge(new Edge(1, 1, 0.3));

	// Execute
	auto set_1 = EdgeSet(); layer.GetSourceEdges(0, set_1);
	auto set_2 = EdgeSet(); layer.GetSourceEdges(1, set_2);
	auto set_3 = EdgeSet(); layer.GetSourceEdges(2, set_3);

	// Confirm
	ASSERT_EQ(set_1.size(), 2); ASSERT_EQ(set_1[0]->GetWeight(), 0.5); ASSERT_EQ(set_1[1]->GetWeight(), 0.6);
	ASSERT_EQ(set_2.size(), 1); ASSERT_EQ(set_2[0]->GetWeight(), 0.3);
	ASSERT_EQ(set_3.size(), 0);
}

/**
 * @brief Determine that we are able to retrieve the valid destination edges
 */
TEST(Layer_Test, destination_edge_retrieval)
{
	// Setup
	auto layer = Layer(5);

	layer.AddEdge(new Edge(0, 1, 0.5));
	layer.AddEdge(new Edge(0, 2, 0.6));
	layer.AddEdge(new Edge(1, 1, 0.3));

	// Execute
	auto set_1 = EdgeSet(); layer.GetDestinationEdges(0, set_1);
	auto set_2 = EdgeSet(); layer.GetDestinationEdges(1, set_2);
	auto set_3 = EdgeSet(); layer.GetDestinationEdges(2, set_3);

	// Confirm
	ASSERT_EQ(set_1.size(), 0);
	ASSERT_EQ(set_2.size(), 2); ASSERT_EQ(set_2[0]->GetWeight(), 0.5); ASSERT_EQ(set_2[1]->GetWeight(), 0.3);
	ASSERT_EQ(set_3.size(), 1); ASSERT_EQ(set_3[0]->GetWeight(), 0.6); 
}