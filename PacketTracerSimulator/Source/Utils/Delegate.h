#pragma once

class BaseDelegate
{
public:
	virtual ~BaseDelegate() = default;

	virtual void CallProcedure()
	{
	}
};

template <class T>
class DelegateNoParam : public BaseDelegate
{
public:
	DelegateNoParam() : obj(nullptr), proc(nullptr)
	{ 
	}

	DelegateNoParam(T* obj) : obj(obj), proc(nullptr)
	{
	}

	DelegateNoParam(T* obj, void (T::* proc)()) : obj(obj), proc(proc)
	{ 
	}

	~DelegateNoParam()
	{	
	}

	void SetObject(T* obj)
	{
		this->obj = obj;
	}

	void SetProcedure(void (T::* proc)())
	{
		this->proc = proc;
	}

	virtual void CallProcedure() override
	{
		if (obj != nullptr && proc != nullptr)
			(obj->*proc)();
	}

private:
	T* obj;
	void (T::* proc)();
};
