#pragma once
/*
********************************************
	Render Graph ADT
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
					-- liangshenge
********************************************
*/

#include<vector>

/*
	Logical Resource
	just used to construct render graph
*/
class LogicalResource
{
	size_t  resource;
};


/*
	Physical Resource Description
	bound to logical resource for searching a real physical resource
*/
struct PhysicalDesc
{
	size_t desc;
};


/*
	Physical Resource 
	the real resource allocated on GPU
	
	Note: reused in every frame
*/
class PhysicalResource
{
	size_t resource;
	PhysicalDesc desc;
};

/*
	Descriptor Resource
	describe how to use logical resource in render pass.
	
	Note: allocated in every frame
*/
class DescriptorResource
{
	size_t resource;
};