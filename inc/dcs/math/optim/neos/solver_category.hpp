/**
 * \file dcs/math/optim/solver_category.hpp
 *
 * \brief Categories of NEOS solvers.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2014 Marco Guazzone (marco.guazzone@gmail.com)
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
 */

#ifndef DCS_MATH_OPTIM_NEOS_SOLVER_CATEGORY_HPP
#define DCS_MATH_OPTIM_NEOS_SOLVER_CATEGORY_HPP

namespace dcs { namespace math { namespace optim {

enum neos_solver_category
{
	bco_neos_solver_category, ///< Bound Constrained Optimization
	co_neos_solver_category, ///< Combinatorial Optimization and Integer Programming
	cp_neos_solver_category, ///< Complementarity Problems
	go_neos_solver_category, ///< Global Optimization
	kestrel_neos_solver_category, ///< Kestrel
	lno_neos_solver_category, ///< Linear Network Programming
	lp_neos_solver_category, ///< Linear Programming
	milp_neos_solver_category, ///< Mixed Integer Linear Programming
	minco_neos_solver_category, ///< Mixed Integer Nonlinearly Constrained Optimization
	multi_neos_solver_category, ///< Multi-Solvers
	nco_neos_solver_category, ///< Nonlinearly Constrained Optimization
	ndo_neos_solver_category, ///< Nondifferentiable Optimization
	sdp_neos_solver_category, ///< Semidefinite Programming
	sio_neos_solver_category, ///< Semi-infinite Optimization
	slp_neos_solver_category, ///< Stochastic Linear Programming
	socp_neos_solver_category, ///< Second Order Conic Programming
	uco_neos_solver_category ///< Unconstrained Optimization
};

}}} // Namespace dcs::math::optim

#endif // DCS_MATH_OPTIM_NEOS_SOLVER_CATEGORY_HPP
