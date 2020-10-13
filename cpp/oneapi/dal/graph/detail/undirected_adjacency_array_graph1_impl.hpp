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

#pragma once

#include <iostream>

#include "oneapi/dal/common.hpp"
#include "oneapi/dal/detail/common.hpp"
#include "oneapi/dal/graph/detail/graph_container.hpp"

namespace oneapi::dal::preview::detail {

template <typename IndexType = std::int32_t>
class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph1_topology {
public:
    using vertex_type = IndexType;
    using edge_type = IndexType;

    undirected_adjacency_array_graph1_topology() = default;
    virtual ~undirected_adjacency_array_graph1_topology() = default;

    vertex_type* _vertex_neighbors;
    vertex_type* _degrees;
    edge_type* _edge_offsets;
};

template <typename VertexValue = float>
class ONEAPI_DAL_EXPORT undirected_adjacency_array_graph1_attribute1 {
public:
    using vertex_user_value_type = VertexValue;

    undirected_adjacency_array_graph1_attribute1() = default;
    virtual ~undirected_adjacency_array_graph1_attribute1() = default;

    vertex_user_value_type* _vertex_value;
};

template <typename VertexValue = empty_value,
          typename EdgeValue = empty_value,
          typename GraphValue = empty_value,
          typename IndexType = std::int32_t,
          typename Allocator = std::allocator<char>>
class undirected_adjacency_array_graph1_impl {
public:
    using allocator_type = Allocator;

    using vertex_type = IndexType;
    using vertex_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<vertex_type>;
    using vertex_set = detail::graph_container<vertex_type, vertex_allocator_type>;
    using vertex_size_type = typename vertex_set::size_type;

    using edge_type = IndexType;
    using edge_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<edge_type>;
    using edge_set = detail::graph_container<edge_type, edge_allocator_type>;
    using edge_size_type = typename edge_set::size_type;

    using vertex_user_value_type = VertexValue;
    using vertex_user_value_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<vertex_user_value_type>;
    using vertex_user_value_set =
        detail::graph_container<vertex_user_value_type, vertex_user_value_allocator_type>;

    using edge_user_value_type = EdgeValue;
    using edge_user_value_allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<edge_user_value_type>;
    using edge_user_value_set =
        detail::graph_container<edge_user_value_type, edge_user_value_allocator_type>;

    undirected_adjacency_array_graph1_impl()
            : topology_impl(new undirected_adjacency_array_graph1_topology<vertex_type>),
              attribute1_impl(
                  new undirected_adjacency_array_graph1_attribute1<vertex_user_value_type>) {}
    virtual ~undirected_adjacency_array_graph1_impl() = default;

    vertex_size_type _vertex_count;
    edge_size_type _edge_count;

    using topology_pimpl =
        oneapi::dal::detail::pimpl<undirected_adjacency_array_graph1_topology<vertex_type>>;

    topology_pimpl topology_impl;

    using attribute1_pimpl = oneapi::dal::detail::pimpl<
        undirected_adjacency_array_graph1_attribute1<vertex_user_value_type>>;
    attribute1_pimpl attribute1_impl;

    //vertex_set _vertex_neighbors;
    //vertex_set _degrees;
    //edge_set _edge_offsets;

    //vertex_user_value_set _vertex_value;
    edge_user_value_set _edge_value;

    allocator_type _allocator;
};

template <typename Topology_layout>
void fill_degrees(oneapi::dal::detail::pimpl<Topology_layout>& layout) {
    layout->_degrees[0] = 1;
    layout->_degrees[1] = 1;
    layout->_degrees[2] = 1;
    std::cout << "fill degrees compiled by app" << std::endl;
}

template <typename Attribute_layout>
void fill_vertex_values(oneapi::dal::detail::pimpl<Attribute_layout>& layout,
                        const typename Attribute_layout::vertex_user_value_type* vertex_values) {
    layout->_vertex_value[0] = vertex_values[0];
    std::cout << "fill_vertex_values compiled by app" << std::endl;
}

template <>
void fill_vertex_values(
    oneapi::dal::detail::pimpl<undirected_adjacency_array_graph1_attribute1<float>>& layout,
    const typename undirected_adjacency_array_graph1_attribute1<float>::vertex_user_value_type*
        vertex_values);

template <>
void fill_degrees<undirected_adjacency_array_graph1_topology<std::int32_t>>(
    oneapi::dal::detail::pimpl<undirected_adjacency_array_graph1_topology<std::int32_t>>& layout);

template <typename Graph_layout>
void some_construct(oneapi::dal::detail::pimpl<Graph_layout>& layout,
                    size_t vertex_count,
                    const typename Graph_layout::vertex_user_value_type* vertex_values) {
    layout->_vertex_count = vertex_count;
    auto& allocator = layout->_allocator;

    auto& topology_layout = layout->topology_impl;
    topology_layout->_degrees = (typename Graph_layout::vertex_type*)allocator.allocate(
        (vertex_count + 1) * (sizeof(typename Graph_layout::vertex_type) / sizeof(char)));

    fill_degrees(topology_layout);

    auto& attribute1_layout = layout->attribute1_impl;
    attribute1_layout->_vertex_value =
        (typename Graph_layout::vertex_user_value_type*)allocator.allocate(
            (vertex_count + 1) *
            (sizeof(typename Graph_layout::vertex_user_value_type) / sizeof(char)));

    fill_vertex_values(attribute1_layout, vertex_values);
}

} // namespace oneapi::dal::preview::detail
