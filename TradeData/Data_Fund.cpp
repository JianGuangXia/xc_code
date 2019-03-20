#include "Data_Fund.h"
#include "Data_Account.h"

CFund::CFund()
{
	initVec_CreditAsset();
	pData = NULL;
	fund_account = "";           //�ʽ��˻�
	money_type = Currency_Default;       //	C3	�������
	current_balance = 0;  //	N16.2	��ǰ���
	begin_balance = 0;    //	N16.2	�ڳ����
	enable_balance = 0;   //	N16.2	�����ʽ�
	foregift_balance = 0; //	N16.2	��ȡ�ʽ�
	mortgage_balance = 0; //	N16.2	��ȡ�ʲ�
	frozen_balance = 0;   //	N16.2	�����ʽ�
	unfrozen_balance = 0; //	N16.2	�ⶳ�ʽ�
	fetch_balance = 0;    //	N16.2	��ȡ���
	fetch_cash = 0;       //	N16.2	��ȡ�ֽ�
	entrust_buy_balance = 0; //	N16.2	ί��������
	market_value = 0;     //	N16.2	֤ȯ��ֵ
	asset_balance = 0;    //	N16.2	�ʲ�ֵ
	interest = 0;         //	N16.2	��������Ϣ
	integral_balance = 0; //	N16.2	��Ϣ����
	fine_integral = 0;    //	N16.2	��Ϣ����
	pre_interest = 0;     //	N16.2	Ԥ����Ϣ
	pre_fine = 0;         //	N16.2	Ԥ�Ʒ�Ϣ
	pre_interest_tax = 0; //	N16.2	Ԥ����Ϣ˰
	correct_balance = 0;  //	N16.2	�ʲ��������
	fund_balance = 0;     //	N16.2	���ʽ����
	opfund_market_value = 0; //	N16.2	������ֵ
	rate_kind = ' ';        //	C1	�������
	real_buy_balance = 0; // N16.2	�ر�������
	real_sell_balance = 0;//	N16.2	�ر��������
	net_asset = 0;        //	N16.2	���ʲ�
	prod_market_value = 0;//	N16.2	����ڲ�Ʒ��ֵ
}

CFund::CFund(CData *lpData, CString strFundID)
{
	initVec_CreditAsset();
	pData = lpData;
	fund_account = strFundID;           //�ʽ��˻�
	money_type = Currency_Default;       //	C3	�������
	current_balance = 0;  //	N16.2	��ǰ���
	begin_balance = 0;    //	N16.2	�ڳ����
	enable_balance = 0;   //	N16.2	�����ʽ�
	foregift_balance = 0; //	N16.2	��ȡ�ʽ�
	mortgage_balance = 0; //	N16.2	��ȡ�ʲ�
	frozen_balance = 0;   //	N16.2	�����ʽ�
	unfrozen_balance = 0; //	N16.2	�ⶳ�ʽ�
	fetch_balance = 0;    //	N16.2	��ȡ���
	fetch_cash = 0;       //	N16.2	��ȡ�ֽ�
	entrust_buy_balance = 0; //	N16.2	ί��������
	market_value = 0;     //	N16.2	֤ȯ��ֵ
	asset_balance = 0;    //	N16.2	�ʲ�ֵ
	interest = 0;         //	N16.2	��������Ϣ
	integral_balance = 0; //	N16.2	��Ϣ����
	fine_integral = 0;    //	N16.2	��Ϣ����
	pre_interest = 0;     //	N16.2	Ԥ����Ϣ
	pre_fine = 0;         //	N16.2	Ԥ�Ʒ�Ϣ
	pre_interest_tax = 0; //	N16.2	Ԥ����Ϣ˰
	correct_balance = 0;  //	N16.2	�ʲ��������
	fund_balance = 0;     //	N16.2	���ʽ����
	opfund_market_value = 0; //	N16.2	������ֵ
	rate_kind = ' ';        //	C1	�������
	real_buy_balance = 0; // N16.2	�ر�������
	real_sell_balance = 0;//	N16.2	�ر��������
	net_asset = 0;        //	N16.2	���ʲ�
	prod_market_value = 0;//	N16.2	����ڲ�Ʒ��ֵ
}

