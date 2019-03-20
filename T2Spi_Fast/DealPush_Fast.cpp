#include "stdafx.h"
#include "T2Spi_Fast.h"
/*�ɽ���ί�лر�����*/

bool CT2Spi_Fast::On620001(const Value &root)
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

bool CT2Spi_Fast::OnSubscribe(const Value &root)
{
	/*ί�лر����ͺͳɽ��ر����;��Բ�������һ�����Ĺ���*/
	switch (convert<int>(root["issue_type"].asString()))
	{
	case 23:
	{
		//����ί�лر�����
		Deal_Entrust(root);
		break;
	}
	case 12:
	{
		/*����ɽ��ر�����*/
		Deal_Deal(root);
		break;
	}
	default:
		LOG(ERROR) << "abnormal issue_type";
		ExceptionInterrupt;
		break;
	}

	return true;
}

/*����ί�лر�����*/
bool CT2Spi_Fast::Deal_Entrust(const Value &root)
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
			case '0':
			{
				/*����ί������Ϊί�е�ί�лر����ͣ�ֻ���µ��Ż����ί������Ϊί�е�ί�лر�����*/
				Deal_Entrust_Entrust(root, i, count);
				break;
			}
			case '2':
			{
				/*����ί������Ϊ������ί�лر�����*/
				Deal_Entrust_Revoke(root, i, count);
				break;
			}
			default:
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

