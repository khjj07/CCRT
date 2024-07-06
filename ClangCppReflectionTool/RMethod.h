#pragma once
#include <cstdlib>
#include <vcruntime_typeinfo.h>

#include "AccessSpecifier.h"
#include "Define.h"
#include "IRMethod.h"

namespace ccrt
{
	template<typename ReturnType,typename... Args>
    class RMethod : public IRMethod
    {
    public:
        RMethod(AccessSpecifier accessSpecifier, std::string name);
        AccessSpecifier GetAccessSpecifier() override;
        std::string GetReturnType() override;
        std::string GetName() override;

        template <class T, ReturnType (T::*TMethod)(Args...)>
        static IRMethod* Create(T* object_ptr, AccessSpecifier accessSpecifier, std::string name)
        {
			RMethod* d = new RMethod(accessSpecifier,name);
            d->object_ptr = object_ptr;
            d->stub_ptr = reinterpret_cast<void*>(&MethodStub<T, TMethod>); // #1
            return d;
        }

    public:
        template <class T, ReturnType(T::*TMethod)(Args...)>
        static ReturnType MethodStub(void* object_ptr, Args... a1)
        {
            T* p = static_cast<T*>(object_ptr);
            return (p->*TMethod)(a1...); // #2
        }

	private:
        AccessSpecifier accessSpecifier_;
        std::string name_;
    };

	template <typename ReturnType, typename ... Args>
	RMethod<ReturnType, Args...>::RMethod(AccessSpecifier accessSpecifier, std::string name)
		:accessSpecifier_(accessSpecifier),name_(name) {}

	template <typename ReturnType, typename ... Args>
	AccessSpecifier RMethod<ReturnType, Args...>::GetAccessSpecifier()
	{
        return accessSpecifier_;
	}

	template <typename ReturnType, typename ... Args>
	std::string RMethod<ReturnType, Args...>::GetReturnType()
	{
        return typeid(ReturnType).name();
	}

	template <typename ReturnType, typename ... Args>
	std::string RMethod<ReturnType, Args...>::GetName()
	{
        return name_;
	}
}
