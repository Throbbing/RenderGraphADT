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