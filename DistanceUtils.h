#pragma once

#include <opencv2/core/types_c.h>

namespace DistanceUtils {

    //! computes the L1 distance between two integer values
    template<typename T> static inline typename std::enable_if<std::is_integral<T>::value,size_t>::type L1dist(T a, T b) {
        return (size_t)abs((int)a-b);
    }

    //! computes the L1 distance between two float values
    template<typename T> static inline typename std::enable_if<std::is_floating_point<T>::value,float>::type L1dist(T a, T b) {
        return fabs((float)a-(float)b);
    }

    //! computes the L1 distance between two generic arrays
    template<size_t nChannels, typename T> static inline auto L1dist(const T* a, const T* b) -> decltype(L1dist(*a,*b)) {
        decltype(L1dist(*a,*b)) oResult = 0;
        for(size_t c=0; c<nChannels; ++c)
            oResult += L1dist(a[c],b[c]);
        return oResult;
    }

    //! computes the L1 distance between two generic arrays
    template<size_t nChannels, typename T> static inline auto L1dist(const T* a, const T* b, size_t nElements, const uchar* m=NULL) -> decltype(L1dist<nChannels>(a,b)) {
        decltype(L1dist<nChannels>(a,b)) oResult = 0;
        size_t nTotElements = nElements*nChannels;
        if(m) {
            for(size_t n=0,i=0; n<nTotElements; n+=nChannels,++i)
                if(m[i])
                    oResult += L1dist<nChannels>(a+n,b+n);
        }
        else {
            for(size_t n=0; n<nTotElements; n+=nChannels)
                oResult += L1dist<nChannels>(a+n,b+n);
        }
        return oResult;
    }

    //! computes the L1 distance between two generic arrays
    template<typename T> static inline auto L1dist(const T* a, const T* b, size_t nElements, size_t nChannels, const uchar* m=NULL) -> decltype(L1dist<3>(a,b,nElements,m)) {
        CV_Assert(nChannels>0 && nChannels<=4);
        switch(nChannels) {
            case 1: return L1dist<1>(a,b,nElements,m);
            case 2: return L1dist<2>(a,b,nElements,m);
            case 3: return L1dist<3>(a,b,nElements,m);
            case 4: return L1dist<4>(a,b,nElements,m);
            default: return 0;
        }
    }

