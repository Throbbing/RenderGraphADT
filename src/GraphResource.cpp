#include "..\include\GraphResource.h"
/*
********************************************
	Render Graph ADT
	出于简化开发流程的考虑，暂不考虑实际的 图形API，
	而是从设计角度完成 ADT 的编写
					-- liangshenge
********************************************
*/

LogicalResourceID GraphResourceMgr::CreateLogicalResource(const std::string& name)
{
	LogicalResourceID id = mLogicalResources.size();
	LogicalResource resource;
	resource.name = name;
	resource.type = Logical_Unknown;

	mLogicalResources[id] = resource;

	return id;
}

LogicalResourceID GraphResourceMgr::CreateLogicalResource(const std::string& name, const PhysicalDesc& desc)
{
	LogicalResourceID id = mLogicalResources.size();
	
	LogicalResource resource;
	resource.name         = name;
	resource.physicalDesc = desc;
	resource.type = Logical_Implicit;
	mLogicalResources[id] = resource;
	return id;
}

LogicalResourceID GraphResourceMgr::CreateLogicalResource(const std::string& name, const PhysicalResourceID& physicalID)
{
	LogicalResourceID id = mLogicalResources.size();
	LogicalResource resource;
	resource.name = name;
	resource.physicalDesc = mPhysicalResources[physicalID].desc;
	resource.type = Logical_Explicit;
	return id;
}

void GraphResourceMgr::BindUnknownResource(const LogicalResourceID& logicalID, const PhysicalResourceID& physicalID)
{
	
	auto& logical = mLogicalResources[logicalID];
	_ASSERT(logical.type == Logical_Unknown);
	logical.physicalDesc = mPhysicalResources[physicalID].desc;
	logical.type = Logical_Implicit;

}


PhysicalResourceID GraphResourceMgr::LoadPhysicalResource(const PhysicalResource& physical)
{
	PhysicalResourceID id = mPhysicalResources.size();
	mPhysicalResources[id] = physical;
	return id;
}

PhysicalResourceID GraphResourceMgr::CreatePhysicalResource(const PhysicalDesc& desc)
{
	// just for ADT Logic

	PhysicalResourceID id = 0;
	return  id;
}
