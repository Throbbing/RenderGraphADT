#pragma once
/*
********************************************
	Render Graph ADT
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
					-- liangshenge
********************************************
*/
using PassID = size_t;
using LogicalResourceID = size_t;
using PhysicalResourceID = size_t;
using DescriptorResourceID = size_t;

constexpr size_t INVALID_ID = (size_t)100000;