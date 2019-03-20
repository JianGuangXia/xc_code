#include "stdafx.h"
#include "T2Spi_Credit.h"


bool CT2Spi_Credit::On620001(const Value &root)
{
	if (root["json"].isNull())
	{
		ErrorLog("On620001 no json");
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
		if (tool::VerifyElement(root, i, SPtr_CData))
		{
			string s_str;
			int subscibe_result = convert<int>(root["json"][i]["subscibe_result"].asString());
			string result_info = root["json"][i]["result_info"].asString();
			int issue_type = convert<int>(root["json"][i]["issue_type"].asString());
			if (subscibe_result != 0)
			{
				switch (issue_type)
				{
				case 12:
					s_str = "�ɽ�����:";
					s_str += result_info;
					break;
				case 23:
					s_str = "ί������:";
					s_str += result_info;
					break;
				default:
					ErrorLog("abnormal issue_type");
					break;
				}
				ErrorLog(s_str);
				SPtr_CData->Queue_T2ErrorInfo.push(s_str);
			}
			else
			{
				switch (issue_type)
				{
				case 12:
					s_str = "�ɽ�����:";
					break;
				case 23:
					s_str = "ί������:";
					break;
				default:
					ErrorLog("abnormal issue_type");
					break;
				}
				s_str += result_info;
				LOG(INFO) << s_str;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			return false;//ֻ��һ��Ԫ�أ�����Ҫ��������ж��Ƿ��¼�ɹ������һ��Ҫ��return
		}
	}
	return true;
}

/*�ɽ���ί������*/
bool CT2Spi_Credit::OnSubscribe(const Value &root)
{
	/*ί�лر����ͺͳɽ��ر����;��Բ�������һ�����Ĺ���*/
	switch (convert<int>(root["issue_type"].asString()))
	{
	case 23:
	{
		//����ί������
		Deal_Entrust(root);
		break;
	}
	case 12:
	{
		/*����ɽ�����*/
		Deal_Deal(root);
		break;
	}
	default:
		LOG(ERROR) << "OnSubscribe issue_type have a abnormal value";
		ExceptionInterrupt;
		break;
	}

	return true;
}

/*����ί������*/
bool CT2Spi_Credit::Deal_Entrust(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� false�˳�����*/
		LOG(ERROR) << "DealEntrustPush no json";
		ExceptionInterrupt;
		return false;
	}
	/*�п��ܶ��ί�е���ͬһ����������ֻ������һ�������������У��Ԫ���Ƿ���ȷ�������ȷ��ȡί�����ͣ����Ԫ�ش���ֱ�ӱ�����������һ��Ԫ��*/
	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
	    if (Inspect_bStock(root,i) == false)
		{
			continue;
		}
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			switch (root["json"][i]["entrust_type"].asString()[0])
			{
			case '2':
			{
				/*����ί������Ϊ������ί������*/
				Deal_Entrust_Revoke(root, i, count);
				break;
			}
			case '6'://��������
			{
				Deal_Entrust_Entrust(root, i, count);
				break;
			}
			case '9'://���ý���
			{
				Deal_Entrust_Entrust(root, i, count);
				break;
			}
			default:
				LOG(ERROR) << "abnormal entrust_type";
				ExceptionInterrupt;
				break;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << "a element illegal";
			ExceptionInterrupt;
			return false;
		}
	}

	return true;
}

