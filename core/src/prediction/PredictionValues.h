/*-------------------------------------------------------------------------------
  This file is part of gradient-forest.

  gradient-forest is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  gradient-forest is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with gradient-forest. If not, see <http://www.gnu.org/licenses/>.
 #-------------------------------------------------------------------------------*/

#ifndef GRADIENTFOREST_PREDICTIONVALUES_H
#define GRADIENTFOREST_PREDICTIONVALUES_H


#include <vector>
#include <string>
#include <map>

class PredictionValues {
public:
  PredictionValues();

  PredictionValues(const std::vector<std::vector<double>>& values,
                   size_t num_nodes,
                   size_t num_types);

  double empty(size_t node) const;

  double get(size_t node, size_t type) const;

  const size_t get_num_nodes() const {
    return num_nodes;
  }

  const size_t get_num_types() const {
    return num_types;
  }

  const std::vector<std::vector<double>>& get_values() const {
    return values;
  }

private:
  std::vector<std::vector<double>> values;
  size_t num_nodes;
  size_t num_types;
};


#endif //GRADIENTFOREST_PREDICTIONVALUES_H
