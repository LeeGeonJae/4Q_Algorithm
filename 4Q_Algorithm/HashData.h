#pragma once

#include <string>

using namespace std;

// �ؽ� ����Ÿ
class HashData
{
public:
	HashData();
	~HashData();

public:
	void DataSetting(string name, int value, float speed);
	const string& GetName();
	const int& GetValue();

private:
	string	m_Name;
	int		m_Value;
	float	m_Speed;
};

