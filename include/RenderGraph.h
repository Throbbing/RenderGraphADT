#pragma once
/*
********************************************
	Render Graph ADT
	出于简化开发流程的考虑，暂不考虑实际的 图形API，
	而是从设计角度完成 ADT 的编写
					-- liangshenge
********************************************
*/
#include<variant>
#include<vector>

#include"RenderPass.h"
class RenderGraph
{
public:
	// 单例模式
	static	RenderGraph* GetInstance()
	{
		static RenderGraph gRenderGraph;
		return &gRenderGraph;
	}

	template<typename T,typename... NodeArgs>
	PassID CreateGraphNode(NodeArgs&&... args)
	{
		auto id = mNodeGraphs.size();
		mNodeGraphs.push_back(new T(std::forward<NodeArgs>(args)));
		return static_cast<PassID>(id);
	}

protected:
	std::vector<IGraphNode*> mNodeGraphs;

};