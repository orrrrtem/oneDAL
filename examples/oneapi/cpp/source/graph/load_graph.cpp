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

#include <iostream>
#include <string>

#include "example_util/utils.hpp"
#include "oneapi/dal/graph/graph_service_functions.hpp"
#include "oneapi/dal/graph/undirected_adjacency_array_graph.hpp"
#include "oneapi/dal/graph/undirected_adjacency_array_graph1.hpp"
#include "oneapi/dal/io/graph_csv_data_source.hpp"
#include "oneapi/dal/io/load_graph.hpp"

using namespace oneapi::dal;
using namespace oneapi::dal::preview;
using namespace std;

struct user_value {
    user_value(){}
    string color = "sd";
    int id = -1;
    double salary = 0;
    size_t age = 0;
};

int main(int argc, char **argv) {
    const string filename = get_data_path("graph.csv");

    const preview::graph_csv_data_source ds(filename);
    const preview::load_graph::descriptor<> d;
    const auto my_graph = preview::load_graph::load(d, ds);

    cout << "Graph is read from file: " << filename << endl;
    cout << "Number of vertices: " << preview::get_vertex_count(my_graph) << endl;
    cout << "Number of edges: " << preview::get_edge_count(my_graph) << endl;
    
    

    using graph_int32_float = undirected_adjacency_array_graph1<float,
                                                                empty_value,
                                                                empty_value,
                                                                int32_t,
                                                                allocator<char>>;

    using graph_int64_float = undirected_adjacency_array_graph1<float,
                                                                empty_value,
                                                                empty_value,
                                                                int64_t,
                                                                allocator<char>>;                                           

    using graph_int32_user = undirected_adjacency_array_graph1<user_value,
                                                               empty_value,
                                                               empty_value,
                                                               int32_t,
                                                               allocator<char>>;

    using graph_int64_user = undirected_adjacency_array_graph1<user_value,
                                                               empty_value,
                                                               empty_value,
                                                               int64_t,
                                                               allocator<char>>;                                                             

    float* lib_vertex_values = new float(preview::get_vertex_count(my_graph));

    user_value*  app_vertex_values = new user_value[preview::get_vertex_count(my_graph)];

    cout << endl << "graph1 with int32 index and float vertex values" << endl;
    graph_int32_float graph11(get_vertex_count(my_graph), lib_vertex_values);


    cout << endl << "graph1 with int64 index and float vertex values" << endl;
    graph_int64_float graph12(get_vertex_count(my_graph), lib_vertex_values);


    cout << endl << "graph1 with int32 index and user vertex values" << endl;
    graph_int32_user graph13(get_vertex_count(my_graph), app_vertex_values);


    cout << endl << "graph1 with int64 index and user vertex values" << endl;
    graph_int64_user graph14(get_vertex_count(my_graph), app_vertex_values);
    return 0;
}
