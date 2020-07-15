#pragma once

/*
********************************************
	Render Graph ADT 
	出于简化开发流程的考虑，暂不考虑实际的 图形API，
	而是从设计角度完成 ADT 的编写
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
		// 暂时不能重复绑定
		_ASSERT(mInputResources.empty());
		mInputResources = InputResources;
	}

	virtual void BindOutput(const std::vector<LogicalResourceID>& OutputResources) override
	{
		// 暂时不能重复绑定
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

	// 函数执行体 对象
	SetupFunc	 mSetupFunc;
	ExecuteFunc  mExecuteFunc;
	
	// 输入资源
	std::vector<LogicalResourceID>		mInputResources;
	// 输出资源
	std::vector<LogicalResourceID>		mOutputResources;
};