#include "..\include\GraphResource.h"
/*
********************************************
	Render Graph ADT
	出于简化开发流程的考虑，暂不考虑实际的 图形API，
	而是从设计角度完成 ADT 的编写
					-- liangshenge
********************************************
*/

LogicalResourceID GraphResourceMgr::CreateLogicalResource(const std::string& name, const PhysicalDesc& desc)
{
	LogicalResourceID id = mLogicalResources.size();
	
	LogicalResource resource;
	resource.name         = name;
	resource.physicalDesc = desc;
	
	mLogicalResources[id] = resource;
	return id;
}

DescriptorResource GraphResourceMgr::CreateStaticDescriptorResource(const std::vector<PhysicalResourceID>& logicalResources, const std::vector<DescriptorDesc>& descs)
{
	_ASSERT(logicalResources.size() == descs.size());
	return DescriptorResource();
}

PhysicalResourceID GraphResourceMgr::CreatePhysicalResource(const PhysicalDesc& desc)
{
	// just for ADT Logic

	PhysicalResourceID id = 0;
	return  id;
}