CFund::CFund(CData *lpData, CFund &Fund)
{
	initVec_CreditAsset();
	pData = lpData;
	fund_account = Fund.fund_account;
	money_type = Fund.money_type;
	current_balance = Fund.current_balance;
	begin_balance = Fund.begin_balance;
	enable_balance = Fund.enable_balance;
	foregift_balance = Fund.foregift_balance;
	mortgage_balance = Fund.mortgage_balance;
	frozen_balance = Fund.frozen_balance;
	unfrozen_balance = Fund.unfrozen_balance;
	fetch_balance = Fund.fetch_balance;
	fetch_cash = Fund.fetch_cash;
	entrust_buy_balance = Fund.entrust_buy_balance;
	market_value = Fund.market_value;
	asset_balance = Fund.asset_balance;
	interest = Fund.interest;
	integral_balance = Fund.integral_balance;
	fine_integral = Fund.fine_integral;
	pre_interest = Fund.pre_interest;
	pre_fine = Fund.pre_fine;
	pre_interest_tax = Fund.pre_interest_tax;
	correct_balance = Fund.correct_balance;
	fund_balance = Fund.fund_balance;
	opfund_market_value = Fund.opfund_market_value;
	rate_kind = Fund.rate_kind;
	real_buy_balance = Fund.real_buy_balance;
	real_sell_balance = Fund.real_sell_balance;
	net_asset = Fund.net_asset;
	prod_market_value = Fund.prod_market_value;
}

CFund::~CFund()
{
	MAccount.clear();
	pData = NULL;
}

void CFund::initVec_CreditAsset()
{
	VCreditAsset.resize(Size_Row);
	for (unsigned int i = 0; i < VCreditAsset.size(); i++)
		VCreditAsset[i].resize(Siz_Column);
	//VCreditAsset[0][0] = "ά�ֵ�������";
	//VCreditAsset[0][2] = "���ʿ��ö��";
	//VCreditAsset[0][4] = "��ȯ���ö��";

	//VCreditAsset[1][0] = "���ñ�֤��";
	//VCreditAsset[1][2] = "�������ö��";
	//VCreditAsset[1][4] = "��ȯ���ö��";

	//VCreditAsset[2][0] = "��ծ�ܸ�ӯ";
	//VCreditAsset[2][2] = "���ʺ�Լ���";
	//VCreditAsset[2][4] = "��ȯ��Լ���";
	//
	//VCreditAsset[3][0] = "���ñ�֤��";
	//VCreditAsset[3][2] = "���ʺ�Լ����";
	//VCreditAsset[3][4] = "��ȯ��Լ����";

	//VCreditAsset[4][0] = "�򵣱�Ʒ�����ʽ�";
	//VCreditAsset[4][2] = "���ʺ�Լ��Ϣ";
	//VCreditAsset[4][4] = "��ȯ��Լ��Ϣ";

	//VCreditAsset[5][0] = "�ֽ𻹿�����ʽ�";
	//VCreditAsset[5][2] = "������ֵ";
	//VCreditAsset[5][4] = "��ȯ��ֵ";

	//VCreditAsset[6][0] = "�����ʱ�Ŀ����ʽ�";
	//VCreditAsset[6][2] = "���ʺ�Լӯ��";
	//VCreditAsset[6][4] = "��ȯ��Լӯ��";

	//VCreditAsset[7][0] = "֤ȯ��ֵ";
	//VCreditAsset[7][2] = "�������ñ�֤��";
	//VCreditAsset[7][4] = "��ȯ���ñ�֤��";

	//VCreditAsset[8][0] = "��ȡ���";
	//VCreditAsset[8][2] = "�ֽ��ʲ�";
	//VCreditAsset[8][4] = "��ȯ���������ܶ�";

	//VCreditAsset[9][0] = "��ȯ�������";
	//VCreditAsset[9][2] = "�����ʲ�";
	//VCreditAsset[9][4] = "��ծ�ܶ�";

	//VCreditAsset[10][0] = "";
	//VCreditAsset[10][2] = "��������";
	//VCreditAsset[10][4] = "���ʶ������";

	//VCreditAsset[11][0] = "";
	//VCreditAsset[11][2] = "���ʲ�";
	//VCreditAsset[11][4] = "��ȯ��ȯ�����ʽ�";
}

