
// This file is part of the LITIV framework; visit the original repository at
// https://github.com/plstcharles/litiv for more information.
//
// Copyright 2016 Pierre-Luc St-Charles; pierre-luc.st-charles<at>polymtl.ca
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

#pragma once

#define OPENGM_ENABLE_FAST_DEBUG_MAT_OPS 1

#include "litiv/utils/opengm.hpp"
#include "litiv/features2d.hpp"
#include "litiv/imgproc.hpp"

// config options
#define STEREOSEGMATCH_CONFIG_USE_DASCGF_AFFINITY   1
#define STEREOSEGMATCH_CONFIG_USE_DASCRF_AFFINITY   0
#define STEREOSEGMATCH_CONFIG_USE_LSS_AFFINITY      0
#define STEREOSEGMATCH_CONFIG_USE_MI_AFFINITY       0
#define STEREOSEGMATCH_CONFIG_USE_SSQDIFF_AFFINITY  0
#define STEREOSEGMATCH_CONFIG_USE_SHAPE_EMD_AFFIN   0
#define STEREOSEGMATCH_CONFIG_USE_UNARY_ONLY_FIRST  1
#define STEREOSEGMATCH_CONFIG_USE_SALIENT_MAP_BORDR 1
#define STEREOSEGMATCH_CONFIG_USE_ROOT_SIFT_DESCS   0
#define STEREOSEGMATCH_CONFIG_USE_GMM_LOCAL_BACKGR  1
#define STEREOSEGMATCH_CONFIG_USE_FGBZ_STEREO_INF   1
#define STEREOSEGMATCH_CONFIG_USE_FASTPD_STEREO_INF 0
#define STEREOSEGMATCH_CONFIG_USE_SOSPD_STEREO_INF  0
#define STEREOSEGMATCH_CONFIG_USE_FGBZ_RESEGM_INF   1
#define STEREOSEGMATCH_CONFIG_USE_SOSPD_RESEGM_INF  0
#define STEREOSEGMATCH_CONFIG_USE_PROGRESS_BARS     0
#define STEREOSEGMATCH_CONFIG_USE_EPIPOLAR_CONN     0

// default param values
#define STEREOSEGMATCH_DEFAULT_TEMPORAL_DEPTH       (size_t(0))
#define STEREOSEGMATCH_DEFAULT_DISPARITY_STEP       (size_t(1))
#define STEREOSEGMATCH_DEFAULT_MAX_MOVE_ITER        (size_t(300))
#define STEREOSEGMATCH_DEFAULT_SCDESC_WIN_RAD       (size_t(40))
#define STEREOSEGMATCH_DEFAULT_SCDESC_RAD_BINS      (size_t(3))
#define STEREOSEGMATCH_DEFAULT_SCDESC_ANG_BINS      (size_t(10))
#define STEREOSEGMATCH_DEFAULT_LSSDESC_RAD          (size_t(40))
#define STEREOSEGMATCH_DEFAULT_LSSDESC_PATCH        (size_t(7))
#define STEREOSEGMATCH_DEFAULT_LSSDESC_RAD_BINS     (size_t(3))
#define STEREOSEGMATCH_DEFAULT_LSSDESC_ANG_BINS     (size_t(10))
#define STEREOSEGMATCH_DEFAULT_SSQDIFF_PATCH        (size_t(7))
#define STEREOSEGMATCH_DEFAULT_MI_WINDOW_RAD        (size_t(12))
#define STEREOSEGMATCH_DEFAULT_GRAD_KERNEL_SIZE     (int(1))
#define STEREOSEGMATCH_DEFAULT_DISTTRANSF_SCALE     (-0.1f)
#define STEREOSEGMATCH_DEFAULT_ITER_PER_RESEGM      ((m_nStereoLabels*3)/2)
#define STEREOSEGMATCH_DEFAULT_RESEGM_PER_LOOP      (3)
#define STEREOSEGMATCH_DEFAULT_SALIENT_SHP_RAD      (3)
#define STEREOSEGMATCH_DEFAULT_DESC_PATCH_SIZE      (15)

