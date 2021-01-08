#pragma once

/* -*-c++-*- SemiGlobalMatching - Copyright (C) 2020.
* Author	: Ethan Li <ethan.li.whu@gmail.com>
* Describe	: header of semi-global matching class
*/

#pragma once

#include "sgm_types.h"

/**
 * \brief SemiGlobalMatching�ࣨGeneral implementation of Semi-Global Matching��
 */
class SemiGlobalMatching
{
public:
	SemiGlobalMatching();
	~SemiGlobalMatching();

	/** \brief SGM�����ṹ�� */
	struct SGMOption {
		uint8	num_paths;		// �ۺ�·���� 4 and 8
		sint32  min_disparity;	// ��С�Ӳ�
		sint32	max_disparity;	// ����Ӳ�

		// P1,P2 
		// P2 = P2_init / (Ip-Iq)
		sint32  p1;				// �ͷ������P1
		sint32  p2_init;		// �ͷ������P2

		SGMOption() : num_paths(8), min_disparity(0), max_disparity(640), p1(10), p2_init(150) {
		}

	};
public:
	/**
	 * \brief ��ĳ�ʼ�������һЩ�ڴ��Ԥ���䡢������Ԥ���õ�
	 * \param width		���룬�������Ӱ���
	 * \param height	���룬�������Ӱ���
	 * \param option	���룬SemiGlobalMatching����
	 */
	bool Initialize(const sint32& width, const sint32& height, const SGMOption& option);

	/**
	 * \brief ִ��ƥ��
	 * \param img_left	���룬��Ӱ������ָ��
	 * \param img_right	���룬��Ӱ������ָ��
	 * \param disp_left	�������Ӱ���Ӳ�ͼָ�룬Ԥ�ȷ����Ӱ��ȳߴ���ڴ�ռ�
	 */
	bool Match(const uint8* img_left, const uint8* img_right, float32* disp_left);

	/**
	 * \brief ����
	 * \param width		���룬�������Ӱ���
	 * \param height	���룬�������Ӱ���
	 * \param option	���룬SemiGlobalMatching����
	 */
	bool Reset(const uint32& width, const uint32& height, const SGMOption& option);

private:

	/** \brief Census�任 */
	void CensusTransform() const;

	/** \brief ���ۼ���	 */
	void ComputeCost() const;

	/** \brief ���۾ۺ�	 */
	void CostAggregation() const;

	/** \brief �Ӳ����	 */
	void ComputeDisparity() const;

	/** \brief �ڴ��ͷ�	 */
	void Release();
private:
	/** \brief SGM����	 */
	SGMOption option_;

	/** \brief Ӱ���	 */
	sint32 width_;

	/** \brief Ӱ���	 */
	sint32 height_;

	/** \brief ��Ӱ������	 */
	const uint8* img_left_;

	/** \brief ��Ӱ������	 */
	const uint8* img_right_;

	/** \brief ��Ӱ��censusֵ	*/
	uint32* census_left_;

	/** \brief ��Ӱ��censusֵ	*/
	uint32* census_right_;

	/** \brief ��ʼƥ�����	*/
	uint8* cost_init_;

	/** \brief �ۺ�ƥ�����	*/
	uint16* cost_aggr_;

	// �K �� �L   5  3  7
	// ��    ��	 1    2
	// �J �� �I   8  4  6
	/** \brief �ۺ�ƥ�����-����1	*/
	uint8* cost_aggr_1_;
	/** \brief �ۺ�ƥ�����-����2	*/
	uint8* cost_aggr_2_;
	/** \brief �ۺ�ƥ�����-����3	*/
	uint8* cost_aggr_3_;
	/** \brief �ۺ�ƥ�����-����4	*/
	uint8* cost_aggr_4_;
	/** \brief �ۺ�ƥ�����-����5	*/
	uint8* cost_aggr_5_;
	/** \brief �ۺ�ƥ�����-����6	*/
	uint8* cost_aggr_6_;
	/** \brief �ۺ�ƥ�����-����7	*/
	uint8* cost_aggr_7_;
	/** \brief �ۺ�ƥ�����-����8	*/
	uint8* cost_aggr_8_;

	/** \brief ��Ӱ���Ӳ�ͼ	*/
	float32* disp_left_;

	/** \brief �Ƿ��ʼ����־	*/
	bool is_initialized_;
};

