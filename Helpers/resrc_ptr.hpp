#pragma once

#include <memory>

#define NOMINMAX
#include "D3DUtil.h"

// resrc_ptr and resrc_inst_ptr are wrapper classes made to handle pointers to resources that are passed around the program
// resrc_ptr has exclusive ownership of the resource. If the resource is re-allocated, all its instances will point to the new location in memory
// resrc_inst_ptrs acts as a 'one-way reference' of its corresponding resrc_ptr
// This means resrc_ptrs can modify the value pointed to by a resrc_inst_ptr, but not the other way around
// resrc_inst_ptrs will always provide access to a resource without exposing ownership

namespace std
{
	template<>
	struct default_delete< ID3D10Effect >
	{
	public:
	  void operator()(ID3D10Effect* ptr)
	  {
		ptr->Release();
	  }
	};
	template<>
	struct default_delete< ID3D10ShaderResourceView >
	{
	public:
	  void operator()(ID3D10ShaderResourceView* ptr)
	  {
		ptr->Release();
	  }
	};
}

template <typename T>
class resource_ptr{
public:
	resource_ptr(void) : pData(nullptr) {}
	resource_ptr(const std::unique_ptr<T>& masterPtr) : pData(&masterPtr) {}
	
	T* operator->() const
	{	
		return pData->get();
	}

	T* get(void)
	{
		return pData->get();
	}

	bool operator==(const T* ptr) const
	{
		return pData->get() == ptr;
	}
	
	bool operator==(const resource_ptr<T>& ptr) const
	{
		return pData->get() == *ptr->pData;
	}
	
	bool operator!=(const T* ptr) const
	{
		return pData->get() != ptr;
	}
	
	bool operator!=(const resource_ptr<T>& ptr) const
	{
		return pData->get() != *ptr->pData;
	}

private:
	const std::unique_ptr<T>* pData;
};
/*
template<typename T>
struct DefaultResourceDeleter
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
};

template<typename T, typename DeleterType = DefaultResourceDeleter<T> > class resrc_ptr{
	 template<typename T> friend class resrc_inst_ptr;
public:
	resrc_ptr(void):pData(nullptr), _Delete(DefaultResourceDeleter<T>()){}
	
	resrc_ptr(T* pResource):pData(pResource), _Delete(DefaultResourceDeleter<T>()){}

	resrc_ptr(T* pResource, DeleterType _delete):pData(pResource), _Delete(_delete){}

	resrc_ptr(resrc_ptr<T>&& src)
	{
		pData = src.pData;
		pData = nullptr;
	}
	
	resrc_ptr<T>& operator=(resrc_ptr<T>&& src)
	{
		if(pData != src.pData){
			delete pData;
			pData = src.pData;
			src.pData = 0;
		}
		return *this
	}
//TODO: Fix warning when deleting temporary resrc_ptr in ResourceService.h
//#pragma warning(disable : 4150)
	~resrc_ptr(void)
	{
		if(pData)
			_Delete(pData);
	}
//#pragma warning(default : 4150)

	resrc_ptr& operator=(T* pResource)
	{
		delete pData;
		pData = pResource;
		return *this;
	}

	T* operator*(void) const
	{
		return pData;
	}
	
	T* operator->(void) const
	{
		return pData;
	}

private:
	T* pData;
	DeleterType _Delete;
	
	//Sharing ownership between resrc_ptrs is not allowed, use resrc_inst_ptr instead
	resrc_ptr(const resrc_ptr& src);// = delete;
	resrc_ptr& operator=(const resrc_ptr& src);// = delete;
};

template<typename T> class resrc_inst_ptr
{
public:
	resrc_inst_ptr(void):ppData(nullptr){}

	explicit resrc_inst_ptr(resrc_ptr<T>& masterPtr):ppData(&masterPtr.pData){}
	
	resrc_inst_ptr(const resrc_inst_ptr<T>& src):ppData(src.ppData){}

	~resrc_inst_ptr(void){}

	resrc_inst_ptr& operator=(resrc_ptr<T>& masterPtr)
	{
		ppData = &masterPtr.pData;
		return *this;
	}
	
	resrc_inst_ptr& operator=(const resrc_inst_ptr<T>& src)
	{
		ppData = src.ppData;
		return *this;
	}
	
	T* operator*(void) const
	{
		if(ppData)
			return *ppData;
		else return nullptr;
	}
	
	T* operator->(void) const
	{
		if(ppData)
			return *ppData;
		else return nullptr;
	}

private:
	T** ppData;
};
*/