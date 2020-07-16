#pragma once
/*
********************************************
	Render Graph ADT
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
					-- liangshenge
********************************************
*/

#include "RenderGraph.h"
struct GraphCompiledResult
{
	// Logical Resource information after being compiled
	struct LogicalResourceCompiledInfo
	{
		// lifetime
		// [start,end]
		size_t start;
		size_t end;


		std::vector<PassID> readers;
		PassID				writer;
	};

	// Render Pass infomation after being compiled
	struct RenderPassCompiledInfo
	{
		// Resources to construct before EXECUTE
		std::vector<LogicalResourceID>	needToConstruct;

		// Resources to desctroy after EXECUTE
		std::vector<LogicalResourceID>	needToDestroy;
	};

	// Directed Acyclic Graph
	struct DAG
	{
		std::unordered_map<PassID, RenderGraphNode> nodes;
	}dag;

	std::unordered_map<LogicalResourceID, LogicalResourceCompiledInfo>	logicalResourceCompiledInfos;
	std::unordered_map<PassID, RenderPassCompiledInfo>					renderPassCompiledInfos;

	// Toposort Resource
	std::vector<PassID>													sortedPass;

	RenderGraph*														renderGraph;
};
class GraphCompiler
{
public:
	// Singleton
	static GraphCompiler* GetInstance()
	{
		static GraphCompiler compiler;
		return &compiler;
	}



	GraphCompiledResult Compile(RenderGraph& graph) const;

protected:
	std::vector<PassID>	TopoSort(GraphCompiledResult::DAG dag) const ;
	

};


class GraphExecutor
{
public:
	// Singleton
	static GraphExecutor* GetInstance()
	{
		static GraphExecutor exe;
		return &exe;
	}

	virtual void Execute(const GraphCompiledResult& compiledResult);
};