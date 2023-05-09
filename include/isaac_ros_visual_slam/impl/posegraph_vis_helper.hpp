// SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
// Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef ISAAC_ROS_VISUAL_SLAM__IMPL__POSEGRAPH_VIS_HELPER_HPP_
#define ISAAC_ROS_VISUAL_SLAM__IMPL__POSEGRAPH_VIS_HELPER_HPP_

#include <memory>
#include <string>

#include "geometry_msgs/msg/pose_array.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "viz_helper.hpp"

namespace isaac_ros
{
namespace visual_slam
{

// visualize Pose Graph
struct PoseGraphVisHelper : public VisHelper
{
public:
  PoseGraphVisHelper(
    ELBRUS_DataLayer layer,
    uint32_t max_items_count = 1024,
    uint32_t period_ms = 500
  );
  ~PoseGraphVisHelper() override;

  void Init(
    const rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr publisher_nodes,
    const rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_edges,
    const rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_edges2,
    ELBRUS_TrackerHandle elbrus_handle,
    const tf2::Transform & base_link_pose_elbrus,
    const rclcpp::Node & node,
    const std::string & frame_id);

  void Reset() override;

  void Run();

protected:
  ELBRUS_DataLayer layer_ = LL_POSE_GRAPH;
  uint32_t max_items_count_ = 1024;
  uint32_t period_ms_ = 500;

  uint64_t last_timestamp_ns_ = 0;

  using nodes_msg_t = std::unique_ptr<geometry_msgs::msg::PoseArray>;

  rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr publisher_nodes_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_edges_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher_edges2_;
};

}  // namespace visual_slam
}  // namespace isaac_ros

#endif  // ISAAC_ROS_VISUAL_SLAM__IMPL__POSEGRAPH_VIS_HELPER_HPP_
