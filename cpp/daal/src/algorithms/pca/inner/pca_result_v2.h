/* file: pca_result_v2.h */
/*******************************************************************************
* Copyright 2014-2021 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of PCA algorithm result.
//--
*/

#ifndef __PCA_RESULT_V2_H__
#define __PCA_RESULT_V2_H__

#include "src/algorithms/pca/inner/pca_result_v1.h"
#include "data_management/data/data_collection.h"
#include "data_management/data/numeric_table.h"

namespace daal
{
namespace algorithms
{
namespace pca
{
namespace interface2
{
class ResultImpl : public interface1::ResultImpl
{
public:
    DAAL_CAST_OPERATOR(ResultImpl);

    bool isWhitening;
    ResultImpl(const size_t n) : interface1::ResultImpl(n), isWhitening(false) {}
    ResultImpl(const ResultImpl & o) : interface1::ResultImpl(o), isWhitening(o.isWhitening) {}
    virtual ~ResultImpl() {};

    /**
    * Allocates memory for storing partial results of the PCA algorithm
    * \param[in] input Pointer to an object containing input data
    * \param[in] nComponents Number of components
    * \param[in] resultsToCompute Results to compute
    * \return Status of computations
    */
    template <typename algorithmFPType>
    services::Status allocate(const daal::algorithms::Input * input, size_t nComponents, DAAL_UINT64 resultsToCompute);

    /**
    * Allocates memory for storing partial results of the PCA algorithm
    * \param[in] partialResult Pointer to an object containing partialResult data
    * \param[in] nComponents Number of components
    * \param[in] resultsToCompute Results to compute
    * \return Status of computations
    */
    template <typename algorithmFPType>
    services::Status allocate(const daal::algorithms::PartialResult * partialResult, size_t nComponents, DAAL_UINT64 resultsToCompute);

    /**
    * Checks the results of the PCA algorithm implementation
    * \param[in] nFeatures      Number of features
    * \param[in] nComponents Number of components
    * \param[in] nTables        Number of tables
    *
    * \return Status
    */
    virtual services::Status check(size_t nFeatures, size_t nComponents, size_t nTables) const;

protected:
    /**
    * Allocates memory for storing partial results of the PCA algorithm
    * \param[in] nFeatures Number of features
    * \param[in] nComponents Number of components
    * \param[in] resultsToCompute Results to compute
    * \return Status of computations
    */
    template <typename algorithmFPType>
    services::Status allocate(size_t nFeatures, size_t nComponents, DAAL_UINT64 resultsToCompute);
};

} // namespace interface2
} // namespace pca
} // namespace algorithms
} // namespace daal

#endif
