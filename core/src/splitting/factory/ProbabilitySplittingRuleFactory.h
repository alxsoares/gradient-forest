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

#ifndef GRADIENTFOREST_PROBABILITYSPLITTINGRULEFACTORY_H
#define GRADIENTFOREST_PROBABILITYSPLITTINGRULEFACTORY_H

#include <vector>

#include "commons/globals.h"
#include "commons/Data.h"
#include "splitting/factory/SplittingRuleFactory.h"

class ProbabilitySplittingRuleFactory: public SplittingRuleFactory {
public:
  ProbabilitySplittingRuleFactory(Data* data, size_t num_classes);
  std::shared_ptr<SplittingRule> create();

private:
  Data* data;
  size_t num_classes;

  DISALLOW_COPY_AND_ASSIGN(ProbabilitySplittingRuleFactory);
};

#endif //GRADIENTFOREST_PROBABILITYSPLITTINGRULEFACTORY_H
