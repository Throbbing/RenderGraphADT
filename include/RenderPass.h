#pragma once

/*
********************************************
	Render Graph ADT 
	���ڼ򻯿������̵Ŀ��ǣ��ݲ�����ʵ�ʵ� ͼ��API��
	���Ǵ���ƽǶ���� ADT �ı�д
					-- liangshenge
********************************************
*/


// Render Pass Interface
class IRenderGraphPass
{
public:
	virtual bool Setup();
};