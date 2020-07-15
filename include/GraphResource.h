#pragma once
/*
********************************************
	Render Graph ADT
	出于简化开发流程的考虑，暂不考虑实际的 图形API，
	而是从设计角度完成 ADT 的编写
					-- liangshenge
********************************************
*/

#include<vector>
#include<unordered_map>

#include"Utils.h"

/*
	Physical Resource Description
	bound to logical resource for searching a real physical resource
*/
struct PhysicalDesc
{
	size_t desc;
};

/*
	Logical Resource
	just used to construct render graph
*/
class LogicalResource
{
public:
	std::string  name;
	size_t		 resource;
	PhysicalDesc physicalDesc;

};


/*
	Physical Resource 
	the real resource allocated on GPU
	
	Note: reused in every frame
*/
class PhysicalResource
{
public:
	size_t resource;
	PhysicalDesc desc;
};

/*
	Descriptor Resource
	describe how to use logical resource in render pass.
	
	Note: may allocated in every frame
*/
class DescriptorResource
{
	size_t resource;
};

struct DescriptorDesc
{
	size_t desc;
};


// 
class GraphResourceMgr
{
public:
	// Singleton 
	static GraphResourceMgr* GetInstance()
	{
		static GraphResourceMgr mgr;
		return &mgr;
	}

	// Create Logical Resource
	LogicalResourceID CreateLogicalResource(const std::string& name, const PhysicalDesc& desc);

	// Create Static Descriptor Resource
	DescriptorResource CreateStaticDescriptorResource(const std::vector<PhysicalResourceID>& logicalResources,
		const std::vector<DescriptorDesc>& descs);
	

protected:
	// Create Physical Resource
	PhysicalResourceID CreatePhysicalResource(const PhysicalDesc& desc);
	std::unordered_map<LogicalResourceID, LogicalResource>		mLogicalResources;
	std::unordered_map<PhysicalResourceID, PhysicalResource>	mPhysicalResources;

	// Logical <-> Physical
	std::unordered_map<LogicalResource, PhysicalResourceID>		mLogical2Physical;


	
	
};