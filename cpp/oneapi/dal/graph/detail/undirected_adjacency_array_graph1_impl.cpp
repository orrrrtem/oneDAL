/*******************************************************************************
* Copyright 2020 Intel Corporation
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

#include "oneapi/dal/graph/detail/undirected_adjacency_array_graph1_impl.hpp"

namespace oneapi::dal::preview::detail {

template class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph1_topology<std::int32_t>;

template class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph1_attribute1<float>;

template <>
void fill_degrees(
    oneapi::dal::detail::pimpl<undirected_adjacency_array_graph1_topology<std::int32_t>>& layout) {
    layout->_degrees[0] = 5;
    layout->_degrees[1] = 5;
    layout->_degrees[2] = 5;
    std::cout << "fill degrees compiled in lib" << std::endl;
}

template <>
void fill_vertex_values(
    oneapi::dal::detail::pimpl<undirected_adjacency_array_graph1_attribute1<float>>& layout,
    const typename undirected_adjacency_array_graph1_attribute1<float>::vertex_user_value_type*
        vertex_values) {
    layout->_vertex_value[0] = vertex_values[0];
    std::cout << "fill_vertex_values compiled in lib" << std::endl;
}

} // namespace oneapi::dal::preview::detail
