#ifndef __p2List_H__
#define __p2List_H__

#define Null 0

#include "Arduino.h"

#define RELEASE( x )                 \
{                                    \
    if( x != Null && x != nullptr )  \
	{                                \
		delete x;                    \
		x = nullptr;                 \
	}								 \
}

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
{                          \
    if( x != nullptr )     \
	{                      \
		delete[] x;        \
		x = nullptr;       \
	}                      \
}

typedef unsigned int uint;

/**
* Contains items from double linked list
*/
template<class tdata>
struct p2List_item
{
	tdata                 data;
	p2List_item<tdata>*   next;
	p2List_item<tdata>*   prev;

	inline p2List_item(const tdata& _data)
	{
		data = _data;
		next = prev = Null;
	}

	~p2List_item()
	{}
};

/**
* Manages a double linked list
*/
template<class tdata>
class p2List
{

public:

	p2List_item<tdata>*   start;
	p2List_item<tdata>*   end;

private:

	unsigned int  size;

public:

	/**
	* Constructor
	*/
	inline p2List()
	{
		start = end = Null;
		size = 0;
	}

	/**
	* Destructor
	*/
	~p2List()
	{
		clear();
	}

	/**
	* Get Size
	*/
	unsigned int count() const
	{
		return size;
	}

	/**
	* Add new item
	*/
	p2List_item<tdata>* add(const tdata& item)
	{
		p2List_item<tdata>*   p_data_item;
		p_data_item = new p2List_item < tdata >(item);

		if(start == Null)
		{
			start = end = p_data_item;
		}
		else
		{
			p_data_item->prev = end;
			end->next = p_data_item;
			end = p_data_item;
		}

		++size;
		return(p_data_item);
	}

	/**
	* Deletes an item from the list
	*/
	bool del(p2List_item<tdata>* item)
	{
		if(item == Null)
		{
			return (false);
		}

		// Now reconstruct the list
		if(item->prev != Null)
		{
			item->prev->next = item->next;

			if(item->next != Null)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}
		}
		else
		{
			if(item->next)
			{
				item->next->prev = Null;
				start = item->next;
			}
			else
			{
				start = end = Null;
			}
		}

		RELEASE(item);
		--size;
		return(true);
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		p2List_item<tdata>*   p_data;
		p2List_item<tdata>*   p_next;
		p_data = start;

		while(p_data != Null)
		{
			p_next = p_data->next;
			RELEASE(p_data);
			p_data = p_next;
		}

		start = end = Null;
		size = 0;
	}

	/**
	* read / write operator access directly to a position in the list
	*/
	tdata& operator  [](const unsigned int index)
	{
		long                  pos;
		p2List_item<tdata>*   p_item;
		pos = 0;
		p_item = start;

		while(p_item != Null)
		{
			if(pos == index)
			{
				break;
			}

			++pos;
			p_item = p_item->next;
		}

		return(p_item->data);
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const tdata& operator  [](const unsigned int index) const
	{
		long                  pos;
		p2List_item<tdata>*   p_item;
		pos = 0;
		p_item = start;

		while(p_item != Null)
		{
			if(pos == index)
			{
				break;
			}

			++pos;
			p_item = p_item->next;
		}

		return(p_item->data);
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const p2List<tdata>& operator +=(const p2List<tdata>& other_list)
	{
		p2List_item<tdata>*   p_item = other_list.start;

		while(p_item != Null)
		{
			add(p_item->data);
			p_item = p_item->next;
		}

		return(*this);
	}

	/**
	* const access to a node in a position in the list
	*/
	const p2List_item<tdata>* At(unsigned int index) const
	{
		long                  pos = 0;
		p2List_item<tdata>*   p_item = start;

		while(p_item != Null)
		{
			if(pos++ == index)
				break;

			p_item = p_item->next;
		}

		return p_item;
	}

	/**
	* access to a node in a position in the list
	*/
	p2List_item<tdata>* At(unsigned int index)
	{
		long                  pos = 0;
		p2List_item<tdata>*   p_item = start;

		while(p_item != Null)
		{
			if(pos++ == index)
				break;

			p_item = p_item->next;
		}

		return p_item;
	}

	// Sort
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			p2List_item<tdata>* tmp = start;

			while(tmp != Null && tmp->next != Null)
			{
				++ret;
				if(tmp->data > tmp->next->data)
				{
					SWAP(tmp->data, tmp->next->data);
					swapped = true;
				}

				tmp = tmp->next;
			}
		}

		return ret;
	}

	/**
	* returns the first apperance of data as index (-1 if not found)
	*/
	int find(const tdata& data)
	{
		p2List_item<tdata>* tmp = start;
		int index = 0;

		while(tmp != Null)
		{
			if(tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}

	void InsertAfter(uint position, const p2List<tdata>& list)
	{
		p2List_item<tdata>* p_my_list = At(position);
		p2List_item<tdata>* p_other_list = list.start;

		while(p_other_list != Null)
		{
			p2List_item<tdata>* p_new_item = new p2List_item<tdata>(p_other_list->data);

			p_new_item->next = (p_my_list) ? p_my_list->next : Null;

			if(p_new_item->next != Null)
				p_new_item->next->prev = p_new_item;
			else
				end = p_new_item;

			p_new_item->prev = p_my_list;
				
			if(p_new_item->prev != Null)
				p_new_item->prev->next = p_new_item;
			else
				start = p_new_item;

			p_my_list = p_new_item;
			p_other_list = p_other_list->next;
		}
	}

	void Pop(tdata &my_item)
	{
		my_item = At(0)->data;
		del(start);
	}
};
#endif /*__p2List_H__*/
