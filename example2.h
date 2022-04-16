#ifndef _EXAMPLE__TWO__H__
#define _EXAMPLE__TWO__H__

#include <iostream>
#include <assert.h>

namespace Example
{
    class Triplet
    {
        public:
            // constructors and destructors
            Triplet() : m_i(0), m_j(0), m_k(0) {}
            Triplet(const Triplet& rhs)
            {
                m_i = rhs.m_i;
                m_j = rhs.m_j;
                m_k = rhs.m_k;
            }
            // destructor not needed - skip it

            // operations
            void Init(int32_t i, int32_t j, int32_t k)
            {
                assert(i < j);
                assert(j < k);
                m_i = i;
                m_j = j;
                m_k = k;
            }

            void Print() const
            {
                std::cout << "{ " 
                          << m_i 
                          << " , " 
                          << m_j 
                          << " , " 
                          << m_k 
                          << " }" 
                          << std::endl;
            }

            // overloads
            bool operator==(const Triplet& rhs)
            {
                return ((m_i == rhs.m_i) &&
                        (m_j == rhs.m_j) &&
                        (m_k == rhs.m_k));
            }


        protected:
            int32_t m_i;
            int32_t m_j;
            int32_t m_k;

        private:
            Triplet& operator=(const Triplet& rhs)=delete;        
    };
}

#endif // _EXAMPLE__TWO__H__
