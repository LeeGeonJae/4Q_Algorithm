#pragma once

#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename KeyType, typename ValueType>
class HashMap
{
public:
	HashMap(int _hashSize);
	~HashMap();

public:
	bool Find(const KeyType& _key);
	int GetHash(KeyType _key);
	void Insert(const KeyType& _key, const ValueType& _value);
	void Delete(const KeyType& _key);

public:
	void PrintCollisionHash();

private:
	vector<list<pair<KeyType, ValueType>>> m_Data;
	int m_HashSize;
};

template<typename KeyType, typename ValueType>
inline HashMap<KeyType, ValueType>::HashMap(int _hashSize)
{
	m_Data.resize(_hashSize);
	m_HashSize = _hashSize;
}

template<typename KeyType, typename ValueType>
inline HashMap<KeyType, ValueType>::~HashMap()
{
	m_Data.clear();
}

template<typename KeyType, typename ValueType>
inline bool HashMap<KeyType, ValueType>::Find(const KeyType& _key)
{
	int index = GetHash(_key);

	for (auto data : m_Data[index])
	{
		if (data.first == _key)
			return true;
	}

	return false;
}

template<typename KeyType, typename ValueType>
inline int HashMap<KeyType, ValueType>::GetHash(KeyType _key)
{
	unsigned long long hash = 0;
	unsigned int keySize = sizeof(_key);

	const char* First = reinterpret_cast<const char*>(&_key);

	for (int i = 0; i < keySize; i++)
	{
		hash ^= static_cast<size_t>(First[i]);
		hash *= _FNV_prime;
	}
	
	hash = (hash * 65523) % m_HashSize;

	return hash;
}

template<typename KeyType, typename ValueType>
inline void HashMap<KeyType, ValueType>::Insert(const KeyType& _key, const ValueType& _value)
{
	int index = GetHash(_key);

	// 키가 같은 데이터도 추가됨 
	m_Data[index].emplace_back(_key, _value);
}

template<typename KeyType, typename ValueType>
inline void HashMap<KeyType, ValueType>::Delete(const KeyType& _key)
{
	int index = GetHash(_key);

	for (auto data : m_Data[index])
	{
		if (data.first == _key)
		{
			m_Data[index].erase(data);
		}
	}
}

template<typename KeyType, typename ValueType>
inline void HashMap<KeyType, ValueType>::PrintCollisionHash()
{
	int hashCollision = 0;
	int MaxhashListSize = 0;

	for (auto hashData : m_Data)
	{
		if (hashData.size() > 1)
		{
			hashCollision++;

			if (MaxhashListSize < hashData.size())
				MaxhashListSize = hashData.size();
		}
	}

	cout << "충돌된 해쉬 갯수 : " << hashCollision << endl;
	cout << "최대 충돌 해쉬 리스트 크기 : " << MaxhashListSize << endl;
}


template <typename ValueType>
class HashMap <string, ValueType>
{
public:
	HashMap(int _hashSize);
	~HashMap();

public:
	bool Find(const string& _key);
	int GetHash(string _key);
	void Insert(const string& _key, const ValueType& _value);
	void Delete(const string& _key);

public:
	void PrintCollisionHash();

private:
	vector<list<pair<string, ValueType>>> m_Data;
	int m_HashSize;
};

template <typename ValueType>
inline HashMap<string, ValueType>::HashMap(int _hashSize)
{
	m_Data.resize(_hashSize);
	m_HashSize = _hashSize;
}

template <typename ValueType>
inline HashMap<string, ValueType>::~HashMap()
{
	m_Data.clear();
}

template <typename ValueType>
inline bool HashMap<string, ValueType>::Find(const string& _key)
{
	int index = GetHash(_key);

	for (auto data : m_Data[index])
	{
		if (data.first == _key)
			return true;
	}

	return false;
}

template <typename ValueType>
inline int HashMap<string, ValueType>::GetHash(string _key)
{
	unsigned long long hash = 0;
	unsigned int keySize = _key.size();

	for (int i = 0; i < keySize; i++)
	{
		hash ^= _key[i];
		hash *= _FNV_prime;
	}

	hash = (hash * 65523) % m_HashSize;

	return hash;
}

template <typename ValueType>
inline void HashMap<string, ValueType>::Insert(const string& _key, const ValueType& _value)
{
	int index = GetHash(_key);

	for (auto data : m_Data[index])
	{
		if (data.first == _key)
			return;
	}
	// 키가 같은 데이터도 추가됨 
	m_Data[index].emplace_back(_key, _value);
}

template <typename ValueType>
inline void HashMap<string, ValueType>::Delete(const string& _key)
{
	int index = GetHash(_key);

	for (auto data : m_Data[index])
	{
		if (data.first == _key)
		{
			m_Data[index].erase(data);
		}
	}
}

template <typename ValueType>
inline void HashMap<string, ValueType>::PrintCollisionHash()
{
	int hashCollision = 0;
	int MaxhashListSize = 0;

	for (auto hashData : m_Data)
	{
		if (hashData.size() > 1)
		{
			hashCollision++;

			if (MaxhashListSize < hashData.size())
				MaxhashListSize = hashData.size();
		}
	}

	cout << "충돌된 해쉬 갯수 : " << hashCollision << endl;
	cout << "최대 충돌 해쉬 리스트 크기 : " << MaxhashListSize << endl;
}
