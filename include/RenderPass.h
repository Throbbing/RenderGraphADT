#pragma once

/*
********************************************
	Render Graph ADT 
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
					-- liangshenge
********************************************
*/
#include<iostream>
#include<functional>
#include<variant>
#include<vector>
#include<map>
#include<unordered_map>

#include "Utils.h"



struct GraphNodeStruct
{
	GraphNodeStruct(GraphNodeStruct&& rhs) noexcept
	{
		inDegree  = std::move(rhs.inDegree);
		outDegree = std::move(rhs.outDegree);
	}
	std::vector<size_t>		inDegree;
	std::vector<size_t>		outDegree;
};

class IGraphNode
{
public:
	virtual int GetInDegree() = 0;
	virtual int GetOutDegree() = 0;
	virtual GraphNodeStruct	 ConvertStruct() const = 0;
};

// Render Pass Interface
class IRenderGraphPass:public IGraphNode
{
public:
	virtual void Setup() = 0;
	virtual void Execute() = 0;
	virtual void BindInput(const std::vector<LogicalResourceID>& InputResources) = 0;
	virtual void BindOutput(const std::vector<LogicalResourceID>& OutputResources) = 0;
	virtual const PassID& GetPassID() const
	{
		return mPassID;
	}

protected:
	PassID			mPassID;
};

template<bool Asyn ,typename SetupFunc,typename ExecuteFunc>
class TRenderGraphPass :public IRenderGraphPass
{
public:
	TRenderGraphPass(const PassID& passID) { mPassID = passID; }
	TRenderGraphPass(const PassID& passID, const SetupFunc& setupFunc, const ExecuteFunc& executeFunc) 
	{ 
		mPassID = passID;  
		mSetupFunc = setupFunc;
		mExecuteFunc = executeFunc;
	}
	TRenderGraphPass(
		const PassID& passID,
		const SetupFunc& setupFunc, 
		const ExecuteFunc& executeFunc,
		const std::vector<LogicalResourceID>& InputResources,
		const std::vector<LogicalResourceID>& OutputResources
		):TRenderGraphPass(passID,setupFunc,executeFunc)
	{
		BindInput(InputResources);
		BindOutput(OutputResources);
	}

	virtual void Setup() override
	{
		mSetupFunc(this);
	}

	virtual void Execute() override
	{
		mExecuteFunc(this);
	}

	virtual void BindInput(const std::vector<LogicalResourceID>& InputResources) override
	{
		// ��ʱ�����ظ���
		_ASSERT(mInputResources.empty());
		mInputResources = InputResources;
	}

	virtual void BindOutput(const std::vector<LogicalResourceID>& OutputResources) override
	{
		// ��ʱ�����ظ���
		_ASSERT(mOutputResources.empty());
		mOutputResources = OutputResources;
	}

	virtual GraphNodeStruct ConvertStruct() const override
	{
		GraphNodeStruct nodeStruct;
		for (const auto& inputIdx : mInputResources)
		{
			nodeStruct.inDegree.push_back(inputIdx);
		}
		for (const auto& outputIdx : mOutputResources)
		{
			nodeStruct.outDegree.push_back(outputIdx);
		}
		return nodeStruct;
	}
	


protected:

	// ����ִ���� ����
	SetupFunc	 mSetupFunc;
	ExecuteFunc  mExecuteFunc;
	
	// ������Դ
	std::vector<LogicalResourceID>		mInputResources;
	// �����Դ
	std::vector<LogicalResourceID>		mOutputResources;
};