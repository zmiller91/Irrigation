// H.h

#ifndef _H_h
#define _H_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// HM.h

#ifndef _HM_h
#define _HM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

using namespace std;
const int TABLE_SIZE = 128;

/*
* HashNode Class Declaration
*/
class HashNode
{
public:
	int key;
	int value;
	HashNode* next;

	HashNode(int key, int value)
	{
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

/*
* HashMap Class Declaration
*/
class HM
{
private:
	HashNode** htable;
	int m_numUsers;
public:
	HM()
	{
		m_numUsers = 0;
		htable = new HashNode*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			htable[i] = NULL;
	}
	~HM()
	{
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			HashNode* entry = htable[i];
			while (entry != NULL)
			{
				HashNode* prev = entry;
				entry = entry->next;
				delete prev;
			}
		}
		delete[] htable;
	}
	/*
	* Hash Function
	*/
	int HashFunc(int key)
	{
		return key % TABLE_SIZE;
	}

	/*
	* Insert Element at a key
	*/
	void Insert(int key, int value)
	{

		if (Search(key) != -1)
		{
			return;
		}
		else
		{
			m_numUsers += 1;
		}

		int hash_val = HashFunc(key);
		HashNode* prev = NULL;
		HashNode* entry = htable[hash_val];
		while (entry != NULL)
		{
			prev = entry;
			entry = entry->next;
		}
		if (entry == NULL)
		{
			entry = new HashNode(key, value);
			if (prev == NULL)
			{
				htable[hash_val] = entry;
			}
			else
			{
				prev->next = entry;
			}
		}
		else
		{
			entry->value = value;
		}
	}
	/*
	* Remove Element at a key
	*/
	void Remove(int key)
	{
		int hash_val = HashFunc(key);
		HashNode* entry = htable[hash_val];

		if (entry == NULL)
		{
			return;
		}

		HashNode* deleted = NULL;

		// If it's the first element then we can delete it and move up next
		if (entry->key == key)
		{
			deleted = entry;
			htable[hash_val] = entry->next;
		}

		// Otherwise we have to go through the chain and figure out what element to delete
		HashNode* prev = NULL;
		HashNode* curr = NULL;
		while (deleted == NULL && entry != NULL && entry->next != NULL)
		{
			prev = entry;
			curr = entry->next;
			if (curr->key == key)
			{
				deleted = curr;
				prev->next = curr->next;
			}
		}

		// if nothing was deleted, then don't decrement
		if (deleted != NULL)
		{
			m_numUsers -= 1;
		}

		delete deleted;

	}
	/*
	* Search Element at a key
	*/
	int Search(int key)
	{
		bool flag = false;
		int hash_val = HashFunc(key);
		HashNode* entry = htable[hash_val];

		if (entry == NULL)
		{
			return -1;
		}

		while (entry != NULL)
		{
			if (entry->key == key)
			{
				flag = true;
				return entry->value;
			}
			entry = entry->next;
		}
		if (!flag)
			return -1;
	}

	int getNumUsers()
	{
		return m_numUsers;
	}
};

#endif


#endif

