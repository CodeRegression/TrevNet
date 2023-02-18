//--------------------------------------------------
// Unit Tests for class NetworkInfo
//
// @author: Wild Boar
//
// @date: 2023-02-18
//--------------------------------------------------

#include <gtest/gtest.h>

#include <TrevNetLib/NetworkInfo.h>
using namespace NVL_AI;

//--------------------------------------------------
// Function Prototype
//--------------------------------------------------
void ValidateEdge(Edge * edge, int source, int destination, double weight);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify that the load happened correct
 */
TEST(NetworkInfo_Test, confirm_load)
{
	// Setup
	auto initString = "0:0:1,0:1:1,1:0:1,1:1:1,2:0:0,2:1:-1.5|0:0:1,1:0:-2|1";

	// Execute
	auto info = NetworkInfo(initString);

	// Confirm
	ASSERT_EQ(info.GetLayerCounts().size(), 3);
	ASSERT_EQ(info.GetLayerCounts()[0], 3);
	ASSERT_EQ(info.GetLayerCounts()[1], 2);
	ASSERT_EQ(info.GetLayerCounts()[2], 1);

	auto& edges_1 = info.GetEdges(0);
	ASSERT_EQ(edges_1.size(), 6);
	ValidateEdge(edges_1[0], 0, 0, 1);
	ValidateEdge(edges_1[1], 0, 1, 1);
	ValidateEdge(edges_1[2], 1, 0, 1);
	ValidateEdge(edges_1[3], 1, 1, 1);
	ValidateEdge(edges_1[4], 2, 0, 0);
	ValidateEdge(edges_1[5], 2, 1, -1.5);

	auto& edges_2 = info.GetEdges(1);
	ASSERT_EQ(edges_2.size(), 2);
	ValidateEdge(edges_2[0], 0, 0, 1);
	ValidateEdge(edges_2[1], 1, 0, -2);

	auto& edges_3 = info.GetEdges(2);
	ASSERT_EQ(edges_3.size(), 0);

	// Teardown
	for (auto layerId = 0; layerId < info.GetLayerCounts().size(); layerId++) 
	{
		auto edges = info.GetEdges(layerId);
		for (auto edge : edges) delete edge;
	}
}

//--------------------------------------------------
// Validation Helpers
//--------------------------------------------------

/**
 * @brief Validate an edge 
 * @param edge The edge that we are validating
 * @param source The expected source id
 * @param destination The expected destination id 
 * @param weight The expected weight
 */
void ValidateEdge(Edge * edge, int source, int destination, double weight) 
{
	ASSERT_EQ(edge->GetSource(), source);
	ASSERT_EQ(edge->GetDestination(), destination);
	ASSERT_EQ(edge->GetWeight(), weight);
}