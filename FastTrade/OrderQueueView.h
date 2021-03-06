#pragma once
#include "../tool/baseView/BaseView_OrderQueue.h"
#include "FastTradeMainView.h"
#include "ViewManager_fast.h"

class COrderQueueView : public CBaseView_OrderQueue
{
	DECLARE_DYNAMIC(COrderQueueView)
public:
	COrderQueueView(CDockListener &listener);
	~COrderQueueView();
	static CBaseView *CreateView(CDockListener &listener) { return new COrderQueueView(listener); }
protected:
	virtual void PostNcDestroy();
};


