#pragma once
/*
********************************************
	Render Graph ADT
	出于简化开发流程的考虑，暂不考虑实际的 图形API，
	而是从设计角度完成 ADT 的编写
					-- liangshenge
********************************************
*/

#include "RenderGraph.h"

class GraphCompiler
{
public:
	// Singleton
	static GraphCompiler* GetInstance()
	{
		static GraphCompiler compiler;
		return &compiler;
	}

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
	};

	GraphCompiledResult Compile(RenderGraph& graph) const;

protected:
	std::vector<PassID>	TopoSort(const GraphCompiledResult::DAG& dag) const ;
	

};