// unary costs params
#define STEREOSEGMATCH_UNARY_COST_OOB_CST           (ValueType(5000))
#define STEREOSEGMATCH_UNARY_COST_OCCLUDED_CST      (ValueType(2000))
#define STEREOSEGMATCH_UNARY_COST_MAXTRUNC_CST      (ValueType(10000))
#define STEREOSEGMATCH_IMGSIM_COST_COLOR_SCALE      (40)
#define STEREOSEGMATCH_IMGSIM_COST_DESC_SCALE       (400)
#define STEREOSEGMATCH_SHPSIM_COST_DESC_SCALE       (400)
#define STEREOSEGMATCH_UNIQUE_COST_OVER_SCALE       (400)
#define STEREOSEGMATCH_SHPDIST_COST_SCALE           (400)
#define STEREOSEGMATCH_SHPDIST_PX_MAX_CST           (10.0f)
#define STEREOSEGMATCH_SHPDIST_INTERSPEC_SCALE      (0.50f)
#define STEREOSEGMATCH_SHPDIST_INITDIST_SCALE       (0.00f)
// pairwise costs params
#define STEREOSEGMATCH_LBLSIM_COST_MAXOCCL          (ValueType(5000))
#define STEREOSEGMATCH_LBLSIM_COST_MAXTRUNC_CST     (ValueType(5000))
#define STEREOSEGMATCH_LBLSIM_RESEGM_SCALE_CST      (400)
#define STEREOSEGMATCH_LBLSIM_STEREO_SCALE_CST      (1.f)
#define STEREOSEGMATCH_LBLSIM_STEREO_MAXDIFF_CST    (10)
#define STEREOSEGMATCH_LBLSIM_USE_EXP_GRADPIVOT     (1)
#if STEREOSEGMATCH_LBLSIM_USE_EXP_GRADPIVOT
#define STEREOSEGMATCH_LBLSIM_COST_GRADRAW_SCALE    (32)
#define STEREOSEGMATCH_LBLSIM_COST_GRADPIVOT_CST    (32)
#else //!STEREOSEGMATCH_LBLSIM_USE_EXP_GRADPIVOT
#define STEREOSEGMATCH_LBLSIM_COST_GRADRAW_SCALE    (10)
#define STEREOSEGMATCH_LBLSIM_COST_GRADPIVOT_CST    (32)
#endif //!STEREOSEGMATCH_LBLSIM_USE_EXP_GRADPIVOT
// higher order costs params
#define STEREOSEGMATCH_HOENERGY_STEREO_STRIDE       (size_t(1))
#define STEREOSEGMATCH_HOENERGY_RESEGM_STRIDE       (size_t(1))
// ...

// hardcoded term relations
#define STEREOSEGMATCH_UNIQUE_COST_INCR_REL(n)      (float((n)*3)/((n)+2))
#define STEREOSEGMATCH_UNIQUE_COST_ZERO_COUNT       (2)

/// this stereo matcher assumes both input images are rectified, and have the same size;
/// it also expects four inputs (image0,mask0,image1,mask1), and provides 4 outputs (disp0,mask0,disp1,mask1)
struct StereoSegmMatcher : ICosegmentor<int32_t,4> { // camera count could be templated... (n-view generalization)
    using InternalLabelType = uint8_t; ///< type used for internal labeling (disparity + fg/bg)
    using OutputLabelType = int32_t; ///< type used in returned labelings (i.e. output of 'apply')
    using AssocCountType = uint16_t; ///< type used for stereo association counting in cv::Mat_'s
    using AssocIdxType = int16_t; ///< type used for stereo association idx listing in cv::Mat_'s
    using ValueType =  int64_t; ///< type used for factor values (@@@@ could be integer? retest speed later?)
    using IndexType = size_t; ///< type used for node indexing (note: pretty much hardcoded everywhere in impl below)
    using ICosegmentor<OutputLabelType,s_nInputArraySize,s_nOutputArraySize>::apply; ///< helps avoid 'no matching function' issues for apply overloads
    template<typename T> using CamArray = std::array<T,getInputStreamCount()/2>; ///< shortcut typename for variables and members that are assigned to each camera head
    static constexpr OutputLabelType s_nDontCareLabel = std::numeric_limits<OutputLabelType>::min(); ///< real label value reserved for 'dont care' pixels
    static constexpr OutputLabelType s_nOccludedLabel = std::numeric_limits<OutputLabelType>::max(); ///< real label value reserved for 'occluded' pixels
    static constexpr OutputLabelType s_nForegroundLabel = OutputLabelType(std::numeric_limits<InternalLabelType>::max()); ///< real label value reserved for foreground pixels
    static constexpr OutputLabelType s_nBackgroundLabel = OutputLabelType(0); ///< real label value reserved for background pixels
    static constexpr InternalLabelType s_nForegroundLabelIdx = InternalLabelType(1); ///< internal label value used for 'foreground' labeling
    static constexpr InternalLabelType s_nBackgroundLabelIdx = InternalLabelType(0); ///< internal label value used for 'background' labeling
    static constexpr OutputLabelType getStereoDontCareLabel() {return s_nDontCareLabel;} ///< returns the output stereo label used to represent 'dont care' pixels
    static constexpr OutputLabelType getStereoOccludedLabel() {return s_nOccludedLabel;} ///< returns the output stereo label used to represent 'occluded' pixels
    static constexpr size_t getCameraCount() {return getInputStreamCount()/2;} ///< returns the expected input camera head count
    static constexpr size_t s_nCameraCount = getInputStreamCount()/2; ///< holds the expected input camera head count
    static_assert(std::is_integral<IndexType>::value,"Graph index type must be integral");
    static_assert(std::is_integral<InternalLabelType>::value,"Graph internal label type must be integral");
    static_assert(size_t(std::numeric_limits<IndexType>::max())>=size_t(std::numeric_limits<InternalLabelType>::max()),"Graph index type max value must be greater than internal label type max value");

