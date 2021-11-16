#pragma once

template <class T>
class List
{
public:
	List()
	{
		buffer = nullptr;
		size = 0;
	}

	List(const List<T>& other)
	{
		buffer = nullptr;
		size = 0;
		Add(other.buffer, other.GetSize());
	}

	List(T items[], int n)
	{
		buffer = nullptr;
		size = 0;
		Add(items, n);
	}

	~List()
	{
		delete[] buffer;
	}
	

	void Add(const T& item)
	{
		IncraseBuffer(1);
		buffer[size - 1] = item;
	}

	void Add(T items[], int n)
	{
		IncraseBuffer(n);
		for (int i = 0; i < n; i++)
			buffer[size - n + i] = items[i];
	}

	void Remove(const T& item)
	{
		RemoveAt(Find(item));
	}

	void RemoveAt(int index)
	{
		if (IsValidIndex(index))
		{
			for (int i = 0; i < size; i++)
				if (i > index)
					buffer[i - 1] = buffer[i];
			DecreaseBuffer();
		}
	}

	int Find(const T& item)
	{
		for (int i = 0; i < size; i++)
			if (buffer[i] == item)
				return i;
		return -1;
	}

	inline bool IsValidIndex(int index) const 
	{
		return index >= 0 && index < size;
	}

	void operator=(const List<T>& other)
	{
		if (size == other.size)
		{
			for (int i = 0; i < size; i++)
				buffer[i] = other[i];
		}
		else
		{
			Erase();
			Add(other.buffer, other.GetSize());
		}
	}

	const T& operator[](int index) const
	{
		return buffer[index];
	}

	T& operator[](int index)
	{
		return buffer[index];
	}

	void Erase()
	{
		delete[] buffer;
		size = 0;
		buffer = nullptr;
	}

	inline int GetSize() const
	{
		return size;
	}

private:
	T* buffer;
	int size;

	void IncraseBuffer(int n)
	{
		T* copy = buffer;
		buffer = new T[size + n];
		for (int i = 0; i < size; i++)
			buffer[i] = copy[i];
		delete copy;
		size += n;
	}

	void DecreaseBuffer()
	{
		T* copy = buffer;
		buffer = new T[size + 1];
		for (int i = 0; i < size -1; i++)
			buffer[i] = copy[i];
		delete copy;
		size--;
	}
};