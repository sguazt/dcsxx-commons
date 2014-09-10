/**
 * \file dcs/math/optim/neos_solver_category.hpp
 *
 * \brief Identifiers of NEOS solvers.
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

#ifndef DCS_MATH_OPTIM_NEOS_SOLVER_ID_HPP
#define DCS_MATH_OPTIM_NEOS_SOLVER_ID_HPP


namespace dcs { namespace math { namespace optim {

enum neos_solver_id
{
	acrs_neos_solver_id, ///< ACRS (http://www.iasi.cnr.it/~liuzzi/DFL/)
	algencan_neos_solver_id, ///< ALGENCAN (http://www.ime.usp.br/~egbirgin/tango/codes.php)
	alphaecp_neos_solver_id, ///< AlphaECP (http://archimedes.scs.uiuc.edu/alphaecp/alphaecp.html)
	asa_neos_solver_id, ///< ASA (http://www.ingber.com/)
	baron_neos_solver_id, ///< BARON (http://archimedes.scs.uiuc.edu/baron/baron.html)
	bdmlp_neos_solver_id, ///< BDMLP (http://www.mcs.anl.gov/otc/Guide/OptWeb/continuous/constrained/linearprog/)
	biqmac_neos_solver_id, ///< BiqMac (http://biqmac.uni-klu.ac.at/)
	blmvm_neos_solver_id, ///< BLMVM (http://www.mcs.anl.gov/research/projects/tao/)
	bnbs_neos_solver_id, ///< bnbs (http://plato.la.asu.edu/)
	bonmin_neos_solver_id, ///< COIN-OR Bonmin (https://projects.coin-or.org/Bonmin)
	bpmpd_neos_solver_id, ///< bpmpd (http://www.sztaki.hu/~meszaros/bpmpd/)
	cbc_neos_solver_id, ///< COIN-OR Cbc (https://projects.coin-or.org/Cbc)
	clp_neos_solver_id, ///< COIN-OR Clp (https://projects.coin-or.org/Clp)
	concorde_neos_solver_id, ///< concorde (http://www.tsp.gatech.edu/concorde.html)
	condor_neos_solver_id, ///< condor (http://www.applied-mathematics.net/CONDORManual/CONDORManual.html)
	conopt_neos_solver_id, ///< CONOPT (http://www.conopt.com/)
	couenne_neos_solver_id, ///< COIN-OR Couenne (https://projects.coin-or.org/Couenne)
	csdp_neos_solver_id, ///< csdp (https://projects.coin-or.org/Csdp/)
	cplex_neos_solver_id, ///< CPLEX (http://www-01.ibm.com/software/integration/optimization/cplex-optimizer/)
	ddsip_neos_solver_id, ///< ddsip (http://plato.asu.edu/ddsip-man.pdf)
	dicopt_neos_solver_id, ///< DICOPT (http://archimedes.scs.uiuc.edu/dicopt/dicopt.html)
	donlp2_neos_solver_id, ///< DONLP2 (http://www.mathematik.tu-darmstadt.de/fbereiche/numerik/staff/spellucci/DONLP2/)
	dsdp_neos_solver_id, ///< DSDP (http://www.mcs.anl.gov/DSDP)
	feaspump_neos_solver_id, ///< feaspump (http://www.dei.unipd.it/~fisch/papers/feasibility_pump_201.pdf)
	filmint_neos_solver_id, ///< FilMINT (http://www.mcs.anl.gov/home/otc/Guide/OptWeb/continuous/constrained/nonlinearcon)
	filter_neos_solver_id, ///< filter (http://www.mcs.anl.gov/~leyffer/solvers.html)
	filtermpec_neos_solver_id, ///< filterMPEC (http://www.mcs.anl.gov/~leyffer/neos/mpec/mpec_options.html - http://wiki.mcs.anl.gov/leyffer/index.php/Sven_Leyffer)
	fortmp_neos_solver_id, ///< FortMP (http://www.optirisk-systems.com/)
	fsqp_neos_solver_id, ///< FSQP (http://www.netlib.org/ampl/solvers/fsqp/README)
	gamsampl_neos_solver_id, ///< GAMS-AMPL
	glpk_neos_solver_id, ///< Glpk (http://www.gnu.org/software/glpk/glpk.html)
	gurobi_neos_solver_id, ///< Gurobi (http://www.gurobi.com/)
	icos_neos_solver_id, ///< icos (http://sites.google.com/site/ylebbah/icos)
	ipopt_neos_solver_id, ///< COIN-OR Ipopt (https://projects.coin-or.org/Ipopt)
	knitro_neos_solver_id, ///< KNITRO (http://www.ziena.com/knitro)
	lancelot_neos_solver_id, ///< LANCELOT (http://www.cse.scitech.ac.uk/nag/lancelot/lancelot.shtml)
	lbfgsb_neos_solver_id, ///< L-BFGS-B (http://www.mcs.anl.gov/otc/GUIDE/OptWeb/continuous/constrained/boundcon/)
	lgo_neos_solver_id, ///< LGO (http://www.pinterconsulting.com/index.html)
	lindoglobal_neos_solver_id, ///< LINDOGlobal (http://archimedes.scs.uiuc.edu/lindoglobal/lindoglobal.html)
	loqo_neos_solver_id, ///< LOQO (http://www.princeton.edu/~rvdb/loqo/LOQO.html)
	lpsolve_neos_solver_id, ///< LP_SOLVE (http://sourceforge.net/projects/lpsolve/)
	lrambo_neos_solver_id, ///< LRAMBO (http://www.mcs.anl.gov/LRAMBO)
	miles_neos_solver_id, ///< MILES (http://www.mcs.anl.gov/otc/Guide/OptWeb/complementarity)
	minlp_neos_solver_id, ///< MINLP (http://www.mcs.anl.gov/~leyffer/solvers.html)
	minos_neos_solver_id, ///< MINOS (http://www.sbsi-sol-optimize.com/asp/sol_product_minos.htm)
	minto_neos_solver_id, ///< MINTO (http://coral.ie.lehigh.edu/~minto/index.html)
	mosek_neos_solver_id, ///< MOSEK (http://www.mosek.com/)
	mslip_neos_solver_id, ///< MSLiP (http://sba.management.dal.ca/profs/hgassmann/mslip.html)
	mlocpsoa_neos_solver_id, // MLOCPSOA (http://www.norg.uminho.pt/aivaz/mlocpsoa.html)
	netflo_neos_solver_id, ///< NETFLO (ftp://dimacs.rutgers.edu/pub/netflow/mincost/solver-1)
	nlpec_neos_solver_id, ///< NLPEC (http://www.mcs.anl.gov/otc/Guide/OptWeb/complementarity)
	nmtr_neos_solver_id, ///< NMTR (http://www.mcs.anl.gov/home/otc/Guide/OptWeb/continuous/unconstrained/)
	nomad_neos_solver_id, ///< NOMAD (http://www.gerad.ca/NOMAD/Project/Home.html)
	npsol_neos_solver_id, ///< NPSOL (http://www.sbsi-sol-optimize.com/asp/sol_product_npsol.htm)
	nsips_neos_solver_id, ///< nsips (http://www.norg.uminho.pt/aivaz/nsips.html)
	ooqp_neos_solver_id, ///< OOQP (http://www.cs.wisc.edu/~swright/ooqp)
	path_neos_solver_id, ///< PATH (http://www.cs.wisc.edu/cpnet/aboutcp.html)
	pathnlp_neos_solver_id, ///< PATHNLP (http://www.mcs.anl.gov/otc/Guide/OptWeb/complementarity)
	penbmi_neos_solver_id, ///< penbmi (http://www.penopt.com/)
	pennon_neos_solver_id, ///< PENNON (http://www2.am.uni-erlangen.de/~kocvara/pennon/)
	pensdp_neos_solver_id, ///< pensdp (http://www.penopt.com/pensdp.html)
	pcx_neos_solver_id, ///< PCx (http://www.cs.wisc.edu/~swright/PCx)
	pgapack_neos_solver_id, ///< PGAPack (http://www-fp.mcs.anl.gov/CCST/research/reports_pre1998/comp_bio/stalk/pgapack.html)
	pswarm_neos_solver_id, ///< PSwarm (http://www.norg.uminho.pt/aivaz/pswarm)
	qsoptex_neos_solver_id, ///< qsopt_ex (http://www.dii.uchile.cl/~daespino/QSoptExact_doc/main.html)
	relax4_neos_solver_id, ///< RELAX4 (http://www.mcs.anl.gov/otc/Guide/OptWeb/continuous/constrained/network/)
	sbb_neos_solver_id, ///< SBB (http://www.mcs.anl.gov/otc/Guide/OptWeb/discrete/integerprog/index.html)
	scip_neos_solver_id, ///< scip (http://scip.zib.de/)
	sdpa_neos_solver_id, ///< SDPA (http://sdpa.sourceforge.net/)
	sdplr_neos_solver_id, ///< sdplr (http://dollar.biz.uiowa.edu/~burer/software/SDPLR/)
	sdpt3_neos_solver_id, ///< sdpt3 (http://www.math.nus.edu.sg/~mattohkc/sdpt3.html)
	sedumi_neos_solver_id, ///< sedumi (http://plato.asu.edu/ftp/SeDuMi_Guide_11.pdf)
	snopt_neos_solver_id, ///< SNOPT (http://www.sbsi-sol-optimize.com/asp/sol_product_snopt.htm)
	symphony_neos_solver_id, ///< SYMPHONY (https://projects.coin-or.org/SYMPHONY)
	tron_neos_solver_id, ///< TRON (http://www.mcs.anl.gov/~more/tron/)
	worhp_neos_solver_id, ///< WORHP (http://www.worhp.de/)
	wsatoip_neos_solver_id, ///< WSAT(OIP) (http://www.ps.uni-saarland.de/~walser/wsatpb/)
	xpressmp_neos_solver_id ///< XpressMP (http://www.dashoptimization.com/ - http://www.fico.com/xpress)
};

}}} // Namespace dcs::math::optim


#endif // DCS_MATH_OPTIM_NEOS_SOLVER_ID_HPP
