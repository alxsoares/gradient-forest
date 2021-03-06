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

#ifndef GRADIENTFOREST_SPLITTINGRULE_H
#define GRADIENTFOREST_SPLITTINGRULE_H

#include <unordered_map>
#include <vector>

class SplittingRule {
public:
  virtual ~SplittingRule() {}
  virtual bool find_best_split(size_t nodeID,
                               const std::vector<size_t>& possible_split_varIDs,
                               const std::unordered_map<size_t, double>& responses_by_sampleID,
                               const std::vector<std::vector<size_t>>& sampleIDs,
                               std::vector<size_t>& split_varIDs,
                               std::vector<double>& split_values) = 0;
};

#endif //GRADIENTFOREST_SPLITTINGRULE_H


