#include "..\include\GraphCompiler.h"

GraphCompiler::GraphCompiledResult GraphCompiler::Compile(RenderGraph& graph) const
{
	GraphCompiledResult compiledResult;
	const auto& passes = graph.mGraphNodes;

	for (const auto& pass:passes)
	{
		for (const LogicalResourceID& inputID : pass->mInputResources)
			compiledResult.logicalResourceCompiledInfos[inputID].readers.push_back(pass->mPassID);
		for (const LogicalResourceID& outputID : pass->mOutputResources)
			compiledResult.logicalResourceCompiledInfos[outputID].writer = pass->mPassID;
	}
	auto& dag = compiledResult.dag;
	for (auto& p : compiledResult.logicalResourceCompiledInfos)
	{
		// TODO: valid assert
		_ASSERT(true);


		auto& node = compiledResult.dag.nodes[p.second.writer];
		for (const auto& reader : p.second.readers)
		{
			node.outDegree.push_back(reader);
			dag.nodes[reader].inDegree.push_back(p.second.writer);
		}
	}

	compiledResult.sortedPass = TopoSort(dag);

	// PassID <-> execute order
	std::unordered_map<PassID, size_t> orders;
	for (size_t i = 0; i < compiledResult.sortedPass.size(); ++i)
	{
		orders[compiledResult.sortedPass[i]] = i;
	}
		
	for (const auto& resInfo : compiledResult.logicalResourceCompiledInfos)
	{

	}


	return GraphCompiledResult();
}

std::vector<PassID> GraphCompiler::TopoSort(const GraphCompiledResult::DAG& dag) const
{
	return std::vector<PassID>();
}
