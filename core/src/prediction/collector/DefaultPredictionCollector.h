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

#ifndef GRADIENTFOREST_FULLPREDICTOR_H
#define GRADIENTFOREST_FULLPREDICTOR_H


#include "forest/Forest.h"
#include "prediction/collector/PredictionCollector.h"

class DefaultPredictionCollector: public PredictionCollector {
public:
  DefaultPredictionCollector(std::shared_ptr<PredictionStrategy> prediction_strategy,
                             uint ci_group_size);

  std::vector<Prediction> collect_predictions(const Forest &forest,
                                              Data *prediction_data,
                                              std::vector<std::vector<size_t>> leaf_nodes_by_tree,
                                              bool oob_prediction);
private:
  void add_sample_weights(const std::vector<size_t>& sampleIDs,
                          std::unordered_map<size_t, double>& weights_by_sampleID);

  void normalize_sample_weights(std::unordered_map<size_t, double>& weights_by_sampleID);

  std::shared_ptr<PredictionStrategy> prediction_strategy;
  uint ci_group_size;
};


#endif //GRADIENTFOREST_FULLPREDICTOR_H
