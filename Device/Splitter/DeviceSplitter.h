/*
 * DeviceSplitter.h
 *
 *  Created on: 5 May 2016
 *      Author: Zeyi Wen
 *		@brief: 
 */

#ifndef DEVICESPLITTER_H_
#define DEVICESPLITTER_H_

#include <vector>

#include "../../Host/UpdateOps/SplitPoint.h"
#include "../../DeviceHost/BaseClasses/BaseSplitter.h"
#include "../../DeviceHost/NodeStat.h"

using std::vector;


class DeviceSplitter: public BaseSplitter
{
public:
	double total_scan_t;
	double total_com_gain_t;
	double total_fix_gain_t;
	double total_fill_gd_t;
	double total_com_idx_t;
	double total_search_t;

	//measure split
	double total_weight_t;
	double total_create_node_t;
	double total_unique_id_t;
	double total_ins2node_t;
	double total_ins2default_t;
	double total_update_new_splittable_t;


public:
	virtual string SpliterType(){return "device";}

	virtual void FeaFinderAllNode(vector<SplitPoint> &vBest, vector<nodeStat> &rchildStat, vector<nodeStat> &lchildStat);
	virtual void SplitAll(vector<TreeNode*> &splittableNode, const vector<SplitPoint> &vBest, RegTree &tree, int &m_nNumofNode,
				  	  	  const vector<nodeStat> &rchildStat, const vector<nodeStat> &lchildStat, bool bLastLevel);
	virtual void ComputeGD(vector<RegTree> &vTree, vector<vector<KeyValue> > & vvInsSparse,  void *stream, int bagId);

private:
	int m_maxNumValuePerFea;//use in (1) prefix sum computation and (2) ins2node kernel configuration.
	void ComputeMaxNumValuePerFea(int *pnEachFeaLen, int numFea);

private:
	int *pBuffIdVec_h;//all splittable node buffer index should be copied
	int *pSNIdToBuffId_h;
public:
	void InitDeviceSplitter(int maxNumSNode)
	{
		pBuffIdVec_h = new int[maxNumSNode];//all splittable node buffer index should be copied
		pSNIdToBuffId_h = new int[maxNumSNode];
	}
};



#endif /* DEVICESPLITTER_H_ */