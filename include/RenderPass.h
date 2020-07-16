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
#include<functional>

#include "Utils.h"
#include "GraphResource.h"


class RenderGraph;




class GraphCompiler;
class RenderGraphPass
{
	friend RenderGraph;
	friend GraphCompiler;
public:
	RenderGraphPass(const PassID& passID) { mPassID = passID; }
	RenderGraphPass(const PassID& passID, const std::function<void(const RenderGraphPass*)>& setupFunc, const std::function<void(const RenderGraphPass*)>& executeFunc)
	{ 
		mPassID = passID;  
		mSetupFunc = setupFunc;
		mExecuteFunc = executeFunc;
	}
	RenderGraphPass(
		const PassID& passID,
		const std::function<void(const RenderGraphPass*)>& setupFunc,
		const std::function<void(const RenderGraphPass*)>& executeFunc,
		const std::vector<LogicalResourceID>& InputResources,
		const std::vector<LogicalResourceID>& OutputResources
		):RenderGraphPass(passID,setupFunc,executeFunc)
	{
		BindInput(InputResources);
		BindOutput(OutputResources);
	}

	virtual void Setup()
	{
		mSetupFunc(this);
	}

	virtual void Execute()
	{
		mExecuteFunc(this);
	}

	virtual void BindInput(const std::vector<LogicalResourceID>& InputResources)
	{
		// Rebind is forbidden for the moment
		_ASSERT(mInputResources.empty());
		mInputResources = InputResources;
	}

	virtual void BindOutput(const std::vector<LogicalResourceID>& OutputResources) 
	{
		// Rebind is forbidden for the moment
		_ASSERT(mOutputResources.empty());
		mOutputResources = OutputResources;
	}

	virtual void BindLogicalDescriptor(const std::vector<LogicalResourceID>& logicalResources, const DescriptorDesc& desc)
	{
		
		/*
			Descritpor Reousrce is a kind of light resource which can be created at each frame
			So the process of allocation will be delayed until EXECUTE starts
		*/
		DescriptorResourceID descriptorID = mDescriptorDescs.size();
		
		/*
			just need to store desc
		*/
		mDescriptorDescs.push_back(desc);
		for (const auto& logicalID : logicalResources)
		{
			mLogical2Descriptor[logicalID] = descriptorID;
		}
	
	}
	

	


protected:

	// Callable Object
	std::function<void(const RenderGraphPass*)>			mSetupFunc;
	std::function<void(const RenderGraphPass*)>			mExecuteFunc;
	


	// Input Resources
	std::vector<LogicalResourceID>		mInputResources;
	// Output Resources
	std::vector<LogicalResourceID>		mOutputResources;
	// Logical <-> Descriptor Resource
	std::unordered_map<LogicalResourceID, DescriptorResourceID> mLogical2Descriptor;
	// Descriptor Resource
	std::vector<DescriptorDesc>			mDescriptorDescs;


	PassID								mPassID;
	std::string							mPassName;
	const RenderGraph*					mRootGraph = nullptr;
};