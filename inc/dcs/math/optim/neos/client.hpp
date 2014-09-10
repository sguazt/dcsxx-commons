/**
 * \file dcs/math/optim/neos/client.hpp
 *
 * \brief Client for interacting with the NEOS server.
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

#ifndef DCS_MATH_OPTIM_NEOS_CLIENT_HPP
#define DCS_MATH_OPTIM_NEOS_CLIENT_HPP


#include <boost/algorithm/string/case_conv.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <dcs/math/optim/neos/solver_category.hpp>
#include <dcs/math/optim/neos/solver_id.hpp>
#include <dcs/math/optim/neos/input_format.hpp>
#include <dcs/text/base64.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
//#include <unistd.h>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>


namespace dcs { namespace math { namespace optim {

enum neos_job_status
{
	done_neos_job_status,
	running_neos_job_status,
	waiting_neos_job_status,
	unknown_job_neos_job_status,
	bad_password_neos_job_status
};


struct neos_solver_category_info
{
	neos_solver_category category;
	::std::string short_name;
	::std::string full_name;
}; // neos_solver_category_info


struct neos_solver_info
{
	neos_solver_category category;
	neos_solver_id solver;
	neos_input_format input_format;
}; // neos_solver_info


struct neos_job_credentials
{
	int id;
	::std::string password;
}; // neos_job_credentials


struct submitted_neos_job_info
{
	neos_solver_info solver;
	neos_job_status status;
}; // submitted_neos_job_info


namespace /*<unnamed>*/ { namespace neos_detail {

inline
::std::string make_url(::std::string const& host, int port)
{
	::std::ostringstream oss;
	oss << "http://" << host << ":" << port;
	return oss.str();
}

inline
::std::string to_string(xmlrpc_c::value::type_t type)
{
	switch (type)
	{
		case xmlrpc_c::value::TYPE_INT:
			return "int";
		case xmlrpc_c::value::TYPE_BOOLEAN:
			return "bool";
		case xmlrpc_c::value::TYPE_DOUBLE:
			return "double";
		case xmlrpc_c::value::TYPE_DATETIME:
			return "datetime";
		case xmlrpc_c::value::TYPE_STRING:
			return "string";
		case xmlrpc_c::value::TYPE_BYTESTRING:
			return "bytestring";
		case xmlrpc_c::value::TYPE_ARRAY:
			return "array";
		case xmlrpc_c::value::TYPE_STRUCT:
			return "struct";
		case xmlrpc_c::value::TYPE_C_PTR:
			return "c_ptr";
		case xmlrpc_c::value::TYPE_NIL:
			return "nil";
		case xmlrpc_c::value::TYPE_I8:
			return "i8";
		case xmlrpc_c::value::TYPE_DEAD:
			return "dead";
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown XML-RPC type");
}

inline
neos_job_status make_job_status(::std::string const& s)
{
	const ::std::string ss = ::boost::algorithm::to_lower_copy(s);

	if (!ss.compare("done"))
	{
		return done_neos_job_status;
	}
	if (!ss.compare("running"))
	{
		return running_neos_job_status;
	}
	if (!ss.compare("waiting"))
	{
		return waiting_neos_job_status;
	}
	if (!ss.compare("unknown job"))
	{
		return unknown_job_neos_job_status;
	}
	if (!ss.compare("bad password"))
	{
		return bad_password_neos_job_status;
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS job status");
}

inline
::std::string to_string(neos_job_status status)
{
	switch (status)
	{
		case done_neos_job_status:
			return "Done";
		case running_neos_job_status:
			return "Running";
		case waiting_neos_job_status:
			return "Waiting";
		case unknown_job_neos_job_status:
			return "Unknown Job";
		case bad_password_neos_job_status:
			return "Bad Password";
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS job status");
}

inline
neos_solver_id make_solver_id(::std::string const& s)
{
	const ::std::string ss = ::boost::algorithm::to_lower_copy(s);

	if (!ss.compare("alphaecp"))
	{
		return alphaecp_neos_solver_id;
	}
	if (!ss.compare("asa"))
	{
		return asa_neos_solver_id;
	}
	if (!ss.compare("baron"))
	{
		return baron_neos_solver_id;
	}
	if (!ss.compare("bdmlp"))
	{
		return bdmlp_neos_solver_id;
	}
	if (!ss.compare("biqmac"))
	{
		return biqmac_neos_solver_id;
	}
	if (!ss.compare("blmvm"))
	{
		return blmvm_neos_solver_id;
	}
	if (!ss.compare("bnbs"))
	{
		return bnbs_neos_solver_id;
	}
	if (!ss.compare("bonmin"))
	{
		return bonmin_neos_solver_id;
	}
	if (!ss.compare("bpmpd"))
	{
		return bpmpd_neos_solver_id;
	}
	if (!ss.compare("cbc"))
	{
		return cbc_neos_solver_id;
	}
	if (!ss.compare("clp"))
	{
		return clp_neos_solver_id;
	}
	if (!ss.compare("concorde"))
	{
		return concorde_neos_solver_id;
	}
	if (!ss.compare("condor"))
	{
		return condor_neos_solver_id;
	}
	if (!ss.compare("conopt"))
	{
		return conopt_neos_solver_id;
	}
	if (!ss.compare("couenne"))
	{
		return couenne_neos_solver_id;
	}
	if (!ss.compare("csdp"))
	{
		return csdp_neos_solver_id;
	}
	if (!ss.compare("ddsip"))
	{
		return ddsip_neos_solver_id;
	}
	if (!ss.compare("dicopt"))
	{
		return dicopt_neos_solver_id;
	}
	if (!ss.compare("dsdp"))
	{
		return dsdp_neos_solver_id;
	}
	if (!ss.compare("feaspump"))
	{
		return feaspump_neos_solver_id;
	}
	if (!ss.compare("filmint"))
	{
		return filmint_neos_solver_id;
	}
	if (!ss.compare("filter"))
	{
		return filter_neos_solver_id;
	}
	if (!ss.compare("filtermpec"))
	{
		return filtermpec_neos_solver_id;
	}
//	if (!ss.compare("filter") || !ss.compare("filtermpec"))
//	{
//		return filtermpec_neos_solver_id;
//	}
	if (!ss.compare("fortmp"))
	{
		return fortmp_neos_solver_id;
	}
	if (!ss.compare("gams-ampl"))
	{
		return gamsampl_neos_solver_id;
	}
	if (!ss.compare("glpk"))
	{
		return glpk_neos_solver_id;
	}
	if (!ss.compare("gurobi"))
	{
		return gurobi_neos_solver_id;
	}
	if (!ss.compare("icos"))
	{
		return icos_neos_solver_id;
	}
	if (!ss.compare("ipopt"))
	{
		return ipopt_neos_solver_id;
	}
	if (!ss.compare("knitro"))
	{
		return knitro_neos_solver_id;
	}
	if (!ss.compare("lancelot"))
	{
		return lancelot_neos_solver_id;
	}
	if (!ss.compare("l-bfgs-b"))
	{
		return lbfgsb_neos_solver_id;
	}
	if (!ss.compare("lindoglobal"))
	{
		return lindoglobal_neos_solver_id;
	}
	if (!ss.compare("loqo"))
	{
		return loqo_neos_solver_id;
	}
	if (!ss.compare("lrambo"))
	{
		return lrambo_neos_solver_id;
	}
	if (!ss.compare("miles"))
	{
		return miles_neos_solver_id;
	}
	if (!ss.compare("minlp"))
	{
		return minlp_neos_solver_id;
	}
	if (!ss.compare("minos"))
	{
		return minos_neos_solver_id;
	}
	if (!ss.compare("minto"))
	{
		return minto_neos_solver_id;
	}
	if (!ss.compare("mosek"))
	{
		return mosek_neos_solver_id;
	}
	if (!ss.compare("mslip"))
	{
		return mslip_neos_solver_id;
	}
	if (!ss.compare("netflo"))
	{
		return netflo_neos_solver_id;
	}
	if (!ss.compare("nlpec"))
	{
		return nlpec_neos_solver_id;
	}
	if (!ss.compare("nmtr"))
	{
		return nmtr_neos_solver_id;
	}
	if (!ss.compare("nsips"))
	{
		return nsips_neos_solver_id;
	}
	if (!ss.compare("ooqp"))
	{
		return ooqp_neos_solver_id;
	}
	if (!ss.compare("path"))
	{
		return path_neos_solver_id;
	}
	if (!ss.compare("pathnlp"))
	{
		return pathnlp_neos_solver_id;
	}
	if (!ss.compare("penbmi"))
	{
		return penbmi_neos_solver_id;
	}
	if (!ss.compare("pennon"))
	{
		return pennon_neos_solver_id;
	}
	if (!ss.compare("pensdp"))
	{
		return pensdp_neos_solver_id;
	}
	if (!ss.compare("pcx"))
	{
		return pcx_neos_solver_id;
	}
	if (!ss.compare("pgapack"))
	{
		return pgapack_neos_solver_id;
	}
	if (!ss.compare("pswarm"))
	{
		return pswarm_neos_solver_id;
	}
	if (!ss.compare("qsopt_ex"))
	{
		return qsoptex_neos_solver_id;
	}
	if (!ss.compare("relax4"))
	{
		return relax4_neos_solver_id;
	}
	if (!ss.compare("sbb"))
	{
		return sbb_neos_solver_id;
	}
	if (!ss.compare("scip"))
	{
		return scip_neos_solver_id;
	}
	if (!ss.compare("sdpa"))
	{
		return sdpa_neos_solver_id;
	}
	if (!ss.compare("sdplr"))
	{
		return sdplr_neos_solver_id;
	}
	if (!ss.compare("sdpt3"))
	{
		return sdpt3_neos_solver_id;
	}
	if (!ss.compare("sedumi"))
	{
		return sedumi_neos_solver_id;
	}
	if (!ss.compare("snopt"))
	{
		return snopt_neos_solver_id;
	}
	if (!ss.compare("symphony"))
	{
		return symphony_neos_solver_id;
	}
	if (!ss.compare("tron"))
	{
		return tron_neos_solver_id;
	}
	if (!ss.compare("xpressmp"))
	{
		return xpressmp_neos_solver_id;
	}
	if (!ss.compare("worhp"))
	{
		return worhp_neos_solver_id;
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS solver id");
}

::std::string to_string(neos_solver_id id)
{
	switch (id)
	{
		case alphaecp_neos_solver_id:
			return "AlphaECP";
		case asa_neos_solver_id:
			return "ASA";
		case baron_neos_solver_id:
			return "BARON";
		case bdmlp_neos_solver_id:
			return "BDMLP";
		case biqmac_neos_solver_id:
			return "BiqMac";
		case blmvm_neos_solver_id:
			return "BLMVM";
		case bnbs_neos_solver_id:
			return "bnbs";
		case bonmin_neos_solver_id:
			return "Bonmin";
		case bpmpd_neos_solver_id:
			return "bpmpd";
		case cbc_neos_solver_id:
			return "Cbc";
		case clp_neos_solver_id:
			return "Clp";
		case concorde_neos_solver_id:
			return "concorde";
		case condor_neos_solver_id:
			return "condor";
		case conopt_neos_solver_id:
			return "CONOPT";
		case couenne_neos_solver_id:
			return "Couenne";
		case csdp_neos_solver_id:
			return "csdp";
		case ddsip_neos_solver_id:
			return "ddsip";
		case dicopt_neos_solver_id:
			return "DICOPT";
		case dsdp_neos_solver_id:
			return "DSDP";
		case feaspump_neos_solver_id:
			return "feaspump";
		case filmint_neos_solver_id:
			return "FilMINT";
		case filter_neos_solver_id:
			return "filter";
		case filtermpec_neos_solver_id:
			return "filterMPEC";
		case fortmp_neos_solver_id:
			return "FortMP";
		case gamsampl_neos_solver_id:
			return "GAMS-AMPL";
		case glpk_neos_solver_id:
			return "Glpk";
		case gurobi_neos_solver_id:
			return "Gurobi";
		case icos_neos_solver_id:
			return "icos";
		case ipopt_neos_solver_id:
			return "Ipopt";
		case knitro_neos_solver_id:
			return "KNITRO";
		case lancelot_neos_solver_id:
			return "LANCELOT";
		case lbfgsb_neos_solver_id:
			return "L-BFGS-B";
		case lindoglobal_neos_solver_id:
			return "LINDOGlobal";
		case loqo_neos_solver_id:
			return "LOQO";
		case lrambo_neos_solver_id:
			return "LRAMBO";
		case miles_neos_solver_id:
			return "MILES";
		case minlp_neos_solver_id:
			return "MINLP";
		case minos_neos_solver_id:
			return "MINOS";
		case minto_neos_solver_id:
			return "MINTO";
		case mosek_neos_solver_id:
			return "MOSEK";
		case mslip_neos_solver_id:
			return "MSLiP";
		case netflo_neos_solver_id:
			return "NETFLO";
		case nlpec_neos_solver_id:
			return "NLPEC";
		case nmtr_neos_solver_id:
			return "NMTR";
		case nsips_neos_solver_id:
			return "nsips";
		case ooqp_neos_solver_id:
			return "OOQP";
		case path_neos_solver_id:
			return "PATH";
		case pathnlp_neos_solver_id:
			return "PATHNLP";
		case penbmi_neos_solver_id:
			return "penbmi";
		case pennon_neos_solver_id:
			return "PENNON";
		case pensdp_neos_solver_id:
			return "pensdp";
		case pcx_neos_solver_id:
			return "PCx";
		case pgapack_neos_solver_id:
			return "PGAPack";
		case pswarm_neos_solver_id:
			return "PSwarm";
		case qsoptex_neos_solver_id:
			return "qsopt_ex";
		case relax4_neos_solver_id:
			return "RELAX4";
		case sbb_neos_solver_id:
			return "SBB";
		case scip_neos_solver_id:
			return "scip";
		case sdpa_neos_solver_id:
			return "SDPA";
		case sdplr_neos_solver_id:
			return "SDPLR";
		case sdpt3_neos_solver_id:
			return "sdpt3";
		case sedumi_neos_solver_id:
			return "sedumi";
		case snopt_neos_solver_id:
			return "SNOPT";
		case symphony_neos_solver_id:
			return "SYMPHONY";
		case tron_neos_solver_id:
			return "TRON";
		case xpressmp_neos_solver_id:
			return "XpressMP";
		case worhp_neos_solver_id:
			return "WORHP";
		default:
			break;
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS solver id");
}

inline
neos_solver_category make_solver_category(::std::string const& s)
{
	const ::std::string ss = ::boost::algorithm::to_lower_copy(s);

	if (!ss.compare("bco"))
	{
		return bco_neos_solver_category;
	}
	if (!ss.compare("co"))
	{
		return co_neos_solver_category;
	}
	if (!ss.compare("cp"))
	{
		return cp_neos_solver_category;
	}
	if (!ss.compare("go"))
	{
		return go_neos_solver_category;
	}
	if (!ss.compare("kestrel"))
	{
		return kestrel_neos_solver_category;
	}
	if (!ss.compare("lno"))
	{
		return lno_neos_solver_category;
	}
	if (!ss.compare("lp"))
	{
		return lp_neos_solver_category;
	}
	if (!ss.compare("milp"))
	{
		return milp_neos_solver_category;
	}
	if (!ss.compare("minco"))
	{
		return minco_neos_solver_category;
	}
	if (!ss.compare("multi"))
	{
		return multi_neos_solver_category;
	}
	if (!ss.compare("nco"))
	{
		return nco_neos_solver_category;
	}
	if (!ss.compare("ndo"))
	{
		return ndo_neos_solver_category;
	}
	if (!ss.compare("sdp"))
	{
		return sdp_neos_solver_category;
	}
	if (!ss.compare("sio"))
	{
		return sio_neos_solver_category;
	}
	if (!ss.compare("slp"))
	{
		return slp_neos_solver_category;
	}
	if (!ss.compare("socp"))
	{
		return socp_neos_solver_category;
	}
	if (!ss.compare("uco"))
	{
		return uco_neos_solver_category;
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS solver category");
}

inline
::std::string to_string(neos_solver_category category)
{
	switch (category)
	{
		case bco_neos_solver_category:
			return "bco";
		case co_neos_solver_category:
			return "co";
		case cp_neos_solver_category:
			return "cp";
		case go_neos_solver_category:
			return "go";
		case kestrel_neos_solver_category:
			return "kestrel";
		case lno_neos_solver_category:
			return "lnp";
		case lp_neos_solver_category:
			return "lp";
		case milp_neos_solver_category:
			return "milp";
		case minco_neos_solver_category:
			return "minco";
		case multi_neos_solver_category:
			return "MULTI";
		case nco_neos_solver_category:
			return "nco";
		case ndo_neos_solver_category:
			return "ndo";
		case sdp_neos_solver_category:
			return "sdp";
		case sio_neos_solver_category:
			return "sio";
		case slp_neos_solver_category:
			return "slp";
		case socp_neos_solver_category:
			return "socp";
		case uco_neos_solver_category:
			return "uco";
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS solver category");
}

inline
neos_input_format make_input_format(::std::string const& s)
{
	const ::std::string ss = ::boost::algorithm::to_lower_copy(s);

	if (!ss.compare("ampl"))
	{
		return ampl_neos_input_format;
	}
	if (!ss.compare("c"))
	{
		return c_neos_input_format;
	}
	if (!ss.compare("cplex"))
	{
		return cplex_neos_input_format;
	}
	if (!ss.compare("dimacs"))
	{
		return dimacs_neos_input_format;
	}
	if (!ss.compare("fortran"))
	{
		return fortran_neos_input_format;
	}
	if (!ss.compare("gams"))
	{
		return gams_neos_input_format;
	}
	if (!ss.compare("lp"))
	{
		return lp_neos_input_format;
	}
	if (!ss.compare("matlab"))
	{
		return matlab_neos_input_format;
	}
	if (!ss.compare("matlab_binary"))
	{
		return matlabbinary_neos_input_format;
	}
	if (!ss.compare("mps"))
	{
		return mps_neos_input_format;
	}
	if (!ss.compare("netflo"))
	{
		return netflo_neos_input_format;
	}
	if (!ss.compare("qps"))
	{
		return qps_neos_input_format;
	}
	if (!ss.compare("relax4"))
	{
		return relax4_neos_input_format;
	}
	if (!ss.compare("sdpa"))
	{
		return sdpa_neos_input_format;
	}
	if (!ss.compare("sdplr"))
	{
		return sdplr_neos_input_format;
	}
	if (!ss.compare("smps"))
	{
		return smps_neos_input_format;
	}
	if (!ss.compare("sparse"))
	{
		return sparse_neos_input_format;
	}
	if (!ss.compare("sparse_sdpa"))
	{
		return sparsesdpa_neos_input_format;
	}
	if (!ss.compare("tsp"))
	{
		return tsp_neos_input_format;
	}
	if (!ss.compare("zimpl"))
	{
		return zimpl_neos_input_format;
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS input method");
}

inline
::std::string to_string(neos_input_format method)
{
	switch (method)
	{
		case ampl_neos_input_format:
			return "AMPL";
		case c_neos_input_format:
			return "C";
		case cplex_neos_input_format:
			return "CPLEX";
		case dimacs_neos_input_format:
			return "DIMACS";
		case fortran_neos_input_format:
			return "Fortran";
		case gams_neos_input_format:
			return "GAMS";
		case lp_neos_input_format:
			return "LP";
		case matlab_neos_input_format:
			return "MATLAB";
		case matlabbinary_neos_input_format:
			return "MATLAB_BINARY";
		case mps_neos_input_format:
			return "MPS";
		case netflo_neos_input_format:
			return "NETFLO";
		case qps_neos_input_format:
			return "QPS";
		case relax4_neos_input_format:
			return "RELAX4";
		case sdpa_neos_input_format:
			return "SDPA";
		case sdplr_neos_input_format:
			return "SDPLR";
		case smps_neos_input_format:
			return "SMPS";
		case sparse_neos_input_format:
			return "SPARSE";
		case sparsesdpa_neos_input_format:
			return "SPARSE_SDPA";
		case tsp_neos_input_format:
			return "TSP";
		case zimpl_neos_input_format:
			return "ZIMPL";
	}

	DCS_EXCEPTION_THROW(::std::runtime_error, "Unknown NEOS input method");
}

inline
neos_solver_info make_solver_info(::std::string const& s)
{
	// Extract the job info from:
	//  <solver-category>:<solver-name>:<input-method>

	const ::std::size_t nk = 3;
	neos_solver_info info;
	::std::size_t bpos = 0;
	for (::std::size_t k = 1; k <= nk; ++k)
	{
		const ::std::size_t epos = s.find(':', bpos);
		if (epos == ::std::string::npos && k < nk)
		{
			::std::ostringstream oss;
			oss << "Cannot find ':' in '" << s << "' from position '" << bpos << "'";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}
		::std::string item = s.substr(bpos, (epos != ::std::string::npos) ? (epos-bpos) : ::std::string::npos);
		switch (k)
		{
			case 1:
				info.category = neos_detail::make_solver_category(item);
				break;
			case 2:
				info.solver = neos_detail::make_solver_id(item);
				break;
			case 3:
				info.input_format = neos_detail::make_input_format(item);
				break;
		}
	}

	return info;
}

inline
neos_solver_category_info make_solver_category_info(::std::string const& s)
{
	// Extract the abbreviated and full category name from:
	//  <abbreviated-name>:<full-name>

	neos_solver_category_info info;

	::std::size_t bpos(0);
	::std::size_t epos(0);
	::std::size_t nk(2);
	for (::std::size_t k = 1; k <= nk; ++k)
	{
		epos = s.find(':', bpos);
		if (epos == ::std::string::npos && k < nk)
		{
			::std::ostringstream oss;
			oss << "[Cannot find ':' in '" << s << "' from position '" << bpos << "'";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}
		::std::string item(s.substr(bpos, (epos != ::std::string::npos) ? (epos-bpos) : ::std::string::npos));
		switch (k)
		{
			case 1:
				info.short_name = item;
				info.category = neos_detail::make_solver_category(item);
				break;
			case 2:
				info.full_name = neos_detail::make_solver_id(item);
				break;
		}
	}

	return info;
}

inline
neos_solver_info make_solver_info(::std::string const& s, neos_solver_category category)
{
	// Extract the solver info from:
	//  <solver-name>:<input-method>

	neos_solver_info info;
	info.category = category;
	::std::size_t bpos(0);
	::std::size_t epos(0);
	::std::size_t nk(2);
	for (::std::size_t k = 1; k <= nk; ++k)
	{
		epos = s.find(':', bpos);
		if (epos == ::std::string::npos && k < nk)
		{
			::std::ostringstream oss;
			oss << "Cannot find ':' in '" << s << "' from position '" << bpos << "'";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}
		::std::string item(s.substr(bpos, (epos != ::std::string::npos) ? (epos-bpos) : ::std::string::npos));
		switch (k)
		{
			case 1:
				info.solver = neos_detail::make_solver_id(item);
				break;
			case 2:
				info.input_format = neos_detail::make_input_format(item);
				break;
		}
	}

	return info;
}

inline
submitted_neos_job_info make_submitted_job_info(::std::string const& s)
{
	submitted_neos_job_info info;

	::std::size_t pos(s.rfind(':'));
	info.solver = make_solver_info(s.substr(0, pos));
	info.status = make_job_status(s.substr(pos));

	return info;
}

}} // Namespace <unnamed>::neos_detail


/**
 * \brief Implements the XML-RPC NEOS API.
 *
 * See http://www.neos-server.org/neos/NEOS-API.html
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
class neos_client
{
	private: typedef xmlrpc_c::cbytestring cbytestring;
	private: typedef xmlrpc_c::carray carray;
	//private: typedef typename carray::const_iterator carray_iterator;


	public: static const ::std::string default_neos_host;
	public: static const int default_neos_port;
	//private: static const float default_zzz_time;


	public: explicit neos_client(::std::string const& host = default_neos_host,
								 int port = default_neos_port)
	: url_(neos_detail::make_url(host,port))
	{
	}

	public: ::std::string help() const
	{
		::std::string res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "help", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		res = xmlrpc_c::value_string(rpc_res);

		DCS_DEBUG_TRACE("Message: " << res);

		return res;
	}

	public: ::std::string welcome() const
	{
		::std::string res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "welcome", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		res = xmlrpc_c::value_string(rpc_res);

		DCS_DEBUG_TRACE("Message: " << res);

		return res;
	}

	public: ::std::string version() const
	{
		::std::string res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "version", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		res = xmlrpc_c::value_string(rpc_res);

		DCS_DEBUG_TRACE("Message: " << res);

		return res;
	}

	public: bool ping() const
	{
		bool res(false);

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "ping", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		::std::string const msg = xmlrpc_c::value_string(rpc_res);

		DCS_DEBUG_TRACE("Message: " << msg);

		// If the NEOS server is up return 'NeosServer is alive'

		::std::string imsg(::boost::algorithm::to_lower_copy(msg));
		if (!imsg.compare("neosserver is alive"))
		{
			res = true;
		}

		return res;
	}


	public: ::std::string queue() const
	{
		::std::string res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "printQueue", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		res = xmlrpc_c::value_string(rpc_res);

		DCS_DEBUG_TRACE("Message: " << res);

		return res;
	}


	public: ::std::string solver_template(neos_solver_category category, neos_solver_id solver, neos_input_format method) const
	{
		::std::string res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_,
				  "getSolverTemplate",
				  "sss",
				  &rpc_res,
				  neos_detail::to_string(category).c_str(),
				  neos_detail::to_string(solver).c_str(),
				  neos_detail::to_string(method).c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		res = xmlrpc_c::value_string(rpc_res);

		DCS_DEBUG_TRACE("Message: " << res);//XXX

		return res;
	}


	public: ::std::string xml(neos_solver_category category, neos_solver_id solver, neos_input_format method) const
	{
		return solver_template(category, solver, method);
	}


	public: ::std::vector<neos_solver_info> all_solvers() const
	{
		typedef carray::const_iterator carray_iterator;

		::std::vector<neos_solver_info> res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "listAllSolvers", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_ARRAY)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_ARRAY) << "' (" << xmlrpc_c::value::TYPE_ARRAY << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		// The returned message is a newline-separated string, where each
		// newline-separated item has the form:
		//  <solver-category>:<solver-name>:<input-method>

		carray const solvers = xmlrpc_c::value_array(rpc_res).vectorValueValue();
		carray_iterator end_it(solvers.end());
		for (carray_iterator it = solvers.begin(); it != end_it; ++it)
		{
			if (it->type() != xmlrpc_c::value::TYPE_STRING)
			{
				::std::ostringstream oss;
				oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(it->type()) << "' (" << it->type() << ").";
				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}

			::std::string const msg = xmlrpc_c::value_string(*it);

			DCS_DEBUG_TRACE("Message: " << msg);

			res.push_back(neos_detail::make_solver_info(msg));
		}

		return res;
	}


	public: ::std::vector<neos_solver_category_info> categories() const
	{
		typedef carray::const_iterator carray_iterator;

		::std::vector<neos_solver_category_info> res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "listCategories", &rpc_res);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_ARRAY)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_ARRAY) << "' (" << xmlrpc_c::value::TYPE_ARRAY << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		// The returned message is a newline-separated string, where each
		// newline-separated item has the form:
		//  <abbreviated-name>:<full-name>

		carray const categories = xmlrpc_c::value_array(rpc_res).vectorValueValue();
		carray_iterator end_it(categories.end());
		for (carray_iterator it = categories.begin(); it != end_it; ++it)
		{
			if (it->type() != xmlrpc_c::value::TYPE_STRING)
			{
				::std::ostringstream oss;
				oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(it->type()) << "' (" << it->type() << ").";
				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}

			::std::string const msg = xmlrpc_c::value_string(*it);

			DCS_DEBUG_TRACE("Message: " << msg);

			res.push_back(neos_detail::make_solver_category_info(msg));
		}

		return res;
	}


	public: ::std::vector<neos_solver_info> solvers_in_category(neos_solver_category category) const
	{
		typedef carray::const_iterator carray_iterator;

		::std::vector<neos_solver_info> res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "listSolversInCategory", "s", &rpc_res, neos_detail::to_string(category).c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_ARRAY)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_ARRAY) << "' (" << xmlrpc_c::value::TYPE_ARRAY << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		// The returned message is a newline-separated string, where each
		// newline-separated item has the form:
		//  <solver-name>:<input-method>

		carray const solvers = xmlrpc_c::value_array(rpc_res).vectorValueValue();
		carray_iterator end_it(solvers.end());
		for (carray_iterator it = solvers.begin(); it != end_it; ++it)
		{
			if (it->type() != xmlrpc_c::value::TYPE_STRING)
			{
				::std::ostringstream oss;
				oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(it->type()) << "' (" << it->type() << ").";
				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}

			::std::string const msg = xmlrpc_c::value_string(*it);

			DCS_DEBUG_TRACE("Message: " << msg);

			res.push_back(neos_detail::make_solver_info(msg, category));
		}

		return res;
	}


	public: neos_job_credentials submit_job(::std::string const& xml) const
	{
		DCS_DEBUG_TRACE("Submitting job: " << xml);//XXX

		neos_job_credentials res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "submitJob", "s", &rpc_res, xml.c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_ARRAY)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_ARRAY) << "' (" << xmlrpc_c::value::TYPE_ARRAY << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		carray const job_creds = xmlrpc_c::value_array(rpc_res).vectorValueValue();
		if (job_creds.size() != 2)
		{
			DCS_EXCEPTION_THROW(::std::runtime_error, "Expected (jobnumber,password) credentials.");
		}
		if (job_creds[0].type() != xmlrpc_c::value::TYPE_INT)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_INT) << "' (" << xmlrpc_c::value::TYPE_INT << "), got type '" << neos_detail::to_string(job_creds[0].type()) << "' (" << job_creds[0].type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}
		if (job_creds[1].type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(job_creds[1].type()) << "' (" << job_creds[1].type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		res.id = xmlrpc_c::value_int(job_creds[0]);
		res.password = xmlrpc_c::value_string(job_creds[1]);

		DCS_DEBUG_TRACE("jobNumber = " << res.id << "\tpassword = " << res.password);

		// Check for NEOS error:
		//   "In case of an error (NEOS Job queue is full), submitJob() will return (0,errorMessage)"
		if (res.id == 0)
		{
			::std::ostringstream oss;
			oss << "Error from NEOS: '" << res.password << "'.";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		return res;
	}


	public: neos_job_status job_status(neos_job_credentials const& creds) const
	{
		neos_job_status res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "getJobStatus", "is", &rpc_res, creds.id, creds.password.c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		::std::string const status_str = xmlrpc_c::value_string(rpc_res);
		res = neos_detail::make_job_status(status_str);

		DCS_DEBUG_TRACE("Status: " << status_str << " (" << res << ").");

		return res;
	}


	public: submitted_neos_job_info job_info(neos_job_credentials const& creds) const
	{
		submitted_neos_job_info res;

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "getJobInfo", "is", &rpc_res, creds.id, creds.password.c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		::std::string const msg = xmlrpc_c::value_string(rpc_res);
		res = neos_detail::make_submitted_job_info(msg);

		DCS_DEBUG_TRACE("Message: " << msg);

		return res;
	}


	///FIXME: what is the return type of 'killJob'?
	public: void kill_job(neos_job_credentials const& creds, ::std::string const& kill_msg = "") const
	{
		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, "killJob", "iss", &rpc_res, creds.id, creds.password.c_str(), kill_msg.c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_STRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_STRING) << "' (" << xmlrpc_c::value::TYPE_STRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}
	}


	public: ::std::string intermediate_results(neos_job_credentials const& creds, int& offset, bool blocking = true) const
	{
		// pre: offset > 0
		DCS_ASSERT(
				offset > 0,
				DCS_EXCEPTION_THROW(::std::invalid_argument, "Invalid offset")
			);

		::std::string res;

		::std::string method;
		if (blocking)
		{
			method = "getIntermediateResults";
		}
		else
		{
			method = "getIntermediateResultsNonBlocking";
		}

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, method, "isi", &rpc_res, creds.id, creds.password.c_str(), offset);
		if (rpc_res.type() != xmlrpc_c::value::TYPE_ARRAY)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_ARRAY) << "' (" << xmlrpc_c::value::TYPE_ARRAY << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		carray const msg_offs = xmlrpc_c::value_array(rpc_res).vectorValueValue();
		if (msg_offs.size() != 2)
		{
			DCS_EXCEPTION_THROW(std::runtime_error, "Expected (msg,offset) result pair.");
		}
		if (msg_offs[0].type() != xmlrpc_c::value::TYPE_BYTESTRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_BYTESTRING) << "' (" << xmlrpc_c::value::TYPE_BYTESTRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}
		if (msg_offs[1].type() != xmlrpc_c::value::TYPE_INT)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_INT) << "' (" << xmlrpc_c::value::TYPE_INT << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		cbytestring const msg_enc = xmlrpc_c::value_bytestring(msg_offs[0]).vectorUcharValue();

		res = dcs::text::base64_decode(dcs::text::base64_encode(msg_enc.data(), msg_enc.size()));

		offset = xmlrpc_c::value_int(msg_offs[1]);

		DCS_DEBUG_TRACE("Message: " << res << " - Offset: " << offset);

		return res;
	}


	public: ::std::string final_results(neos_job_credentials const& creds, bool blocking = true) const
	{
		::std::string res;

		::std::string method;
		if (blocking)
		{
			method = "getFinalResults";
		}
		else
		{
			method = "getFinalResultsNonBlocking";
		}

		xmlrpc_c::clientSimple neos;

		xmlrpc_c::value rpc_res;
		neos.call(url_, method, "is", &rpc_res, creds.id, creds.password.c_str());
		if (rpc_res.type() != xmlrpc_c::value::TYPE_BYTESTRING)
		{
			::std::ostringstream oss;
			oss << "Expected type '" << neos_detail::to_string(xmlrpc_c::value::TYPE_BYTESTRING) << "' (" << xmlrpc_c::value::TYPE_BYTESTRING << "), got type '" << neos_detail::to_string(rpc_res.type()) << "' (" << rpc_res.type() << ").";
			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		cbytestring const msg_enc = xmlrpc_c::value_bytestring(rpc_res).vectorUcharValue();

		res = dcs::text::base64_decode(dcs::text::base64_encode(msg_enc.data(), msg_enc.size()));

		DCS_DEBUG_TRACE("Message: " << res);

		return res;
	}


	private: ::std::string url_;
}; // neos_client

//const ::std::string client::default_neos_host("neos-dev1.discovery.wisc.edu");
const ::std::string neos_client::default_neos_host("www.neos-server.org");
const int neos_client::default_neos_port = 3332;
//const float client::default_zzz_time(1);


/// Execute the given job on the NEOS server and return the result.
inline
::std::string execute_neos_job(neos_client const& neos,
							   ::std::string const& job_xml)
{
	// pre: !empty(job_xml)
	DCS_ASSERT(!job_xml.empty(),
			   DCS_EXCEPTION_THROW(::std::invalid_argument, "Invalid job"));

	::std::string res;

	neos_job_credentials creds;
	creds = neos.submit_job(job_xml);

	DCS_DEBUG_TRACE("Job Crediantials: (" << creds.id << "," << creds.password << ")");//XXX

	res = neos.final_results(creds, false);

	if (res.empty())
	{
		::std::size_t zzz_time = 2;
		::std::size_t num_trials = 0;
		const ::std::size_t max_num_trials = 3600/zzz_time; // ... so that we wait at least for 1 hour

		neos_job_status status;
		do
		{
			++num_trials;

			DCS_DEBUG_TRACE("Waiting... (Trial: " << num_trials << ", Zzz: " << zzz_time << " sec)");//XXX

			::sleep(zzz_time);
			::boost::this_thread::sleep_for(::boost::chrono::seconds(2));
//			zzz_time *= 1.5; // exponential backoff (1.5 -> 50% increase per back-off)
			//zzz_time += 0.5;
			zzz_time += 1;

			status = neos.job_status(creds);
		}
		while ((status == running_neos_job_status || status == waiting_neos_job_status) && num_trials < max_num_trials);

		if (status == done_neos_job_status)
		{
			res = neos.final_results(creds);
		}
		else
		{
			DCS_DEBUG_TRACE("Killing...");//XXX

			neos.kill_job(creds);
		}
	}

	DCS_DEBUG_TRACE("Result: " << res);//XXX

	return res;
}


/// Create an AMPL job XML from the given XML template.
::std::string make_neos_ampl_job(::std::string const& xml_tmpl,
								 ::std::string const& model,
								 ::std::string const& data,
								 ::std::string const& commands = "",
								 ::std::string const& options = "",
								 ::std::string const& comments = "")
{
	// pre: !empty(model)
	DCS_ASSERT(!model.empty(),
			   DCS_EXCEPTION_THROW(::std::invalid_argument, "Invalid AMPL model"));
	// pre: !empty(data)
	DCS_ASSERT(!data.empty(),
			   DCS_EXCEPTION_THROW(::std::invalid_argument, "Invalid AMPL data"));

	::boost::property_tree::ptree xml_tree;
	::std::istringstream iss(xml_tmpl);
	::std::ostringstream oss;

	::boost::property_tree::read_xml(iss, xml_tree);
	xml_tree.put("document.model", "reset;"+model);
	xml_tree.put("document.data", data);
	xml_tree.put("document.commands", commands);
	xml_tree.put("document.options", options);
	xml_tree.put("document.comments", comments);
	::boost::property_tree::write_xml(oss, xml_tree);

	return oss.str();
}


/// Execute the given AMPL job on the NEOS server and return the result.
inline
::std::string execute_neos_ampl_job(neos_client const& neos,
									neos_solver_category solver_category,
									neos_solver_id solver_id,
									::std::string const& model,
									::std::string const& data,
									::std::string const& commands = "",
									::std::string const& options = "",
									::std::string const& comments = "")
{
	const ::std::string xml(neos.solver_template(solver_category, solver_id, ampl_neos_input_format));

	return execute_neos_job(neos, make_neos_ampl_job(xml, model, data, commands, options, comments));
}


/// Create an GAMS job XML from the given XML template.
::std::string make_neos_gams_job(::std::string const& xml_tmpl,
								 ::std::string const& model,
								 ::std::string const& options = "",
								 ::std::string const& gdx = "",
								 bool want_gdx = false,
								 bool want_log = false,
								 ::std::string const& comments = "")
{
	// pre: !empty(model)
	DCS_ASSERT(!model.empty(),
			   DCS_EXCEPTION_THROW(::std::invalid_argument, "Invalid GAMS model"));

	::boost::property_tree::ptree xml_tree;
	::std::istringstream iss(xml_tmpl);
	::std::ostringstream oss;

	::boost::property_tree::read_xml(iss, xml_tree);
	xml_tree.put("document.model", model);
	xml_tree.put("document.options", options);
	xml_tree.put("document.gdx", gdx);
	xml_tree.put("document.wantgdx", want_gdx);
	xml_tree.put("document.wantlog", want_log);
	xml_tree.put("document.comments", comments);
	::boost::property_tree::write_xml(oss, xml_tree);

	return oss.str();
}


/// Execute the given GAMS job on the NEOS server and return the result.
inline
::std::string execute_neos_gams_job(neos_client const& neos,
									neos_solver_category solver_category,
									neos_solver_id solver_id,
									::std::string const& model,
									::std::string const& options = "",
									::std::string const& gdx = "",
									bool want_gdx = false,
									bool want_log = false,
									::std::string const& comments = "")
{
	const ::std::string xml(neos.solver_template(solver_category, solver_id, gams_neos_input_format));

	return execute_neos_job(neos, make_neos_gams_job(xml, model, options, gdx, want_gdx, want_log, comments));
}

}}} // Namespace dcs::math::optim


#endif // DCS_MATH_OPTIM_NEOS_CLIENT_HPP