/*����ί������Ϊ������ί������*/
bool CT2Spi_Credit::Deal_Entrust_Revoke(const Value &root, const int i, const int count)
{
	string stock_code = root["json"][i]["stock_code"].asString();
	COrder obj_COrder;/*fixing �ѱ��ĵ����˳��ؽ������������������*/
	if (GainObjOrder(root, i, obj_COrder) == false)
	{
		LOG(ERROR) << "GainObjOrder fail";
		ExceptionInterrupt;
		AfxMessageBox("GainObjOrder in Deal_Entrust_Revoke");//fixing 
		return false;
	}

	if ('1' == obj_COrder.ArrivalSequence_WithdrawOrder[index_DealPush])
	{
		/*�ɽ������ȵ������ѭ�����ӵ����Ͱ�*/
		obj_COrder.ArrivalSequence_WithdrawOrder[index_EntrustPush] = '0';
		obj_COrder.ArrivalSequence_WithdrawOrder[index_DealPush] = '0';
		return true;
	}
	else
	{
		/*������������ɽ��������*/
		obj_COrder.ArrivalSequence_WithdrawOrder[index_EntrustPush] = '1';
	}

	switch (obj_COrder.entrust_status)
	{
	case YiBao:
		obj_COrder.entrust_status = YiBaoDaiChe;
		break;
	case BuCheng:
		obj_COrder.entrust_status = BuChengDaiChe;
		break;
	default:
		LOG(ERROR) << "abnormal entrust_status";
		ExceptionInterrupt;/*fixing ���ⱨ��һ�δ�����ʱ��ί��״̬Ϊ�ѳ�*/
		AfxMessageBox("abnormal entrust_status");//fixing
		break;
	}

	CString stock_account;
	stock_account = root["json"][i]["stock_account"].asString().c_str();

	if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
	{
		LOG(ERROR) << "SetOrder fail";
		ExceptionInterrupt;
		return false;
	}
	bPostMessage = true;
	UpdateFund_Position(stock_code);
	return true;
}

/*����ί������Ϊ�������ʡ����ý��׵�ί������*/
bool CT2Spi_Credit::Deal_Entrust_Entrust(const Value &root, const int i, const int count)
{
	//��Ʊ���� ��Ʊ���� ���� ί����� ί�м۸� ί������ �ɽ����� ί��״̬ ί�к�
	/*������Ҫ���µĳɽ�������ί��״̬*/
	CString stock_account;
	CString MarketCode;
	COrder obj_COrder;

	if (GainObjOrder(root, i, obj_COrder) == true && obj_COrder.ArrivalSequence_PlaceOrder[index_DealPush] == '1')
	{
		/*�ɽ������ȵ�*/
		ExceptionInterrupt;
	}
	else
	{
		/*ί�������ȵ���Ӧ���ȵ�*/
		updateEntrust_status(obj_COrder, root["json"][i]["entrust_status"].asString(), root["json"][i]["cancel_info"].asString()); /*ί��״̬*/
	}

	stock_account = root["json"][i]["stock_account"].asString().c_str();
	//��Ʊ���� ��Ʊ���� ���� ί����� ί�м۸� ί������ �ɽ����� ί��״̬ ί�к�
	obj_COrder.stock_code = root["json"][i]["stock_code"].asString().c_str();
	if (SPtr_CData->SecCode2SecName(obj_COrder.stock_code,obj_COrder.stock_name) == false)
	{
		return false;
	}
	updateEntrust_bs(obj_COrder, root["json"][i]["entrust_bs"].asString());
	updateEntrust_type(obj_COrder, root["json"][i]["entrust_type"].asString());
	obj_COrder.entrust_price = convert<double>(root["json"][i]["entrust_price"].asString());

	obj_COrder.entrust_amount = convert<UInt_64>(root["json"][i]["entrust_amount"].asString());
	obj_COrder.entrust_no = convert<UInt_64>(root["json"][i]["entrust_no"].asString());

	tool::WriteCheckList(SPtr_CData,root, i, stock_account);

	if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
	{
		LOG(ERROR) << "SetOrder fail";
		ExceptionInterrupt;
		return false;
	}

	/*�п��ܶ��ί�е���ί�����ͷ���ͬһ�������У���PostMessageֻ���ػ���˿������һ��ִ��*/
	int pos = i;
	if (pos == count - 1)
	{
		bPostMessage = true;
	}
	UpdateFund_Position(string(obj_COrder.stock_code));
	return true;
}

