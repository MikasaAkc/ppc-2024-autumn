
#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <cmath>
#include <vector>

#include "mpi/komshina_d_grid_torus_topology/include/ops_mpi.hpp"

TEST(komshina_d_grid_torus_topology_mpi, TestDataTransmission) {
  boost::mpi::communicator world;
  if (world.size() < 4) return;

  std::vector<uint8_t> input_data(4);
  std::iota(input_data.begin(), input_data.end(), 9);
  std::vector<uint8_t> output_data(4);

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(input_data.data());
  task_data->inputs_count.emplace_back(input_data.size());
  task_data->outputs.emplace_back(output_data.data());
  task_data->outputs_count.emplace_back(output_data.size());

  komshina_d_grid_torus_topology_mpi::GridTorusTopologyParallel task(task_data);
  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
}

TEST(komshina_d_grid_torus_topology_mpi, TestSingleElementInput) {
  boost::mpi::communicator world;
  if (world.size() < 2) return;

  std::vector<uint8_t> input_data(1);
  input_data[0] = 9;
  std::vector<uint8_t> output_data(1);

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(input_data.data());
  task_data->inputs_count.emplace_back(input_data.size());
  task_data->outputs.emplace_back(output_data.data());
  task_data->outputs_count.emplace_back(output_data.size());

  komshina_d_grid_torus_topology_mpi::GridTorusTopologyParallel task(task_data);

  ASSERT_TRUE(task.validation());

  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.post_processing());

  EXPECT_EQ(output_data[0], input_data[0]);
}

TEST(komshina_d_grid_torus_topology_mpi, TestSmallNumberOfProcesses) {
  boost::mpi::communicator world;
  if (world.size() < 2) return;

  std::vector<uint8_t> input_data(4);
  std::iota(input_data.begin(), input_data.end(), 9);
  std::vector<uint8_t> output_data(4);

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(input_data.data());
  task_data->inputs_count.emplace_back(input_data.size());
  task_data->outputs.emplace_back(output_data.data());
  task_data->outputs_count.emplace_back(output_data.size());

  komshina_d_grid_torus_topology_mpi::GridTorusTopologyParallel task(task_data);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());

  ASSERT_TRUE(task.run());

  for (size_t i = 0; i < output_data.size(); ++i) {
    EXPECT_EQ(output_data[i], input_data[i]);
  }
}

TEST(komshina_d_grid_torus_topology_mpi, TestLargeNumberOfProcesses) {
  boost::mpi::communicator world;
  if (world.size() < 16) return;

  std::vector<uint8_t> input_data(16);
  std::iota(input_data.begin(), input_data.end(), 9);
  std::vector<uint8_t> output_data(16);

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(input_data.data());
  task_data->inputs_count.emplace_back(input_data.size());
  task_data->outputs.emplace_back(output_data.data());
  task_data->outputs_count.emplace_back(output_data.size());

  komshina_d_grid_torus_topology_mpi::GridTorusTopologyParallel task(task_data);

  ASSERT_TRUE(task.validation());
  ASSERT_TRUE(task.pre_processing());
  ASSERT_TRUE(task.run());

  for (size_t i = 0; i < output_data.size(); ++i) {
    EXPECT_EQ(output_data[i], input_data[i]);
  }
}

TEST(komshina_d_grid_torus_topology_mpi, TestInsufficientProcesses) {
  boost::mpi::communicator world;
  if (world.size() < 2) return;

  std::vector<uint8_t> input_data(4);
  std::iota(input_data.begin(), input_data.end(), 9);
  std::vector<uint8_t> output_data(4);

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(input_data.data());
  task_data->inputs_count.emplace_back(input_data.size());
  task_data->outputs.emplace_back(output_data.data());
  task_data->outputs_count.emplace_back(output_data.size());

  komshina_d_grid_torus_topology_mpi::GridTorusTopologyParallel task(task_data);

  ASSERT_FALSE(task.validation());
}

TEST(komshina_d_grid_torus_topology_mpi, TestInsufficientProcesses) {
  boost::mpi::communicator world;
  if (world.size() < 2) return;

  std::vector<uint8_t> input_data(4);
  std::iota(input_data.begin(), input_data.end(), 9);
  std::vector<uint8_t> output_data(4);

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs.emplace_back(input_data.data());
  task_data->inputs_count.emplace_back(input_data.size());
  task_data->outputs.emplace_back(output_data.data());
  task_data->outputs_count.emplace_back(output_data.size());

  komshina_d_grid_torus_topology_mpi::GridTorusTopologyParallel task(task_data);

  ASSERT_FALSE(task.validation());
}