    /// defines the indices of provided matrices inside the input array
    enum InputPackingList {
        InputPackSize=4,
        InputPackOffset=2,
        // absolute values for direct indexing
        InputPack_LeftImg=0,
        InputPack_LeftMask=1,
        InputPack_RightImg=2,
        InputPack_RightMask=3,
        // relative values for cam-based indexing
        InputPackOffset_Img=0,
        InputPackOffset_Mask=1,
    };

    /// defines the indices of provided matrices inside the input array
    enum OutputPackingList {
        OutputPackSize=4,
        OutputPackOffset=2,
        // absolute values for direct indexing
        OutputPack_LeftDisp=0,
        OutputPack_LeftMask=1,
        OutputPack_RightDisp=2,
        OutputPack_RightMask=3,
        // relative values for cam-based indexing
        OutputPackOffset_Disp=0,
        OutputPackOffset_Mask=1,
    };

    // interface forward declarations for pimpl helpers
    struct GraphModelData;
    struct StereoGraphInference;
    struct ResegmGraphInference;

    /// full stereo graph matcher constructor; only takes parameters to ready graphical model base initialization
    StereoSegmMatcher(size_t nMinDispOffset, size_t nMaxDispOffset);
    /// default (empty) destructor (required explicitly here due to pimpl idiom and unique_ptr usage)
    ~StereoSegmMatcher();
    /// stereo graph matcher initialization function; will allocate & initialize graph model using provided ROI data (one ROI per camera head)
    virtual void initialize(const std::array<cv::Mat,s_nCameraCount>& aROIs, size_t nPrimaryCamIdx=0);
    /// stereo matcher function; solves the graph model to find pixel-level matches on epipolar lines in the masked input images, and returns disparity maps + masks
    virtual void apply(const MatArrayIn& aInputs, MatArrayOut& aOutputs) override;
    /// (pre)calculates initial features required for model updates, and optionally returns them in packet format for archiving
    virtual void calcFeatures(const MatArrayIn& aInputs, cv::Mat* pFeatsPacket=nullptr);
    /// sets a previously precalculated initial features packet to be used in the next 'apply' call (do not modify its data before that!)
    virtual void setNextFeatures(const cv::Mat& oPackedFeats);
    /// returns the (friendly) name of the input image feature extractor that will be used internally
    virtual std::string getFeatureExtractorName() const;
    /// returns the (maximum) number of stereo disparity labels used in the output masks
    virtual size_t getMaxLabelCount() const override;
    /// returns the list of (real) stereo disparity labels used in the output masks
    virtual const std::vector<OutputLabelType>& getLabels() const override;
    /// helper func to display segmentation maps
    cv::Mat getResegmMapDisplay(size_t nCamIdx) const;
    /// helper func to display scaled disparity maps
    cv::Mat getStereoDispMapDisplay(size_t nCamIdx) const;
    /// helper func to display scaled assoc count maps (for primary cam only)
    cv::Mat getAssocCountsMapDisplay() const;

protected:
    /// disparity label step size (will be passed to model constr)
    size_t m_nDispStep;
    /// output disparity label set (will be passed to model constr)
    std::vector<OutputLabelType> m_vStereoLabels;
    /// holds bimodel data & inference algo impls
    std::unique_ptr<GraphModelData> m_pModelData;
    /*/// converts a floating point value to the model's value type, rounding if necessary
    template<typename TVal>
    static inline std::enable_if_t<std::is_floating_point<TVal>::value,ValueType> cost_cast(TVal val) {return (ValueType)std::round(val);}
    /// converts an integral value to the model's value type
    template<typename TVal>
    static inline std::enable_if_t<std::is_integral<TVal>::value,ValueType> cost_cast(TVal val) {return (ValueType)val;}*/
    template<typename TVal>
    static inline ValueType cost_cast(TVal val) {return (ValueType)val;}
};