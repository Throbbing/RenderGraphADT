#pragma once
/*
********************************************
	Render Graph ADT
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
					-- liangshenge
********************************************
*/
#include<variant>
#include<vector>
#include"Utils.h"
#include"RenderPass.h"

struct RenderGraphNode
{
	PassID id;
	std::vector<size_t> outDegree;
	int inDegreeSize = 0;
};

class GraphCompiler;
class RenderGraph
{
	friend class GraphCompiler;
public:
	// Singleton
	static	RenderGraph* GetInstance()
	{
		static RenderGraph gRenderGraph;
		return &gRenderGraph;
	}

	template<typename... NodeArgs>
	PassID CreateGraphNode(NodeArgs&&... args)
	{
		auto id = mNodeGraphs.size();
		RenderGraphPass* node = new RenderGraphPass(std::forward<NodeArgs>(args);
		node->mRootGraph = this;
		mGraphNodes.push_back(node);
		mPassMap[id] = node;
		return static_cast<PassID>(id);
	}

	

	RenderGraphPass* GetPass(PassID passID)
	{
		auto p = mPassMap.find(passID);
		if (p != mPassMap.end())
			return p->second;
		else
			return nullptr;
	}


protected:
	std::vector<RenderGraphPass*> mGraphNodes;
	std::unordered_map<PassID, RenderGraphPass*> mPassMap;
};