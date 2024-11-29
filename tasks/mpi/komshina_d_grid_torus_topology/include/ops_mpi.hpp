#pragma once
#include <gtest/gtest.h>

#include <array>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <cmath>
#include <functional>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace komshina_d_grid_torus_topology_mpi {

class GridTorusTopologyParallel : public ppc::core::Task {
 public:
  explicit GridTorusTopologyParallel(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  boost::mpi::communicator world;
  std::vector<int> input_;
  std::vector<int> result;
  std::vector<int> order;
  int rank;
  std::vector<int> neighbors;  
  void compute_neighbors();
};

}  // namespace komshina_d_grid_torus_topology_mpi