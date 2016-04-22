
// This file is part of the LITIV framework; visit the original repository at
// https://github.com/plstcharles/litiv for more information.
//
// Copyright 2015 Pierre-Luc St-Charles; pierre-luc.st-charles<at>polymtl.ca
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "litiv/imgproc/EdgeDetectorCanny.hpp"

EdgeDetectorCanny::EdgeDetectorCanny(double dHystLowThrshFactor, double dGaussianKernelSigma) :
        m_dHystLowThrshFactor(dHystLowThrshFactor),
        m_dGaussianKernelSigma(dGaussianKernelSigma) {
    CV_Assert(m_dHystLowThrshFactor>0 && m_dHystLowThrshFactor<1);
    CV_Assert(m_dGaussianKernelSigma>=0);
}

void EdgeDetectorCanny::apply_threshold(cv::InputArray _oInputImage, cv::OutputArray _oEdgeMask, double dThreshold) {
    cv::Mat oInputImg = _oInputImage.getMat();
    CV_Assert(!oInputImg.empty());
    CV_Assert(oInputImg.channels()==1 || oInputImg.channels()==3 || oInputImg.channels()==4);
    if(m_dGaussianKernelSigma>0) {
        // follows the approach used in Matlab's edge.m implementation of Canny's method
        const int nDefaultKernelSize = int(8*ceil(m_dGaussianKernelSigma));
        const int nRealHalfKernelSize = (nDefaultKernelSize-1)/2;
        oInputImg = oInputImg.clone();
        cv::GaussianBlur(oInputImg,oInputImg,cv::Size(nRealHalfKernelSize,nRealHalfKernelSize),m_dGaussianKernelSigma,m_dGaussianKernelSigma);
    }
    _oEdgeMask.create(oInputImg.size(),CV_8UC1);
    cv::Mat oEdgeMask = _oEdgeMask.getMat();
    if(dThreshold<0||dThreshold>1)
        dThreshold = getDefaultThreshold();
    const size_t nCurrBaseHystThreshold = (size_t)(dThreshold*EDGCANNY_MAX_THRESHOLD);
    static const int nWindowSize = EDGCANNY_SOBEL_KERNEL_SIZE;
    static const bool bUseL2Gradient = EDGCANNY_USE_L2_GRADIENT_NORM;
    cv::Canny(oInputImg,oEdgeMask,nCurrBaseHystThreshold*m_dHystLowThrshFactor,(double)nCurrBaseHystThreshold,nWindowSize,bUseL2Gradient);
}

void EdgeDetectorCanny::apply(cv::InputArray _oInputImage, cv::OutputArray _oEdgeMask) {
    cv::Mat oInputImg = _oInputImage.getMat();
    CV_Assert(!oInputImg.empty());
    CV_Assert(oInputImg.channels()==1 || oInputImg.channels()==3 || oInputImg.channels()==4);
    _oEdgeMask.create(oInputImg.size(),CV_8UC1);
    cv::Mat oEdgeMask = _oEdgeMask.getMat();
    oEdgeMask = cv::Scalar_<uchar>(0);
    cv::Mat oTempEdgeMask = oEdgeMask.clone();
    for(size_t nCurrThreshold=0; nCurrThreshold<UCHAR_MAX; ++nCurrThreshold) {
        apply_threshold(oInputImg,oTempEdgeMask,double(nCurrThreshold)/UCHAR_MAX);
        oEdgeMask += oTempEdgeMask/UCHAR_MAX;
    }
    cv::normalize(oEdgeMask,oEdgeMask,0,UCHAR_MAX,cv::NORM_MINMAX);
}