    //! computes the L1 distance between two opencv vectors
    template<int nChannels, typename T> static inline auto L1dist(const cv::Vec<T,nChannels>& a, const cv::Vec<T,nChannels>& b) -> decltype(L1dist<nChannels,T>((T*)(0),(T*)(0))) {
        T a_array[nChannels], b_array[nChannels];
        for(int c=0; c<nChannels; ++c) {
            a_array[c] = a[(int)c];
            b_array[c] = b[(int)c];
        }
        return L1dist<nChannels>(a_array,b_array);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    //! computes the squared L2 distance between two generic variables
    template<typename T> static inline auto L2sqrdist(T a, T b) -> decltype(L1dist(a,b)) {
        auto oResult = L1dist(a,b);
        return oResult*oResult;
    }

    //! computes the squared L2 distance between two generic arrays
    template<size_t nChannels, typename T> static inline auto L2sqrdist(const T* a, const T* b) -> decltype(L2sqrdist(*a,*b)) {
        static_assert(nChannels>0,"vectors should have at least one channel");
        decltype(L2sqrdist(*a,*b)) oResult = 0;
        for(size_t c=0; c<nChannels; ++c)
            oResult += L2sqrdist(a[c],b[c]);
        return oResult;
    }

    //! computes the squared L2 distance between two generic arrays
    template<size_t nChannels, typename T> static inline auto L2sqrdist(const T* a, const T* b, size_t nElements, const uchar* m=NULL) -> decltype(L2sqrdist<nChannels>(a,b)) {
        decltype(L2sqrdist<nChannels>(a,b)) oResult = 0;
        size_t nTotElements = nElements*nChannels;
        if(m) {
            for(size_t n=0,i=0; n<nTotElements; n+=nChannels,++i)
                if(m[i])
                    oResult += L2sqrdist<nChannels>(a+n,b+n);
        }
        else {
            for(size_t n=0; n<nTotElements; n+=nChannels)
                oResult += L2sqrdist<nChannels>(a+n,b+n);
        }
        return oResult;
    }

    //! computes the squared L2 distance between two generic arrays
    template<typename T> static inline auto L2sqrdist(const T* a, const T* b, size_t nElements, size_t nChannels, const uchar* m=NULL) -> decltype(L2sqrdist<3>(a,b,nElements,m)) {
        CV_Assert(nChannels>0 && nChannels<=4);
        switch(nChannels) {
            case 1: return L2sqrdist<1>(a,b,nElements,m);
            case 2: return L2sqrdist<2>(a,b,nElements,m);
            case 3: return L2sqrdist<3>(a,b,nElements,m);
            case 4: return L2sqrdist<4>(a,b,nElements,m);
            default: return 0;
        }
    }

    //! computes the squared L2 distance between two opencv vectors
    template<int nChannels, typename T> static inline auto L2sqrdist(const cv::Vec<T,nChannels>& a, const cv::Vec<T,nChannels>& b) -> decltype(L2sqrdist<nChannels,T>((T*)(0),(T*)(0))) {
        T a_array[nChannels], b_array[nChannels];
        for(int c=0; c<nChannels; ++c) {
            a_array[c] = a[(int)c];
            b_array[c] = b[(int)c];
        }
        return L2sqrdist<nChannels>(a_array,b_array);
    }

    //! computes the L2 distance between two generic arrays
    template<size_t nChannels, typename T> static inline float L2dist(const T* a, const T* b) {
        static_assert(nChannels>0,"vectors should have at least one channel");
        decltype(L2sqrdist(*a,*b)) oResult = 0;
        for(size_t c=0; c<nChannels; ++c)
            oResult += L2sqrdist(a[c],b[c]);
        return sqrt((float)oResult);
    }

    //! computes the L2 distance between two generic arrays
    template<size_t nChannels, typename T> static inline float L2dist(const T* a, const T* b, size_t nElements, const uchar* m=NULL) {
        decltype(L2sqrdist<nChannels>(a,b)) oResult = 0;
        size_t nTotElements = nElements*nChannels;
        if(m) {
            for(size_t n=0,i=0; n<nTotElements; n+=nChannels,++i)
                if(m[i])
                    oResult += L2sqrdist<nChannels>(a+n,b+n);
        }
        else {
            for(size_t n=0; n<nTotElements; n+=nChannels)
                oResult += L2sqrdist<nChannels>(a+n,b+n);
        }
        return sqrt((float)oResult);
    }

    //! computes the squared L2 distance between two generic arrays
    template<typename T> static inline float L2dist(const T* a, const T* b, size_t nElements, size_t nChannels, const uchar* m=NULL) {
        CV_Assert(nChannels>0 && nChannels<=4);
        switch(nChannels) {
            case 1: return L2dist<1>(a,b,nElements,m);
            case 2: return L2dist<2>(a,b,nElements,m);
            case 3: return L2dist<3>(a,b,nElements,m);
            case 4: return L2dist<4>(a,b,nElements,m);
            default: return 0;
        }
    }

    //! computes the L2 distance between two opencv vectors
    template<int nChannels, typename T> static inline float L2dist(const cv::Vec<T,nChannels>& a, const cv::Vec<T,nChannels>& b) {
        T a_array[nChannels], b_array[nChannels];
        for(int c=0; c<nChannels; ++c) {
            a_array[c] = a[(int)c];
            b_array[c] = b[(int)c];
        }
        return L2dist<nChannels>(a_array,b_array);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    //! computes the color distortion between two integer arrays
    template<size_t nChannels, typename T> static inline typename std::enable_if<std::is_integral<T>::value,size_t>::type cdist(const T* curr, const T* bg) {
        static_assert(nChannels>1,"vectors should have more than one channel");
        static_assert(sizeof(size_t)>=8,"cdist: cannot be used with 32 bit integers, might integer overflow");
        bool bNonConstDist = false;
        bool bNonNullDist = (curr[0]!=bg[0]);
        bool bNonNullBG = (bg[0]>0);
        for(size_t c=1; c<nChannels; ++c) {
            bNonConstDist |= (curr[c]!=curr[c-1]) || (bg[c]!=bg[c-1]);
            bNonNullDist |= (curr[c]!=bg[c]);
            bNonNullBG |= (bg[c]>0);
        }
        if(!bNonConstDist || !bNonNullDist)
            return 0;
        if(!bNonNullBG) {
            size_t nulldist = 0;
            for(size_t c=0; c<nChannels; ++c)
                nulldist += curr[c];
            return nulldist;
        }
        size_t curr_sqr = 0;
        size_t bg_sqr = 0;
        size_t mix = 0;
        for(size_t c=0; c<nChannels; ++c) {
            curr_sqr += curr[c]*curr[c];
            bg_sqr += bg[c]*bg[c];
            mix += curr[c]*bg[c];
        }
        return (size_t)sqrt((float)(curr_sqr-(mix*mix)/bg_sqr));
    }

    //! computes the color distortion between two float arrays
    template<size_t nChannels, typename T> static inline typename std::enable_if<std::is_floating_point<T>::value,float>::type cdist(const T* curr, const T* bg) {
        static_assert(nChannels>1,"vectors should have more than one channel");
        bool bNonConstDist = false;
        bool bNonNullDist = (curr[0]!=bg[0]);
        bool bNonNullBG = (bg[0]>0);
        for(size_t c=1; c<nChannels; ++c) {
            bNonConstDist |= (curr[c]!=curr[c-1]) || (bg[c]!=bg[c-1]);
            bNonNullDist |= (curr[c]!=bg[c]);
            bNonNullBG |= (bg[c]>0);
        }
        if(!bNonConstDist || !bNonNullDist)
            return 0;
        if(!bNonNullBG) {
            float nulldist = 0;
            for(size_t c=0; c<nChannels; ++c)
                nulldist += curr[c];
            return nulldist;
        }
        float curr_sqr = 0;
        float bg_sqr = 0;
        float mix = 0;
        for(size_t c=0; c<nChannels; ++c) {
            curr_sqr += (float)curr[c]*curr[c];
            bg_sqr += (float)bg[c]*bg[c];
            mix += (float)curr[c]*bg[c];
        }
        if(curr_sqr<(mix*mix)/bg_sqr)
            return 0;
        else
            return (float)sqrt(curr_sqr-(mix*mix)/bg_sqr);
    }

    //! computes the color distortion between two generic arrays
    template<size_t nChannels, typename T> static inline auto cdist(const T* a, const T* b, size_t nElements, const uchar* m=NULL) -> decltype(cdist<nChannels>(a,b)) {
        decltype(cdist<nChannels>(a,b)) oResult = 0;
        size_t nTotElements = nElements*nChannels;
        if(m) {
            for(size_t n=0,i=0; n<nTotElements; n+=nChannels,++i)
                if(m[i])
                    oResult += cdist<nChannels>(a+n,b+n);
        }
        else {
            for(size_t n=0; n<nTotElements; n+=nChannels)
                oResult += cdist<nChannels>(a+n,b+n);
        }
        return oResult;
    }

    //! computes the color distortion between two generic arrays
    template<typename T> static inline auto cdist(const T* a, const T* b, size_t nElements, size_t nChannels, const uchar* m=NULL) -> decltype(cdist<3>(a,b,nElements,m)) {
        CV_Assert(nChannels>0 && nChannels<=4);
        switch(nChannels) {
            case 2: return cdist<2>(a,b,nElements,m);
            case 3: return cdist<3>(a,b,nElements,m);
            case 4: return cdist<4>(a,b,nElements,m);
            default: return 0;
        }
    }

    //! computes the color distortion between two opencv vectors
    template<int nChannels, typename T> static inline auto cdist(const cv::Vec<T,nChannels>& a, const cv::Vec<T,nChannels>& b) -> decltype(cdist<nChannels,T>((T*)(0),(T*)(0))) {
        T a_array[nChannels], b_array[nChannels];
        for(int c=0; c<nChannels; ++c) {
            a_array[c] = a[(int)c];
            b_array[c] = b[(int)c];
        }
        return cdist<nChannels>(a_array,b_array);
    }

    //! computes a color distortion-distance mix using two generic distances
    template<typename T> static inline T cmixdist(T oL1Distance, T oCDistortion) {
        return (oL1Distance/2+oCDistortion*4);
    }

    //! computes a color distortion-distance mix using two generic arrays
    template<size_t nChannels, typename T> static inline typename std::enable_if<std::is_integral<T>::value,size_t>::type cmixdist(const T* curr, const T* bg) {
        return cmixdist(L1dist<nChannels>(curr,bg),cdist<nChannels>(curr,bg));
    }

    //! computes a color distortion-distance mix using two generic arrays
    template<size_t nChannels, typename T> static inline typename std::enable_if<std::is_floating_point<T>::value,float>::type cmixdist(const T* curr, const T* bg) {
        return cmixdist(L1dist<nChannels>(curr,bg),cdist<nChannels>(curr,bg));
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////

    //! popcount LUT for 8-bit vectors
    static const uchar popcount_LUT8[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    };

    //! computes the population count of an N-byte vector using an 8-bit popcount LUT
    template<typename T> static inline size_t popcount(T x) {
        size_t nResult = 0;
        for(size_t l=0; l<sizeof(T); ++l)
            nResult += popcount_LUT8[(uchar)(x>>l*8)];
        return nResult;
    }

    //! computes the hamming distance between two N-byte vectors using an 8-bit popcount LUT
    template<typename T> static inline size_t hdist(T a, T b) {
        return popcount(a^b);
    }

    //! computes the gradient magnitude distance between two N-byte vectors using an 8-bit popcount LUT
    template<typename T> static inline size_t gdist(T a, T b) {
        return L1dist(popcount(a),popcount(b));
    }

    //! computes the population count of a (nChannels*N)-byte vector using an 8-bit popcount LUT
    template<size_t nChannels, typename T> static inline size_t popcount(const T* x) {
        static_assert(nChannels>0,"vector should have at least one channel");
        size_t nResult = 0;
        for(size_t c=0; c<nChannels; ++c)
            for(size_t l=0; l<sizeof(T); ++l)
                nResult += popcount_LUT8[(uchar)(*(x+c)>>l*8)];
        return nResult;
    }

    //! computes the hamming distance between two (nChannels*N)-byte vectors using an 8-bit popcount LUT
    template<size_t nChannels, typename T> static inline size_t hdist(const T* a, const T* b) {
        T xor_array[nChannels];
        for(size_t c=0; c<nChannels; ++c)
            xor_array[c] = a[c]^b[c];
        return popcount<nChannels>(xor_array);
    }

    //! computes the gradient magnitude distance between two (nChannels*N)-byte vectors using an 8-bit popcount LUT
    template<size_t nChannels, typename T> static inline size_t gdist(const T* a, const T* b) {
        return L1dist(popcount<nChannels>(a),popcount<nChannels>(b));
    }

#if HAVE_GLSL

    static inline std::string getShaderFunctionSource_absdiff(bool bUseBuiltinDistance) {
        // @@@@ test with/without built-in in final impl
        std::stringstream ssSrc;
        ssSrc << "uvec3 absdiff(in uvec3 a, in uvec3 b) {\n"
                 "    return uvec3(abs(ivec3(a)-ivec3(b)));\n"
                 "}\n"
                 "uint absdiff(in uint a, in uint b) {\n"
                 "    return uint(" << (bUseBuiltinDistance?"distance(a,b)":"abs((int)a-(int)b)") << ");\n"
                 "}\n";
        return ssSrc.str();
    }

    static inline std::string getShaderFunctionSource_L1dist() {
        std::stringstream ssSrc;
        ssSrc << "uint L1dist(in uvec3 a, in uvec3 b) {\n"
                 "    ivec3 absdiffs = abs(ivec3(a)-ivec3(b));\n"
                 "    return uint(absdiffs.b+absdiffs.g+absdiffs.r);\n"
                 "}\n";
        return ssSrc.str();
    }

    static inline std::string getShaderFunctionSource_L2dist(bool bUseBuiltinDistance) {
        std::stringstream ssSrc;
        ssSrc << "uint L2dist(in uvec3 a, in uvec3 b) {\n"
                 "    return uint(" << (bUseBuiltinDistance?"distance(a,b)":"sqrt(dot(ivec3(a)-ivec3(b)))") << ");\n"
                 "}\n";
        return ssSrc.str();
    }

    static inline std::string getShaderFunctionSource_hdist() {
        std::stringstream ssSrc;
        ssSrc << "uvec3 hdist(in uvec3 a, in uvec3 b) {\n"
                 "    return bitCount(a^b);\n"
                 "}\n"
                 "uint hdist(in uint a, in uint b) {\n"
                 "    return bitCount(a^b);\n"
                 "}\n";
        return ssSrc.str();
    }

#endif //HAVE_GLSL

}; //namespace DistanceUtils
