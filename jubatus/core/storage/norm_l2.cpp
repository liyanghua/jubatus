// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#include "norm_l2.hpp"
#include <string>

namespace jubatus {
namespace core {
namespace storage {

norm_l2::norm_l2() {
}

norm_l2::~norm_l2() {
}

void norm_l2::clear() {
  jubatus::util::data::unordered_map<std::string, float>().swap(sq_norms_);
}

void norm_l2::notify(const std::string& row, float old_val, float new_val) {
  float& v = sq_norms_[row];
  v -= old_val * old_val;
  v += new_val * new_val;
}

float norm_l2::calc_norm(const std::string& row) const {
  jubatus::util::data::unordered_map<std::string, float>::const_iterator it =
    sq_norms_.find(row);
  if (it == sq_norms_.end()) {
    return 0.f;
  }
  return std::sqrt(it->second);
}

}  // namespace storage
}  // namespace core
}  // namespace jubatus
