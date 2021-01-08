/* -*-c++-*- SemiGlobalMatching - Copyright (C) 2020.
* Author	: Ethan Li <ethan.li.whu@gmail.com>
* Describe	: implement of sgm_util
*/

#pragma once
#include "sgm_types.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(P) {if(P) delete[](P);(P)=nullptr;}
#endif

namespace sgm_util
{
	//������������ census���߼�
	// census�任

	/**
	 * \brief census�任
	 * \param source	���룬Ӱ������
	 * \param census	�����censusֵ����
	 * \param width		���룬Ӱ���
	 * \param height	���룬Ӱ���
	 */
	void census_transform_5x5(const uint8* source, uint32* census, const sint32& width, const sint32& height);
	void census_transform_9x7(const uint8* source, uint64* census, const sint32& width, const sint32& height);
	// Hamming����
	uint8 Hamming32(const uint32& x, const uint32& y);


	/**
	 * \brief ����·���ۺ� �� ��
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ�����ң�������Ϊ���ҵ���
	 */
	void CostAggregateLeftRight(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	/**
	 * \brief ����·���ۺ� �� ��
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ���ϵ��£�������Ϊ���µ��ϣ�
	 */
	void CostAggregateUpDown(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	/**
	 * \brief �Խ���1·���ۺϣ�����<->���£��K �I
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ�����ϵ����£�������Ϊ�����µ����ϣ�
	 */
	void CostAggregateDagonal_1(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);

	/**
	 * \brief �Խ���2·���ۺϣ�����<->���£��L �J
	 * \param img_data			���룬Ӱ������
	 * \param width				���룬Ӱ���
	 * \param height			���룬Ӱ���
	 * \param min_disparity		���룬��С�Ӳ�
	 * \param max_disparity		���룬����Ӳ�
	 * \param p1				���룬�ͷ���P1
	 * \param p2_init			���룬�ͷ���P2_Init
	 * \param cost_init			���룬��ʼ��������
	 * \param cost_aggr			�����·���ۺϴ�������
	 * \param is_forward		���룬�Ƿ�Ϊ������������Ϊ���ϵ��£�������Ϊ���µ��ϣ�
	 */
	void CostAggregateDagonal_2(const uint8* img_data, const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity,
		const sint32& p1, const sint32& p2_init, const uint8* cost_init, uint8* cost_aggr, bool is_forward = true);
}