bool CFund::ClearMPosition()
{
	bool ret;
	DataMutex_MAccount.lock_shared();
	for (auto iter = MAccount.begin();iter != MAccount.end();iter++)
	{
		ret = iter->second->ClearMPosition();
		if (false == ret)
		{
			ErrorLog("ClearMPosition fail");
			break;
		}
	}
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::ClearMOrder()
{
	bool ret;
	DataMutex_MAccount.lock_shared();
	for (auto iter = MAccount.begin(); iter != MAccount.end(); iter++)
	{
		ret = iter->second->ClearMOrder();
		if (false == ret)
		{
			ErrorLog("ClearMOrder fail");
			break;
		}
	}
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::SetAccount(CAccount& Account)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(Account.stock_account);
	if (ite != MAccount.end())
	{
		ite->second->DataMutex_CAccount.lock();
		*ite->second = Account;      // ����CAccount��
		ite->second->DataMutex_CAccount.unlock();
	}
	else
	{
		DataMutex_MAccount.lock_upgrade();
		PtrAccount NewAccount(new CAccount(this, Account)); // �½�CAccount��
		MAccount[NewAccount->stock_account] = NewAccount;       // ����CAccount��MAP����
		DataMutex_MAccount.unlock_upgrade();
	}
	DataMutex_MAccount.unlock_shared();
	return true;
}

bool CFund::SetAccount(CString strAccountID)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return true;
	}
		
	DataMutex_MAccount.lock_upgrade();
	PtrAccount NewAccount(new CAccount(this, strAccountID));  // �½�CAccount��
	MAccount[NewAccount->stock_account] = NewAccount;             // ����CAccount��MAP����
	DataMutex_MAccount.unlock_upgrade();
	DataMutex_MAccount.unlock_shared();
	return true;
}

