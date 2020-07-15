#include "..\include\GraphResource.h"
/*
********************************************
	Render Graph ADT
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
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