/*����ɽ�����*/
bool CT2Spi_Credit::Deal_Deal(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� false�˳�����*/
		LOG(ERROR) << "Deal_Deal no json";
		ExceptionInterrupt;
		return false;
	}

	int count = root["json"].size();
	for (int i = 0; i < count; i++)
	{
        if (Inspect_bStock(root, i) == false)
		{
			continue;
		}
		if (tool::VerifyElement(root, i, SPtr_CData) == true)
		{
			if (root["json"][i]["entrust_type"].isNull())
			{
				/*δ������ʱ��ԭί�л��յ�һ�ʳɽ�����Ϊ�����ĳɽ����ͣ�Ҫ��ʵֻ������������²������ش�*/
				Deal_Deal_WeiBaoRevoke(root, i, count);
			}
			else
			{
				switch (root["json"][i]["entrust_type"].asString()[0])
				{
				case '6'://��������
				{
					/*����ί������Ϊ�������ʵĳɽ����� �µ��ͳ����������*/
					Deal_Deal_Entrust(root, i, count);
					break;
				}
				case '9'://���ý���
				{
					Deal_Deal_Entrust(root, i, count);
					break;
				}
				default:
					LOG(ERROR) << "abnormal enturst_type";
					ExceptionInterrupt;
					break;
				}
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			ExceptionInterrupt;
			return false;
		}
	}

	return true;
}

bool CT2Spi_Credit::Deal_Deal_WeiBaoRevoke(const Value &root, const int i, const int count)
{
	CString stock_account;
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	string stock_code = root["json"][i]["stock_code"].asString().c_str();
	COrder obj_COrder;
	if (GainObjOrder(root, i, obj_COrder) == false)/*fix ʵ�����ܷ���������*/
	{
		LOG(ERROR) << "GainObjOrder fail";/*δ��û��ί�����Ʋ鲻��ί�У����δ�������޷���������ֱ��return��*/
		ExceptionInterrupt;
		return false;
	}

	switch (root["json"][i]["entrust_status"].asString()[0])
	{
	case '6':
		obj_COrder.entrust_status = YiChe;
		break;
	default:
		LOG(ERROR) << "abnormal entrust_status";
		ExceptionInterrupt;
		break;
	}

	if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
	{
		LOG(ERROR) << "SetOrder fail";
		ExceptionInterrupt;
		return false;
	}
	UpdateFund_Position(stock_code);
	bPostMessage = true;
	return true;
}

/*����ί������Ϊ�������ʵĳɽ�����*/
bool CT2Spi_Credit::Deal_Deal_Entrust(const Value &root, const int i, const int count)
{
	switch (convert<int>(root["json"][i]["real_type"].asString()))
	{
	case 0://�ɽ�����Ϊ����
	{
		Deal_Deal_Entrust_BS(root, i, count);
		break;
	}
	case 2://�ɽ�����Ϊ����
	{
		Deal_Deal_Entrust_Revoke(root, i, count);
		break;
	}
	default:
		break;
	}

	return true;
}

