#pragma once
#include <cstdlib>

#include "Define.h"
#include "IRMethod.h"

namespace ccrt
{

	template<typename ReturnType,typename... Args>
    class RMethod : public IRMethod
    {
    public:
        RMethod(){}

        template <class T, ReturnType (T::*TMethod)(Args...)>
        static IRMethod* from_method(T* object_ptr)
        {
			RMethod* d = new RMethod;
            d->object_ptr = object_ptr;
            d->stub_ptr = reinterpret_cast<void*>(&method_stub<T, TMethod>); // #1
            return d;
        }

    public:
        template <class T, ReturnType(T::*TMethod)(Args...)>
        static ReturnType method_stub(void* object_ptr, Args... a1)
        {
            T* p = static_cast<T*>(object_ptr);
            return (p->*TMethod)(a1...); // #2
        }
    };

}
