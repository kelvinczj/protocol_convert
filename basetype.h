#ifndef __BASETYPE_H__
#define __BASETYPE_H__

#include <stdint.h>
#include <string>
#include <list> 
#include <string>

#include "platform_exception.h"

namespace Protocol 
{
    class INT8
    {
        public:
            int8_t Value() { return V; }
        private:
            int8_t V;
    };

    class INT16
    {
        public:
            int16_t Value() { return V; }
        private:
            int16_t V;
    };

    class INT24
    {
        public:
            int32_t Value() { return V; }
        private:
            int32_t V;
    };

    class INT32
    {
        public:
            int32_t Value() { return V; }
        private:
            int32_t V;
    };

    class INT48 
    {
        public:
            int64_t Value() { return V; }
        private:
            int64_t V;
    };

    class INT64 
    {
        public:
            int64_t Value() { return V; }
        private:
            int64_t V;
    };


    /** 
     * @brief StringLenFieldSize 代表了协议中代表字符串长度的字段的所占的bytes
     *        不同的协议中，所占的bytes可能会不一样
     */
    template<int StringLenFieldSize>
        class ProString 
        {
            public:
                static int GetStringLenFieldSize() {return StringLenFieldSize; }
                std::string Value() { return V; }
            private:
                std::string V;
        };

    /** 
     * @brief ListCntFieldSize 是 协议中描述list个数的字段所占的bytes。 
     *        不同的协议中，所占的bytes可能会不一样
     */
    template<int ListCntFieldSize, class T>
        class ProList 
        {
            public: 
                typedef T ValueType;
                static int GetListCntFieldSize() { return ListCntFieldSize; }
                const T& operator[](int Index) throw(CExcept)  
                {  try {
                           return V[Index]; 
                       } catch {
                           Except oExcept(__FILE__, __FUNCTION__, __LINE__);
                           std::stringstream oss;
                           oss << "Invalid index " << Index << stsd::endl;
                           oExcept.m_strErrMsg = oss.str();
                           throw oExcept;
                       }
                }
            private:
                std::vector<T> V;

        };


    /** 
     * @brief 现在bit最多时支持8个 
     *        因为协议支持的最低粒度时bit，所以要定义BIT类型。
     *
     *          */
    template<int BitCnt> 
        class BITS
        {
            public:
                static int GetBitCnt() 
                { 
                    assert( 1 / (BitCnt > 8 ? 0 : 1));
                    return BitCnt; 
                }
                int8_t ToInt8() { return ((int8_t)V); }
                int16_t ToInt16() { return ((int16_t)V); }
                int32_t ToInt32() { return ((int32_t)V); } 
                int64_t ToInt64() { return ((int64_t)V); } 
            private: 
                char V;
        }

    typedef BITS<1>     BITS1;
    typedef BITS<2>     BITS2;
    typedef BITS<3>     BITS3;
    typedef BITS<4>     BITS4;
    typedef BITS<5>     BITS5;
    typedef BITS<6>     BITS6;
    typedef BITS<7>     BITS7;
    typedef BITS<8>     BITS8; 


}; //namespace

#endif
