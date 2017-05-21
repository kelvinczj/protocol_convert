#ifndef __BIT_STRAM_H__
#define __BIT_STRAM_H__

#include <assert.h>
#include <string>

#include "basetype.h"

namespace Protocol 
{
    class BitStream 
    {
    
        public:
            BitStream(char* pStreamBuff, int nStreamSize, int nDataLen, bool bLittleEddien = false)
                :m_pStreamBuff(pStreamBuff)
            {
                assert(NULL != pStreamBuff);
                int nTest = 1;
                //机器是大端存储
                if (1 == *((char*)&nTest)) {
                    m_bDiffEndding = bLittleEddien ? false : true;
                } else {
                //机器是小端存储
                    m_bDiffEndding = bLittleEddien ? true : false;
                }

                m_nWriteRemainBits = (nStreamSize - nDataLen) * 8;
                m_nReadRemainBits = nDataLen * 8;
                m_nReadBitPos = 0;
                m_nWriteBitPos = nDataLen * 8;
            }
            ~BitStream() {}
            const std::string& GetErrMsg() { return m_strErrmsg; }

        protected:

            void _Read_Walk(int nBitStep) throw(CExcept)
            {   
                if (nBitStep > m_nReadRemainBits) {
                    CExcept oExcept(__FILE__, __FUNCTION__, __LINE__);
                    std::stringstream oss;
                    oss << "Read Out of Range" << std::endl;
                    oExcept.strErrMsg = oss.str();
                    throw oExcept;
                }

                m_nReadRemainBits -= nBitStep;
                m_nReadBitPos += nBitStep;
            } 

            void _Write_Walk(int nBitStep) throw(CExcept)
            {
                if (nBitStep > m_nWriteRemainBits) {
                    CExcept oExcept(__FILE__, __FUNCTION__, __LINE__);
                    std::stringstream oss;
                    oss << "Write out of range" << std::endl;
                    oExcept.strErrMsg = oss.str();
                    throw oExcept;
                }

                m_nWriteRemainBits -= nBitStep;
                m_nWriteBitPos += nBitStep;
                m_nReadRemainBits += nBitStep;
            }
        protected:
            char *m_pStreamBuff;
            int m_nReadBitPos;
            int m_nWriteBitPos;
            int m_nReadRemainBits;
            int m_nWriteRemainBits;
            bool m_bDiffEddien;
            std::string m_strErrMsg;
    };
};


#endif
