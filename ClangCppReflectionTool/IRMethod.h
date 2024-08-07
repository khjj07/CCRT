﻿#pragma once
#include <vector>
#include "Define.h"


namespace ccrt
{
    class CRRTAPI IRMethod
    {
    public:
        virtual AccessSpecifier GetAccessSpecifier() = 0;
        virtual std::string GetName() = 0;
        virtual std::string GetReturnType() = 0;

        template<typename ReturnType, typename... Args>
        ReturnType Invoke(Args... a1) const
        {
            auto x=  reinterpret_cast<ReturnType(*)(void*, Args...)>(stub_ptr);
            return (*x)(object_ptr, a1...);
        }

    public:
        void* object_ptr;
        void* stub_ptr;
    };
}
