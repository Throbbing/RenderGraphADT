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

#include"RenderPass.h"
class RenderGraph
{
public:
	// ����ģʽ
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