/*����ί������Ϊί�е�ί�лر�����*/
bool CT2Spi_Fast::Deal_Entrust_Entrust(const Value &root, const int i, const int count)
{
	/*��Ʊ���� ��Ʊ���� ���� ί�м۸� ί������ �ɽ����� ί��״̬ ί�к� �걨ʱ��*/
	CString stock_account;
	COrder obj_COrder;
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	/*����Ӧ���ȵ���ί�������ȵ����ɽ������ȵ�������� ��ί�����͸���Ϊ��������ֻ��ί������ ��ʵֻ�гɽ�������Ҫ*/
	if (GainObjOrder(root,i, obj_COrder) == true && obj_COrder.ArrivalSequence_PlaceOrder[index_DealPush] == '1')
	{
		/*�ɽ������ȵ�,������*/
		ExceptionInterrupt;
		LOG(WARNING) << "�ɽ������ȵ�";
	}
	else 
	{
		/*ί�������ȵ���Ӧ���ȵ�*/
		updateEntrust_status(obj_COrder, root["json"][i]["entrust_status"].asString(), root["json"][i]["cancel_info"].asString()); /*ί��״̬*/
	}
	obj_COrder.stock_code = root["json"][i]["stock_code"].asString().c_str();//��Ʊ����
	if (SPtr_CData->SecCode2SecName(obj_COrder.stock_code, obj_COrder.stock_name) == false)
	{
		return false;
	}
	updateEntrust_bs(obj_COrder, root["json"][i]["entrust_bs"].asString());/*��������*/
	obj_COrder.entrust_amount = convert<UInt_64>(root["json"][i]["entrust_amount"].asString());//ί������
	obj_COrder.entrust_price = convert<double>(root["json"][i]["entrust_price"].asString());//ί�м۸�

	obj_COrder.entrust_no = convert<UInt_64>(root["json"][i]["entrust_no"].asString());//ί�б��
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	obj_COrder.report_time = tool::DealReportTime(root["json"][i]["report_time"].asString()) .c_str();//�걨ʱ��

	if (!VerifyEntrust_no(obj_COrder.entrust_no) )
	{
		return false;
	}
	tool::WriteCheckList(SPtr_CData,root,i, stock_account);

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

/*����ί������Ϊ������ί������*/
bool CT2Spi_Fast::Deal_Entrust_Revoke(const Value &root, const int i, const int count)
{
	/*����ԭ״̬�ֶ�����*/
	string stock_code = root["json"][i]["stock_code"].asString();
	COrder obj_COrder;
	if (GainObjOrder(root, i,obj_COrder) == false)
	{
		/*������ʱ�򲻿�����ί�е������ڵ��������Ϊί������һ�������͵����пͻ���*/
		ExceptionInterrupt;
		LOG(ERROR) << "GainObjOrder fail";
		return false;
	}
	/*�ɽ������ȵ�������²��ٸ���ί�е���ί�������ȵ���Ҫ���£�δ�����������ͣ�*/
	if ('1' == obj_COrder.ArrivalSequence_WithdrawOrder[index_DealPush])
	{
		//�ڳ����ϵ�(�ɽ�����)�ٳ�����ʱ���ֱ���˳�������������м�״̬����������²�����ַϵ�
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
		ExceptionInterrupt;
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

/*����ɽ�����*/
bool CT2Spi_Fast::Deal_Deal(const Value &root)
{
	if (root["json"].isNull())
	{
		/*δ�ҵ� false�˳�����*/
		ErrorLog("DealDealPush no json");
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
			switch (root["json"][i]["entrust_type"].asString()[0])
			{
			case '0':
			{
				/*����ί������ί�еĳɽ��ر����� �µ��ͳ����������*/
				Deal_Deal_Entrust(root, i, count);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			LOG(ERROR) << "function id:" << root["function_id"].asString() << " a element illegal";
			return false;
		}
	}

	return true;
}

/*����ί������Ϊί�еĳɽ��ر�����*/
bool CT2Spi_Fast::Deal_Deal_Entrust(const Value &root, const int i, const int count)
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

/*����ί������Ϊί�гɽ�����Ϊ�����ĳɽ�����*/
bool CT2Spi_Fast::Deal_Deal_Entrust_BS(const Value &root, const int i, const int count)
{
	CString stock_account;
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	string stock_code = root["json"][i]["stock_code"].asString().c_str();
	/*���������ί�����͡��µ�Ӧ���ȵ�*/
	COrder obj_COrder;
	if (GainObjOrder(root, i, obj_COrder) == false)
	{
		ExceptionInterrupt;
		LOG(WARNING) << "GainObjOrder false �ɽ������ȵ�";
	}
	obj_COrder.entrust_no = convert<UInt_64>(root["json"][i]["entrust_no"].asString());
	obj_COrder.ArrivalSequence_PlaceOrder[index_DealPush] = '1';
	/*���³ɽ�����*/
	obj_COrder.business_amount += convert<UInt_64>(root["json"][i]["business_amount"].asString());
	/*����ί��״̬*/
	updateEntrust_status(obj_COrder, root["json"][i]["entrust_status"].asString(),root["json"][i]["cancel_info"].asString());
	
	if (0 == obj_COrder.entrust_no)
	{
		ErrorLog("entrust_no is 0");
		return false;
	}

	if (SPtr_CData->SetOrder(SPtr_CData->fund_account, stock_account, obj_COrder) == false)
	{
		LOG(ERROR) << "SetOrder fail";
		ExceptionInterrupt;
		return false;
	}
	UpdateFund_Position(stock_code);
	/*д�ɽ�*/
	/*�ͻ��������ǹ�Ʊ���ơ���Ʊ���롢�������򡢳ɽ��������ɽ��۸񡢳ɽ�ʱ�䡢�ɽ���š�ί�б�š�Ӷ��ӡ��˰��������*/
	CString MarketCode;
	string s_entrust_no;
	CDeal obj_CDeal;//ÿ�ζ��ǵ�һ�Σ��ɽ�set֮�󲻲��ܸ���

	obj_CDeal.stock_code = root["json"][i]["stock_code"].asString().c_str();//֤ȯ����
	obj_CDeal.stock_name = obj_COrder.stock_name;

	/*��������*/
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
		LOG(ERROR) << "entrust_no is 0";
		ExceptionInterrupt;
		return false;
	}

	obj_CDeal.business_balance = obj_CDeal.business_amount*obj_CDeal.business_price;//fix �����ӿ������⣬�ĳ��Լ���˼���
	if (SPtr_CData->SetDeal(SPtr_CData->fund_account, stock_account, obj_CDeal.entrust_no, obj_CDeal) == false)
	{
		LOG(ERROR) << "SetDeal fali";
		ExceptionInterrupt;
		return false;
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

/*����ί������Ϊί�гɽ�����Ϊ�����ĳɽ�����*/
bool CT2Spi_Fast::Deal_Deal_Entrust_Revoke(const Value &root, const int i, const int count)
{
	CString stock_account;
	stock_account = root["json"][i]["stock_account"].asString().c_str();
	string stock_code  = root["json"][i]["stock_code"].asString().c_str();
	COrder obj_COrder;
	if (GainObjOrder(root, i,obj_COrder) == false)
	{
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
	UpdateFund_Position(stock_code);
	int pos = i;
	if (pos == count - 1)
	{
		bPostMessage = true;
	}
	return true;
}

bool CT2Spi_Fast::UpdateFund_Position(const string SecCode)
{
	M_QueryData[SecCode] = true;
	return true;
}