bool CFund::SetSecurity(CString strAccountID, CSecurity &Security)
{
	DataMutex_MAccount.lock_shared();
	bool ret;
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		ret = ite->second->SetSecurity(Security);;
		DataMutex_MAccount.unlock_shared();
		return ret;
	}

	if (!SetAccount(strAccountID))
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	ret = ite->second->SetSecurity(Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::SetSecurity_BiaoDi(CString strAccountID, CSecurity &Security)
{
	DataMutex_MAccount.lock_shared();

	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		bool ret = ite->second->SetSecurity_BiaoDi(Security);
		DataMutex_MAccount.unlock_shared();
		return ret;
	}

	if (!SetAccount(strAccountID))
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->SetSecurity_BiaoDi(Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::SetSecurity_DanBao(CString strAccountID, CSecurity &Security)
{
	DataMutex_MAccount.lock_shared();

	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		bool ret = ite->second->SetSecurity_DanBao(Security);
		DataMutex_MAccount.unlock_shared();
		return ret;
	}

	if (!SetAccount(strAccountID))
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->SetSecurity_DanBao(Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}


bool CFund::SetVCreditAsset(VecCreditAsset &VCreditAssetTmp)
{
	DataMutex_VCreditAsset.lock();
	VCreditAsset = VCreditAssetTmp;
	DataMutex_VCreditAsset.unlock();
	return true;
}

bool CFund::SetPosition(CString strAccountID, CPosition& Position)
{
	DataMutex_MAccount.lock_shared();
	bool ret;
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		ret = ite->second->SetPosition(Position);
		DataMutex_MAccount.unlock_shared();
		return ret;
	}

	if (!SetAccount(strAccountID))
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
		
	ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	ret = ite->second->SetPosition(Position);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::SetOrder(CString strAccountID, COrder& Order)
{
	DataMutex_MAccount.lock_shared();
	bool ret;
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		ret = ite->second->SetOrder(Order);
		DataMutex_MAccount.unlock_shared();
		return ret;
	}

	if (!SetAccount(strAccountID))
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
		
	ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	ret = ite->second->SetOrder(Order);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::SetDeal(CString strAccountID, UInt_64 entrust_no, CDeal& Deal)
{
	DataMutex_MAccount.lock_shared();
	bool ret;
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite != MAccount.end())
	{
		ret = ite->second->SetDeal(entrust_no, Deal);
		DataMutex_MAccount.unlock_shared();
		return ret;
	}
	
	if (!SetAccount(strAccountID))
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	
	ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
    ret = ite->second->SetDeal(entrust_no, Deal);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetAccount(CString strAccountID, CAccount& Account)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	
	ite->second->DataMutex_CAccount.lock_shared();
	Account = *ite->second;
	ite->second->DataMutex_CAccount.unlock_shared();
	DataMutex_MAccount.unlock_shared();
	return true;
}

bool CFund::GetPosition(CString strAccountID, CString strSecCode, CPosition& Position)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	bool ret = ite->second->GetPosition(strSecCode, Position);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetOrder(CString strAccountID, UInt_64 entrust_no, COrder& Order)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	bool ret = ite->second->GetOrder(entrust_no, Order);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetDeal(CString strAccountID, UInt_64 entrust_no, CString business_id, CDeal& Deal)
{
	DataMutex_MAccount.lock_shared();
	bool ret;
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	ret = ite->second->GetDeal(entrust_no, business_id, Deal);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetMAccount(_Account& Account)
{
	if (&MAccount == NULL)
		return false;
	Account.clear();
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.begin();
	while (ite != MAccount.end())
	{
		ite->second->DataMutex_CAccount.lock_shared();
		PtrAccount NewAccount(new CAccount(this, *ite->second)); // �½�CAccount��
		Account[NewAccount->stock_account] = NewAccount;       // ����CAccount��MAP����
		ite->second->DataMutex_CAccount.unlock_shared();
		ite++;
	}
	DataMutex_MAccount.unlock_shared();
	return true;
}

bool CFund::GetMPosition(CString strAccountID, _Position& Position)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	bool ret = ite->second->GetMPosition(Position);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetMOrder(CString strAccountID, _Order& Order)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
		
	bool ret = ite->second->GetMOrder(Order);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetMDeal(CString strAccountID, UInt_64 entrust_no, _Deal& Deal)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		ExceptionInterrupt;
		LOG(ERROR) << "abnormal strAccountID"<< strAccountID;
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	bool ret = ite->second->GetMDeal(entrust_no, Deal);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetMSecurity(CString strAccountID, _Security& Security)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->GetMSecurity(Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}
	
bool CFund::GetMSecurity_BiaoDi(CString strAccountID, _Security& Security)
{
	DataMutex_MAccount.lock_shared();

	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->GetMSecurity_BiaoDi(Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetMSecurity_DanBao(CString strAccountID, _Security& Security)
{
	DataMutex_MAccount.lock_shared();

	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->GetMSecurity_DanBao(Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetSecurity(CString strAccountID, CString strSecCode, CSecurity &Security)
{
	DataMutex_MAccount.lock_shared();
	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}
	bool ret = ite->second->GetSecurity(strSecCode, Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetVCreditAsset(VecCreditAsset &VCreditAssetTmp)
{
	DataMutex_VCreditAsset.lock_shared();
	VCreditAssetTmp = VCreditAsset;
	DataMutex_VCreditAsset.unlock_shared();
	return true;
}

bool CFund::GetSecurity_BiaoDi(CString strAccountID, CString strSecCode, CSecurity &Security)
{
	DataMutex_MAccount.lock_shared();

	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->GetSecurity_BiaoDi(strSecCode, Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}

bool CFund::GetSecurity_DanBao(CString strAccountID, CString strSecCode, CSecurity &Security)
{
	DataMutex_MAccount.lock_shared();

	_Account::iterator ite = MAccount.find(strAccountID);
	if (ite == MAccount.end())
	{
		DataMutex_MAccount.unlock_shared();
		return false;
	}

	bool ret = ite->second->GetSecurity_DanBao(strSecCode, Security);
	DataMutex_MAccount.unlock_shared();
	return ret;
}