bool CT2Spi_Credit::Deal_Deal_Entrust_BS(const Value &root, const int i, const int count)
{
	CString stock_account;
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	string stock_code = root["json"][i]["stock_code"].asString().c_str();
	COrder obj_COrder;
	if (GainObjOrder(root, i,obj_COrder) == false)
	{
		ExceptionInterrupt;
	}
	obj_COrder.ArrivalSequence_PlaceOrder[index_DealPush] = '1';
	/*���³ɽ�����*/
	obj_COrder.business_amount += convert<UInt_64>(root["json"][i]["business_amount"].asString());
	/*����ί��״̬*/
	updateEntrust_status(obj_COrder, root["json"][i]["entrust_status"].asString(), root["json"][i]["cancel_info"].asString());

	if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
	{
		LOG(ERROR) << "SetOrder fail";
		ExceptionInterrupt;
		return false;
	}
	UpdateFund_Position(stock_code);
	/*д�ɽ�*/
	/*��Ʊ���� ��Ʊ���� ���� �ɽ����� �ɽ��۸� �ɽ�ʱ�� �ɽ���� ί�к� */
	CString MarketCode;
	string s_entrust_no;
	CDeal obj_CDeal;//ÿ�ζ��ǵ�һ�Σ��ɽ�set֮�󲻲��ܸ���

	obj_CDeal.stock_code = root["json"][i]["stock_code"].asString().c_str();//֤ȯ����
	obj_CDeal.stock_name = obj_COrder.stock_name;

	updateEntrust_bs(obj_CDeal, root["json"][i]["entrust_bs"].asString());

	/*�ɽ�����*/
	obj_CDeal.business_amount = convert<UInt_64>(root["json"][i]["business_amount"].asString());
	/*�ɽ��۸�*/
	obj_CDeal.business_price = convert<double>(root["json"][i]["business_price"].asString());
	/*�ɽ�ʱ��*/
	obj_CDeal.business_time = convert<UInt_32>(root["json"][i]["business_time"].asString());
	/*�ɽ����*/
	obj_CDeal.business_id = root["json"][i]["business_id"].asString().c_str();
	/*ί�б��*/
	obj_CDeal.entrust_no = convert<UInt_64>(root["json"][i]["entrust_no"].asString());
	if (obj_CDeal.entrust_no == 0)
	{
		LOG(ERROR) << "entrust_no is 0 in OnQueryDeal";
		ExceptionInterrupt;
	}

	obj_CDeal.business_balance = obj_CDeal.business_amount*obj_CDeal.business_price;
	if (SPtr_CData->SetDeal(SPtr_CData->fund_account, stock_account, obj_CDeal.entrust_no, obj_CDeal) == false)
	{
		LOG(ERROR) << "SetDeal fali";
		ExceptionInterrupt;
	}

	int pos = i;
	if (pos == count - 1)
	{
		/*�ػ�Deal��Order��������ѯ���Է������һ��ִ��*/
		bPostMessage = true;
		UpdateFund_Position(string(obj_CDeal.stock_code));
	}
	return true;
}

bool CT2Spi_Credit::Deal_Deal_Entrust_Revoke(const Value &root, const int i, const int count)
{
	CString stock_account;
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	string stock_code = root["json"][i]["stock_code"].asString().c_str();
	COrder obj_COrder;
	if (GainObjOrder(root, i,obj_COrder) == false)
	{
		/*��֧�ֶ���ͻ���ͬʱ��½*/
		LOG(ERROR) << "GainObjOrder fail";
		ExceptionInterrupt;
		return false;
	}
	if ('1' == obj_COrder.ArrivalSequence_WithdrawOrder[index_EntrustPush])
	{
		/*ί�������ȵ����������ѭ��*/
		obj_COrder.ArrivalSequence_WithdrawOrder[index_EntrustPush] = '0';
		obj_COrder.ArrivalSequence_WithdrawOrder[index_DealPush] = '0';
	}
	else
	{
		/*�ɽ��쳣��ʱ����ʾί�����ͣ�������ί����������*/
		obj_COrder.ArrivalSequence_WithdrawOrder[index_DealPush] = '1';
	}

	/*����ί��״̬*/
	updateEntrust_status(obj_COrder, root["json"][i]["entrust_status"].asString(), root["json"][i]["cancel_info"].asString());

	if (0 == obj_COrder.entrust_no)
	{
		LOG(ERROR) << "entrust_no is 0";
		ExceptionInterrupt;
		return false;
	}

	if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
	{
		LOG(ERROR) << "SetOrder fail";
		ExceptionInterrupt;
		return false;
	}
	int pos = i;
	if (pos == count - 1)
	{
		bPostMessage = true;
	}
	UpdateFund_Position(stock_code);
	return true;
}

bool CT2Spi_Credit::UpdateFund_Position(const string SecCode)
{
	M_QueryData[SecCode] = true;
	return true;
}




