/**
 * \file dcs/math/optim/neos/input_format.hpp
 *
 * \brief Categories of input formats for the NEOS solver.
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

#ifndef DCS_MATH_OPTIM_NEOS_INPUT_FORMAT_HPP
#define DCS_MATH_OPTIM_NEOS_INPUT_FORMAT_HPP


namespace dcs { namespace math { namespace optim {

enum neos_input_format
{
	ampl_neos_input_format, ///< AMPL (http://www.ampl.com)
	c_neos_input_format, ///< C
	cplex_neos_input_format, ///< CPLEX (http://plato.asu.edu/cplex_lp.pdf)
	dimacs_neos_input_format, ///< DIMACS (http://www.mcs.anl.gov/otc/Guide/OptWeb/continuous/constrained/network/dimacs_mcf.html)
	fortran_neos_input_format, ///< Fortran
	gams_neos_input_format, ///< GAMS (http://www.gams.com)
	lp_neos_input_format, ///< LP (http://plato.asu.edu/ftp/lp_format.txt)
	matlab_neos_input_format, ///< MATLAB
	matlabbinary_neos_input_format, ///< MATLAB_BINARY (http://plato.asu.edu/ftp/usrguide.pdf)
	mps_neos_input_format, ///< MPS (http://en.wikipedia.org/wiki/MPS_(format))
	netflo_neos_input_format, ///< NETFLO (http://www.mcs.anl.gov/otc/Guide/SoftwareGuide/Blurbs/netflo.html)
	qps_neos_input_format, ///< QPS (http://plato.asu.edu/QPS.pdf)
	relax4_neos_input_format, ///< RELAX4 (http://www.mcs.anl.gov/otc/Guide/OptWeb/continuous/constrained/network/relax4-format.html)
	sdpa_neos_input_format, ///< SDPA (http://www.nmt.edu/~sdplib/FORMAT)
	sdplr_neos_input_format, ///< SDPLR (http://dollar.biz.uiowa.edu/~sburer/files/SDPLR/files/SDPLR-1.03-beta-usrguide.pdf)
	smps_neos_input_format, ///< SMPS (http://myweb.dal.ca/gassmann/smps2.htm)
	sparse_neos_input_format, ///< SPARSE
	sparsesdpa_neos_input_format, ///< SPARSE_SDPA (http://plato.asu.edu/ftp/sdpa_format.txt)
	tsp_neos_input_format, ///< TSP (http://plato.asu.edu/tsplib.pdf)
	zimpl_neos_input_format ///< ZIMPL (http://www.zib.de/koch/zimpl/download/zimpl.pdf)
};

}}} // Namespace dcs::math::optim


#endif // DCS_MATH_OPTIM_NEOS_INPUT_FORMAT_HPP
