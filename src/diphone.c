/***************************************************************************
 *   Author Alan Crispin                                                   *
 *   crispinalan@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation.                                         *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "diphone.h"
#include "voice8.h"

unsigned char *load_diphone_arry(char* diphone_str)
{
	
	unsigned char *diphone_arry;
	diphone_arry = (unsigned char*)malloc(0 * sizeof(unsigned char));
	
	//aa diphones	
	if (g_strcmp0(diphone_str,"aa-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_aa_raw_len * sizeof(unsigned char));
	diphone_arry = aa_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ae_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ah_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ao_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_aw_raw_len * sizeof(unsigned char));
	diphone_arry = aa_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ax_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ay_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-b")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_b_raw_len * sizeof(unsigned char));
	diphone_arry = aa_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ch_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-d")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_d_raw_len * sizeof(unsigned char));
	diphone_arry = aa_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_dh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_eh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-er")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_er_raw_len * sizeof(unsigned char));
	diphone_arry = aa_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ey_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-f")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_f_raw_len * sizeof(unsigned char));
	diphone_arry = aa_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-g")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_g_raw_len * sizeof(unsigned char));
	diphone_arry = aa_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_hh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ih_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_iy_raw_len * sizeof(unsigned char));
	diphone_arry = aa_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_jh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-k")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_k_raw_len * sizeof(unsigned char));
	diphone_arry = aa_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-l")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_l_raw_len * sizeof(unsigned char));
	diphone_arry = aa_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-m")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_m_raw_len * sizeof(unsigned char));
	diphone_arry = aa_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-n")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_n_raw_len * sizeof(unsigned char));
	diphone_arry = aa_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ng_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_ow_raw_len * sizeof(unsigned char));
	diphone_arry = aa_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_oy_raw_len * sizeof(unsigned char));
	diphone_arry = aa_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-p")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_p_raw_len * sizeof(unsigned char));
	diphone_arry = aa_p_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_pau_raw_len * sizeof(unsigned char));
	diphone_arry = aa_pau_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-r")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_r_raw_len * sizeof(unsigned char));
	diphone_arry = aa_r_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-s")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_s_raw_len * sizeof(unsigned char));
	diphone_arry = aa_s_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_sh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_sh_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-t")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_t_raw_len * sizeof(unsigned char));
	diphone_arry = aa_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-th")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_th_raw_len * sizeof(unsigned char));
	diphone_arry = aa_th_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_uh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aa-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_uw_raw_len * sizeof(unsigned char));
	diphone_arry = aa_uw_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-v")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_v_raw_len * sizeof(unsigned char));
	diphone_arry = aa_v_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-w")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_w_raw_len * sizeof(unsigned char));
	diphone_arry = aa_w_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-y")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_y_raw_len * sizeof(unsigned char));
	diphone_arry =aa_y_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-z")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_z_raw_len * sizeof(unsigned char));
	diphone_arry = aa_z_raw;	
	}
	if (g_strcmp0(diphone_str,"aa-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(aa_zh_raw_len * sizeof(unsigned char));
	diphone_arry = aa_zh_raw;	
	}
	
	//ae diphones
	if (g_strcmp0(diphone_str,"ae-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ae_aa_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ae_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ah_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ao_raw;	
	}
	
	if (g_strcmp0(diphone_str,"ae-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ae_aw_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ax_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ay_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_b_raw_len * sizeof(unsigned char));
	diphone_arry = ae_b_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ch_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_d_raw_len * sizeof(unsigned char));
	diphone_arry = ae_d_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_dh_raw;	
	}

	
	if (g_strcmp0(diphone_str,"ae-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_eh_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_er_raw_len * sizeof(unsigned char));
	diphone_arry = ae_er_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ey_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_f_raw_len * sizeof(unsigned char));
	diphone_arry = ae_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ae-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_g_raw_len * sizeof(unsigned char));
	diphone_arry = ae_g_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_hh_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ih_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_iy_raw_len * sizeof(unsigned char));
	diphone_arry =ae_iy_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_jh_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_k_raw_len * sizeof(unsigned char));
	diphone_arry = ae_k_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_l_raw_len * sizeof(unsigned char));
	diphone_arry = ae_l_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_m_raw_len * sizeof(unsigned char));
	diphone_arry = ae_m_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_n_raw_len * sizeof(unsigned char));
	diphone_arry = ae_n_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ng_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ae_ow_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ae_oy_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_p_raw_len * sizeof(unsigned char));
	diphone_arry = ae_p_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ae_pau_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_r_raw_len * sizeof(unsigned char));
	diphone_arry = ae_r_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_s_raw_len * sizeof(unsigned char));
	diphone_arry = ae_s_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_sh_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_t_raw_len * sizeof(unsigned char));
	diphone_arry = ae_t_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_th_raw_len * sizeof(unsigned char));
	diphone_arry = ae_th_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_uh_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ae_uw_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_v_raw_len * sizeof(unsigned char));
	diphone_arry = ae_v_raw;	
	}
	//
	if (g_strcmp0(diphone_str,"ae-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_y_raw_len * sizeof(unsigned char));
	diphone_arry = ae_y_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_z_raw_len * sizeof(unsigned char));
	diphone_arry = ae_z_raw;	
	}
	if (g_strcmp0(diphone_str,"ae-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ae_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ae_zh_raw;	
	}
	
	//ah diphones
	if (g_strcmp0(diphone_str,"ah-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ah_aa_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ae_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ah_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ao_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ah_aw_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ax_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ay_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_b_raw_len * sizeof(unsigned char));
	diphone_arry = ah_b_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ch_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_d_raw_len * sizeof(unsigned char));
	diphone_arry = ah_d_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_dh_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_eh_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_er_raw_len * sizeof(unsigned char));
	diphone_arry = ah_er_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ey_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_f_raw_len * sizeof(unsigned char));
	diphone_arry = ah_f_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_g_raw_len * sizeof(unsigned char));
	diphone_arry = ah_g_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_hh_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ah_iy_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_jh_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_k_raw_len * sizeof(unsigned char));
	diphone_arry = ah_k_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_l_raw_len * sizeof(unsigned char));
	diphone_arry = ah_l_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_m_raw_len * sizeof(unsigned char));
	diphone_arry = ah_m_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_n_raw_len * sizeof(unsigned char));
	diphone_arry = ah_n_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ng_raw;	
	}
	if (g_strcmp0(diphone_str,"ah-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ah_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ah_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_p_raw_len * sizeof(unsigned char));
	diphone_arry = ah_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ah_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_r_raw_len * sizeof(unsigned char));
	diphone_arry = ah_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_s_raw_len * sizeof(unsigned char));
	diphone_arry = ah_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_t_raw_len * sizeof(unsigned char));
	diphone_arry = ah_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_th_raw_len * sizeof(unsigned char));
	diphone_arry = ah_th_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ah_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_v_raw_len * sizeof(unsigned char));
	diphone_arry = ah_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_w_raw_len * sizeof(unsigned char));
	diphone_arry = ah_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_y_raw_len * sizeof(unsigned char));
	diphone_arry = ah_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_z_raw_len * sizeof(unsigned char));
	diphone_arry = ah_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ah-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ah_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ah_zh_raw;
	
	}
	
	//ao diphones	
	if (g_strcmp0(diphone_str,"ao-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ao_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ao_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_b_raw_len * sizeof(unsigned char));
	diphone_arry = ao_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_d_raw_len * sizeof(unsigned char));
	diphone_arry = ao_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_er_raw_len * sizeof(unsigned char));
	diphone_arry = ao_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_f_raw_len * sizeof(unsigned char));
	diphone_arry = ao_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_g_raw_len * sizeof(unsigned char));
	diphone_arry = ao_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ao_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_k_raw_len * sizeof(unsigned char));
	diphone_arry = ao_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_l_raw_len * sizeof(unsigned char));
	diphone_arry = ao_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_m_raw_len * sizeof(unsigned char));
	diphone_arry = ao_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_n_raw_len * sizeof(unsigned char));
	diphone_arry = ao_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ao_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ao_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_p_raw_len * sizeof(unsigned char));
	diphone_arry = ao_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ao_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_r_raw_len * sizeof(unsigned char));
	diphone_arry = ao_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_s_raw_len * sizeof(unsigned char));
	diphone_arry = ao_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_t_raw_len * sizeof(unsigned char));
	diphone_arry = ao_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_th_raw_len * sizeof(unsigned char));
	diphone_arry = ao_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ao-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ao_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_v_raw_len * sizeof(unsigned char));
	diphone_arry = ao_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_w_raw_len * sizeof(unsigned char));
	diphone_arry = ao_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_y_raw_len * sizeof(unsigned char));
	diphone_arry = ao_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_z_raw_len * sizeof(unsigned char));
	diphone_arry = ao_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ao-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ao_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ao_zh_raw;
	
	}
	
	//aw diphones
	if (g_strcmp0(diphone_str,"aw-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_aa_raw_len * sizeof(unsigned char));
	diphone_arry = aw_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ae_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ah_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ao_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_aw_raw_len * sizeof(unsigned char));
	diphone_arry = aw_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ax_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ay_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-b")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_b_raw_len * sizeof(unsigned char));
	diphone_arry = aw_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ch_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-d")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_d_raw_len * sizeof(unsigned char));
	diphone_arry = aw_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_dh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_eh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-er")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_er_raw_len * sizeof(unsigned char));
	diphone_arry = aw_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ey_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-f")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_f_raw_len * sizeof(unsigned char));
	diphone_arry = aw_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-g")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_g_raw_len * sizeof(unsigned char));
	diphone_arry = aw_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_hh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ih_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_iy_raw_len * sizeof(unsigned char));
	diphone_arry = aw_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-jh")==0) {
	diphone_arry = (unsigned char*)malloc(aw_jh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-k")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_k_raw_len * sizeof(unsigned char));
	diphone_arry = aw_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-l")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_l_raw_len * sizeof(unsigned char));
	diphone_arry = aw_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-m")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_m_raw_len * sizeof(unsigned char));
	diphone_arry = aw_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-n")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_n_raw_len * sizeof(unsigned char));
	diphone_arry = aw_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ng_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_ow_raw_len * sizeof(unsigned char));
	diphone_arry = aw_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_oy_raw_len * sizeof(unsigned char));
	diphone_arry = aw_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-p")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_p_raw_len * sizeof(unsigned char));
	diphone_arry = aw_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_pau_raw_len * sizeof(unsigned char));
	diphone_arry = aw_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-r")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_r_raw_len * sizeof(unsigned char));
	diphone_arry = aw_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-s")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_s_raw_len * sizeof(unsigned char));
	diphone_arry = aw_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_sh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-t")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_t_raw_len * sizeof(unsigned char));
	diphone_arry = aw_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-th")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_th_raw_len * sizeof(unsigned char));
	diphone_arry = aw_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"aw-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_uh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_uw_raw_len * sizeof(unsigned char));
	diphone_arry = aw_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-v")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_v_raw_len * sizeof(unsigned char));
	diphone_arry = aw_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-w")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_w_raw_len * sizeof(unsigned char));
	diphone_arry = aw_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-y")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_y_raw_len * sizeof(unsigned char));
	diphone_arry = aw_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-z")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_z_raw_len * sizeof(unsigned char));
	diphone_arry = aw_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"aw-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(aw_zh_raw_len * sizeof(unsigned char));
	diphone_arry = aw_zh_raw;	
	}
	
	//ax diphones
	if (g_strcmp0(diphone_str,"ax-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ax_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ax_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_b_raw_len * sizeof(unsigned char));
	diphone_arry = ax_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_d_raw_len * sizeof(unsigned char));
	diphone_arry = ax_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_er_raw_len * sizeof(unsigned char));
	diphone_arry = ax_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_f_raw_len * sizeof(unsigned char));
	diphone_arry = ax_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_g_raw_len * sizeof(unsigned char));
	diphone_arry = ax_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ax_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_k_raw_len * sizeof(unsigned char));
	diphone_arry = ax_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_l_raw_len * sizeof(unsigned char));
	diphone_arry = ax_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_m_raw_len * sizeof(unsigned char));
	diphone_arry = ax_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-n")==0) {
	diphone_arry = (unsigned char*)malloc(ax_n_raw_len * sizeof(unsigned char));
	diphone_arry = ax_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ax_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ax_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_p_raw_len * sizeof(unsigned char));
	diphone_arry = ax_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ax_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_r_raw_len * sizeof(unsigned char));
	diphone_arry = ax_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_s_raw_len * sizeof(unsigned char));
	diphone_arry = ax_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_t_raw_len * sizeof(unsigned char));
	diphone_arry = ax_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_th_raw_len * sizeof(unsigned char));
	diphone_arry = ax_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ax-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ax_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_v_raw_len * sizeof(unsigned char));
	diphone_arry = ax_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_w_raw_len * sizeof(unsigned char));
	diphone_arry = ax_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_y_raw_len * sizeof(unsigned char));
	diphone_arry = ax_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_z_raw_len * sizeof(unsigned char));
	diphone_arry = ax_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ax-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ax_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ax_zh_raw;	
	}
	
	//ay diphones
	if (g_strcmp0(diphone_str,"ay-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ay_aa_raw;	
	}
	if (g_strcmp0(diphone_str,"ay-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ay_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_b_raw_len * sizeof(unsigned char));
	diphone_arry = ay_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_d_raw_len * sizeof(unsigned char));
	diphone_arry = ay_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ay_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ay_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_er_raw_len * sizeof(unsigned char));
	diphone_arry = ay_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_f_raw_len * sizeof(unsigned char));
	diphone_arry = ay_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_g_raw_len * sizeof(unsigned char));
	diphone_arry = ay_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ay_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ih")==0) {
	diphone_arry = (unsigned char*)malloc(ay_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ay_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ay_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_k_raw_len * sizeof(unsigned char));
	diphone_arry = ay_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_l_raw_len * sizeof(unsigned char));
	diphone_arry = ay_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_m_raw_len * sizeof(unsigned char));
	diphone_arry = ay_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_n_raw_len * sizeof(unsigned char));
	diphone_arry = ay_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ay_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ay_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_p_raw_len * sizeof(unsigned char));
	diphone_arry = ay_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ay_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_r_raw_len * sizeof(unsigned char));
	diphone_arry = ay_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_s_raw_len * sizeof(unsigned char));
	diphone_arry = ay_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ay_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_t_raw_len * sizeof(unsigned char));
	diphone_arry = ay_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_th_raw_len * sizeof(unsigned char));
	diphone_arry = ay_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ay-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ay_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ay_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_v_raw_len * sizeof(unsigned char));
	diphone_arry = ay_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_w_raw_len * sizeof(unsigned char));
	diphone_arry = ay_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_y_raw_len * sizeof(unsigned char));
	diphone_arry = ay_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_z_raw_len * sizeof(unsigned char));
	diphone_arry = ay_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ay-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ay_zh_raw_len * sizeof(unsigned char));
	diphone_arry =ay_zh_raw;	
	}
	
	//b diphones
	if (g_strcmp0(diphone_str,"b-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(b_aa_raw_len * sizeof(unsigned char));
	diphone_arry = b_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ae_raw_len * sizeof(unsigned char));
	diphone_arry = b_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ah_raw_len * sizeof(unsigned char));
	diphone_arry = b_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ao_raw_len * sizeof(unsigned char));
	diphone_arry = b_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(b_aw_raw_len * sizeof(unsigned char));
	diphone_arry = b_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ax_raw_len * sizeof(unsigned char));
	diphone_arry = b_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ay_raw_len * sizeof(unsigned char));
	diphone_arry = b_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-b")==0) { 
	diphone_arry = (unsigned char*)malloc(b_b_raw_len * sizeof(unsigned char));
	diphone_arry = b_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ch_raw_len * sizeof(unsigned char));
	diphone_arry = b_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-d")==0) { 
	diphone_arry = (unsigned char*)malloc(b_d_raw_len * sizeof(unsigned char));
	diphone_arry = b_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_dh_raw_len * sizeof(unsigned char));
	diphone_arry = b_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_eh_raw_len * sizeof(unsigned char));
	diphone_arry = b_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-er")==0) { 
	diphone_arry = (unsigned char*)malloc(b_er_raw_len * sizeof(unsigned char));
	diphone_arry = b_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ey_raw_len * sizeof(unsigned char));
	diphone_arry = b_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-f")==0) { 
	diphone_arry = (unsigned char*)malloc(b_f_raw_len * sizeof(unsigned char));
	diphone_arry = b_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-g")==0) { 
	diphone_arry = (unsigned char*)malloc(b_g_raw_len * sizeof(unsigned char));
	diphone_arry = b_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_hh_raw_len * sizeof(unsigned char));
	diphone_arry = b_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ih_raw_len * sizeof(unsigned char));
	diphone_arry = b_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(b_iy_raw_len * sizeof(unsigned char));
	diphone_arry = b_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_jh_raw_len * sizeof(unsigned char));
	diphone_arry = b_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-k")==0) { 
	diphone_arry = (unsigned char*)malloc(b_k_raw_len * sizeof(unsigned char));
	diphone_arry = b_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-l")==0) { 
	diphone_arry = (unsigned char*)malloc(b_l_raw_len * sizeof(unsigned char));
	diphone_arry = b_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-m")==0) { 
	diphone_arry = (unsigned char*)malloc(b_m_raw_len * sizeof(unsigned char));
	diphone_arry = b_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-n")==0) { 
	diphone_arry = (unsigned char*)malloc(b_n_raw_len * sizeof(unsigned char));
	diphone_arry = b_n_raw;
	
	}
	
	if (g_strcmp0(diphone_str,"b-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(b_ow_raw_len * sizeof(unsigned char));
	diphone_arry = b_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(b_oy_raw_len * sizeof(unsigned char));
	diphone_arry = b_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-p")==0) { 
	diphone_arry = (unsigned char*)malloc(b_p_raw_len * sizeof(unsigned char));
	diphone_arry = b_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(b_pau_raw_len * sizeof(unsigned char));
	diphone_arry = b_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-r")==0) { 
	diphone_arry = (unsigned char*)malloc(b_r_raw_len * sizeof(unsigned char));
	diphone_arry = b_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-s")==0) { 
	diphone_arry = (unsigned char*)malloc(b_s_raw_len * sizeof(unsigned char));
	diphone_arry = b_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_sh_raw_len * sizeof(unsigned char));
	diphone_arry = b_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-t")==0) { 
	diphone_arry = (unsigned char*)malloc(b_t_raw_len * sizeof(unsigned char));
	diphone_arry = b_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-th")==0) { 
	diphone_arry = (unsigned char*)malloc(b_th_raw_len * sizeof(unsigned char));
	diphone_arry = b_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"b-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_uh_raw_len * sizeof(unsigned char));
	diphone_arry = b_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(b_uw_raw_len * sizeof(unsigned char));
	diphone_arry = b_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-v")==0) { 
	diphone_arry = (unsigned char*)malloc(b_v_raw_len * sizeof(unsigned char));
	diphone_arry = b_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-w")==0) { 
	diphone_arry = (unsigned char*)malloc(b_w_raw_len * sizeof(unsigned char));
	diphone_arry = b_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-y")==0) { 
	diphone_arry = (unsigned char*)malloc(b_y_raw_len * sizeof(unsigned char));
	diphone_arry = b_y_raw;
	
	}	
	if (g_strcmp0(diphone_str,"b-z")==0) { 
	diphone_arry = (unsigned char*)malloc(b_z_raw_len * sizeof(unsigned char));
	diphone_arry = b_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"b-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(b_zh_raw_len * sizeof(unsigned char));
	diphone_arry = b_zh_raw;	
	}
	
		
	//ch diphones
	if (g_strcmp0(diphone_str,"ch-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ch_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ch_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_b_raw_len * sizeof(unsigned char));
	diphone_arry = ch_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_d_raw_len * sizeof(unsigned char));
	diphone_arry = ch_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_er_raw_len * sizeof(unsigned char));
	diphone_arry = ch_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_f_raw_len * sizeof(unsigned char));
	diphone_arry = ch_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_g_raw_len * sizeof(unsigned char));
	diphone_arry = ch_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ch_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_k_raw_len * sizeof(unsigned char));
	diphone_arry = ch_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_l_raw_len * sizeof(unsigned char));
	diphone_arry = ch_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_m_raw_len * sizeof(unsigned char));
	diphone_arry = ch_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_n_raw_len * sizeof(unsigned char));
	diphone_arry = ch_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ch_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ch_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_p_raw_len * sizeof(unsigned char));
	diphone_arry = ch_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ch_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_r_raw_len * sizeof(unsigned char));
	diphone_arry = ch_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_s_raw_len * sizeof(unsigned char));
	diphone_arry = ch_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_t_raw_len * sizeof(unsigned char));
	diphone_arry = ch_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_th_raw_len * sizeof(unsigned char));
	diphone_arry = ch_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ch-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ch_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_v_raw_len * sizeof(unsigned char));
	diphone_arry = ch_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_w_raw_len * sizeof(unsigned char));
	diphone_arry = ch_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_y_raw_len * sizeof(unsigned char));
	diphone_arry = ch_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_z_raw_len * sizeof(unsigned char));
	diphone_arry = ch_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ch-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ch_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ch_zh_raw;	
	}
	
	//d diphones
	if (g_strcmp0(diphone_str,"d-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(d_aa_raw_len * sizeof(unsigned char));
	diphone_arry = d_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ae_raw_len * sizeof(unsigned char));
	diphone_arry = d_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ah_raw_len * sizeof(unsigned char));
	diphone_arry = d_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ao_raw_len * sizeof(unsigned char));
	diphone_arry = d_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(d_aw_raw_len * sizeof(unsigned char));
	diphone_arry = d_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ax_raw_len * sizeof(unsigned char));
	diphone_arry = d_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ay_raw_len * sizeof(unsigned char));
	diphone_arry = d_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-b")==0) { 
	diphone_arry = (unsigned char*)malloc(d_b_raw_len * sizeof(unsigned char));
	diphone_arry = d_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ch_raw_len * sizeof(unsigned char));
	diphone_arry = d_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-d")==0) { 
	diphone_arry = (unsigned char*)malloc(d_d_raw_len * sizeof(unsigned char));
	diphone_arry = d_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_dh_raw_len * sizeof(unsigned char));
	diphone_arry = d_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_eh_raw_len * sizeof(unsigned char));
	diphone_arry = d_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-er")==0) { 
	diphone_arry = (unsigned char*)malloc(d_er_raw_len * sizeof(unsigned char));
	diphone_arry = d_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ey_raw_len * sizeof(unsigned char));
	diphone_arry = d_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-f")==0) { 
	diphone_arry = (unsigned char*)malloc(d_f_raw_len * sizeof(unsigned char));
	diphone_arry = d_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-g")==0) { 
	diphone_arry = (unsigned char*)malloc(d_g_raw_len * sizeof(unsigned char));
	diphone_arry = d_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_hh_raw_len * sizeof(unsigned char));
	diphone_arry = d_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ih_raw_len * sizeof(unsigned char));
	diphone_arry = d_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(d_iy_raw_len * sizeof(unsigned char));
	diphone_arry = d_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_jh_raw_len * sizeof(unsigned char));
	diphone_arry = d_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-k")==0) { 
	diphone_arry = (unsigned char*)malloc(d_k_raw_len * sizeof(unsigned char));
	diphone_arry = d_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-l")==0) { 
	diphone_arry = (unsigned char*)malloc(d_l_raw_len * sizeof(unsigned char));
	diphone_arry = d_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-m")==0) { 
	diphone_arry = (unsigned char*)malloc(d_m_raw_len * sizeof(unsigned char));
	diphone_arry = d_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-n")==0) { 
	diphone_arry = (unsigned char*)malloc(d_n_raw_len * sizeof(unsigned char));
	diphone_arry = d_n_raw;
	
	}
		
	if (g_strcmp0(diphone_str,"d-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(d_ow_raw_len * sizeof(unsigned char));
	diphone_arry = d_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(d_oy_raw_len * sizeof(unsigned char));
	diphone_arry = d_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-p")==0) { 
	diphone_arry = (unsigned char*)malloc(d_p_raw_len * sizeof(unsigned char));
	diphone_arry = d_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(d_pau_raw_len * sizeof(unsigned char));
	diphone_arry = d_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-r")==0) { 
	diphone_arry = (unsigned char*)malloc(d_r_raw_len * sizeof(unsigned char));
	diphone_arry = d_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-s")==0) { 
	diphone_arry = (unsigned char*)malloc(d_s_raw_len * sizeof(unsigned char));
	diphone_arry = d_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_sh_raw_len * sizeof(unsigned char));
	diphone_arry = d_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-t")==0) { 
	diphone_arry = (unsigned char*)malloc(d_t_raw_len * sizeof(unsigned char));
	diphone_arry = d_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-th")==0) { 
	diphone_arry = (unsigned char*)malloc(d_th_raw_len * sizeof(unsigned char));
	diphone_arry = d_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"d-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_uh_raw_len * sizeof(unsigned char));
	diphone_arry = d_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(d_uw_raw_len * sizeof(unsigned char));
	diphone_arry = d_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-v")==0) { 
	diphone_arry = (unsigned char*)malloc(d_v_raw_len * sizeof(unsigned char));
	diphone_arry = d_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-w")==0) { 
	diphone_arry = (unsigned char*)malloc(d_w_raw_len * sizeof(unsigned char));
	diphone_arry = d_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-y")==0) { 
	diphone_arry = (unsigned char*)malloc(d_y_raw_len * sizeof(unsigned char));
	diphone_arry = d_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-z")==0) { 
	diphone_arry = (unsigned char*)malloc(d_z_raw_len * sizeof(unsigned char));
	diphone_arry = d_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"d-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(d_zh_raw_len * sizeof(unsigned char));
	diphone_arry = d_zh_raw;
	
	}
	
	//dh diphones
	if (g_strcmp0(diphone_str,"dh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = dh_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ah_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_aw_raw_len * sizeof(unsigned char));
	diphone_arry = dh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-b")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_b_raw_len * sizeof(unsigned char));
	diphone_arry = dh_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-d")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_d_raw_len * sizeof(unsigned char));
	diphone_arry = dh_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_dh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-er")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_er_raw_len * sizeof(unsigned char));
	diphone_arry = dh_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-f")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_f_raw_len * sizeof(unsigned char));
	diphone_arry = dh_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-g")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_g_raw_len * sizeof(unsigned char));
	diphone_arry = dh_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_hh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_iy_raw_len * sizeof(unsigned char));
	diphone_arry = dh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_jh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-k")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_k_raw_len * sizeof(unsigned char));
	diphone_arry = dh_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-l")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_l_raw_len * sizeof(unsigned char));
	diphone_arry = dh_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-m")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_m_raw_len * sizeof(unsigned char));
	diphone_arry = dh_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-n")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_n_raw_len * sizeof(unsigned char));
	diphone_arry = dh_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = dh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = dh_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-p")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_p_raw_len * sizeof(unsigned char));
	diphone_arry = dh_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_pau_raw_len * sizeof(unsigned char));
	diphone_arry = dh_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-r")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_r_raw_len * sizeof(unsigned char));
	diphone_arry = dh_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-s")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_s_raw_len * sizeof(unsigned char));
	diphone_arry = dh_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_sh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-t")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_t_raw_len * sizeof(unsigned char));
	diphone_arry = dh_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-th")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_th_raw_len * sizeof(unsigned char));
	diphone_arry = dh_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"dh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = dh_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-v")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_v_raw_len * sizeof(unsigned char));
	diphone_arry = dh_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-w")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_w_raw_len * sizeof(unsigned char));
	diphone_arry = dh_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-y")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_y_raw_len * sizeof(unsigned char));
	diphone_arry = dh_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-z")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_z_raw_len * sizeof(unsigned char));
	diphone_arry = dh_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"dh-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(dh_zh_raw_len * sizeof(unsigned char));
	diphone_arry = dh_zh_raw;
	
	}
	
	//eh diphones
	if (g_strcmp0(diphone_str,"eh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = eh_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ah_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_aw_raw_len * sizeof(unsigned char));
	diphone_arry = eh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-b")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_b_raw_len * sizeof(unsigned char));
	diphone_arry = eh_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-d")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_d_raw_len * sizeof(unsigned char));
	diphone_arry = eh_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_dh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-er")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_er_raw_len * sizeof(unsigned char));
	diphone_arry = eh_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-f")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_f_raw_len * sizeof(unsigned char));
	diphone_arry = eh_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-g")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_g_raw_len * sizeof(unsigned char));
	diphone_arry = eh_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_hh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_iy_raw_len * sizeof(unsigned char));
	diphone_arry = eh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_jh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-k")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_k_raw_len * sizeof(unsigned char));
	diphone_arry = eh_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-l")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_l_raw_len * sizeof(unsigned char));
	diphone_arry = eh_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-m")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_m_raw_len * sizeof(unsigned char));
	diphone_arry = eh_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-n")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_n_raw_len * sizeof(unsigned char));
	diphone_arry = eh_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ng_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = eh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = eh_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-p")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_p_raw_len * sizeof(unsigned char));
	diphone_arry = eh_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_pau_raw_len * sizeof(unsigned char));
	diphone_arry = eh_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-r")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_r_raw_len * sizeof(unsigned char));
	diphone_arry = eh_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-s")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_s_raw_len * sizeof(unsigned char));
	diphone_arry = eh_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_sh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-t")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_t_raw_len * sizeof(unsigned char));
	diphone_arry = eh_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-th")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_th_raw_len * sizeof(unsigned char));
	diphone_arry = eh_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"eh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = eh_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-v")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_v_raw_len * sizeof(unsigned char));
	diphone_arry = eh_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-w")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_w_raw_len * sizeof(unsigned char));
	diphone_arry = eh_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-y")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_y_raw_len * sizeof(unsigned char));
	diphone_arry = eh_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-z")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_z_raw_len * sizeof(unsigned char));
	diphone_arry = eh_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"eh-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_zh_raw_len * sizeof(unsigned char));
	diphone_arry = eh_zh_raw;	
	}
	
	
	// er diphones
	
	if (g_strcmp0(diphone_str,"er-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(er_aa_raw_len * sizeof(unsigned char));
	diphone_arry = er_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ae_raw_len * sizeof(unsigned char));
	diphone_arry = er_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ah_raw_len * sizeof(unsigned char));
	diphone_arry = er_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ao_raw_len * sizeof(unsigned char));
	diphone_arry = er_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(er_aw_raw_len * sizeof(unsigned char));
	diphone_arry = er_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ax_raw_len * sizeof(unsigned char));
	diphone_arry = er_ax_raw;	
	}
	
	if (g_strcmp0(diphone_str,"er-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ay_raw_len * sizeof(unsigned char));
	diphone_arry = er_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-b")==0) { 
	diphone_arry = (unsigned char*)malloc(er_b_raw_len * sizeof(unsigned char));
	diphone_arry = er_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ch_raw_len * sizeof(unsigned char));
	diphone_arry = er_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-d")==0) { 
	diphone_arry = (unsigned char*)malloc(er_d_raw_len * sizeof(unsigned char));
	diphone_arry = er_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_dh_raw_len * sizeof(unsigned char));
	diphone_arry = er_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_eh_raw_len * sizeof(unsigned char));
	diphone_arry = er_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-er")==0) { 
	diphone_arry = (unsigned char*)malloc(er_er_raw_len * sizeof(unsigned char));
	diphone_arry = er_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ey_raw_len * sizeof(unsigned char));
	diphone_arry = er_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-f")==0) { 
	diphone_arry = (unsigned char*)malloc(er_f_raw_len * sizeof(unsigned char));
	diphone_arry = er_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-g")==0) { 
	diphone_arry = (unsigned char*)malloc(er_g_raw_len * sizeof(unsigned char));
	diphone_arry = er_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_hh_raw_len * sizeof(unsigned char));
	diphone_arry = er_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(er_ih_raw_len * sizeof(unsigned char));
	diphone_arry = er_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(er_iy_raw_len * sizeof(unsigned char));
	diphone_arry = er_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_jh_raw_len * sizeof(unsigned char));
	diphone_arry = er_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-k")==0) { 
	diphone_arry = (unsigned char*)malloc(er_k_raw_len * sizeof(unsigned char));
	diphone_arry = er_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-l")==0) { 
	diphone_arry = (unsigned char*)malloc(er_l_raw_len * sizeof(unsigned char));
	diphone_arry = er_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-m")==0) { 
	diphone_arry = (unsigned char*)malloc(er_m_raw_len * sizeof(unsigned char));
	diphone_arry = er_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-n")==0) { 
	diphone_arry = (unsigned char*)malloc(er_n_raw_len * sizeof(unsigned char));
	diphone_arry = er_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-ow")==0) {
	diphone_arry = (unsigned char*)malloc(er_ow_raw_len * sizeof(unsigned char));
	diphone_arry = er_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(er_oy_raw_len * sizeof(unsigned char));
	diphone_arry = er_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-p")==0) { 
	diphone_arry = (unsigned char*)malloc(er_p_raw_len * sizeof(unsigned char));
	diphone_arry = er_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(er_pau_raw_len * sizeof(unsigned char));
	diphone_arry = er_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-r")==0) { 
	diphone_arry = (unsigned char*)malloc(er_r_raw_len * sizeof(unsigned char));
	diphone_arry = er_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-s")==0) { 
	diphone_arry = (unsigned char*)malloc(er_s_raw_len * sizeof(unsigned char));
	diphone_arry = er_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_sh_raw_len * sizeof(unsigned char));
	diphone_arry = er_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-t")==0) { 
	diphone_arry = (unsigned char*)malloc(er_t_raw_len * sizeof(unsigned char));
	diphone_arry = er_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-th")==0) { 
	diphone_arry = (unsigned char*)malloc(er_th_raw_len * sizeof(unsigned char));
	diphone_arry = er_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"er-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_uh_raw_len * sizeof(unsigned char));
	diphone_arry = er_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(er_uw_raw_len * sizeof(unsigned char));
	diphone_arry = er_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-v")==0) { 
	diphone_arry = (unsigned char*)malloc(er_v_raw_len * sizeof(unsigned char));
	diphone_arry = er_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-w")==0) { 
	diphone_arry = (unsigned char*)malloc(er_w_raw_len * sizeof(unsigned char));
	diphone_arry = er_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-y")==0) { 
	diphone_arry = (unsigned char*)malloc(er_y_raw_len * sizeof(unsigned char));
	diphone_arry = er_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-z")==0) { 
	diphone_arry = (unsigned char*)malloc(er_z_raw_len * sizeof(unsigned char));
	diphone_arry = er_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"er-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(er_zh_raw_len * sizeof(unsigned char));
	diphone_arry = er_zh_raw;	
	}
	
	//ey diphones
	if (g_strcmp0(diphone_str,"ey-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ey_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ey_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_b_raw_len * sizeof(unsigned char));
	diphone_arry = ey_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_d_raw_len * sizeof(unsigned char));
	diphone_arry = ey_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(eh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_er_raw_len * sizeof(unsigned char));
	diphone_arry = ey_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_f_raw_len * sizeof(unsigned char));
	diphone_arry = ey_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_g_raw_len * sizeof(unsigned char));
	diphone_arry = ey_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ey_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_k_raw_len * sizeof(unsigned char));
	diphone_arry = ey_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_l_raw_len * sizeof(unsigned char));
	diphone_arry = ey_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_m_raw_len * sizeof(unsigned char));
	diphone_arry = ey_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_n_raw_len * sizeof(unsigned char));
	diphone_arry = ey_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ey_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ey_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_p_raw_len * sizeof(unsigned char));
	diphone_arry = ey_p_raw;	
	}
	
	if (g_strcmp0(diphone_str,"ey-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ey_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_r_raw_len * sizeof(unsigned char));
	diphone_arry = ey_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_s_raw_len * sizeof(unsigned char));
	diphone_arry = ey_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_t_raw_len * sizeof(unsigned char));
	diphone_arry = ey_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-th")==0) {
	diphone_arry = (unsigned char*)malloc(ey_th_raw_len * sizeof(unsigned char));
	diphone_arry = ey_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ey-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ey_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_v_raw_len * sizeof(unsigned char));
	diphone_arry = ey_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_w_raw_len * sizeof(unsigned char));
	diphone_arry = ey_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_y_raw_len * sizeof(unsigned char));
	diphone_arry = ey_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_z_raw_len * sizeof(unsigned char));
	diphone_arry = ey_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ey-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ey_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ey_zh_raw;	
	}
	
	//f diphones
	if (g_strcmp0(diphone_str,"f-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(f_aa_raw_len * sizeof(unsigned char));
	diphone_arry = f_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ae_raw_len * sizeof(unsigned char));
	diphone_arry = f_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ah_raw_len * sizeof(unsigned char));
	diphone_arry = f_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ao_raw_len * sizeof(unsigned char));
	diphone_arry = f_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(f_aw_raw_len * sizeof(unsigned char));
	diphone_arry = f_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ax_raw_len * sizeof(unsigned char));
	diphone_arry = f_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ay_raw_len * sizeof(unsigned char));
	diphone_arry = f_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-b")==0) { 
	diphone_arry = (unsigned char*)malloc(f_b_raw_len * sizeof(unsigned char));
	diphone_arry = f_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ch_raw_len * sizeof(unsigned char));
	diphone_arry = f_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-d")==0) { 
	diphone_arry = (unsigned char*)malloc(f_d_raw_len * sizeof(unsigned char));
	diphone_arry = f_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_dh_raw_len * sizeof(unsigned char));
	diphone_arry = f_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_eh_raw_len * sizeof(unsigned char));
	diphone_arry = f_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-er")==0) { 
	diphone_arry = (unsigned char*)malloc(f_er_raw_len * sizeof(unsigned char));
	diphone_arry = f_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ey_raw_len * sizeof(unsigned char));
	diphone_arry = f_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-f")==0) { 
	diphone_arry = (unsigned char*)malloc(f_f_raw_len * sizeof(unsigned char));
	diphone_arry = f_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-g")==0) { 
	diphone_arry = (unsigned char*)malloc(f_g_raw_len * sizeof(unsigned char));
	diphone_arry = f_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_hh_raw_len * sizeof(unsigned char));
	diphone_arry = f_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(f_ih_raw_len * sizeof(unsigned char));
	diphone_arry = f_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(f_iy_raw_len * sizeof(unsigned char));
	diphone_arry = f_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_jh_raw_len * sizeof(unsigned char));
	diphone_arry = f_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-k")==0) { 
	diphone_arry = (unsigned char*)malloc(f_k_raw_len * sizeof(unsigned char));
	diphone_arry = f_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-l")==0) { 
	diphone_arry = (unsigned char*)malloc(f_l_raw_len * sizeof(unsigned char));
	diphone_arry = f_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-m")==0) { 
	diphone_arry = (unsigned char*)malloc(f_m_raw_len * sizeof(unsigned char));
	diphone_arry = f_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-n")==0) { 
	diphone_arry = (unsigned char*)malloc(f_n_raw_len * sizeof(unsigned char));
	diphone_arry = f_n_raw;
	
	}
	
	if (g_strcmp0(diphone_str,"f-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(f_oy_raw_len * sizeof(unsigned char));
	diphone_arry = f_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-p")==0) { 
	diphone_arry = (unsigned char*)malloc(f_p_raw_len * sizeof(unsigned char));
	diphone_arry = f_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(f_pau_raw_len * sizeof(unsigned char));
	diphone_arry = f_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-r")==0) { 
	diphone_arry = (unsigned char*)malloc(f_r_raw_len * sizeof(unsigned char));
	diphone_arry = f_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-s")==0) { 
	diphone_arry = (unsigned char*)malloc(f_s_raw_len * sizeof(unsigned char));
	diphone_arry = f_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_sh_raw_len * sizeof(unsigned char));
	diphone_arry = f_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-t")==0) { 
	diphone_arry = (unsigned char*)malloc(f_t_raw_len * sizeof(unsigned char));
	diphone_arry = f_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-th")==0) { 
	diphone_arry = (unsigned char*)malloc(f_th_raw_len * sizeof(unsigned char));
	diphone_arry = f_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"f-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_uh_raw_len * sizeof(unsigned char));
	diphone_arry = f_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(f_uw_raw_len * sizeof(unsigned char));
	diphone_arry = f_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-v")==0) { 
	diphone_arry = (unsigned char*)malloc(f_v_raw_len * sizeof(unsigned char));
	diphone_arry = f_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-w")==0) { 
	diphone_arry = (unsigned char*)malloc(f_w_raw_len * sizeof(unsigned char));
	diphone_arry = f_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-y")==0) { 
	diphone_arry = (unsigned char*)malloc(f_y_raw_len * sizeof(unsigned char));
	diphone_arry = f_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-z")==0) { 
	diphone_arry = (unsigned char*)malloc(f_z_raw_len * sizeof(unsigned char));
	diphone_arry = f_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"f-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(f_zh_raw_len * sizeof(unsigned char));
	diphone_arry = f_zh_raw;	
	}
	
	//g diphones
	if (g_strcmp0(diphone_str,"g-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(g_aa_raw_len * sizeof(unsigned char));
	diphone_arry = g_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ae_raw_len * sizeof(unsigned char));
	diphone_arry = g_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ah_raw_len * sizeof(unsigned char));
	diphone_arry = g_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ao_raw_len * sizeof(unsigned char));
	diphone_arry = g_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(g_aw_raw_len * sizeof(unsigned char));
	diphone_arry = g_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ax_raw_len * sizeof(unsigned char));
	diphone_arry = g_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ay_raw_len * sizeof(unsigned char));
	diphone_arry = g_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-b")==0) { 
	diphone_arry = (unsigned char*)malloc(g_b_raw_len * sizeof(unsigned char));
	diphone_arry = g_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ch_raw_len * sizeof(unsigned char));
	diphone_arry = g_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-d")==0) {
	diphone_arry = (unsigned char*)malloc(g_d_raw_len * sizeof(unsigned char));
	diphone_arry = g_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_dh_raw_len * sizeof(unsigned char));
	diphone_arry = g_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_eh_raw_len * sizeof(unsigned char));
	diphone_arry = g_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-er")==0) { 
	diphone_arry = (unsigned char*)malloc(g_er_raw_len * sizeof(unsigned char));
	diphone_arry = g_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ey_raw_len * sizeof(unsigned char));
	diphone_arry = g_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-f")==0) { 
	diphone_arry = (unsigned char*)malloc(g_f_raw_len * sizeof(unsigned char));
	diphone_arry = g_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-g")==0) { 
	diphone_arry = (unsigned char*)malloc(g_g_raw_len * sizeof(unsigned char));
	diphone_arry = g_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_hh_raw_len * sizeof(unsigned char));
	diphone_arry = g_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ih_raw_len * sizeof(unsigned char));
	diphone_arry = g_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(g_iy_raw_len * sizeof(unsigned char));
	diphone_arry = g_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_jh_raw_len * sizeof(unsigned char));
	diphone_arry = g_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-k")==0) { 
	diphone_arry = (unsigned char*)malloc(g_k_raw_len * sizeof(unsigned char));
	diphone_arry = g_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-l")==0) { 
	diphone_arry = (unsigned char*)malloc(g_l_raw_len * sizeof(unsigned char));
	diphone_arry = g_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-m")==0) { 
	diphone_arry = (unsigned char*)malloc(g_m_raw_len * sizeof(unsigned char));
	diphone_arry = g_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-n")==0) { 
	diphone_arry = (unsigned char*)malloc(g_n_raw_len * sizeof(unsigned char));
	diphone_arry = g_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(g_ow_raw_len * sizeof(unsigned char));
	diphone_arry = g_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(g_oy_raw_len * sizeof(unsigned char));
	diphone_arry = g_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-p")==0) { 
	diphone_arry = (unsigned char*)malloc(g_p_raw_len * sizeof(unsigned char));
	diphone_arry = g_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(g_pau_raw_len * sizeof(unsigned char));
	diphone_arry = g_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-r")==0) { 
	diphone_arry = (unsigned char*)malloc(g_r_raw_len * sizeof(unsigned char));
	diphone_arry = g_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-s")==0) { 
	diphone_arry = (unsigned char*)malloc(g_s_raw_len * sizeof(unsigned char));
	diphone_arry = g_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_sh_raw_len * sizeof(unsigned char));
	diphone_arry = g_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-t")==0) { 
	diphone_arry = (unsigned char*)malloc(g_t_raw_len * sizeof(unsigned char));
	diphone_arry = g_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-th")==0) { 
	diphone_arry = (unsigned char*)malloc(g_th_raw_len * sizeof(unsigned char));
	diphone_arry = g_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"g-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_uh_raw_len * sizeof(unsigned char));
	diphone_arry = g_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(g_uw_raw_len * sizeof(unsigned char));
	diphone_arry = g_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-v")==0) { 
	diphone_arry = (unsigned char*)malloc(g_v_raw_len * sizeof(unsigned char));
	diphone_arry = g_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-w")==0) { 
	diphone_arry = (unsigned char*)malloc(g_w_raw_len * sizeof(unsigned char));
	diphone_arry = g_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-y")==0) { 
	diphone_arry = (unsigned char*)malloc(g_y_raw_len * sizeof(unsigned char));
	diphone_arry = g_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-z")==0) { 
	diphone_arry = (unsigned char*)malloc(g_z_raw_len * sizeof(unsigned char));
	diphone_arry = g_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"g-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(g_zh_raw_len * sizeof(unsigned char));
	diphone_arry = g_zh_raw;	
	}
	
		
	//hh diphones
	if (g_strcmp0(diphone_str,"hh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = hh_aa_raw;	
	}
	
	if (g_strcmp0(diphone_str,"hh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ah_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_aw_raw_len * sizeof(unsigned char));
	diphone_arry = hh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = hh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_iy_raw_len * sizeof(unsigned char));
	diphone_arry =hh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = hh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = hh_oy_raw;
	
	}
	
	if (g_strcmp0(diphone_str,"hh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = hh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"hh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(hh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = hh_uw_raw;
	
	}
	
	
	//ih diphones
	if (g_strcmp0(diphone_str,"ih-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ih_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ih_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_b_raw_len * sizeof(unsigned char));
	diphone_arry = ih_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_d_raw_len * sizeof(unsigned char));
	diphone_arry = ih_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_er_raw_len * sizeof(unsigned char));
	diphone_arry = ih_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_f_raw_len * sizeof(unsigned char));
	diphone_arry = ih_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_g_raw_len * sizeof(unsigned char));
	diphone_arry = ih_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ih_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_k_raw_len * sizeof(unsigned char));
	diphone_arry = ih_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_l_raw_len * sizeof(unsigned char));
	diphone_arry = ih_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_m_raw_len * sizeof(unsigned char));
	diphone_arry = ih_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_n_raw_len * sizeof(unsigned char));
	diphone_arry = ih_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ih_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ih_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_p_raw_len * sizeof(unsigned char));
	diphone_arry = ih_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ih_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_r_raw_len * sizeof(unsigned char));
	diphone_arry = ih_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_s_raw_len * sizeof(unsigned char));
	diphone_arry = ih_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_t_raw_len * sizeof(unsigned char));
	diphone_arry = ih_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_th_raw_len * sizeof(unsigned char));
	diphone_arry = ih_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ih-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ih_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_v_raw_len * sizeof(unsigned char));
	diphone_arry = ih_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_w_raw_len * sizeof(unsigned char));
	diphone_arry = ih_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_y_raw_len * sizeof(unsigned char));
	diphone_arry = ih_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_z_raw_len * sizeof(unsigned char));
	diphone_arry = ih_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ih-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ih_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ih_zh_raw;	
	}
	
	
	//iy diphones
	if (g_strcmp0(diphone_str,"iy-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_aa_raw_len * sizeof(unsigned char));
	diphone_arry = iy_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ae_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ah_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ao_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_aw_raw_len * sizeof(unsigned char));
	diphone_arry = iy_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ax_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ay_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-b")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_b_raw_len * sizeof(unsigned char));
	diphone_arry = iy_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ch_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-d")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_d_raw_len * sizeof(unsigned char));
	diphone_arry = iy_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_dh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_eh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-er")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_er_raw_len * sizeof(unsigned char));
	diphone_arry = iy_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ey_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-f")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_f_raw_len * sizeof(unsigned char));
	diphone_arry = iy_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-g")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_g_raw_len * sizeof(unsigned char));
	diphone_arry = iy_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_hh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ih_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_iy_raw_len * sizeof(unsigned char));
	diphone_arry = iy_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_jh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-k")==0) {
	diphone_arry = (unsigned char*)malloc(iy_k_raw_len * sizeof(unsigned char));
	diphone_arry = iy_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-l")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_l_raw_len * sizeof(unsigned char));
	diphone_arry =iy_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-m")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_m_raw_len * sizeof(unsigned char));
	diphone_arry = iy_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-n")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_n_raw_len * sizeof(unsigned char));
	diphone_arry = iy_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ng_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_ow_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-oy")==0) {
	diphone_arry = (unsigned char*)malloc(iy_ow_raw_len * sizeof(unsigned char));
	diphone_arry = iy_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-p")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_p_raw_len * sizeof(unsigned char));
	diphone_arry = iy_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_pau_raw_len * sizeof(unsigned char));
	diphone_arry = iy_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-r")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_r_raw_len * sizeof(unsigned char));
	diphone_arry = iy_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-s")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_s_raw_len * sizeof(unsigned char));
	diphone_arry = iy_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_sh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-t")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_t_raw_len * sizeof(unsigned char));
	diphone_arry = iy_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-th")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_th_raw_len * sizeof(unsigned char));
	diphone_arry = iy_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"iy-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_uh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_uw_raw_len * sizeof(unsigned char));
	diphone_arry = iy_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-v")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_v_raw_len * sizeof(unsigned char));
	diphone_arry = iy_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-w")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_w_raw_len * sizeof(unsigned char));
	diphone_arry = iy_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-y")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_y_raw_len * sizeof(unsigned char));
	diphone_arry = iy_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-z")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_z_raw_len * sizeof(unsigned char));
	diphone_arry = iy_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"iy-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(iy_zh_raw_len * sizeof(unsigned char));
	diphone_arry = iy_zh_raw;	
	}
	
	//jh diphones
	if (g_strcmp0(diphone_str,"jh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = jh_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ah_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_aw_raw_len * sizeof(unsigned char));
	diphone_arry =jh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-b")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_b_raw_len * sizeof(unsigned char));
	diphone_arry = jh_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-d")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_d_raw_len * sizeof(unsigned char));
	diphone_arry = jh_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_dh_raw_len * sizeof(unsigned char));
	diphone_arry =jh_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = jh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-er")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_er_raw_len * sizeof(unsigned char));
	diphone_arry = jh_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-f")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_f_raw_len * sizeof(unsigned char));
	diphone_arry = jh_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-g")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_g_raw_len * sizeof(unsigned char));
	diphone_arry = jh_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_hh_raw_len * sizeof(unsigned char));
	diphone_arry = jh_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_iy_raw_len * sizeof(unsigned char));
	diphone_arry = jh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_jh_raw_len * sizeof(unsigned char));
	diphone_arry = jh_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-k")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_k_raw_len * sizeof(unsigned char));
	diphone_arry = jh_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-l")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_l_raw_len * sizeof(unsigned char));
	diphone_arry = jh_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-m")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_m_raw_len * sizeof(unsigned char));
	diphone_arry = jh_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-n")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_n_raw_len * sizeof(unsigned char));
	diphone_arry = jh_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = jh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = jh_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-p")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_p_raw_len * sizeof(unsigned char));
	diphone_arry = jh_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_pau_raw_len * sizeof(unsigned char));
	diphone_arry = jh_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-r")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_r_raw_len * sizeof(unsigned char));
	diphone_arry = jh_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-s")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_s_raw_len * sizeof(unsigned char));
	diphone_arry = jh_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_sh_raw_len * sizeof(unsigned char));
	diphone_arry = jh_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-t")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_t_raw_len * sizeof(unsigned char));
	diphone_arry = jh_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-th")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_th_raw_len * sizeof(unsigned char));
	diphone_arry = jh_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"jh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = jh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = jh_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-v")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_v_raw_len * sizeof(unsigned char));
	diphone_arry = jh_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-w")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_w_raw_len * sizeof(unsigned char));
	diphone_arry = jh_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-y")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_y_raw_len * sizeof(unsigned char));
	diphone_arry = jh_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-z")==0) {
	diphone_arry = (unsigned char*)malloc(jh_z_raw_len * sizeof(unsigned char));
	diphone_arry = jh_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"jh-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(jh_zh_raw_len * sizeof(unsigned char));
	diphone_arry = jh_zh_raw;	
	}
	
	//k diphones
	
	if (g_strcmp0(diphone_str,"k-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(k_aa_raw_len * sizeof(unsigned char));
	diphone_arry = k_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ae_raw_len * sizeof(unsigned char));
	diphone_arry = k_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ah_raw_len * sizeof(unsigned char));
	diphone_arry = k_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ao")==0) {
	diphone_arry = (unsigned char*)malloc(k_ao_raw_len * sizeof(unsigned char));
	diphone_arry = k_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(k_aw_raw_len * sizeof(unsigned char));
	diphone_arry = k_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ax_raw_len * sizeof(unsigned char));
	diphone_arry = k_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ay_raw_len * sizeof(unsigned char));
	diphone_arry = k_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-b")==0) { 
	diphone_arry = (unsigned char*)malloc(k_b_raw_len * sizeof(unsigned char));
	diphone_arry = k_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ch_raw_len * sizeof(unsigned char));
	diphone_arry = k_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-d")==0) { 
	diphone_arry = (unsigned char*)malloc(k_d_raw_len * sizeof(unsigned char));
	diphone_arry = k_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_dh_raw_len * sizeof(unsigned char));
	diphone_arry = k_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_eh_raw_len * sizeof(unsigned char));
	diphone_arry = k_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-er")==0) { 
	diphone_arry = (unsigned char*)malloc(k_er_raw_len * sizeof(unsigned char));
	diphone_arry = k_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ey_raw_len * sizeof(unsigned char));
	diphone_arry = k_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-f")==0) { 
	diphone_arry = (unsigned char*)malloc(k_f_raw_len * sizeof(unsigned char));
	diphone_arry = k_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-g")==0) { 
	diphone_arry = (unsigned char*)malloc(k_g_raw_len * sizeof(unsigned char));
	diphone_arry = k_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_hh_raw_len * sizeof(unsigned char));
	diphone_arry = k_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ih_raw_len * sizeof(unsigned char));
	diphone_arry = k_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(k_iy_raw_len * sizeof(unsigned char));
	diphone_arry = k_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_jh_raw_len * sizeof(unsigned char));
	diphone_arry = k_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-k")==0) { 
	diphone_arry = (unsigned char*)malloc(k_k_raw_len * sizeof(unsigned char));
	diphone_arry = k_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-l")==0) { 
	diphone_arry = (unsigned char*)malloc(k_l_raw_len * sizeof(unsigned char));
	diphone_arry = k_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-m")==0) { 
	diphone_arry = (unsigned char*)malloc(k_m_raw_len * sizeof(unsigned char));
	diphone_arry = k_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-n")==0) { 
	diphone_arry = (unsigned char*)malloc(k_n_raw_len * sizeof(unsigned char));
	diphone_arry = k_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(k_ow_raw_len * sizeof(unsigned char));
	diphone_arry = k_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(k_oy_raw_len * sizeof(unsigned char));
	diphone_arry = k_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-p")==0) { 
	diphone_arry = (unsigned char*)malloc(k_p_raw_len * sizeof(unsigned char));
	diphone_arry = k_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(k_pau_raw_len * sizeof(unsigned char));
	diphone_arry = k_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-r")==0) { 
	diphone_arry = (unsigned char*)malloc(k_r_raw_len * sizeof(unsigned char));
	diphone_arry = k_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-s")==0) { 
	diphone_arry = (unsigned char*)malloc(k_s_raw_len * sizeof(unsigned char));
	diphone_arry = k_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_sh_raw_len * sizeof(unsigned char));
	diphone_arry = k_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-t")==0) { 
	diphone_arry = (unsigned char*)malloc(k_t_raw_len * sizeof(unsigned char));
	diphone_arry = k_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-th")==0) { 
	diphone_arry = (unsigned char*)malloc(k_th_raw_len * sizeof(unsigned char));
	diphone_arry = k_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"k-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_uh_raw_len * sizeof(unsigned char));
	diphone_arry = k_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(k_uw_raw_len * sizeof(unsigned char));
	diphone_arry = k_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-v")==0) { 
	diphone_arry = (unsigned char*)malloc(k_v_raw_len * sizeof(unsigned char));
	diphone_arry = k_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-w")==0) { 
	diphone_arry = (unsigned char*)malloc(k_w_raw_len * sizeof(unsigned char));
	diphone_arry = k_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-y")==0) { 
	diphone_arry = (unsigned char*)malloc(k_y_raw_len * sizeof(unsigned char));
	diphone_arry = k_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-z")==0) { 
	diphone_arry = (unsigned char*)malloc(k_z_raw_len * sizeof(unsigned char));
	diphone_arry = k_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"k-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(k_zh_raw_len * sizeof(unsigned char));
	diphone_arry = k_zh_raw;	
	}
	
	//l diphones
	if (g_strcmp0(diphone_str,"l-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(l_aa_raw_len * sizeof(unsigned char));
	diphone_arry = l_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ae_raw_len * sizeof(unsigned char));
	diphone_arry = l_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ah_raw_len * sizeof(unsigned char));
	diphone_arry = l_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ao_raw_len * sizeof(unsigned char));
	diphone_arry = l_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(l_aw_raw_len * sizeof(unsigned char));
	diphone_arry = l_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(l_aw_raw_len * sizeof(unsigned char));
	diphone_arry = l_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ay_raw_len * sizeof(unsigned char));
	diphone_arry = l_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-b")==0) { 
	diphone_arry = (unsigned char*)malloc(l_b_raw_len * sizeof(unsigned char));
	diphone_arry = l_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ch_raw_len * sizeof(unsigned char));
	diphone_arry = l_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-d")==0) { 
	diphone_arry = (unsigned char*)malloc(l_d_raw_len * sizeof(unsigned char));
	diphone_arry = l_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_dh_raw_len * sizeof(unsigned char));
	diphone_arry = l_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_eh_raw_len * sizeof(unsigned char));
	diphone_arry = l_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-er")==0) { 
	diphone_arry = (unsigned char*)malloc(l_er_raw_len * sizeof(unsigned char));
	diphone_arry = l_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ey_raw_len * sizeof(unsigned char));
	diphone_arry = l_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-f")==0) { 
	diphone_arry = (unsigned char*)malloc(l_f_raw_len * sizeof(unsigned char));
	diphone_arry = l_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-g")==0) { 
	diphone_arry = (unsigned char*)malloc(l_g_raw_len * sizeof(unsigned char));
	diphone_arry = l_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_hh_raw_len * sizeof(unsigned char));
	diphone_arry =l_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ih_raw_len * sizeof(unsigned char));
	diphone_arry = l_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(l_iy_raw_len * sizeof(unsigned char));
	diphone_arry = l_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_jh_raw_len * sizeof(unsigned char));
	diphone_arry = l_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-k")==0) { 
	diphone_arry = (unsigned char*)malloc(l_k_raw_len * sizeof(unsigned char));
	diphone_arry = l_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-l")==0) { 
	diphone_arry = (unsigned char*)malloc(l_l_raw_len * sizeof(unsigned char));
	diphone_arry = l_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-m")==0) { 
	diphone_arry = (unsigned char*)malloc(l_m_raw_len * sizeof(unsigned char));
	diphone_arry = l_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-n")==0) { 
	diphone_arry = (unsigned char*)malloc(l_n_raw_len * sizeof(unsigned char));
	diphone_arry = l_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(l_ow_raw_len * sizeof(unsigned char));
	diphone_arry = l_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(l_oy_raw_len * sizeof(unsigned char));
	diphone_arry = l_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-p")==0) { 
	diphone_arry = (unsigned char*)malloc(l_p_raw_len * sizeof(unsigned char));
	diphone_arry = l_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(l_pau_raw_len * sizeof(unsigned char));
	diphone_arry = l_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-r")==0) { 
	diphone_arry = (unsigned char*)malloc(l_r_raw_len * sizeof(unsigned char));
	diphone_arry = l_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-s")==0) { 
	diphone_arry = (unsigned char*)malloc(l_s_raw_len * sizeof(unsigned char));
	diphone_arry = l_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_sh_raw_len * sizeof(unsigned char));
	diphone_arry = l_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-t")==0) { 
	diphone_arry = (unsigned char*)malloc(l_t_raw_len * sizeof(unsigned char));
	diphone_arry = l_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-th")==0) { 
	diphone_arry = (unsigned char*)malloc(l_th_raw_len * sizeof(unsigned char));
	diphone_arry = l_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"l-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_uh_raw_len * sizeof(unsigned char));
	diphone_arry = l_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(l_uw_raw_len * sizeof(unsigned char));
	diphone_arry =l_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-v")==0) { 
	diphone_arry = (unsigned char*)malloc(l_v_raw_len * sizeof(unsigned char));
	diphone_arry = l_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-w")==0) { 
	diphone_arry = (unsigned char*)malloc(l_w_raw_len * sizeof(unsigned char));
	diphone_arry = l_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-y")==0) { 
	diphone_arry = (unsigned char*)malloc(l_y_raw_len * sizeof(unsigned char));
	diphone_arry = l_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-z")==0) { 
	diphone_arry = (unsigned char*)malloc(l_z_raw_len * sizeof(unsigned char));
	diphone_arry = l_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"l-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(l_zh_raw_len * sizeof(unsigned char));
	diphone_arry = l_zh_raw;	
	}
	
	//m diphones
	if (g_strcmp0(diphone_str,"m-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(m_aa_raw_len * sizeof(unsigned char));
	diphone_arry = m_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ae_raw_len * sizeof(unsigned char));
	diphone_arry = m_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ah_raw_len * sizeof(unsigned char));
	diphone_arry = m_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ao_raw_len * sizeof(unsigned char));
	diphone_arry = m_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(m_aw_raw_len * sizeof(unsigned char));
	diphone_arry = m_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ax_raw_len * sizeof(unsigned char));
	diphone_arry = m_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ay_raw_len * sizeof(unsigned char));
	diphone_arry = m_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-b")==0) { 
	diphone_arry = (unsigned char*)malloc(m_b_raw_len * sizeof(unsigned char));
	diphone_arry = m_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ch_raw_len * sizeof(unsigned char));
	diphone_arry = m_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-d")==0) { 
	diphone_arry = (unsigned char*)malloc(m_d_raw_len * sizeof(unsigned char));
	diphone_arry = m_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_dh_raw_len * sizeof(unsigned char));
	diphone_arry = m_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_eh_raw_len * sizeof(unsigned char));
	diphone_arry = m_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-er")==0) { 
	diphone_arry = (unsigned char*)malloc(m_er_raw_len * sizeof(unsigned char));
	diphone_arry = m_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ey_raw_len * sizeof(unsigned char));
	diphone_arry = m_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-f")==0) { 
	diphone_arry = (unsigned char*)malloc(m_f_raw_len * sizeof(unsigned char));
	diphone_arry = m_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-g")==0) { 
	diphone_arry = (unsigned char*)malloc(m_g_raw_len * sizeof(unsigned char));
	diphone_arry = m_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_hh_raw_len * sizeof(unsigned char));
	diphone_arry = m_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ih_raw_len * sizeof(unsigned char));
	diphone_arry = m_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(m_iy_raw_len * sizeof(unsigned char));
	diphone_arry = m_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_jh_raw_len * sizeof(unsigned char));
	diphone_arry = m_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-k")==0) { 
	diphone_arry = (unsigned char*)malloc(m_k_raw_len * sizeof(unsigned char));
	diphone_arry = m_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-l")==0) { 
	diphone_arry = (unsigned char*)malloc(m_l_raw_len * sizeof(unsigned char));
	diphone_arry = m_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-m")==0) { 
	diphone_arry = (unsigned char*)malloc(m_m_raw_len * sizeof(unsigned char));
	diphone_arry = m_m_raw;	
	}
	
	if (g_strcmp0(diphone_str,"m-n")==0) { 
	diphone_arry = (unsigned char*)malloc(m_n_raw_len * sizeof(unsigned char));
	diphone_arry = m_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(m_ow_raw_len * sizeof(unsigned char));
	diphone_arry = m_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(m_oy_raw_len * sizeof(unsigned char));
	diphone_arry = m_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-p")==0) { 
	diphone_arry = (unsigned char*)malloc(m_p_raw_len * sizeof(unsigned char));
	diphone_arry = m_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(m_pau_raw_len * sizeof(unsigned char));
	diphone_arry = m_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-r")==0) { 
	diphone_arry = (unsigned char*)malloc(m_r_raw_len * sizeof(unsigned char));
	diphone_arry = m_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-s")==0) { 
	diphone_arry = (unsigned char*)malloc(m_s_raw_len * sizeof(unsigned char));
	diphone_arry = m_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_sh_raw_len * sizeof(unsigned char));
	diphone_arry = m_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-t")==0) { 
	diphone_arry = (unsigned char*)malloc(m_t_raw_len * sizeof(unsigned char));
	diphone_arry = m_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-th")==0) { 
	diphone_arry = (unsigned char*)malloc(m_th_raw_len * sizeof(unsigned char));
	diphone_arry = m_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"m-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_uh_raw_len * sizeof(unsigned char));
	diphone_arry = m_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(m_uw_raw_len * sizeof(unsigned char));
	diphone_arry = m_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-v")==0) { 
	diphone_arry = (unsigned char*)malloc(m_v_raw_len * sizeof(unsigned char));
	diphone_arry = m_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-w")==0) { 
	diphone_arry = (unsigned char*)malloc(m_w_raw_len * sizeof(unsigned char));
	diphone_arry = m_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-y")==0) { 
	diphone_arry = (unsigned char*)malloc(m_y_raw_len * sizeof(unsigned char));
	diphone_arry = m_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-z")==0) { 
	diphone_arry = (unsigned char*)malloc(m_z_raw_len * sizeof(unsigned char));
	diphone_arry = m_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"m-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(m_zh_raw_len * sizeof(unsigned char));
	diphone_arry = m_zh_raw;	
	}
	
	//n diphones
	if (g_strcmp0(diphone_str,"n-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(n_aa_raw_len * sizeof(unsigned char));
	diphone_arry = n_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ae_raw_len * sizeof(unsigned char));
	diphone_arry = n_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ah_raw_len * sizeof(unsigned char));
	diphone_arry = n_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ao_raw_len * sizeof(unsigned char));
	diphone_arry = n_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(n_aw_raw_len * sizeof(unsigned char));
	diphone_arry = n_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ax_raw_len * sizeof(unsigned char));
	diphone_arry = n_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ay_raw_len * sizeof(unsigned char));
	diphone_arry = n_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-b")==0) { 
	diphone_arry = (unsigned char*)malloc(n_b_raw_len * sizeof(unsigned char));
	diphone_arry = n_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ch_raw_len * sizeof(unsigned char));
	diphone_arry = n_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-d")==0) { 
	diphone_arry = (unsigned char*)malloc(n_d_raw_len * sizeof(unsigned char));
	diphone_arry = n_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_dh_raw_len * sizeof(unsigned char));
	diphone_arry = n_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_eh_raw_len * sizeof(unsigned char));
	diphone_arry = n_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-er")==0) { 
	diphone_arry = (unsigned char*)malloc(n_er_raw_len * sizeof(unsigned char));
	diphone_arry = n_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ey")==0) {
	diphone_arry = (unsigned char*)malloc(n_ey_raw_len * sizeof(unsigned char));
	diphone_arry = n_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-f")==0) { 
	diphone_arry = (unsigned char*)malloc(n_f_raw_len * sizeof(unsigned char));
	diphone_arry = n_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-g")==0) { 
	diphone_arry = (unsigned char*)malloc(n_g_raw_len * sizeof(unsigned char));
	diphone_arry = n_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_hh_raw_len * sizeof(unsigned char));
	diphone_arry = n_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ih_raw_len * sizeof(unsigned char));
	diphone_arry = n_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(n_iy_raw_len * sizeof(unsigned char));
	diphone_arry = n_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_jh_raw_len * sizeof(unsigned char));
	diphone_arry = n_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-k")==0) { 
	diphone_arry = (unsigned char*)malloc(n_k_raw_len * sizeof(unsigned char));
	diphone_arry = n_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-l")==0) { 
	diphone_arry = (unsigned char*)malloc(n_l_raw_len * sizeof(unsigned char));
	diphone_arry = n_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-m")==0) { 
	diphone_arry = (unsigned char*)malloc(n_m_raw_len * sizeof(unsigned char));
	diphone_arry = n_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-n")==0) { 
	diphone_arry = (unsigned char*)malloc(n_n_raw_len * sizeof(unsigned char));
	diphone_arry = n_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(n_ow_raw_len * sizeof(unsigned char));
	diphone_arry = n_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(n_oy_raw_len * sizeof(unsigned char));
	diphone_arry = n_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-p")==0) { 
	diphone_arry = (unsigned char*)malloc(m_p_raw_len * sizeof(unsigned char));
	diphone_arry = n_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(n_pau_raw_len * sizeof(unsigned char));
	diphone_arry = n_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-r")==0) { 
	diphone_arry = (unsigned char*)malloc(n_r_raw_len * sizeof(unsigned char));
	diphone_arry = n_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-s")==0) { 
	diphone_arry = (unsigned char*)malloc(n_s_raw_len * sizeof(unsigned char));
	diphone_arry = n_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_sh_raw_len * sizeof(unsigned char));
	diphone_arry = n_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-t")==0) { 
	diphone_arry = (unsigned char*)malloc(n_t_raw_len * sizeof(unsigned char));
	diphone_arry = n_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-th")==0) { 
	diphone_arry = (unsigned char*)malloc(n_th_raw_len * sizeof(unsigned char));
	diphone_arry = n_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"n-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_uh_raw_len * sizeof(unsigned char));
	diphone_arry = n_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(n_uw_raw_len * sizeof(unsigned char));
	diphone_arry = n_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-v")==0) { 
	diphone_arry = (unsigned char*)malloc(n_v_raw_len * sizeof(unsigned char));
	diphone_arry = n_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-w")==0) { 
	diphone_arry = (unsigned char*)malloc(n_w_raw_len * sizeof(unsigned char));
	diphone_arry = n_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-y")==0) { 
	diphone_arry = (unsigned char*)malloc(n_y_raw_len * sizeof(unsigned char));
	diphone_arry = n_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-z")==0) { 
	diphone_arry = (unsigned char*)malloc(n_z_raw_len * sizeof(unsigned char));
	diphone_arry = n_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"n-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(n_zh_raw_len * sizeof(unsigned char));
	diphone_arry = n_zh_raw;	
	}
	
	
	
	//ng diphones
	if (g_strcmp0(diphone_str,"ng-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ng_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ah")==0) {
	diphone_arry = (unsigned char*)malloc(ng_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-aw")==0) {
	diphone_arry = (unsigned char*)malloc(ng_aw_raw_len * sizeof(unsigned char));
	diphone_arry = ng_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_b_raw_len * sizeof(unsigned char));
	diphone_arry = ng_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_d_raw_len * sizeof(unsigned char));
	diphone_arry = ng_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_dh_raw;	
	}
	
	if (g_strcmp0(diphone_str,"ng-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_er_raw_len * sizeof(unsigned char));
	diphone_arry = ng_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_f_raw_len * sizeof(unsigned char));
	diphone_arry = ng_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_g_raw_len * sizeof(unsigned char));
	diphone_arry = ng_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ng_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_k_raw_len * sizeof(unsigned char));
	diphone_arry = ng_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_l_raw_len * sizeof(unsigned char));
	diphone_arry = ng_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_m_raw_len * sizeof(unsigned char));
	diphone_arry = ng_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_n_raw_len * sizeof(unsigned char));
	diphone_arry = ng_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ng_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ng_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_p_raw_len * sizeof(unsigned char));
	diphone_arry = ng_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ng_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_r_raw_len * sizeof(unsigned char));
	diphone_arry = ng_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_s_raw_len * sizeof(unsigned char));
	diphone_arry = ng_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_t_raw_len * sizeof(unsigned char));
	diphone_arry = ng_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_th_raw_len * sizeof(unsigned char));
	diphone_arry = ng_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ng-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ng_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-v")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_v_raw_len * sizeof(unsigned char));
	diphone_arry = ng_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_w_raw_len * sizeof(unsigned char));
	diphone_arry = ng_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_y_raw_len * sizeof(unsigned char));
	diphone_arry = ng_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_z_raw_len * sizeof(unsigned char));
	diphone_arry = ng_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ng-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ng_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ng_zh_raw;	
	}
	
	
	//ow diphones
	if (g_strcmp0(diphone_str,"ow-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_aa_raw_len * sizeof(unsigned char));
	diphone_arry = ow_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ae_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ah_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ao_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_aw_raw_len * sizeof(unsigned char));
	diphone_arry =ow_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ax_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ay_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-b")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_b_raw_len * sizeof(unsigned char));
	diphone_arry = ow_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ch_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-d")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_d_raw_len * sizeof(unsigned char));
	diphone_arry = ow_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_dh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_eh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-er")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_er_raw_len * sizeof(unsigned char));
	diphone_arry = ow_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ey_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-f")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_f_raw_len * sizeof(unsigned char));
	diphone_arry = ow_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-g")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_g_raw_len * sizeof(unsigned char));
	diphone_arry = ow_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_hh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ih_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_iy_raw_len * sizeof(unsigned char));
	diphone_arry = ow_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_jh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-k")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_k_raw_len * sizeof(unsigned char));
	diphone_arry = ow_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-l")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_l_raw_len * sizeof(unsigned char));
	diphone_arry = ow_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-m")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_m_raw_len * sizeof(unsigned char));
	diphone_arry =ow_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-n")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_n_raw_len * sizeof(unsigned char));
	diphone_arry = ow_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ng_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_ow_raw_len * sizeof(unsigned char));
	diphone_arry = ow_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-oy")==0) {
	diphone_arry = (unsigned char*)malloc(ow_oy_raw_len * sizeof(unsigned char));
	diphone_arry = ow_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-p")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_p_raw_len * sizeof(unsigned char));
	diphone_arry = ow_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_pau_raw_len * sizeof(unsigned char));
	diphone_arry = ow_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-r")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_r_raw_len * sizeof(unsigned char));
	diphone_arry = ow_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-s")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_s_raw_len * sizeof(unsigned char));
	diphone_arry = ow_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_sh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-t")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_t_raw_len * sizeof(unsigned char));
	diphone_arry = ow_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-th")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_th_raw_len * sizeof(unsigned char));
	diphone_arry = ow_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"ow-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_uh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_uw_raw_len * sizeof(unsigned char));
	diphone_arry = ow_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-v")==0) {
	diphone_arry = (unsigned char*)malloc(ow_v_raw_len * sizeof(unsigned char));
	diphone_arry =ow_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-w")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_w_raw_len * sizeof(unsigned char));
	diphone_arry = ow_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-y")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_y_raw_len * sizeof(unsigned char));
	diphone_arry = ow_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-z")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_z_raw_len * sizeof(unsigned char));
	diphone_arry = ow_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"ow-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(ow_zh_raw_len * sizeof(unsigned char));
	diphone_arry = ow_zh_raw;	
	}
	
	
	//oy diphones
	if (g_strcmp0(diphone_str,"oy-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_aa_raw_len * sizeof(unsigned char));
	diphone_arry = oy_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ae_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ah_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ao_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_aw_raw_len * sizeof(unsigned char));
	diphone_arry =oy_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ax_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ay_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-b")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_b_raw_len * sizeof(unsigned char));
	diphone_arry = oy_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ch_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-d")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_d_raw_len * sizeof(unsigned char));
	diphone_arry = oy_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_dh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_eh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-er")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_er_raw_len * sizeof(unsigned char));
	diphone_arry = oy_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ey_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-f")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_f_raw_len * sizeof(unsigned char));
	diphone_arry = oy_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-g")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_g_raw_len * sizeof(unsigned char));
	diphone_arry = oy_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_hh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ih_raw_len * sizeof(unsigned char));
	diphone_arry =oy_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_iy_raw_len * sizeof(unsigned char));
	diphone_arry = oy_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_jh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-k")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_k_raw_len * sizeof(unsigned char));
	diphone_arry = oy_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-l")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_l_raw_len * sizeof(unsigned char));
	diphone_arry = oy_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-m")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_m_raw_len * sizeof(unsigned char));
	diphone_arry =oy_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-n")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_n_raw_len * sizeof(unsigned char));
	diphone_arry = oy_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ng_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ow_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_oy_raw_len * sizeof(unsigned char));
	diphone_arry = oy_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-p")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_p_raw_len * sizeof(unsigned char));
	diphone_arry = oy_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_pau_raw_len * sizeof(unsigned char));
	diphone_arry = oy_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-r")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_r_raw_len * sizeof(unsigned char));
	diphone_arry = oy_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-s")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_s_raw_len * sizeof(unsigned char));
	diphone_arry = oy_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_sh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-t")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_t_raw_len * sizeof(unsigned char));
	diphone_arry = oy_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-th")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_th_raw_len * sizeof(unsigned char));
	diphone_arry = oy_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"oy-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_uh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_ow_raw_len * sizeof(unsigned char));
	diphone_arry = oy_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-v")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_v_raw_len * sizeof(unsigned char));
	diphone_arry = oy_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-w")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_w_raw_len * sizeof(unsigned char));
	diphone_arry = oy_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-y")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_y_raw_len * sizeof(unsigned char));
	diphone_arry = oy_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-z")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_z_raw_len * sizeof(unsigned char));
	diphone_arry = oy_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"oy-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(oy_zh_raw_len * sizeof(unsigned char));
	diphone_arry = oy_zh_raw;	
	}
	
	//p diphones
	if (g_strcmp0(diphone_str,"p-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(p_aa_raw_len * sizeof(unsigned char));
	diphone_arry = p_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ae_raw_len * sizeof(unsigned char));
	diphone_arry = p_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ah_raw_len * sizeof(unsigned char));
	diphone_arry = p_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ao_raw_len * sizeof(unsigned char));
	diphone_arry = p_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(p_aw_raw_len * sizeof(unsigned char));
	diphone_arry = p_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ax_raw_len * sizeof(unsigned char));
	diphone_arry = p_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ay_raw_len * sizeof(unsigned char));
	diphone_arry = p_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-b")==0) { 
	diphone_arry = (unsigned char*)malloc(p_b_raw_len * sizeof(unsigned char));
	diphone_arry = p_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ch_raw_len * sizeof(unsigned char));
	diphone_arry = p_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-d")==0) { 
	diphone_arry = (unsigned char*)malloc(p_d_raw_len * sizeof(unsigned char));
	diphone_arry = p_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_dh_raw_len * sizeof(unsigned char));
	diphone_arry = p_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_eh_raw_len * sizeof(unsigned char));
	diphone_arry = p_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-er")==0) { 
	diphone_arry = (unsigned char*)malloc(p_er_raw_len * sizeof(unsigned char));
	diphone_arry = p_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ey_raw_len * sizeof(unsigned char));
	diphone_arry = p_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-f")==0) { 
	diphone_arry = (unsigned char*)malloc(p_f_raw_len * sizeof(unsigned char));
	diphone_arry = p_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-g")==0) { 
	diphone_arry = (unsigned char*)malloc(p_g_raw_len * sizeof(unsigned char));
	diphone_arry = p_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_hh_raw_len * sizeof(unsigned char));
	diphone_arry = p_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ih_raw_len * sizeof(unsigned char));
	diphone_arry = p_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(p_iy_raw_len * sizeof(unsigned char));
	diphone_arry = p_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_jh_raw_len * sizeof(unsigned char));
	diphone_arry = p_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-k")==0) { 
	diphone_arry = (unsigned char*)malloc(p_k_raw_len * sizeof(unsigned char));
	diphone_arry = p_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-l")==0) { 
	diphone_arry = (unsigned char*)malloc(p_l_raw_len * sizeof(unsigned char));
	diphone_arry = p_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-m")==0) { 
	diphone_arry = (unsigned char*)malloc(p_m_raw_len * sizeof(unsigned char));
	diphone_arry = p_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-n")==0) { 
	diphone_arry = (unsigned char*)malloc(p_n_raw_len * sizeof(unsigned char));
	diphone_arry = p_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(p_ow_raw_len * sizeof(unsigned char));
	diphone_arry = p_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(p_oy_raw_len * sizeof(unsigned char));
	diphone_arry = p_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-p")==0) { 
	diphone_arry = (unsigned char*)malloc(p_p_raw_len * sizeof(unsigned char));
	diphone_arry = p_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(p_pau_raw_len * sizeof(unsigned char));
	diphone_arry = p_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-r")==0) { 
	diphone_arry = (unsigned char*)malloc(p_r_raw_len * sizeof(unsigned char));
	diphone_arry = p_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-s")==0) { 
	diphone_arry = (unsigned char*)malloc(p_s_raw_len * sizeof(unsigned char));
	diphone_arry = p_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_sh_raw_len * sizeof(unsigned char));
	diphone_arry = p_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-t")==0) { 
	diphone_arry = (unsigned char*)malloc(p_t_raw_len * sizeof(unsigned char));
	diphone_arry = p_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-th")==0) { 
	diphone_arry = (unsigned char*)malloc(p_th_raw_len * sizeof(unsigned char));
	diphone_arry = p_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"p-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_uh_raw_len * sizeof(unsigned char));
	diphone_arry = p_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(p_uw_raw_len * sizeof(unsigned char));
	diphone_arry = p_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-v")==0) { 
	diphone_arry = (unsigned char*)malloc(p_v_raw_len * sizeof(unsigned char));
	diphone_arry = p_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-w")==0) { 
	diphone_arry = (unsigned char*)malloc(p_w_raw_len * sizeof(unsigned char));
	diphone_arry = p_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-y")==0) { 
	diphone_arry = (unsigned char*)malloc(p_y_raw_len * sizeof(unsigned char));
	diphone_arry = p_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-z")==0) { 
	diphone_arry = (unsigned char*)malloc(p_z_raw_len * sizeof(unsigned char));
	diphone_arry = p_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"p-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(p_zh_raw_len * sizeof(unsigned char));
	diphone_arry = p_zh_raw;	
	}
		
	//pau diphones
	if (g_strcmp0(diphone_str,"pau-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_aa_raw_len * sizeof(unsigned char));
	diphone_arry = pau_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ae_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ah_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ao_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_aw_raw_len * sizeof(unsigned char));
	diphone_arry = pau_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ax_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ay_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-b")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_b_raw_len * sizeof(unsigned char));
	diphone_arry = pau_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ch_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-d")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_d_raw_len * sizeof(unsigned char));
	diphone_arry = pau_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_dh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_eh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-er")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_er_raw_len * sizeof(unsigned char));
	diphone_arry = pau_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ey_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-f")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_f_raw_len * sizeof(unsigned char));
	diphone_arry = pau_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-g")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_g_raw_len * sizeof(unsigned char));
	diphone_arry = pau_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_hh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ih_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_iy_raw_len * sizeof(unsigned char));
	diphone_arry = pau_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_jh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-k")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_k_raw_len * sizeof(unsigned char));
	diphone_arry = pau_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-l")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_l_raw_len * sizeof(unsigned char));
	diphone_arry = pau_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-m")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_m_raw_len * sizeof(unsigned char));
	diphone_arry = pau_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-n")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_n_raw_len * sizeof(unsigned char));
	diphone_arry = pau_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_ow_raw_len * sizeof(unsigned char));
	diphone_arry = pau_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-oy")==0) {
	diphone_arry = (unsigned char*)malloc(pau_oy_raw_len * sizeof(unsigned char));
	diphone_arry = pau_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-p")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_p_raw_len * sizeof(unsigned char));
	diphone_arry = pau_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_pau_raw_len * sizeof(unsigned char));
	diphone_arry = pau_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-r")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_r_raw_len * sizeof(unsigned char));
	diphone_arry = pau_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-s")==0) {
	diphone_arry = (unsigned char*)malloc(pau_s_raw_len * sizeof(unsigned char));
	diphone_arry = pau_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_sh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-t")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_t_raw_len * sizeof(unsigned char));
	diphone_arry = pau_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-th")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_th_raw_len * sizeof(unsigned char));
	diphone_arry = pau_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"pau-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_uh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_uw_raw_len * sizeof(unsigned char));
	diphone_arry = pau_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-v")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_v_raw_len * sizeof(unsigned char));
	diphone_arry = pau_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-w")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_w_raw_len * sizeof(unsigned char));
	diphone_arry = pau_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-y")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_y_raw_len * sizeof(unsigned char));
	diphone_arry = pau_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-z")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_z_raw_len * sizeof(unsigned char));
	diphone_arry = pau_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"pau-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(pau_zh_raw_len * sizeof(unsigned char));
	diphone_arry = pau_zh_raw;	
	}
	
	//r diphones
	
	if (g_strcmp0(diphone_str,"r-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(r_aa_raw_len * sizeof(unsigned char));
	diphone_arry = r_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ae_raw_len * sizeof(unsigned char));
	diphone_arry = r_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ah_raw_len * sizeof(unsigned char));
	diphone_arry = r_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ao_raw_len * sizeof(unsigned char));
	diphone_arry = r_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(r_aw_raw_len * sizeof(unsigned char));
	diphone_arry = r_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ax_raw_len * sizeof(unsigned char));
	diphone_arry = r_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ay_raw_len * sizeof(unsigned char));
	diphone_arry = r_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-b")==0) { 
	diphone_arry = (unsigned char*)malloc(r_b_raw_len * sizeof(unsigned char));
	diphone_arry = r_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ch_raw_len * sizeof(unsigned char));
	diphone_arry = r_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-d")==0) { 
	diphone_arry = (unsigned char*)malloc(r_d_raw_len * sizeof(unsigned char));
	diphone_arry = r_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_dh_raw_len * sizeof(unsigned char));
	diphone_arry = r_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_eh_raw_len * sizeof(unsigned char));
	diphone_arry = r_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-er")==0) { 
	diphone_arry = (unsigned char*)malloc(r_er_raw_len * sizeof(unsigned char));
	diphone_arry = r_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ey_raw_len * sizeof(unsigned char));
	diphone_arry = r_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-f")==0) { 
	diphone_arry = (unsigned char*)malloc(r_f_raw_len * sizeof(unsigned char));
	diphone_arry = r_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-g")==0) { 
	diphone_arry = (unsigned char*)malloc(r_g_raw_len * sizeof(unsigned char));
	diphone_arry = r_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_hh_raw_len * sizeof(unsigned char));
	diphone_arry = r_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ih_raw_len * sizeof(unsigned char));
	diphone_arry =r_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(r_iy_raw_len * sizeof(unsigned char));
	diphone_arry = r_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_jh_raw_len * sizeof(unsigned char));
	diphone_arry = r_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-k")==0) { 
	diphone_arry = (unsigned char*)malloc(r_k_raw_len * sizeof(unsigned char));
	diphone_arry = r_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-l")==0) { 
	diphone_arry = (unsigned char*)malloc(r_l_raw_len * sizeof(unsigned char));
	diphone_arry = r_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-m")==0) { 
	diphone_arry = (unsigned char*)malloc(r_m_raw_len * sizeof(unsigned char));
	diphone_arry = r_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-n")==0) { 
	diphone_arry = (unsigned char*)malloc(r_n_raw_len * sizeof(unsigned char));
	diphone_arry = r_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(r_ow_raw_len * sizeof(unsigned char));
	diphone_arry = r_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(r_oy_raw_len * sizeof(unsigned char));
	diphone_arry = r_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-p")==0) { 
	diphone_arry = (unsigned char*)malloc(r_p_raw_len * sizeof(unsigned char));
	diphone_arry = r_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(r_pau_raw_len * sizeof(unsigned char));
	diphone_arry = r_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-r")==0) { 
	diphone_arry = (unsigned char*)malloc(r_r_raw_len * sizeof(unsigned char));
	diphone_arry = r_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-s")==0) { 
	diphone_arry = (unsigned char*)malloc(r_s_raw_len * sizeof(unsigned char));
	diphone_arry = r_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_sh_raw_len * sizeof(unsigned char));
	diphone_arry = r_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-t")==0) { 
	diphone_arry = (unsigned char*)malloc(r_t_raw_len * sizeof(unsigned char));
	diphone_arry = r_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-th")==0) { 
	diphone_arry = (unsigned char*)malloc(r_th_raw_len * sizeof(unsigned char));
	diphone_arry = r_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"r-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_uh_raw_len * sizeof(unsigned char));
	diphone_arry = r_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(r_uw_raw_len * sizeof(unsigned char));
	diphone_arry = r_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-v")==0) { 
	diphone_arry = (unsigned char*)malloc(r_v_raw_len * sizeof(unsigned char));
	diphone_arry = r_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-w")==0) { 
	diphone_arry = (unsigned char*)malloc(r_w_raw_len * sizeof(unsigned char));
	diphone_arry = r_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-y")==0) { 
	diphone_arry = (unsigned char*)malloc(r_y_raw_len * sizeof(unsigned char));
	diphone_arry = r_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-z")==0) { 
	diphone_arry = (unsigned char*)malloc(r_z_raw_len * sizeof(unsigned char));
	diphone_arry = r_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"r-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(r_zh_raw_len * sizeof(unsigned char));
	diphone_arry = r_zh_raw;	
	}
	
	//s diphones
	if (g_strcmp0(diphone_str,"s-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(s_aa_raw_len * sizeof(unsigned char));
	diphone_arry = s_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ae_raw_len * sizeof(unsigned char));
	diphone_arry = s_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ah_raw_len * sizeof(unsigned char));
	diphone_arry = s_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ao_raw_len * sizeof(unsigned char));
	diphone_arry = s_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(s_aw_raw_len * sizeof(unsigned char));
	diphone_arry = s_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ax_raw_len * sizeof(unsigned char));
	diphone_arry = s_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ay_raw_len * sizeof(unsigned char));
	diphone_arry = s_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-b")==0) { 
	diphone_arry = (unsigned char*)malloc(s_b_raw_len * sizeof(unsigned char));
	diphone_arry = s_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ch_raw_len * sizeof(unsigned char));
	diphone_arry = s_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-d")==0) { 
	diphone_arry = (unsigned char*)malloc(s_d_raw_len * sizeof(unsigned char));
	diphone_arry = s_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_dh_raw_len * sizeof(unsigned char));
	diphone_arry = s_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_eh_raw_len * sizeof(unsigned char));
	diphone_arry = s_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-er")==0) { 
	diphone_arry = (unsigned char*)malloc(s_er_raw_len * sizeof(unsigned char));
	diphone_arry = s_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ey_raw_len * sizeof(unsigned char));
	diphone_arry = s_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-f")==0) { 
	diphone_arry = (unsigned char*)malloc(s_f_raw_len * sizeof(unsigned char));
	diphone_arry = s_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-g")==0) { 
	diphone_arry = (unsigned char*)malloc(s_g_raw_len * sizeof(unsigned char));
	diphone_arry = s_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_hh_raw_len * sizeof(unsigned char));
	diphone_arry = s_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ih_raw_len * sizeof(unsigned char));
	diphone_arry = s_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(s_iy_raw_len * sizeof(unsigned char));
	diphone_arry = s_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_jh_raw_len * sizeof(unsigned char));
	diphone_arry = s_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-k")==0) { 
	diphone_arry = (unsigned char*)malloc(s_k_raw_len * sizeof(unsigned char));
	diphone_arry = s_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-l")==0) { 
	diphone_arry = (unsigned char*)malloc(s_l_raw_len * sizeof(unsigned char));
	diphone_arry = s_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-m")==0) { 
	diphone_arry = (unsigned char*)malloc(s_m_raw_len * sizeof(unsigned char));
	diphone_arry = s_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-n")==0) { 
	diphone_arry = (unsigned char*)malloc(s_n_raw_len * sizeof(unsigned char));
	diphone_arry = s_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(s_ow_raw_len * sizeof(unsigned char));
	diphone_arry = s_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(s_oy_raw_len * sizeof(unsigned char));
	diphone_arry = s_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-p")==0) { 
	diphone_arry = (unsigned char*)malloc(s_p_raw_len * sizeof(unsigned char));
	diphone_arry = s_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(s_pau_raw_len * sizeof(unsigned char));
	diphone_arry = s_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-r")==0) { 
	diphone_arry = (unsigned char*)malloc(s_r_raw_len * sizeof(unsigned char));
	diphone_arry = s_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-s")==0) {
	diphone_arry = (unsigned char*)malloc(s_s_raw_len * sizeof(unsigned char));
	diphone_arry = s_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_sh_raw_len * sizeof(unsigned char));
	diphone_arry = s_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-t")==0) { 
	diphone_arry = (unsigned char*)malloc(s_t_raw_len * sizeof(unsigned char));
	diphone_arry = s_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-th")==0) { 
	diphone_arry = (unsigned char*)malloc(s_th_raw_len * sizeof(unsigned char));
	diphone_arry = s_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"s-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_uh_raw_len * sizeof(unsigned char));
	diphone_arry = s_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(s_uw_raw_len * sizeof(unsigned char));
	diphone_arry = s_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-v")==0) { 
	diphone_arry = (unsigned char*)malloc(s_v_raw_len * sizeof(unsigned char));
	diphone_arry = s_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-w")==0) { 
	diphone_arry = (unsigned char*)malloc(s_w_raw_len * sizeof(unsigned char));
	diphone_arry = s_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-y")==0) { 
	diphone_arry = (unsigned char*)malloc(s_y_raw_len * sizeof(unsigned char));
	diphone_arry = s_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-z")==0) { 
	diphone_arry = (unsigned char*)malloc(s_z_raw_len * sizeof(unsigned char));
	diphone_arry = s_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"s-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(s_zh_raw_len * sizeof(unsigned char));
	diphone_arry = s_zh_raw;	
	}
	
	
	//sh diphones
	if (g_strcmp0(diphone_str,"sh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = sh_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_aw_raw_len * sizeof(unsigned char));
	diphone_arry = sh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-b")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_b_raw_len * sizeof(unsigned char));
	diphone_arry = sh_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-d")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_d_raw_len * sizeof(unsigned char));
	diphone_arry = sh_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-dh")==0) {
	diphone_arry = (unsigned char*)malloc(sh_dh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-er")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_er_raw_len * sizeof(unsigned char));
	diphone_arry = sh_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-f")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_f_raw_len * sizeof(unsigned char));
	diphone_arry = sh_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-g")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_g_raw_len * sizeof(unsigned char));
	diphone_arry = sh_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_hh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_iy_raw_len * sizeof(unsigned char));
	diphone_arry = sh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_jh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-k")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_k_raw_len * sizeof(unsigned char));
	diphone_arry = sh_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-l")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_l_raw_len * sizeof(unsigned char));
	diphone_arry = sh_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-m")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_m_raw_len * sizeof(unsigned char));
	diphone_arry = sh_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-n")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_n_raw_len * sizeof(unsigned char));
	diphone_arry = sh_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = sh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = sh_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-p")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_p_raw_len * sizeof(unsigned char));
	diphone_arry = sh_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_pau_raw_len * sizeof(unsigned char));
	diphone_arry = sh_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-r")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_r_raw_len * sizeof(unsigned char));
	diphone_arry = sh_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-s")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_s_raw_len * sizeof(unsigned char));
	diphone_arry = sh_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_sh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-t")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_t_raw_len * sizeof(unsigned char));
	diphone_arry = sh_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-th")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_th_raw_len * sizeof(unsigned char));
	diphone_arry = sh_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"sh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = sh_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-v")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_v_raw_len * sizeof(unsigned char));
	diphone_arry = sh_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-w")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_w_raw_len * sizeof(unsigned char));
	diphone_arry = sh_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-y")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_y_raw_len * sizeof(unsigned char));
	diphone_arry = sh_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-z")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_z_raw_len * sizeof(unsigned char));
	diphone_arry = sh_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"sh-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(sh_zh_raw_len * sizeof(unsigned char));
	diphone_arry = sh_zh_raw;	
	}
	
	
	//t diphones
	if (g_strcmp0(diphone_str,"t-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(t_aa_raw_len * sizeof(unsigned char));
	diphone_arry = t_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ae_raw_len * sizeof(unsigned char));
	diphone_arry = t_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ah_raw_len * sizeof(unsigned char));
	diphone_arry = t_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ao_raw_len * sizeof(unsigned char));
	diphone_arry = t_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(t_aw_raw_len * sizeof(unsigned char));
	diphone_arry = t_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ax_raw_len * sizeof(unsigned char));
	diphone_arry = t_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ay_raw_len * sizeof(unsigned char));
	diphone_arry = t_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-b")==0) { 
	diphone_arry = (unsigned char*)malloc(t_b_raw_len * sizeof(unsigned char));
	diphone_arry = t_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ch_raw_len * sizeof(unsigned char));
	diphone_arry = t_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-d")==0) { 
	diphone_arry = (unsigned char*)malloc(t_d_raw_len * sizeof(unsigned char));
	diphone_arry = t_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_dh_raw_len * sizeof(unsigned char));
	diphone_arry = t_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_eh_raw_len * sizeof(unsigned char));
	diphone_arry = t_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-er")==0) { 
	diphone_arry = (unsigned char*)malloc(t_er_raw_len * sizeof(unsigned char));
	diphone_arry = t_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ey_raw_len * sizeof(unsigned char));
	diphone_arry = t_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-f")==0) { 
	diphone_arry = (unsigned char*)malloc(t_f_raw_len * sizeof(unsigned char));
	diphone_arry = t_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-g")==0) { 
	diphone_arry = (unsigned char*)malloc(t_g_raw_len * sizeof(unsigned char));
	diphone_arry = t_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_hh_raw_len * sizeof(unsigned char));
	diphone_arry = t_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ih_raw_len * sizeof(unsigned char));
	diphone_arry = t_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(t_iy_raw_len * sizeof(unsigned char));
	diphone_arry = t_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_jh_raw_len * sizeof(unsigned char));
	diphone_arry = t_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-k")==0) { 
	diphone_arry = (unsigned char*)malloc(t_k_raw_len * sizeof(unsigned char));
	diphone_arry = t_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-l")==0) { 
	diphone_arry = (unsigned char*)malloc(t_l_raw_len * sizeof(unsigned char));
	diphone_arry = t_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-m")==0) { 
	diphone_arry = (unsigned char*)malloc(t_m_raw_len * sizeof(unsigned char));
	diphone_arry = t_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-n")==0) { 
	diphone_arry = (unsigned char*)malloc(t_n_raw_len * sizeof(unsigned char));
	diphone_arry = t_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(t_ow_raw_len * sizeof(unsigned char));
	diphone_arry = t_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(t_oy_raw_len * sizeof(unsigned char));
	diphone_arry = t_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-p")==0) { 
	diphone_arry = (unsigned char*)malloc(t_p_raw_len * sizeof(unsigned char));
	diphone_arry = t_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(t_pau_raw_len * sizeof(unsigned char));
	diphone_arry = t_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-r")==0) { 
	diphone_arry = (unsigned char*)malloc(t_r_raw_len * sizeof(unsigned char));
	diphone_arry = t_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-s")==0) { 
	diphone_arry = (unsigned char*)malloc(t_s_raw_len * sizeof(unsigned char));
	diphone_arry = t_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_sh_raw_len * sizeof(unsigned char));
	diphone_arry = t_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-t")==0) { 
	diphone_arry = (unsigned char*)malloc(t_t_raw_len * sizeof(unsigned char));
	diphone_arry = t_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-th")==0) { 
	diphone_arry = (unsigned char*)malloc(t_th_raw_len * sizeof(unsigned char));
	diphone_arry = t_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"t-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_uh_raw_len * sizeof(unsigned char));
	diphone_arry = t_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(t_uw_raw_len * sizeof(unsigned char));
	diphone_arry = t_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-v")==0) { 
	diphone_arry = (unsigned char*)malloc(t_v_raw_len * sizeof(unsigned char));
	diphone_arry = t_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-w")==0) { 
	diphone_arry = (unsigned char*)malloc(t_w_raw_len * sizeof(unsigned char));
	diphone_arry = t_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-y")==0) { 
	diphone_arry = (unsigned char*)malloc(t_y_raw_len * sizeof(unsigned char));
	diphone_arry = t_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-z")==0) { 
	diphone_arry = (unsigned char*)malloc(t_z_raw_len * sizeof(unsigned char));
	diphone_arry = t_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"t-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(t_zh_raw_len * sizeof(unsigned char));
	diphone_arry = t_zh_raw;	
	}
		
	//th diphones
	if (g_strcmp0(diphone_str,"th-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(th_aa_raw_len * sizeof(unsigned char));
	diphone_arry = th_aa_raw;	
	}
	
	if (g_strcmp0(diphone_str,"th-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ae_raw_len * sizeof(unsigned char));
	diphone_arry = th_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ah_raw_len * sizeof(unsigned char));
	diphone_arry = th_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ao_raw_len * sizeof(unsigned char));
	diphone_arry = th_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(th_aw_raw_len * sizeof(unsigned char));
	diphone_arry = th_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ax_raw_len * sizeof(unsigned char));
	diphone_arry = th_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ay_raw_len * sizeof(unsigned char));
	diphone_arry = th_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-b")==0) { 
	diphone_arry = (unsigned char*)malloc(th_b_raw_len * sizeof(unsigned char));
	diphone_arry = th_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ch_raw_len * sizeof(unsigned char));
	diphone_arry = th_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-d")==0) { 
	diphone_arry = (unsigned char*)malloc(th_d_raw_len * sizeof(unsigned char));
	diphone_arry = th_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_dh_raw_len * sizeof(unsigned char));
	diphone_arry = th_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_dh_raw_len * sizeof(unsigned char));
	diphone_arry = th_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-er")==0) { 
	diphone_arry = (unsigned char*)malloc(th_er_raw_len * sizeof(unsigned char));
	diphone_arry = th_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ey_raw_len * sizeof(unsigned char));
	diphone_arry = th_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-f")==0) { 
	diphone_arry = (unsigned char*)malloc(th_f_raw_len * sizeof(unsigned char));
	diphone_arry = th_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-g")==0) { 
	diphone_arry = (unsigned char*)malloc(th_g_raw_len * sizeof(unsigned char));
	diphone_arry = th_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_hh_raw_len * sizeof(unsigned char));
	diphone_arry = th_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ih_raw_len * sizeof(unsigned char));
	diphone_arry = th_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(th_iy_raw_len * sizeof(unsigned char));
	diphone_arry = th_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_jh_raw_len * sizeof(unsigned char));
	diphone_arry = th_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-k")==0) { 
	diphone_arry = (unsigned char*)malloc(th_k_raw_len * sizeof(unsigned char));
	diphone_arry = th_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-l")==0) { 
	diphone_arry = (unsigned char*)malloc(th_l_raw_len * sizeof(unsigned char));
	diphone_arry = th_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-m")==0) { 
	diphone_arry = (unsigned char*)malloc(th_m_raw_len * sizeof(unsigned char));
	diphone_arry = th_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-n")==0) { 
	diphone_arry = (unsigned char*)malloc(th_n_raw_len * sizeof(unsigned char));
	diphone_arry = th_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(th_ow_raw_len * sizeof(unsigned char));
	diphone_arry = th_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(th_oy_raw_len * sizeof(unsigned char));
	diphone_arry = th_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-p")==0) { 
	diphone_arry = (unsigned char*)malloc(th_p_raw_len * sizeof(unsigned char));
	diphone_arry = th_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(th_pau_raw_len * sizeof(unsigned char));
	diphone_arry = th_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-r")==0) { 
	diphone_arry = (unsigned char*)malloc(th_r_raw_len * sizeof(unsigned char));
	diphone_arry = th_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-s")==0) { 
	diphone_arry = (unsigned char*)malloc(th_s_raw_len * sizeof(unsigned char));
	diphone_arry = th_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_sh_raw_len * sizeof(unsigned char));
	diphone_arry = th_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-t")==0) { 
	diphone_arry = (unsigned char*)malloc(th_t_raw_len * sizeof(unsigned char));
	diphone_arry = th_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-th")==0) { 
	diphone_arry = (unsigned char*)malloc(th_th_raw_len * sizeof(unsigned char));
	diphone_arry = th_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"th-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_uh_raw_len * sizeof(unsigned char));
	diphone_arry = th_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(th_uw_raw_len * sizeof(unsigned char));
	diphone_arry = th_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-v")==0) { 
	diphone_arry = (unsigned char*)malloc(th_v_raw_len * sizeof(unsigned char));
	diphone_arry = th_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-w")==0) { 
	diphone_arry = (unsigned char*)malloc(th_w_raw_len * sizeof(unsigned char));
	diphone_arry = th_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-y")==0) { 
	diphone_arry = (unsigned char*)malloc(th_y_raw_len * sizeof(unsigned char));
	diphone_arry = th_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-z")==0) { 
	diphone_arry = (unsigned char*)malloc(th_z_raw_len * sizeof(unsigned char));
	diphone_arry = th_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"th-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(th_zh_raw_len * sizeof(unsigned char));
	diphone_arry = th_zh_raw;	
	}
	
	
	//uh diphones
	if (g_strcmp0(diphone_str,"uh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = uh_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ah_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_aw_raw_len * sizeof(unsigned char));
	diphone_arry = uh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ay_raw;	
	}
	
	if (g_strcmp0(diphone_str,"uh-b")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_b_raw_len * sizeof(unsigned char));
	diphone_arry = uh_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-d")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_d_raw_len * sizeof(unsigned char));
	diphone_arry = uh_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_dh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-er")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_er_raw_len * sizeof(unsigned char));
	diphone_arry = uh_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-f")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_f_raw_len * sizeof(unsigned char));
	diphone_arry = uh_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-g")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_g_raw_len * sizeof(unsigned char));
	diphone_arry = uh_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_hh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_iy_raw_len * sizeof(unsigned char));
	diphone_arry = uh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_jh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-k")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_k_raw_len * sizeof(unsigned char));
	diphone_arry = uh_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-l")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_l_raw_len * sizeof(unsigned char));
	diphone_arry = uh_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-m")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_m_raw_len * sizeof(unsigned char));
	diphone_arry = uh_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-n")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_n_raw_len * sizeof(unsigned char));
	diphone_arry = uh_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_ng_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-ow")==0) {
	diphone_arry = (unsigned char*)malloc(uh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = uh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = uh_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-p")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_p_raw_len * sizeof(unsigned char));
	diphone_arry = uh_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_pau_raw_len * sizeof(unsigned char));
	diphone_arry = uh_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-r")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_r_raw_len * sizeof(unsigned char));
	diphone_arry = uh_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-s")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_s_raw_len * sizeof(unsigned char));
	diphone_arry = uh_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_sh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-t")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_t_raw_len * sizeof(unsigned char));
	diphone_arry = uh_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-th")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_th_raw_len * sizeof(unsigned char));
	diphone_arry = uh_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"uh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = uh_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-v")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_v_raw_len * sizeof(unsigned char));
	diphone_arry = uh_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-w")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_w_raw_len * sizeof(unsigned char));
	diphone_arry = uh_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-y")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_y_raw_len * sizeof(unsigned char));
	diphone_arry = uh_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-z")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_z_raw_len * sizeof(unsigned char));
	diphone_arry = uh_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"uh-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(uh_zh_raw_len * sizeof(unsigned char));
	diphone_arry = uh_zh_raw;	
	}
	
		
	
	//uw diphones
	if (g_strcmp0(diphone_str,"uw-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_aa_raw_len * sizeof(unsigned char));
	diphone_arry = uw_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ae_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ah_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ao_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_aw_raw_len * sizeof(unsigned char));
	diphone_arry = uw_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ax_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ay_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-b")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_b_raw_len * sizeof(unsigned char));
	diphone_arry = uw_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ch_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-d")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_d_raw_len * sizeof(unsigned char));
	diphone_arry = uw_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_dh_raw_len * sizeof(unsigned char));
	diphone_arry = uw_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_eh_raw_len * sizeof(unsigned char));
	diphone_arry = uw_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-er")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_er_raw_len * sizeof(unsigned char));
	diphone_arry = uw_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ey_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-f")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_f_raw_len * sizeof(unsigned char));
	diphone_arry = uw_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-g")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_g_raw_len * sizeof(unsigned char));
	diphone_arry = uw_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_hh_raw_len * sizeof(unsigned char));
	diphone_arry =uw_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ih_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_iy_raw_len * sizeof(unsigned char));
	diphone_arry = uw_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_jh_raw_len * sizeof(unsigned char));
	diphone_arry = uw_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-k")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_k_raw_len * sizeof(unsigned char));
	diphone_arry = uw_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-l")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_l_raw_len * sizeof(unsigned char));
	diphone_arry = uw_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-m")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_m_raw_len * sizeof(unsigned char));
	diphone_arry = uw_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-n")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_n_raw_len * sizeof(unsigned char));
	diphone_arry = uw_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ng")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ng_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ng_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_ow_raw_len * sizeof(unsigned char));
	diphone_arry = uw_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_oy_raw_len * sizeof(unsigned char));
	diphone_arry = uw_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-p")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_p_raw_len * sizeof(unsigned char));
	diphone_arry = uw_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_pau_raw_len * sizeof(unsigned char));
	diphone_arry = uw_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-r")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_r_raw_len * sizeof(unsigned char));
	diphone_arry = uw_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-s")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_s_raw_len * sizeof(unsigned char));
	diphone_arry = uw_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_sh_raw_len * sizeof(unsigned char));
	diphone_arry = uw_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-t")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_t_raw_len * sizeof(unsigned char));
	diphone_arry = uw_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-th")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_th_raw_len * sizeof(unsigned char));
	diphone_arry = uw_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"uw-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_uh_raw_len * sizeof(unsigned char));
	diphone_arry = uw_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_uw_raw_len * sizeof(unsigned char));
	diphone_arry = uw_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-v")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_v_raw_len * sizeof(unsigned char));
	diphone_arry = uw_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-w")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_w_raw_len * sizeof(unsigned char));
	diphone_arry = uw_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-y")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_y_raw_len * sizeof(unsigned char));
	diphone_arry = uw_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-z")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_z_raw_len * sizeof(unsigned char));
	diphone_arry = uw_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"uw-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(uw_zh_raw_len * sizeof(unsigned char));
	diphone_arry = uw_zh_raw;	
	}
	
	
	//v diphones
	if (g_strcmp0(diphone_str,"v-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(v_aa_raw_len * sizeof(unsigned char));
	diphone_arry = v_aa_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ae_raw_len * sizeof(unsigned char));
	diphone_arry = v_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ah_raw_len * sizeof(unsigned char));
	diphone_arry = v_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ao_raw_len * sizeof(unsigned char));
	diphone_arry = v_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(v_aw_raw_len * sizeof(unsigned char));
	diphone_arry = v_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ax_raw_len * sizeof(unsigned char));
	diphone_arry = v_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ay_raw_len * sizeof(unsigned char));
	diphone_arry = v_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-b")==0) { 
	diphone_arry = (unsigned char*)malloc(v_b_raw_len * sizeof(unsigned char));
	diphone_arry = v_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ch_raw_len * sizeof(unsigned char));
	diphone_arry = v_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-d")==0) { 
	diphone_arry = (unsigned char*)malloc(v_d_raw_len * sizeof(unsigned char));
	diphone_arry = v_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_dh_raw_len * sizeof(unsigned char));
	diphone_arry = v_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_eh_raw_len * sizeof(unsigned char));
	diphone_arry = v_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-er")==0) { 
	diphone_arry = (unsigned char*)malloc(v_er_raw_len * sizeof(unsigned char));
	diphone_arry = v_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ey_raw_len * sizeof(unsigned char));
	diphone_arry = v_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-f")==0) { 
	diphone_arry = (unsigned char*)malloc(v_f_raw_len * sizeof(unsigned char));
	diphone_arry = v_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-g")==0) { 
	diphone_arry = (unsigned char*)malloc(v_g_raw_len * sizeof(unsigned char));
	diphone_arry = v_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_hh_raw_len * sizeof(unsigned char));
	diphone_arry = v_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ih_raw_len * sizeof(unsigned char));
	diphone_arry = v_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(v_iy_raw_len * sizeof(unsigned char));
	diphone_arry = v_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_jh_raw_len * sizeof(unsigned char));
	diphone_arry = v_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-k")==0) { 
	diphone_arry = (unsigned char*)malloc(v_k_raw_len * sizeof(unsigned char));
	diphone_arry = v_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-l")==0) { 
	diphone_arry = (unsigned char*)malloc(v_l_raw_len * sizeof(unsigned char));
	diphone_arry = v_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-m")==0) { 
	diphone_arry = (unsigned char*)malloc(v_m_raw_len * sizeof(unsigned char));
	diphone_arry = v_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-n")==0) { 
	diphone_arry = (unsigned char*)malloc(v_n_raw_len * sizeof(unsigned char));
	diphone_arry = v_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(v_ow_raw_len * sizeof(unsigned char));
	diphone_arry = v_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(v_oy_raw_len * sizeof(unsigned char));
	diphone_arry = v_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-p")==0) { 
	diphone_arry = (unsigned char*)malloc(v_p_raw_len * sizeof(unsigned char));
	diphone_arry = v_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(v_pau_raw_len * sizeof(unsigned char));
	diphone_arry = v_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-r")==0) { 
	diphone_arry = (unsigned char*)malloc(v_r_raw_len * sizeof(unsigned char));
	diphone_arry = v_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-s")==0) { 
	diphone_arry = (unsigned char*)malloc(v_s_raw_len * sizeof(unsigned char));
	diphone_arry = v_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_sh_raw_len * sizeof(unsigned char));
	diphone_arry = v_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-t")==0) { 
	diphone_arry = (unsigned char*)malloc(v_t_raw_len * sizeof(unsigned char));
	diphone_arry = v_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-th")==0) { 
	diphone_arry = (unsigned char*)malloc(v_th_raw_len * sizeof(unsigned char));
	diphone_arry = v_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"v-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_uh_raw_len * sizeof(unsigned char));
	diphone_arry = v_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(v_uw_raw_len * sizeof(unsigned char));
	diphone_arry = v_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-v")==0) { 
	diphone_arry = (unsigned char*)malloc(v_v_raw_len * sizeof(unsigned char));
	diphone_arry = v_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-w")==0) { 
	diphone_arry = (unsigned char*)malloc(v_w_raw_len * sizeof(unsigned char));
	diphone_arry = v_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-y")==0) { 
	diphone_arry = (unsigned char*)malloc(v_y_raw_len * sizeof(unsigned char));
	diphone_arry = v_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-z")==0) { 
	diphone_arry = (unsigned char*)malloc(v_z_raw_len * sizeof(unsigned char));
	diphone_arry = v_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"v-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(v_zh_raw_len * sizeof(unsigned char));
	diphone_arry = v_zh_raw;	
	}
		
	if (g_strcmp0(diphone_str,"w-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ae_raw_len * sizeof(unsigned char));
	diphone_arry = w_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ah_raw_len * sizeof(unsigned char));
	diphone_arry = w_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ao_raw_len * sizeof(unsigned char));
	diphone_arry = w_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(w_aw_raw_len * sizeof(unsigned char));
	diphone_arry = w_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ax_raw_len * sizeof(unsigned char));
	diphone_arry = w_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ay_raw_len * sizeof(unsigned char));
	diphone_arry = w_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(w_eh_raw_len * sizeof(unsigned char));
	diphone_arry = w_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ey_raw_len * sizeof(unsigned char));
	diphone_arry = w_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ih_raw_len * sizeof(unsigned char));
	diphone_arry = w_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(w_iy_raw_len * sizeof(unsigned char));
	diphone_arry = w_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(w_ow_raw_len * sizeof(unsigned char));
	diphone_arry = w_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(w_oy_raw_len * sizeof(unsigned char));
	diphone_arry = w_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(w_uh_raw_len * sizeof(unsigned char));
	diphone_arry = w_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"w-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(w_uw_raw_len * sizeof(unsigned char));
	diphone_arry =w_uw_raw;	
	}
		
	//y diphones	
	if (g_strcmp0(diphone_str,"y-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(y_aa_raw_len * sizeof(unsigned char));
	diphone_arry = y_aa_raw;	
	}
	
	if (g_strcmp0(diphone_str,"y-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ae_raw_len * sizeof(unsigned char));
	diphone_arry = y_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ah_raw_len * sizeof(unsigned char));
	diphone_arry = y_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ao_raw_len * sizeof(unsigned char));
	diphone_arry = y_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(y_aw_raw_len * sizeof(unsigned char));
	diphone_arry = y_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ax_raw_len * sizeof(unsigned char));
	diphone_arry = y_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ay_raw_len * sizeof(unsigned char));
	diphone_arry = y_ay_raw;
	
	}	
	if (g_strcmp0(diphone_str,"y-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(y_eh_raw_len * sizeof(unsigned char));
	diphone_arry = y_eh_raw;
	
	}	
	if (g_strcmp0(diphone_str,"y-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ey_raw_len * sizeof(unsigned char));
	diphone_arry = y_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ih_raw_len * sizeof(unsigned char));
	diphone_arry = y_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(y_iy_raw_len * sizeof(unsigned char));
	diphone_arry = y_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ow_raw_len * sizeof(unsigned char));
	diphone_arry = y_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(y_ow_raw_len * sizeof(unsigned char));
	diphone_arry = y_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(y_uh_raw_len * sizeof(unsigned char));
	diphone_arry = y_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"y-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(y_uw_raw_len * sizeof(unsigned char));
	diphone_arry = y_uw_raw;	
	}
	
	
	//z diphones	
	if (g_strcmp0(diphone_str,"z-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(z_aa_raw_len * sizeof(unsigned char));
	diphone_arry = z_aa_raw;	
	}
	
	if (g_strcmp0(diphone_str,"z-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ae_raw_len * sizeof(unsigned char));
	diphone_arry = z_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ah_raw_len * sizeof(unsigned char));
	diphone_arry = z_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ao_raw_len * sizeof(unsigned char));
	diphone_arry = z_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(z_aw_raw_len * sizeof(unsigned char));
	diphone_arry = z_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ax_raw_len * sizeof(unsigned char));
	diphone_arry = z_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ay_raw_len * sizeof(unsigned char));
	diphone_arry = z_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-b")==0) { 
	diphone_arry = (unsigned char*)malloc(z_b_raw_len * sizeof(unsigned char));
	diphone_arry = z_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ch_raw_len * sizeof(unsigned char));
	diphone_arry = z_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-d")==0) { 
	diphone_arry = (unsigned char*)malloc(z_d_raw_len * sizeof(unsigned char));
	diphone_arry = z_d_raw;	
	}
	
	if (g_strcmp0(diphone_str,"z-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_dh_raw_len * sizeof(unsigned char));
	diphone_arry = z_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_eh_raw_len * sizeof(unsigned char));
	diphone_arry = z_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-er")==0) { 
	diphone_arry = (unsigned char*)malloc(z_er_raw_len * sizeof(unsigned char));
	diphone_arry = z_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ey_raw_len * sizeof(unsigned char));
	diphone_arry = z_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-f")==0) { 
	diphone_arry = (unsigned char*)malloc(z_f_raw_len * sizeof(unsigned char));
	diphone_arry = z_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-g")==0) { 
	diphone_arry = (unsigned char*)malloc(z_g_raw_len * sizeof(unsigned char));
	diphone_arry = z_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_hh_raw_len * sizeof(unsigned char));
	diphone_arry = z_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ih_raw_len * sizeof(unsigned char));
	diphone_arry = z_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(z_iy_raw_len * sizeof(unsigned char));
	diphone_arry = z_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_jh_raw_len * sizeof(unsigned char));
	diphone_arry = z_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-k")==0) { 
	diphone_arry = (unsigned char*)malloc(z_k_raw_len * sizeof(unsigned char));
	diphone_arry = z_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-l")==0) { 
	diphone_arry = (unsigned char*)malloc(z_l_raw_len * sizeof(unsigned char));
	diphone_arry = z_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-m")==0) { 
	diphone_arry = (unsigned char*)malloc(z_m_raw_len * sizeof(unsigned char));
	diphone_arry = z_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-n")==0) { 
	diphone_arry = (unsigned char*)malloc(z_n_raw_len * sizeof(unsigned char));
	diphone_arry = z_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(z_ow_raw_len * sizeof(unsigned char));
	diphone_arry = z_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(z_oy_raw_len * sizeof(unsigned char));
	diphone_arry = z_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-p")==0) { 
	diphone_arry = (unsigned char*)malloc(z_p_raw_len * sizeof(unsigned char));
	diphone_arry = z_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(z_pau_raw_len * sizeof(unsigned char));
	diphone_arry = z_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-r")==0) { 
	diphone_arry = (unsigned char*)malloc(z_r_raw_len * sizeof(unsigned char));
	diphone_arry = z_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-s")==0) { 
	diphone_arry = (unsigned char*)malloc(z_s_raw_len * sizeof(unsigned char));
	diphone_arry = z_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_sh_raw_len * sizeof(unsigned char));
	diphone_arry = z_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-t")==0) { 
	diphone_arry = (unsigned char*)malloc(z_t_raw_len * sizeof(unsigned char));
	diphone_arry = z_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-th")==0) { 
	diphone_arry = (unsigned char*)malloc(z_th_raw_len * sizeof(unsigned char));
	diphone_arry = z_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"z-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_uh_raw_len * sizeof(unsigned char));
	diphone_arry = z_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(z_uw_raw_len * sizeof(unsigned char));
	diphone_arry = z_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-v")==0) { 
	diphone_arry = (unsigned char*)malloc(z_v_raw_len * sizeof(unsigned char));
	diphone_arry = z_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-w")==0) { 
	diphone_arry = (unsigned char*)malloc(z_w_raw_len * sizeof(unsigned char));
	diphone_arry = z_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-y")==0) { 
	diphone_arry = (unsigned char*)malloc(z_y_raw_len * sizeof(unsigned char));
	diphone_arry = z_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-z")==0) { 
	diphone_arry = (unsigned char*)malloc(z_z_raw_len * sizeof(unsigned char));
	diphone_arry = z_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"z-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(z_zh_raw_len * sizeof(unsigned char));
	diphone_arry = z_zh_raw;	
	}
	
	//zh diphones
	if (g_strcmp0(diphone_str,"zh-aa")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_aa_raw_len * sizeof(unsigned char));
	diphone_arry = zh_aa_raw;	
	}
	
	if (g_strcmp0(diphone_str,"zh-ae")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ae_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ae_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ah")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ah_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ah_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ao")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ao_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ao_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-aw")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_aw_raw_len * sizeof(unsigned char));
	diphone_arry = zh_aw_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ax")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ax_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ax_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ay")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ay_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ay_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-b")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_b_raw_len * sizeof(unsigned char));
	diphone_arry = zh_b_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ch")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ch_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ch_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-d")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_d_raw_len * sizeof(unsigned char));
	diphone_arry = zh_d_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-dh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_dh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_dh_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-eh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_eh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_eh_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-er")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_er_raw_len * sizeof(unsigned char));
	diphone_arry = zh_er_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ey")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ey_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ey_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-f")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_f_raw_len * sizeof(unsigned char));
	diphone_arry = zh_f_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-g")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_g_raw_len * sizeof(unsigned char));
	diphone_arry = zh_g_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-hh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_hh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_hh_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ih")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ih_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ih_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-iy")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_iy_raw_len * sizeof(unsigned char));
	diphone_arry = zh_iy_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-jh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_jh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_jh_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-k")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_k_raw_len * sizeof(unsigned char));
	diphone_arry = zh_k_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-l")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_l_raw_len * sizeof(unsigned char));
	diphone_arry = zh_l_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-m")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_m_raw_len * sizeof(unsigned char));
	diphone_arry = zh_m_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-n")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_n_raw_len * sizeof(unsigned char));
	diphone_arry = zh_n_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-ow")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_ow_raw_len * sizeof(unsigned char));
	diphone_arry = zh_ow_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-oy")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_oy_raw_len * sizeof(unsigned char));
	diphone_arry = zh_oy_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-p")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_p_raw_len * sizeof(unsigned char));
	diphone_arry = zh_p_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-pau")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_pau_raw_len * sizeof(unsigned char));
	diphone_arry = zh_pau_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-r")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_r_raw_len * sizeof(unsigned char));
	diphone_arry = zh_r_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-s")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_s_raw_len * sizeof(unsigned char));
	diphone_arry = zh_s_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-sh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_sh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_sh_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-t")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_t_raw_len * sizeof(unsigned char));
	diphone_arry = zh_t_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-th")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_th_raw_len * sizeof(unsigned char));
	diphone_arry = zh_th_raw;
	
	}	
	if (g_strcmp0(diphone_str,"zh-uh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_uh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_uh_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-uw")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_uw_raw_len * sizeof(unsigned char));
	diphone_arry = zh_uw_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-v")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_v_raw_len * sizeof(unsigned char));
	diphone_arry = zh_v_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-w")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_w_raw_len * sizeof(unsigned char));
	diphone_arry = zh_w_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-y")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_y_raw_len * sizeof(unsigned char));
	diphone_arry = zh_y_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-z")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_z_raw_len * sizeof(unsigned char));
	diphone_arry = zh_z_raw;
	
	}
	if (g_strcmp0(diphone_str,"zh-zh")==0) { 
	diphone_arry = (unsigned char*)malloc(zh_zh_raw_len * sizeof(unsigned char));
	diphone_arry = zh_zh_raw;	
	}
				
	return diphone_arry;
}

//---------------------------------------------------------------------

unsigned int load_diphone_len(char* diphone_str)
{
	
	unsigned int len =0;
		    
	    
	   if (g_strcmp0(diphone_str,"aa-aa")==0) { 
	   len=aa_aa_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ae")==0) { 
	   len=aa_ae_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"aa-ah")==0) { 
	   len=aa_ah_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ao")==0) { 
	   len=aa_ao_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-aw")==0) { 
	   len=aa_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ax")==0) { 
	   len=aa_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ay")==0) { 
	   len=aa_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-b")==0) { 
	   len=aa_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ch")==0) { 
	   len=aa_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-d")==0) { 
	   len=aa_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-dh")==0) { 
	   len=aa_dh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-eh")==0) { 
	   len=aa_eh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-er")==0) { 
	   len=aa_er_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ey")==0) { 
	   len=aa_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-f")==0) { 
	   len=aa_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-g")==0) { 
	   len=aa_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-hh")==0) { 
	   len=aa_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ih")==0) { 
	   len=aa_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-iy")==0) { 
	   len=aa_iy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-jh")==0) { 
	   len=aa_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-k")==0) { 
	   len=aa_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-l")==0) { 
	   len=aa_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-m")==0) { 
	   len=aa_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-n")==0) { 
	   len=aa_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ng")==0) { 
	   len=aa_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-ow")==0) { 
	   len=aa_ow_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-oy")==0) { 
	   len=aa_oy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-p")==0) { 
	   len=aa_p_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-pau")==0) { 
	   len=aa_pau_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-r")==0) { 
	   len=aa_r_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-s")==0) { 
	   len=aa_s_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-sh")==0) { 
	   len=aa_sh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-t")==0) { 
	   len=aa_t_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-th")==0) { 
	   len=aa_th_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-uh")==0) { 
	   len=aa_uh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-uw")==0) { 
	   len=aa_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-v")==0) { 
	   len=aa_v_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-w")==0) { 
	   len=aa_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aa-y")==0) { 
	   len=aa_y_raw_len;	
	   }
	   if (g_strcmp0(diphone_str,"aa-z")==0) { 
	   len=aa_z_raw_len;	   
	   }
	   if (g_strcmp0(diphone_str,"aa-zh")==0) { 
	   len=aa_zh_raw_len;	   
	   }
	   
	   //ae diphones
	   if (g_strcmp0(diphone_str,"ae-aa")==0) { 
	   len=ae_aa_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ae")==0) { 
	   len=ae_ae_raw_len; 
	   }
	   if (g_strcmp0(diphone_str,"ae-ah")==0) { 
	   len=ae_ah_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ao")==0) { 
	   len=ae_ao_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-aw")==0) { 
	   len=ae_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ax")==0) { 
	   len=ae_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ay")==0) { 
	   len=ae_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-b")==0) { 
	   len=ae_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ch")==0) { 
	   len=ae_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-d")==0) { 
	   len=ae_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-dh")==0) { 
	   len=ae_dh_raw_len;
	   }
	    
	   if (g_strcmp0(diphone_str,"ae-eh")==0) { 
	   len=ae_eh_raw_len;	   
	   }
	   if (g_strcmp0(diphone_str,"ae-er")==0) { 
	   len=ae_er_raw_len;	   
	   }
	   if (g_strcmp0(diphone_str,"ae-ey")==0) { 
	   len=ae_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-f")==0) { 
	   len=ae_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-g")==0) { 
	   len=ae_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-hh")==0) { 
	   len=ae_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ih")==0) { 
	   len=ae_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-iy")==0) { 
	   len=ae_iy_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"ae-jh")==0) { 
	   len=ae_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-k")==0) { 
	   len=ae_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-l")==0) { 
	   len=ae_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-m")==0) { 
	   len=ae_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-n")==0) { 
	   len=ae_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ng")==0) { 
	   len=ae_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-ow")==0) { 
	   len=ae_ow_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-oy")==0) { 
	   len=ae_oy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-p")==0) { 
	   len=ae_p_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-pau")==0) { 
	   len=ae_pau_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-r")==0) { 
	   len=ae_r_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-s")==0) { 
	   len=ae_s_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-sh")==0) { 
	   len=ae_sh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-t")==0) { 
	   len=ae_t_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-th")==0) { 
	   len=ae_th_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-uh")==0) { 
	   len=ae_uh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-uw")==0) { 
	   len=ae_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-v")==0) { 
	   len=ae_v_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"ae-y")==0) { 
	   len=ae_y_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-z")==0) { 
	   len=ae_z_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ae-zh")==0) { 
	   len=ae_zh_raw_len;
	   }
	   
	   
	   //ah diphones
	   if (g_strcmp0(diphone_str,"ah-aa")==0) { 
	   len=ah_aa_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ae")==0) { 
	   len=ah_ae_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ah")==0) { 
	   len=ah_ah_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ao")==0) { 
	   len=ah_ao_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-aw")==0) { 
	   len=ah_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ax")==0) { 
	   len=ah_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ay")==0) { 
	   len=ah_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-b")==0) { 
	   len=ah_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ch")==0) { 
	   len=ah_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-d")==0) { 
	   len=ah_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-dh")==0) { 
	   len=ah_dh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-eh")==0) { 
	   len=ah_eh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-er")==0) { 
	   len=ah_er_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ey")==0) { 
	   len=ah_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-f")==0) { 
	   len=ah_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-g")==0) { 
	   len=ah_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-hh")==0) { 
	   len=ah_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ih")==0) { 
	   len=ah_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-iy")==0) { 
	   len=ah_iy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-jh")==0) { 
	   len=ah_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-k")==0) { 
	   len=ah_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-l")==0) { 
	   len=ah_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-m")==0) { 
	   len=ah_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-n")==0) { 
	   len=ah_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ng")==0) { 
	   len=ah_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-ow")==0) { 
	   len=ah_ow_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-oy")==0) { 
	   len=ah_oy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-p")==0) { 
	   len=ah_p_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-pau")==0) { 
	   len=ah_pau_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-r")==0) { 
	   len=ah_r_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-s")==0) { 
	   len=ah_s_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-sh")==0) { 
	   len=ah_sh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-t")==0) { 
	   len=ah_t_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-th")==0) { 
	   len=ah_th_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-uh")==0) { 
	   len=ah_uh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-uw")==0) { 
	   len=ah_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-v")==0) { 
	   len=ah_v_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-w")==0) { 
	   len=ah_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-y")==0) { 
	   len=ah_y_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-z")==0) { 
	   len=ah_z_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ah-zh")==0) { 
	   len=ah_zh_raw_len;
	   }
	   
	   //ao diphones	
	   if (g_strcmp0(diphone_str,"ao-aa")==0) { 
	   len=ao_aa_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ae")==0) { 
	   len=ao_ae_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ah")==0) { 
	   len=ao_ah_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ao")==0) { 
	   len=ao_ao_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-aw")==0) { 
	   len=ao_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ax")==0) { 
	   len=ao_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ay")==0) { 
	   len=ao_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-b")==0) { 
	   len=ao_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ch")==0) { 
	   len=ao_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-d")==0) { 
	   len=ao_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-dh")==0) { 
	   len=ao_dh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-eh")==0) { 
	   len=ao_eh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-er")==0) { 
	   len=ao_er_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ey")==0) { 
	   len=ao_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-f")==0) { 
	   len=ao_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-g")==0) { 
	   len=ao_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-hh")==0) { 
	   len=ao_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ih")==0) { 
	   len=ao_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-iy")==0) { 
	   len=ao_iy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-jh")==0) { 
	   len=ao_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-k")==0) { 
	   len=ao_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-l")==0) { 
	   len=ao_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-m")==0) { 
	   len=ao_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-n")==0) { 
	   len=ao_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ng")==0) { 
	   len=ao_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-ow")==0) { 
	   len=ao_ow_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-oy")==0) { 
	   len=ao_oy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-p")==0) { 
	   len=ao_p_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-pau")==0) { 
	   len=ao_pau_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-r")==0) { 
	   len=ao_r_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-s")==0) { 
	   len=ao_s_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-sh")==0) { 
	   len=ao_sh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-t")==0) { 
	   len=ao_t_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-th")==0) { 
	   len=ao_th_raw_len;
	   }	
	   if (g_strcmp0(diphone_str,"ao-uh")==0) { 
	   len=ao_uh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-uw")==0) { 
	   len=ao_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-v")==0) { 
	   len=ao_v_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-w")==0) { 
	   len=ao_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-y")==0) { 
	   len=ao_y_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-z")==0) { 
	   len=ao_z_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ao-zh")==0) { 
	   len=ao_zh_raw_len;
	   }
	   
	   //aw diphones
	   if (g_strcmp0(diphone_str,"aw-aa")==0) { 
	   len=aw_aa_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ae")==0) { 
	   len=aw_ae_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ah")==0) { 
	   len=aw_ah_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ao")==0) { 
	   len=aw_ao_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-aw")==0) { 
	   len=aw_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ax")==0) { 
	   len=aw_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ay")==0) { 
	   len=aw_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-b")==0) { 
	   len=aw_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ch")==0) { 
	   len=aw_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-d")==0) { 
	   len=aw_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-dh")==0) { 
	   len=aw_dh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-eh")==0) { 
	   len=aw_eh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-er")==0) { 
	   len=aw_er_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ey")==0) { 
	   len=aw_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-f")==0) { 
	   len=aw_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-g")==0) { 
	   len=aw_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-hh")==0) { 
	   len=aw_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ih")==0) { 
	   len=aw_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-iy")==0) { 
	   len=aw_iy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-jh")==0) {
	   len=aw_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-k")==0) { 
	   len=aw_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-l")==0) { 
	   len=aw_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-m")==0) { 
	   len=aw_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-n")==0) { 
	   len=aw_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ng")==0) { 
	   len=aw_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-ow")==0) { 
	   len=aw_ow_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-oy")==0) { 
	   len=aw_oy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-p")==0) { 
	   len=aw_p_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-pau")==0) { 
	   len=aw_pau_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-r")==0) { 
	   len=aw_r_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-s")==0) { 
	   len=aw_s_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-sh")==0) { 
	   len=aw_sh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-t")==0) { 
	   len=aw_t_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-th")==0) { 
	   len=aw_th_raw_len;
	   }	
	   if (g_strcmp0(diphone_str,"aw-uh")==0) { 
	   len=aw_uh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-uw")==0) { 
	   len=aw_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-v")==0) { 
	   len=aw_v_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-w")==0) { 
	   len=aw_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-y")==0) { 
	   len=aw_y_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-z")==0) { 
	   len=aw_z_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"aw-zh")==0) { 
	   len=aw_zh_raw_len;
	   }
	   
	   //ax diphones
	   if (g_strcmp0(diphone_str,"ax-aa")==0) { 
	   len=ax_aa_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ae")==0) { 
	   len=ax_ae_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ah")==0) { 
	   len=ax_ah_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ao")==0) { 
	   len=ax_ao_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-aw")==0) { 
	   len=ax_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ax")==0) { 
	   len=ax_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ay")==0) { 
	   len=ax_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-b")==0) { 
	   len=ax_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ch")==0) { 
	   len=ax_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-d")==0) { 
	   len=ax_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-dh")==0) { 
	   len=ax_dh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-eh")==0) { 
	   len=ax_eh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-er")==0) { 
	   len=ax_er_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ey")==0) { 
	   len=ax_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-f")==0) { 
	   len=ax_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-g")==0) { 
	   len=ax_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-hh")==0) { 
	   len=ax_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ih")==0) { 
	   len=ax_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-iy")==0) { 
	   len=ax_iy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-jh")==0) { 
	   len=ax_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-k")==0) { 
	   len=ax_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-l")==0) { 
	   len=ax_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-m")==0) { 
	   len=ax_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-n")==0) {
	   len=ax_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ng")==0) { 
	   len=ax_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-ow")==0) { 
	   len=ax_ow_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-oy")==0) { 
	   len=ax_oy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-p")==0) { 
	   len=ax_p_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-pau")==0) { 
	   len=ax_pau_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-r")==0) { 
	   len=ax_r_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-s")==0) { 
	   len=ax_s_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-sh")==0) { 
	   len=ax_sh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-t")==0) { 
	   len=ax_t_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-th")==0) { 
	   len=ax_th_raw_len;
	   }	
	   if (g_strcmp0(diphone_str,"ax-uh")==0) { 
	   len=ax_uh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-uw")==0) { 
	   len=ax_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-v")==0) { 
	   len=ax_v_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-w")==0) { 
	   len=ax_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-y")==0) { 
	   len=ax_y_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-z")==0) { 
	   len=ax_z_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ax-zh")==0) { 
	   len=ax_zh_raw_len;
	   }
	   
	   //ay diphones
	   if (g_strcmp0(diphone_str,"ay-aa")==0) { 
	   len=ay_aa_raw_len;
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-ae")==0) { 
	   len=ay_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-ah")==0) { 
	   len=ay_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-ao")==0) { 
	   len=ay_ao_raw_len;  
	   }
	   if (g_strcmp0(diphone_str,"ay-aw")==0) { 
	   len=ay_aw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ax")==0) { 
	   len=ay_ax_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ay")==0) { 
	   len=ay_ay_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-b")==0) { 
	   len=ay_b_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ch")==0) { 
	   len=ay_ch_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-d")==0) { 
	   len=ay_d_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-dh")==0) { 
	   len=ay_dh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-eh")==0) { 
	   len=ay_eh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-er")==0) { 
	   len=ay_er_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ey")==0) { 
	   len=ay_ey_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-f")==0) { 
	   len=ay_f_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-g")==0) { 
	   len=ay_g_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-hh")==0) { 
	   len=ay_hh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ih")==0) {
	   len=ay_ih_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-iy")==0) { 
	   len=ay_iy_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-jh")==0) { 
	   len=ay_jh_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-k")==0) { 
	   len=ay_k_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-l")==0) { 
	   len=ay_l_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-m")==0) { 
	   len=ay_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-n")==0) { 
	   len=ay_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ng")==0) { 
	   len=ay_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ay-ow")==0) { 
	   len=ay_ow_raw_len;
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-oy")==0) { 
	   len=ay_oy_raw_len;
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-p")==0) { 
	   len=ay_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-pau")==0) { 
	   len=ay_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-r")==0) { 
	   len=ay_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-s")==0) { 
	   len=ay_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-sh")==0) { 
	   len=ay_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-t")==0) { 
	   len=ay_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-th")==0) { 
	   len=ay_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"ay-uh")==0) { 
	   len=ay_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-uw")==0) { 
	   len=ay_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-v")==0) { 
	   len=ay_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-w")==0) { 
	   len=ay_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-y")==0) { 
	   len=ay_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-z")==0) { 
	   len=ay_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ay-zh")==0) { 
	   len=ay_zh_raw_len;	  
	   }
	   
	   //b diphones
	   if (g_strcmp0(diphone_str,"b-aa")==0) { 
	   len=b_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ae")==0) { 
	   len=b_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ah")==0) { 
	   len=b_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ao")==0) { 
	   len=b_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-aw")==0) { 
	   len=b_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ax")==0) { 
	   len=b_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ay")==0) { 
	   len=b_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-b")==0) { 
	   len=b_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ch")==0) { 
	   len=b_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-d")==0) { 
	   len=b_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-dh")==0) { 
	   len=b_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-eh")==0) { 
	   len=b_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-er")==0) { 
	   len=b_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ey")==0) { 
	   len=b_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-f")==0) { 
	   len=b_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-g")==0) { 
	   len=b_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-hh")==0) { 
	   len=b_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-ih")==0) { 
	   len=b_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-iy")==0) { 
	   len=b_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-jh")==0) { 
	   len=b_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-k")==0) { 
	   len=b_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-l")==0) { 
	   len=b_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-m")==0) { 
	   len=b_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-n")==0) { 
	   len=b_n_raw_len;
	   
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"b-ow")==0) { 
	   len=b_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-oy")==0) { 
	   len=b_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-p")==0) { 
	   len=b_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-pau")==0) { 
	   len=b_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-r")==0) { 
	   len=b_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-s")==0) { 
	   len=b_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-sh")==0) { 
	   len=b_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-t")==0) { 
	   len=b_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-th")==0) { 
	   len=b_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"b-uh")==0) { 
	   len=b_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-uw")==0) { 
	   len=b_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-v")==0) { 
	   len=b_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-w")==0) { 
	   len=b_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-y")==0) { 
	   len=b_y_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"b-z")==0) { 
	   len=b_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"b-zh")==0) { 
	   len=b_zh_raw_len;
	   
	   }
	   
	   
	   //ch diphones
	   if (g_strcmp0(diphone_str,"ch-aa")==0) { 
	   len=ch_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ae")==0) { 
	   len=ch_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ah")==0) { 
	   len=ch_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ao")==0) { 
	   len=ch_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-aw")==0) { 
	   len=ch_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ax")==0) { 
	   len=ch_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ay")==0) { 
	   len=ch_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-b")==0) { 
	   len=ch_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ch")==0) { 
	   len=ch_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-d")==0) { 
	   len=ch_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-dh")==0) { 
	   len=ch_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-eh")==0) { 
	   len=ch_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-er")==0) { 
	   len=ch_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ey")==0) { 
	   len=ch_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-f")==0) { 
	   len=ch_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-g")==0) { 
	   len=ch_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-hh")==0) { 
	   len=ch_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ih")==0) { 
	   len=ch_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-iy")==0) { 
	   len=ch_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-jh")==0) { 
	   len=ch_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-k")==0) { 
	   len=ch_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-l")==0) { 
	   len=ch_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-m")==0) { 
	   len=ch_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-n")==0) { 
	   len=ch_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-ow")==0) { 
	   len=ch_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-oy")==0) { 
	   len=ch_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-p")==0) { 
	   len=ch_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-pau")==0) { 
	   len=ch_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-r")==0) { 
	   len=ch_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-s")==0) { 
	   len=ch_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-sh")==0) { 
	   len=ch_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-t")==0) { 
	   len=ch_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-th")==0) { 
	   len=ch_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"ch-uh")==0) { 
	   len=ch_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-uw")==0) { 
	   len=ch_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-v")==0) { 
	   len=ch_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-w")==0) { 
	   len=ch_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-y")==0) { 
	   len=ch_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-z")==0) { 
	   len=ch_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ch-zh")==0) { 
	   len=ch_zh_raw_len;
	   
	   }
	   
	   //d diphones
	   if (g_strcmp0(diphone_str,"d-aa")==0) { 
	   len=d_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ae")==0) { 
	   len=d_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ah")==0) { 
	   len=d_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ao")==0) { 
	   len=d_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-aw")==0) { 
	   len=d_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ax")==0) { 
	   len=d_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ay")==0) { 
	   len=d_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-b")==0) { 
	   len=d_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ch")==0) { 
	   len=d_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-d")==0) { 
	   len=d_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-dh")==0) { 
	   len=d_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-eh")==0) { 
	   len=d_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-er")==0) { 
	   len=d_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ey")==0) { 
	   len=d_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-f")==0) { 
	   len=d_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-g")==0) { 
	   len=d_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-hh")==0) { 
	   len=d_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-ih")==0) { 
	   len=d_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-iy")==0) { 
	   len=d_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-jh")==0) { 
	   len=d_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-k")==0) { 
	   len=d_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-l")==0) { 
	   len=d_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-m")==0) { 
	   len=d_m_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"d-n")==0) { 
	   len=d_n_raw_len;
	   }
	 	   
	   if (g_strcmp0(diphone_str,"d-ow")==0) { 
	   len=d_ow_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"d-oy")==0) { 
	   len=d_oy_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"d-p")==0) { 
	   len=d_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-pau")==0) { 
	   len=d_pau_raw_len;
	   
	   }
	   if (g_strcmp0(diphone_str,"d-r")==0) { 
	   len=d_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-s")==0) { 
	   len=d_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-sh")==0) { 
	   len=d_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-t")==0) { 
	   len=d_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-th")==0) { 
	   len=d_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"d-uh")==0) { 
	   len=d_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-uw")==0) { 
	   len=d_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-v")==0) { 
	   len=d_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-w")==0) { 
	   len=d_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-y")==0) { 
	   len=d_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-z")==0) { 
	   len=d_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"d-zh")==0) { 
	   len=d_zh_raw_len;
	   
	   
	   }
	   
	   //dh diphones
	   if (g_strcmp0(diphone_str,"dh-aa")==0) { 
	   len=dh_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ae")==0) { 
	   len=dh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ah")==0) { 
	   len=dh_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ao")==0) { 
	   len=dh_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-aw")==0) { 
	   len=dh_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ax")==0) { 
	   len=dh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ay")==0) { 
	   len=dh_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-b")==0) { 
	   len=dh_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ch")==0) { 
	   len=dh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-d")==0) { 
	   len=dh_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-dh")==0) { 
	   len=dh_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-eh")==0) { 
	   len=dh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-er")==0) { 
	   len=dh_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ey")==0) { 
	   len=dh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-f")==0) { 
	   len=dh_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-g")==0) { 
	   len=dh_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-hh")==0) { 
	   len=dh_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ih")==0) { 
	   len=dh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-iy")==0) { 
	   len=dh_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-jh")==0) { 
	   len=dh_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-k")==0) { 
	   len=dh_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-l")==0) { 
	   len=dh_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-m")==0) { 
	   len=dh_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-n")==0) { 
	   len=dh_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-ow")==0) { 
	   len=dh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-oy")==0) { 
	   len=dh_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-p")==0) { 
	   len=dh_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-pau")==0) { 
	   len=dh_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-r")==0) { 
	   len=dh_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-s")==0) { 
	   len=dh_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-sh")==0) { 
	   len=dh_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-t")==0) { 
	   len=dh_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-th")==0) { 
	   len=dh_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"dh-uh")==0) { 
	   len=dh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-uw")==0) { 
	   len=dh_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-v")==0) { 
	   len=dh_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-w")==0) { 
	   len=dh_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-y")==0) { 
	   len=dh_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-z")==0) { 
	   len=dh_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"dh-zh")==0) { 
	   len=dh_zh_raw_len;
	   
	   
	   }
	   
	   //eh diphones
	   if (g_strcmp0(diphone_str,"eh-aa")==0) { 
	   len=eh_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ae")==0) { 
	   len=eh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ah")==0) { 
	   len=eh_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ao")==0) { 
	   len=eh_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-aw")==0) { 
	   len=eh_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ax")==0) { 
	   len=eh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ay")==0) { 
	   len=eh_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-b")==0) { 
	   len=eh_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ch")==0) { 
	   len=eh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-d")==0) { 
	   len=eh_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-dh")==0) { 
	   len=eh_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-eh")==0) { 
	   len=eh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-er")==0) { 
	   len=eh_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ey")==0) { 
	   len=eh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-f")==0) { 
	   len=eh_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-g")==0) { 
	   len=eh_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-hh")==0) { 
	   len=eh_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ih")==0) { 
	   len=eh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-iy")==0) { 
	   len=eh_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-jh")==0) { 
	   len=eh_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-k")==0) { 
	   len=eh_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-l")==0) { 
	   len=eh_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-m")==0) { 
	   len=eh_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-n")==0) { 
	   len=eh_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ng")==0) { 
	   len=eh_ng_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-ow")==0) { 
	   len=eh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-oy")==0) { 
	   len=eh_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-p")==0) { 
	   len=eh_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-pau")==0) { 
	   len=eh_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-r")==0) { 
	   len=eh_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-s")==0) { 
	   len=eh_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-sh")==0) { 
	   len=eh_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-t")==0) { 
	   len=eh_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-th")==0) { 
	   len=eh_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"eh-uh")==0) { 
	   len=eh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-uw")==0) { 
	   len=eh_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-v")==0) { 
	   len=eh_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-w")==0) { 
	   len=eh_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-y")==0) { 
	   len=eh_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-z")==0) { 
	   len=eh_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"eh-zh")==0) { 
	   len=eh_zh_raw_len;
	   
	   }
	   
	   
	   // er diphones
	   
	   if (g_strcmp0(diphone_str,"er-aa")==0) { 
	   len=er_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ae")==0) { 
	   len=er_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ah")==0) { 
	   len=er_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ao")==0) { 
	   len=er_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-aw")==0) { 
	   len=er_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ax")==0) { 
	   len=er_ax_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"er-ay")==0) { 
	   len=er_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-b")==0) { 
	   len=er_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ch")==0) { 
	   len=er_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-d")==0) { 
	   len=er_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-dh")==0) { 
	   len=er_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-eh")==0) { 
	   len=er_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-er")==0) { 
	   len=er_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ey")==0) { 
	   len=er_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-f")==0) { 
	   len=er_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-g")==0) { 
	   len=er_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-hh")==0) { 
	   len=er_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ih")==0) { 
	   len=er_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-iy")==0) { 
	   len=er_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-jh")==0) { 
	   len=er_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-k")==0) { 
	   len=er_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-l")==0) { 
	   len=er_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-m")==0) { 
	   len=er_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-n")==0) { 
	   len=er_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-ow")==0) {
	   len=er_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-oy")==0) { 
	   len=er_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-p")==0) { 
	   len=er_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-pau")==0) { 
	   len=er_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-r")==0) { 
	   len=er_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-s")==0) { 
	   len=er_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-sh")==0) { 
	   len=er_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-t")==0) { 
	   len=er_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-th")==0) { 
	   len=er_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"er-uh")==0) { 
	   len=er_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-uw")==0) { 
	   len=er_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-v")==0) { 
	   len=er_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-w")==0) { 
	   len=er_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-y")==0) { 
	   len=er_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-z")==0) { 
	   len=er_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"er-zh")==0) { 
	   len=er_zh_raw_len;
	   
	   }
	   
	   //ey diphones
	   if (g_strcmp0(diphone_str,"ey-aa")==0) { 
	   len=ey_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ae")==0) { 
	   len=ey_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ah")==0) { 
	   len=ey_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ao")==0) { 
	   len=ey_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-aw")==0) { 
	   len=ey_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ax")==0) { 
	   len=ey_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ay")==0) { 
	   len=ey_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-b")==0) { 
	   len=ey_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ch")==0) { 
	   len=eh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-d")==0) { 
	   len=ey_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-dh")==0) { 
	   len=ey_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-eh")==0) { 
	   len=eh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-er")==0) { 
	   len=ey_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ey")==0) { 
	   len=ey_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-f")==0) { 
	   len=ey_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-g")==0) { 
	   len=ey_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-hh")==0) { 
	   len=ey_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ih")==0) { 
	   len=ey_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-iy")==0) { 
	   len=ey_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-jh")==0) { 
	   len=ey_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-k")==0) { 
	   len=ey_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-l")==0) { 
	   len=ey_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-m")==0) { 
	   len=ey_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-n")==0) { 
	   len=ey_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ng")==0) { 
	   len=ey_ng_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-ow")==0) { 
	   len=ey_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-oy")==0) { 
	   len=ey_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-p")==0) { 
	   len=ey_p_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"ey-pau")==0) { 
	   len=ey_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-r")==0) { 
	   len=ey_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-s")==0) { 
	   len=ey_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-sh")==0) { 
	   len=ey_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-t")==0) { 
	   len=ey_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-th")==0) {
	   len=ey_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"ey-uh")==0) { 
	   len=ey_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-uw")==0) { 
	   len=ey_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-v")==0) { 
	   len=ey_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-w")==0) { 
	   len=ey_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-y")==0) { 
	   len=ey_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-z")==0) { 
	   len=ey_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ey-zh")==0) { 
	   len=ey_zh_raw_len;
	   
	   }
	   
	   //f diphones
	   if (g_strcmp0(diphone_str,"f-aa")==0) { 
	   len=f_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ae")==0) { 
	   len=f_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ah")==0) { 
	   len=f_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ao")==0) { 
	   len=f_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-aw")==0) { 
	   len=f_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ax")==0) { 
	   len=f_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ay")==0) { 
	   len=f_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-b")==0) { 
	   len=f_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ch")==0) { 
	   len=f_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-d")==0) { 
	   len=f_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-dh")==0) { 
	   len=f_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-eh")==0) { 
	   len=f_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-er")==0) { 
	   len=f_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ey")==0) { 
	   len=f_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-f")==0) { 
	   len=f_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-g")==0) { 
	   len=f_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-hh")==0) { 
	   len=f_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-ih")==0) { 
	   len=f_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-iy")==0) { 
	   len=f_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-jh")==0) { 
	   len=f_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-k")==0) { 
	   len=f_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-l")==0) { 
	   len=f_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-m")==0) { 
	   len=f_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-n")==0) { 
	   len=f_n_raw_len;
	   
	   
	   }
	   //if (g_strcmp0(diphone_str,"f-ng")==0) { 
	   //len=f_ng_raw_len;
	   //}
	   
	   if (g_strcmp0(diphone_str,"f-oy")==0) { 
	   len=f_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-p")==0) { 
	   len=f_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-pau")==0) { 
	   len=f_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-r")==0) { 
	   len=f_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-s")==0) { 
	   len=f_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-sh")==0) { 
	   len=f_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-t")==0) { 
	   len=f_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-th")==0) { 
	   len=f_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"f-uh")==0) { 
	   len=f_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-uw")==0) { 
	   len=f_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-v")==0) { 
	   len=f_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-w")==0) { 
	   len=f_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-y")==0) { 
	   len=f_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-z")==0) { 
	   len=f_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"f-zh")==0) { 
	   len=f_zh_raw_len;
	   
	   }
	   
	   //g diphones
	   if (g_strcmp0(diphone_str,"g-aa")==0) { 
	   len=g_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ae")==0) { 
	   len=g_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ah")==0) { 
	   len=g_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ao")==0) { 
	   len=g_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-aw")==0) { 
	   len=g_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ax")==0) { 
	   len=g_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ay")==0) { 
	   len=g_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-b")==0) { 
	   len=g_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ch")==0) { 
	   len=g_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-d")==0) {
	   len=g_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-dh")==0) { 
	   len=g_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-eh")==0) { 
	   len=g_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-er")==0) { 
	   len=g_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ey")==0) { 
	   len=g_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-f")==0) { 
	   len=g_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-g")==0) { 
	   len=g_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-hh")==0) { 
	   len=g_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ih")==0) { 
	   len=g_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-iy")==0) { 
	   len=g_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-jh")==0) { 
	   len=g_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-k")==0) { 
	   len=g_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-l")==0) { 
	   len=g_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-m")==0) { 
	   len=g_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-n")==0) { 
	   len=g_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-ow")==0) { 
	   len=g_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-oy")==0) { 
	   len=g_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-p")==0) { 
	   len=g_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-pau")==0) { 
	   len=g_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-r")==0) { 
	   len=g_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-s")==0) { 
	   len=g_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-sh")==0) { 
	   len=g_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-t")==0) { 
	   len=g_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-th")==0) { 
	   len=g_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"g-uh")==0) { 
	   len=g_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-uw")==0) { 
	   len=g_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-v")==0) { 
	   len=g_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-w")==0) { 
	   len=g_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-y")==0) { 
	   len=g_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-z")==0) { 
	   len=g_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"g-zh")==0) { 
	   len=g_zh_raw_len;
	   
	   }
	   
	
	   //hh diphones
	   if (g_strcmp0(diphone_str,"hh-aa")==0) { 
	   len=hh_aa_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"hh-ae")==0) { 
	   len=hh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-ah")==0) { 
	   len=hh_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-ao")==0) { 
	   len=hh_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-aw")==0) { 
	   len=hh_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-ax")==0) { 
	   len=hh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-ay")==0) { 
	   len=hh_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-eh")==0) { 
	   len=hh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-ey")==0) { 
	   len=hh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-ih")==0) { 
	   len=hh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-iy")==0) { 
	   len=hh_iy_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"hh-ow")==0) { 
	   len=hh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-oy")==0) { 
	   len=hh_oy_raw_len;
	   
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"hh-uh")==0) { 
	   len=hh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"hh-uw")==0) { 
	   len=hh_uw_raw_len;
	   
	   
	   }
	   
	   
	   //ih diphones
	   if (g_strcmp0(diphone_str,"ih-aa")==0) { 
	   len=ih_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ae")==0) { 
	   len=ih_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ah")==0) { 
	   len=ih_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ao")==0) { 
	   len=ih_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-aw")==0) { 
	   len=ih_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ax")==0) { 
	   len=ih_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ay")==0) { 
	   len=ih_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-b")==0) { 
	   len=ih_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ch")==0) { 
	   len=ih_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-d")==0) { 
	   len=ih_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-dh")==0) { 
	   len=ih_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-eh")==0) { 
	   len=ih_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-er")==0) { 
	   len=ih_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ey")==0) { 
	   len=ih_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-f")==0) { 
	   len=ih_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-g")==0) { 
	   len=ih_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-hh")==0) { 
	   len=ih_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ih")==0) { 
	   len=ih_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-iy")==0) { 
	   len=ih_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-jh")==0) { 
	   len=ih_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-k")==0) { 
	   len=ih_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-l")==0) { 
	   len=ih_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-m")==0) { 
	   len=ih_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-n")==0) { 
	   len=ih_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ng")==0) { 
	   len=ih_ng_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-ow")==0) { 
	   len=ih_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-oy")==0) { 
	   len=ih_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-p")==0) { 
	   len=ih_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-pau")==0) { 
	   len=ih_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-r")==0) { 
	   len=ih_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-s")==0) { 
	   len=ih_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-sh")==0) { 
	   len=ih_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-t")==0) { 
	   len=ih_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-th")==0) { 
	   len=ih_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"ih-uh")==0) { 
	   len=ih_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-uw")==0) { 
	   len=ih_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-v")==0) { 
	   len=ih_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-w")==0) { 
	   len=ih_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-y")==0) { 
	   len=ih_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-z")==0) { 
	   len=ih_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ih-zh")==0) { 
	   len=ih_zh_raw_len;
	   
	   }
	   
	   
	   //iy diphones
	   if (g_strcmp0(diphone_str,"iy-aa")==0) { 
	   len=iy_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ae")==0) { 
	   len=iy_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ah")==0) { 
	   len=iy_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ao")==0) { 
	   len=iy_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-aw")==0) { 
	   len=iy_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ax")==0) { 
	   len=iy_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ay")==0) { 
	   len=iy_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-b")==0) { 
	   len=iy_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ch")==0) { 
	   len=iy_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-d")==0) { 
	   len=iy_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-dh")==0) { 
	   len=iy_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-eh")==0) { 
	   len=iy_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-er")==0) { 
	   len=iy_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ey")==0) { 
	   len=iy_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-f")==0) { 
	   len=iy_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-g")==0) { 
	   len=iy_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-hh")==0) { 
	   len=iy_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ih")==0) { 
	   len=iy_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-iy")==0) { 
	   len=iy_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-jh")==0) { 
	   len=iy_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-k")==0) {
	   len=iy_k_raw_len;
	   
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"iy-l")==0) { 
	   len=iy_l_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"iy-m")==0) { 
	   len=iy_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-n")==0) { 
	   len=iy_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ng")==0) { 
	   len=iy_ng_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-ow")==0) { 
	   len=iy_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-oy")==0) {
	   len=iy_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-p")==0) { 
	   len=iy_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-pau")==0) { 
	   len=iy_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-r")==0) { 
	   len=iy_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-s")==0) { 
	   len=iy_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-sh")==0) { 
	   len=iy_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-t")==0) { 
	   len=iy_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-th")==0) { 
	   len=iy_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"iy-uh")==0) { 
	   len=iy_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-uw")==0) { 
	   len=iy_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-v")==0) { 
	   len=iy_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-w")==0) { 
	   len=iy_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-y")==0) { 
	   len=iy_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-z")==0) { 
	   len=iy_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"iy-zh")==0) { 
	   len=iy_zh_raw_len;
	   
	   }
	   
	   //jh diphones
	   if (g_strcmp0(diphone_str,"jh-aa")==0) { 
	   len=jh_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ae")==0) { 
	   len=jh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ah")==0) { 
	   len=jh_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ao")==0) { 
	   len=jh_ao_raw_len;
	   
	   
	   }
	  
	   if (g_strcmp0(diphone_str,"jh-aw")==0) { 
	   len=jh_aw_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"jh-ax")==0) { 
	   len=jh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ay")==0) { 
	   len=jh_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-b")==0) { 
	   len=jh_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ch")==0) { 
	   len=jh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-d")==0) { 
	   len=jh_d_raw_len;
	   
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"jh-dh")==0) { 
	   len=jh_dh_raw_len; 
	   }
	   
	   if (g_strcmp0(diphone_str,"jh-eh")==0) { 
	   len=jh_eh_raw_len;	   
	   }
	   
	   
	   if (g_strcmp0(diphone_str,"jh-er")==0) { 
	   len=jh_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ey")==0) { 
	   len=jh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-f")==0) { 
	   len=jh_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-g")==0) { 
	   len=jh_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-hh")==0) { 
	   len=jh_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ih")==0) { 
	   len=jh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-iy")==0) { 
	   len=jh_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-jh")==0) { 
	   len=jh_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-k")==0) { 
	   len=jh_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-l")==0) { 
	   len=jh_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-m")==0) { 
	   len=jh_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-n")==0) { 
	   len=jh_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-ow")==0) { 
	   len=jh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-oy")==0) { 
	   len=jh_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-p")==0) { 
	   len=jh_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-pau")==0) { 
	   len=jh_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-r")==0) { 
	   len=jh_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-s")==0) { 
	   len=jh_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-sh")==0) { 
	   len=jh_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-t")==0) { 
	   len=jh_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-th")==0) { 
	   len=jh_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"jh-uh")==0) { 
	   len=jh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-uw")==0) { 
	   len=jh_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-v")==0) { 
	   len=jh_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-w")==0) { 
	   len=jh_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-y")==0) { 
	   len=jh_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-z")==0) {
	   len=jh_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"jh-zh")==0) { 
	   len=jh_zh_raw_len;
	   
	   }
	   
	   //k diphones
	   
	   if (g_strcmp0(diphone_str,"k-aa")==0) { 
	   len=k_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ae")==0) { 
	   len=k_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ah")==0) { 
	   len=k_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ao")==0) {
	   len=k_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-aw")==0) { 
	   len=k_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ax")==0) { 
	   len=k_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ay")==0) { 
	   len=k_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-b")==0) { 
	   len=k_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ch")==0) { 
	   len=k_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-d")==0) { 
	   len=k_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-dh")==0) { 
	   len=k_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-eh")==0) { 
	   len=k_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-er")==0) { 
	   len=k_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ey")==0) { 
	   len=k_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-f")==0) { 
	   len=k_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-g")==0) { 
	   len=k_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-hh")==0) { 
	   len=k_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ih")==0) { 
	   len=k_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-iy")==0) { 
	   len=k_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-jh")==0) { 
	   len=k_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-k")==0) { 
	   len=k_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-l")==0) { 
	   len=k_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-m")==0) { 
	   len=k_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-n")==0) { 
	   len=k_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-ow")==0) { 
	   len=k_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-oy")==0) { 
	   len=k_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-p")==0) { 
	   len=k_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-pau")==0) { 
	   len=k_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-r")==0) { 
	   len=k_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-s")==0) { 
	   len=k_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-sh")==0) { 
	   len=k_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-t")==0) { 
	   len=k_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-th")==0) { 
	   len=k_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"k-uh")==0) { 
	   len=k_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-uw")==0) { 
	   len=k_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-v")==0) { 
	   len=k_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-w")==0) { 
	   len=k_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-y")==0) { 
	   len=k_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-z")==0) { 
	   len=k_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"k-zh")==0) { 
	   len=k_zh_raw_len;
	   
	   }
	   
	   //l diphones
	   if (g_strcmp0(diphone_str,"l-aa")==0) { 
	   len=l_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ae")==0) { 
	   len=l_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ah")==0) { 
	   len=l_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ao")==0) { 
	   len=l_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-aw")==0) { 
	   len=l_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ax")==0) { 
	   len=l_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ay")==0) { 
	   len=l_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-b")==0) { 
	   len=l_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ch")==0) { 
	   len=l_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-d")==0) { 
	   len=l_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-dh")==0) { 
	   len=l_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-eh")==0) { 
	   len=l_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-er")==0) { 
	   len=l_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ey")==0) { 
	   len=l_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-f")==0) { 
	   len=l_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-g")==0) { 
	   len=l_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-hh")==0) { 
	   len=l_hh_raw_len;
	  
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ih")==0) { 
	   len=l_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-iy")==0) { 
	   len=l_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-jh")==0) { 
	   len=l_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-k")==0) { 
	   len=l_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-l")==0) { 
	   len=l_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-m")==0) { 
	   len=l_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-n")==0) { 
	   len=l_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-ow")==0) { 
	   len=l_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-oy")==0) { 
	   len=l_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-p")==0) { 
	   len=l_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-pau")==0) { 
	   len=l_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-r")==0) { 
	   len=l_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-s")==0) { 
	   len=l_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-sh")==0) { 
	   len=l_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-t")==0) { 
	   len=l_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-th")==0) { 
	   len=l_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"l-uh")==0) { 
	   len=l_uh_raw_len;
	   
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"l-uw")==0) { 
	   len=l_uw_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"l-v")==0) { 
	   len=l_v_raw_len;	   
	   }
	   
	   if (g_strcmp0(diphone_str,"l-w")==0) { 
	   len=l_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"l-y")==0) { 
	   len=l_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-z")==0) { 
	   len=l_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"l-zh")==0) { 
	   len=l_zh_raw_len;
	   
	   }
	   
	   //m diphones
	   if (g_strcmp0(diphone_str,"m-aa")==0) { 
	   len=m_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ae")==0) { 
	   len=m_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ah")==0) { 
	   len=m_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ao")==0) { 
	   len=m_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-aw")==0) { 
	   len=m_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ax")==0) { 
	   len=m_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ay")==0) { 
	   len=m_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-b")==0) { 
	   len=m_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ch")==0) { 
	   len=m_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-d")==0) { 
	   len=m_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-dh")==0) { 
	   len=m_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-eh")==0) { 
	   len=m_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-er")==0) { 
	   len=m_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ey")==0) { 
	   len=m_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-f")==0) { 
	   len=m_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-g")==0) { 
	   len=m_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-hh")==0) { 
	   len=m_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ih")==0) { 
	   len=m_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-iy")==0) { 
	   len=m_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-jh")==0) { 
	   len=m_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-k")==0) { 
	   len=m_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-l")==0) { 
	   len=m_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-m")==0) { 
	   len=m_m_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"m-n")==0) { 
	   len=m_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-ow")==0) { 
	   len=m_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-oy")==0) { 
	   len=m_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-p")==0) { 
	   len=m_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-pau")==0) { 
	   len=m_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-r")==0) { 
	   len=m_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-s")==0) { 
	   len=m_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-sh")==0) { 
	   len=m_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-t")==0) { 
	   len=m_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-th")==0) { 
	   len=m_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"m-uh")==0) { 
	   len=m_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-uw")==0) { 
	   len=m_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-v")==0) { 
	   len=m_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-w")==0) { 
	   len=m_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-y")==0) { 
	   len=m_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-z")==0) { 
	   len=m_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"m-zh")==0) { 
	   len=m_zh_raw_len;
	   
	   }
	   
	   //n diphones
	   if (g_strcmp0(diphone_str,"n-aa")==0) { 
	   len=n_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ae")==0) { 
	   len=n_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ah")==0) { 
	   len=n_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ao")==0) { 
	   len=n_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-aw")==0) { 
	   len=n_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ax")==0) { 
	   len=n_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ay")==0) { 
	   len=n_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-b")==0) { 
	   len=n_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ch")==0) { 
	   len=n_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-d")==0) { 
	   len=n_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-dh")==0) { 
	   len=n_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-eh")==0) { 
	   len=n_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-er")==0) { 
	   len=n_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ey")==0) {
	   len=n_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-f")==0) { 
	   len=n_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-g")==0) { 
	   len=n_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-hh")==0) { 
	   len=n_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ih")==0) { 
	   len=n_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-iy")==0) { 
	   len=n_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-jh")==0) { 
	   len=n_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-k")==0) { 
	   len=n_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-l")==0) { 
	   len=n_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-m")==0) { 
	   len=n_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-n")==0) { 
	   len=n_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-ow")==0) { 
	   len=n_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-oy")==0) { 
	   len=n_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-p")==0) { 
	   len=m_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-pau")==0) { 
	   len=n_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-r")==0) { 
	   len=n_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-s")==0) { 
	   len=n_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-sh")==0) { 
	   len=n_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-t")==0) { 
	   len=n_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-th")==0) { 
	   len=n_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"n-uh")==0) { 
	   len=n_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-uw")==0) { 
	   len=n_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-v")==0) { 
	   len=n_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-w")==0) { 
	   len=n_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-y")==0) { 
	   len=n_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-z")==0) { 
	   len=n_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"n-zh")==0) { 
	   len=n_zh_raw_len;
	   
	   }
	 
	   
	   //ng diphones
	   if (g_strcmp0(diphone_str,"ng-aa")==0) { 
	   len=ng_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ae")==0) { 
	   len=ng_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ah")==0) {
	   len=ng_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ao")==0) { 
	   len=ng_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-aw")==0) {
	   len=ng_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ax")==0) { 
	   len=ng_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ay")==0) { 
	   len=ng_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-b")==0) { 
	   len=ng_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ch")==0) { 
	   len=ng_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-d")==0) { 
	   len=ng_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-dh")==0) { 
	   len=ng_dh_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"ng-eh")==0) { 
	   len=ng_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-er")==0) { 
	   len=ng_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ey")==0) { 
	   len=ng_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-f")==0) { 
	   len=ng_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-g")==0) { 
	   len=ng_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-hh")==0) { 
	   len=ng_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ih")==0) { 
	   len=ng_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-iy")==0) { 
	   len=ng_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-jh")==0) { 
	   len=ng_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-k")==0) { 
	   len=ng_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-l")==0) { 
	   len=ng_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-m")==0) { 
	   len=ng_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-n")==0) { 
	   len=ng_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-ow")==0) { 
	   len=ng_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-oy")==0) { 
	   len=ng_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-p")==0) { 
	   len=ng_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-pau")==0) { 
	   len=ng_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-r")==0) { 
	   len=ng_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-s")==0) { 
	   len=ng_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-sh")==0) { 
	   len=ng_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-t")==0) { 
	   len=ng_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-th")==0) { 
	   len=ng_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"ng-uh")==0) { 
	   len=ng_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-uw")==0) { 
	   len=ng_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-v")==0) { 
	   len=ng_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-w")==0) { 
	   len=ng_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-y")==0) { 
	   len=ng_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-z")==0) { 
	   len=ng_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ng-zh")==0) { 
	   len=ng_zh_raw_len;
	   
	   }
	   
	   
	   //ow diphones
	   if (g_strcmp0(diphone_str,"ow-aa")==0) { 
	   len=ow_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ae")==0) { 
	   len=ow_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ah")==0) { 
	   len=ow_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ao")==0) { 
	   len=ow_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-aw")==0) { 
	   len=ow_aw_raw_len;	
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ax")==0) { 
	   len=ow_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ay")==0) { 
	   len=ow_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-b")==0) { 
	   len=ow_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ch")==0) { 
	   len=ow_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-d")==0) { 
	   len=ow_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-dh")==0) { 
	   len=ow_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-eh")==0) { 
	   len=ow_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-er")==0) { 
	   len=ow_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ey")==0) { 
	   len=ow_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-f")==0) { 
	   len=ow_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-g")==0) { 
	   len=ow_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-hh")==0) { 
	   len=ow_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-ih")==0) { 
	   len=ow_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-iy")==0) { 
	   len=ow_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-jh")==0) { 
	   len=ow_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-k")==0) { 
	   len=ow_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-l")==0) { 
	   len=ow_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-m")==0) { 
	   len=ow_m_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"ow-n")==0) { 
	   len=ow_n_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ow-ng")==0) { 
	   len=ow_ng_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"ow-ow")==0) { 
	   len=ow_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-oy")==0) {
	   len=ow_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-p")==0) { 
	   len=ow_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-pau")==0) { 
	   len=ow_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-r")==0) { 
	   len=ow_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-s")==0) { 
	   len=ow_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-sh")==0) { 
	   len=ow_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-t")==0) { 
	   len=ow_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-th")==0) { 
	   len=ow_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"ow-uh")==0) { 
	   len=ow_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-uw")==0) { 
	   len=ow_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-v")==0) {
	   len=ow_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-w")==0) { 
	   len=ow_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-y")==0) { 
	   len=ow_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-z")==0) { 
	   len=ow_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"ow-zh")==0) { 
	   len=ow_zh_raw_len;
	   
	   }
	   
	   
	   //oy diphones
	   if (g_strcmp0(diphone_str,"oy-aa")==0) { 
	   len=oy_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ae")==0) { 
	   len=oy_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ah")==0) { 
	   len=oy_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ao")==0) { 
	   len=oy_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-aw")==0) { 
	   len=oy_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ax")==0) { 
	   len=oy_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ay")==0) { 
	   len=oy_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-b")==0) { 
	   len=oy_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ch")==0) { 
	   len=oy_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-d")==0) { 
	   len=oy_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-dh")==0) { 
	   len=oy_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-eh")==0) { 
	   len=oy_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-er")==0) { 
	   len=oy_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ey")==0) { 
	   len=oy_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-f")==0) { 
	   len=oy_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-g")==0) { 
	   len=oy_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-hh")==0) { 
	   len=oy_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ih")==0) { 
	   len=oy_ih_raw_len;
	  
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-iy")==0) { 
	   len=oy_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-jh")==0) { 
	   len=oy_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-k")==0) { 
	   len=oy_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-l")==0) { 
	   len=oy_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-m")==0) { 
	   len=oy_m_raw_len;
	 
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-n")==0) { 
	   len=oy_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ng")==0) { 
	   len=oy_ng_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-ow")==0) { 
	   len=oy_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-oy")==0) { 
	   len=oy_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-p")==0) { 
	   len=oy_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-pau")==0) { 
	   len=oy_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-r")==0) { 
	   len=oy_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-s")==0) { 
	   len=oy_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-sh")==0) { 
	   len=oy_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-t")==0) { 
	   len=oy_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-th")==0) { 
	   len=oy_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"oy-uh")==0) { 
	   len=oy_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-uw")==0) { 
	   len=oy_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-v")==0) { 
	   len=oy_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-w")==0) { 
	   len=oy_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-y")==0) { 
	   len=oy_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-z")==0) { 
	   len=oy_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"oy-zh")==0) { 
	   len=oy_zh_raw_len;
	   
	   }
	   
	   //p diphones
	   if (g_strcmp0(diphone_str,"p-aa")==0) { 
	   len=p_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ae")==0) { 
	   len=p_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ah")==0) { 
	   len=p_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ao")==0) { 
	   len=p_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-aw")==0) { 
	   len=p_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ax")==0) { 
	   len=p_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ay")==0) { 
	   len=p_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-b")==0) { 
	   len=p_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ch")==0) { 
	   len=p_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-d")==0) { 
	   len=p_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-dh")==0) { 
	   len=p_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-eh")==0) { 
	   len=p_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-er")==0) { 
	   len=p_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ey")==0) { 
	   len=p_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-f")==0) { 
	   len=p_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-g")==0) { 
	   len=p_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-hh")==0) { 
	   len=p_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ih")==0) { 
	   len=p_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-iy")==0) { 
	   len=p_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-jh")==0) { 
	   len=p_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-k")==0) { 
	   len=p_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-l")==0) { 
	   len=p_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-m")==0) { 
	   len=p_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-n")==0) { 
	   len=p_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-ow")==0) { 
	   len=p_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-oy")==0) { 
	   len=p_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-p")==0) { 
	   len=p_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-pau")==0) { 
	   len=p_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-r")==0) { 
	   len=p_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-s")==0) { 
	   len=p_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-sh")==0) { 
	   len=p_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-t")==0) { 
	   len=p_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-th")==0) { 
	   len=p_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"p-uh")==0) { 
	   len=p_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-uw")==0) { 
	   len=p_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-v")==0) { 
	   len=p_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-w")==0) { 
	   len=p_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-y")==0) { 
	   len=p_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-z")==0) { 
	   len=p_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"p-zh")==0) { 
	   len=p_zh_raw_len;
	   
	   }
	   
	  
	   
	   //pau diphones
	   if (g_strcmp0(diphone_str,"pau-aa")==0) { 
	   len=pau_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ae")==0) { 
	   len=pau_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ah")==0) { 
	   len=pau_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ao")==0) { 
	   len=pau_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-aw")==0) { 
	   len=pau_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ax")==0) { 
	   len=pau_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ay")==0) { 
	   len=pau_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-b")==0) { 
	   len=pau_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ch")==0) { 
	   len=pau_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-d")==0) { 
	   len=pau_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-dh")==0) { 
	   len=pau_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-eh")==0) { 
	   len=pau_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-er")==0) { 
	   len=pau_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ey")==0) { 
	   len=pau_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-f")==0) { 
	   len=pau_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-g")==0) { 
	   len=pau_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-hh")==0) { 
	   len=pau_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ih")==0) { 
	   len=pau_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-iy")==0) { 
	   len=pau_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-jh")==0) { 
	   len=pau_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-k")==0) { 
	   len=pau_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-l")==0) { 
	   len=pau_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-m")==0) { 
	   len=pau_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-n")==0) { 
	   len=pau_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-ow")==0) { 
	   len=pau_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-oy")==0) {
	   len=pau_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-p")==0) { 
	   len=pau_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-pau")==0) { 
	   len=pau_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-r")==0) { 
	   len=pau_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-s")==0) {
	   len=pau_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-sh")==0) { 
	   len=pau_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-t")==0) { 
	   len=pau_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-th")==0) { 
	   len=pau_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"pau-uh")==0) { 
	   len=pau_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-uw")==0) { 
	   len=pau_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-v")==0) { 
	   len=pau_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-w")==0) { 
	   len=pau_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-y")==0) { 
	   len=pau_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-z")==0) { 
	   len=pau_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"pau-zh")==0) { 
	   len=pau_zh_raw_len;
	   
	   }
	   
	   //r diphones
	   
	   if (g_strcmp0(diphone_str,"r-aa")==0) { 
	   len=r_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ae")==0) { 
	   len=r_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ah")==0) { 
	   len=r_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ao")==0) { 
	   len=r_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-aw")==0) { 
	   len=r_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ax")==0) { 
	   len=r_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ay")==0) { 
	   len=r_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-b")==0) { 
	   len=r_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ch")==0) { 
	   len=r_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-d")==0) { 
	   len=r_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-dh")==0) { 
	   len=r_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-eh")==0) { 
	   len=r_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-er")==0) { 
	   len=r_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ey")==0) { 
	   len=r_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-f")==0) { 
	   len=r_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-g")==0) { 
	   len=r_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-hh")==0) { 
	   len=r_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ih")==0) { 
	   len=r_ih_raw_len;
	 
	   
	   }
	   if (g_strcmp0(diphone_str,"r-iy")==0) { 
	   len=r_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-jh")==0) { 
	   len=r_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-k")==0) { 
	   len=r_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-l")==0) { 
	   len=r_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-m")==0) { 
	   len=r_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-n")==0) { 
	   len=r_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-ow")==0) { 
	   len=r_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-oy")==0) { 
	   len=r_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-p")==0) { 
	   len=r_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-pau")==0) { 
	   len=r_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-r")==0) { 
	   len=r_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-s")==0) { 
	   len=r_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-sh")==0) { 
	   len=r_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-t")==0) { 
	   len=r_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-th")==0) { 
	   len=r_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"r-uh")==0) { 
	   len=r_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-uw")==0) { 
	   len=r_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-v")==0) { 
	   len=r_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-w")==0) { 
	   len=r_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-y")==0) { 
	   len=r_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-z")==0) { 
	   len=r_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"r-zh")==0) { 
	   len=r_zh_raw_len;
	   
	   }
	   
	   //s diphones
	   if (g_strcmp0(diphone_str,"s-aa")==0) { 
	   len=s_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ae")==0) { 
	   len=s_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ah")==0) { 
	   len=s_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ao")==0) { 
	   len=s_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-aw")==0) { 
	   len=s_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ax")==0) { 
	   len=s_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ay")==0) { 
	   len=s_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-b")==0) { 
	   len=s_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ch")==0) { 
	   len=s_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-d")==0) { 
	   len=s_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-dh")==0) { 
	   len=s_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-eh")==0) { 
	   len=s_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-er")==0) { 
	   len=s_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ey")==0) { 
	   len=s_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-f")==0) { 
	   len=s_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-g")==0) { 
	   len=s_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-hh")==0) { 
	   len=s_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ih")==0) { 
	   len=s_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-iy")==0) { 
	   len=s_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-jh")==0) { 
	   len=s_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-k")==0) { 
	   len=s_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-l")==0) { 
	   len=s_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-m")==0) { 
	   len=s_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-n")==0) { 
	   len=s_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-ow")==0) { 
	   len=s_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-oy")==0) { 
	   len=s_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-p")==0) { 
	   len=s_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-pau")==0) { 
	   len=s_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-r")==0) { 
	   len=s_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-s")==0) {
	   len=s_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-sh")==0) { 
	   len=s_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-t")==0) { 
	   len=s_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-th")==0) { 
	   len=s_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"s-uh")==0) { 
	   len=s_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-uw")==0) { 
	   len=s_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-v")==0) { 
	   len=s_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-w")==0) { 
	   len=s_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-y")==0) { 
	   len=s_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-z")==0) { 
	   len=s_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"s-zh")==0) { 
	   len=s_zh_raw_len;
	   
	   }
	   
	   
	   //sh diphones
	   if (g_strcmp0(diphone_str,"sh-aa")==0) { 
	   len=sh_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ae")==0) { 
	   len=sh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ah")==0) { 
	   len=sh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ao")==0) { 
	   len=sh_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-aw")==0) { 
	   len=sh_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ax")==0) { 
	   len=sh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ay")==0) { 
	   len=sh_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-b")==0) { 
	   len=sh_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ch")==0) { 
	   len=sh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-d")==0) { 
	   len=sh_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-dh")==0) {
	   len=sh_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-eh")==0) { 
	   len=sh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-er")==0) { 
	   len=sh_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ey")==0) { 
	   len=sh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-f")==0) { 
	   len=sh_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-g")==0) { 
	   len=sh_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-hh")==0) { 
	   len=sh_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ih")==0) { 
	   len=sh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-iy")==0) { 
	   len=sh_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-jh")==0) { 
	   len=sh_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-k")==0) { 
	   len=sh_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-l")==0) { 
	   len=sh_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-m")==0) { 
	   len=sh_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-n")==0) { 
	   len=sh_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-ow")==0) { 
	   len=sh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-oy")==0) { 
	   len=sh_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-p")==0) { 
	   len=sh_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-pau")==0) { 
	   len=sh_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-r")==0) { 
	   len=sh_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-s")==0) { 
	   len=sh_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-sh")==0) { 
	   len=sh_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-t")==0) { 
	   len=sh_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-th")==0) { 
	   len=sh_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"sh-uh")==0) { 
	   len=sh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-uw")==0) { 
	   len=sh_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-v")==0) { 
	   len=sh_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-w")==0) { 
	   len=sh_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-y")==0) { 
	   len=sh_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-z")==0) { 
	   len=sh_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"sh-zh")==0) { 
	   len=sh_zh_raw_len;
	   
	   }
	   
	   
	   //t diphones
	   if (g_strcmp0(diphone_str,"t-aa")==0) { 
	   len=t_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ae")==0) { 
	   len=t_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ah")==0) { 
	   len=t_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ao")==0) { 
	   len=t_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-aw")==0) { 
	   len=t_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ax")==0) { 
	   len=t_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ay")==0) { 
	   len=t_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-b")==0) { 
	   len=t_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ch")==0) { 
	   len=t_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-d")==0) { 
	   len=t_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-dh")==0) { 
	   len=t_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-eh")==0) { 
	   len=t_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-er")==0) { 
	   len=t_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ey")==0) { 
	   len=t_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-f")==0) { 
	   len=t_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-g")==0) { 
	   len=t_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-hh")==0) { 
	   len=t_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ih")==0) { 
	   len=t_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-iy")==0) { 
	   len=t_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-jh")==0) { 
	   len=t_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-k")==0) { 
	   len=t_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-l")==0) { 
	   len=t_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-m")==0) { 
	   len=t_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-n")==0) { 
	   len=t_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-ow")==0) { 
	   len=t_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-oy")==0) { 
	   len=t_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-p")==0) { 
	   len=t_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-pau")==0) { 
	   len=t_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-r")==0) { 
	   len=t_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-s")==0) { 
	   len=t_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-sh")==0) { 
	   len=t_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-t")==0) { 
	   len=t_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-th")==0) { 
	   len=t_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"t-uh")==0) { 
	   len=t_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-uw")==0) { 
	   len=t_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-v")==0) { 
	   len=t_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-w")==0) { 
	   len=t_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-y")==0) { 
	   len=t_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-z")==0) { 
	   len=t_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"t-zh")==0) { 
	   len=t_zh_raw_len;
	   
	   }
	   
	   //th diphones
	   if (g_strcmp0(diphone_str,"th-aa")==0) { 
	   len=th_aa_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"th-ae")==0) { 
	   len=th_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ah")==0) { 
	   len=th_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ao")==0) { 
	   len=th_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-aw")==0) { 
	   len=th_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ax")==0) { 
	   len=th_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ay")==0) { 
	   len=th_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-b")==0) { 
	   len=th_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ch")==0) { 
	   len=th_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-d")==0) { 
	   len=th_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-dh")==0) { 
	   len=th_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-eh")==0) { 
	   len=th_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-er")==0) { 
	   len=th_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ey")==0) { 
	   len=th_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-f")==0) { 
	   len=th_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-g")==0) { 
	   len=th_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-hh")==0) { 
	   len=th_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ih")==0) { 
	   len=th_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-iy")==0) { 
	   len=th_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-jh")==0) { 
	   len=th_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-k")==0) { 
	   len=th_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-l")==0) { 
	   len=th_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-m")==0) { 
	   len=th_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-n")==0) { 
	   len=th_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-ow")==0) { 
	   len=th_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-oy")==0) { 
	   len=th_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-p")==0) { 
	   len=th_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-pau")==0) { 
	   len=th_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-r")==0) { 
	   len=th_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-s")==0) { 
	   len=th_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-sh")==0) { 
	   len=th_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-t")==0) { 
	   len=th_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-th")==0) { 
	   
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"th-uh")==0) { 
	   len=th_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-uw")==0) { 
	   len=th_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-v")==0) { 
	   len=th_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-w")==0) { 
	   len=th_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-y")==0) { 
	   len=th_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-z")==0) { 
	   len=th_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"th-zh")==0) { 
	   len=th_zh_raw_len;
	   
	   }
	   
	   
	   //uh diphones
	   if (g_strcmp0(diphone_str,"uh-aa")==0) { 
	   len=uh_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ae")==0) { 
	   len=uh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ah")==0) { 
	   len=uh_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ao")==0) { 
	   len=uh_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-aw")==0) { 
	   len=uh_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ax")==0) { 
	   len=uh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ay")==0) { 
	   len=uh_ay_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"uh-b")==0) { 
	   len=uh_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ch")==0) { 
	   len=uh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-d")==0) { 
	   len=uh_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-dh")==0) { 
	   len=uh_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-eh")==0) { 
	   len=uh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-er")==0) { 
	   len=uh_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ey")==0) { 
	   len=uh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-f")==0) { 
	   len=uh_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-g")==0) { 
	   len=uh_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-hh")==0) { 
	   len=uh_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ih")==0) { 
	   len=uh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-iy")==0) { 
	   len=uh_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-jh")==0) { 
	   len=uh_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-k")==0) { 
	   len=uh_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-l")==0) { 
	   len=uh_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-m")==0) { 
	   len=uh_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-n")==0) { 
	   len=uh_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ng")==0) { 
	   len=uh_ng_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-ow")==0) {
	   len=uh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-oy")==0) { 
	   len=uh_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-p")==0) { 
	   len=uh_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-pau")==0) { 
	   len=uh_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-r")==0) { 
	   len=uh_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-s")==0) { 
	   len=uh_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-sh")==0) { 
	   len=uh_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-t")==0) { 
	   len=uh_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-th")==0) { 
	   len=uh_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"uh-uh")==0) { 
	   len=uh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-uw")==0) { 
	   len=uh_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-v")==0) { 
	   len=uh_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-w")==0) { 
	   len=uh_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-y")==0) { 
	   len=uh_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-z")==0) { 
	   len=uh_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uh-zh")==0) { 
	   len=uh_zh_raw_len;
	   
	   }
	   
	   
	   
	   //uw diphones
	   if (g_strcmp0(diphone_str,"uw-aa")==0) { 
	   len=uw_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ae")==0) { 
	   len=uw_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ah")==0) { 
	   len=uw_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ao")==0) { 
	   len=uw_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-aw")==0) { 
	   len=uw_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ax")==0) { 
	   len=uw_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ay")==0) { 
	   len=uw_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-b")==0) { 
	   len=uw_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ch")==0) { 
	   len=uw_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-d")==0) { 
	   len=uw_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-dh")==0) { 
	   len=uw_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-eh")==0) { 
	   len=uw_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-er")==0) { 
	   len=uw_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ey")==0) { 
	   len=uw_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-f")==0) { 
	   len=uw_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-g")==0) { 
	   len=uw_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-hh")==0) { 
	   len=uw_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-ih")==0) { 
	   len=uw_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-iy")==0) { 
	   len=uw_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-jh")==0) { 
	   len=uw_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-k")==0) { 
	   len=uw_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-l")==0) { 
	   len=uw_l_raw_len;	   
	   }
	   
	   
	   if (g_strcmp0(diphone_str,"uw-m")==0) { 
	   len=uw_m_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"uw-n")==0) { 
	   len=uw_n_raw_len; 
	   }
	   
	   if (g_strcmp0(diphone_str,"uw-ng")==0) { 
	   len=uw_ng_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"uw-ow")==0) { 
	   len=uw_ow_raw_len; 
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"uw-oy")==0) { 
	   len=uw_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-p")==0) { 
	   len=uw_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-pau")==0) { 
	   len=uw_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-r")==0) { 
	   len=uw_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-s")==0) { 
	   len=uw_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-sh")==0) { 
	   len=uw_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-t")==0) { 
	   len=uw_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-th")==0) { 
	   len=uw_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"uw-uh")==0) { 
	   len=uw_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-uw")==0) { 
	   len=uw_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-v")==0) { 
	   len=uw_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-w")==0) { 
	   len=uw_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-y")==0) { 
	   len=uw_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-z")==0) { 
	   len=uw_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"uw-zh")==0) { 
	   len=uw_zh_raw_len;
	   
	   }
	   
	   
	   //v diphones
	   if (g_strcmp0(diphone_str,"v-aa")==0) { 
	   len=v_aa_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ae")==0) { 
	   len=v_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ah")==0) { 
	   len=v_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ao")==0) { 
	   len=v_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-aw")==0) { 
	   len=v_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ax")==0) { 
	   len=v_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ay")==0) { 
	   len=v_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-b")==0) { 
	   len=v_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ch")==0) { 
	   len=v_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-d")==0) { 
	   len=v_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-dh")==0) { 
	   len=v_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-eh")==0) { 
	   len=v_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-er")==0) { 
	   len=v_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ey")==0) { 
	   len=v_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-f")==0) { 
	   len=v_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-g")==0) { 
	   len=v_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-hh")==0) { 
	   len=v_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ih")==0) { 
	   len=v_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-iy")==0) { 
	   len=v_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-jh")==0) { 
	   len=v_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-k")==0) { 
	   len=v_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-l")==0) { 
	   len=v_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-m")==0) { 
	   len=v_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-n")==0) { 
	   len=v_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-ow")==0) { 
	   len=v_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-oy")==0) { 
	   len=v_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-p")==0) { 
	   len=v_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-pau")==0) { 
	   len=v_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-r")==0) { 
	   len=v_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-s")==0) { 
	   len=v_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-sh")==0) { 
	   len=v_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-t")==0) { 
	   len=v_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-th")==0) { 
	   len=v_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"v-uh")==0) { 
	   len=v_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-uw")==0) { 
	   len=v_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-v")==0) { 
	   len=v_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-w")==0) { 
	   len=v_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-y")==0) { 
	   len=v_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-z")==0) { 
	   len=v_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"v-zh")==0) { 
	   len=v_zh_raw_len;
	   
	   }
	   
	   //w diphones
	   
	   if (g_strcmp0(diphone_str,"w-ae")==0) { 
	   len=w_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ah")==0) { 
	   len=w_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ao")==0) { 
	   len=w_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-aw")==0) { 
	   len=w_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ax")==0) { 
	   len=w_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ay")==0) { 
	   len=w_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-eh")==0) { 
	   len=w_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ey")==0) { 
	   len=w_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ih")==0) { 
	   len=w_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-iy")==0) { 
	   len=w_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-ow")==0) { 
	   len=w_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-oy")==0) { 
	   len=w_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-uh")==0) { 
	   len=w_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"w-uw")==0) { 
	   len=w_uw_raw_len;	
	   }
	   
	   
	   
	   //y diphones	
	   if (g_strcmp0(diphone_str,"y-aa")==0) { 
	   len=y_aa_raw_len;	
	   }
	   
	   if (g_strcmp0(diphone_str,"y-ae")==0) { 
	   len=y_ae_raw_len;
	   }
	   
	   if (g_strcmp0(diphone_str,"y-ah")==0) { 
	   len=y_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-ao")==0) { 
	   len=y_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-aw")==0) { 
	   len=y_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-ax")==0) { 
	   len=y_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-ay")==0) { 
	   len=y_ay_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"y-eh")==0) { 
	   len=y_eh_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"y-ey")==0) { 
	   len=y_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-ih")==0) { 
	   len=y_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-iy")==0) { 
	   len=y_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-ow")==0) { 
	   len=y_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-oy")==0) { 
	   len=y_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-uh")==0) { 
	   len=y_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"y-uw")==0) { 
	   len=y_uw_raw_len;
	   
	   }
	   
	   
	   //z diphones	
	   if (g_strcmp0(diphone_str,"z-aa")==0) { 
	   len=z_aa_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"z-ae")==0) { 
	   len=z_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ah")==0) { 
	   len=z_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ao")==0) { 
	   len=z_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-aw")==0) { 
	   len=z_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ax")==0) { 
	   len=z_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ay")==0) { 
	   len=z_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-b")==0) { 
	   len=z_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ch")==0) { 
	   len=z_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-d")==0) { 
	   len=z_d_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"z-dh")==0) { 
	   len=z_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-eh")==0) { 
	   len=z_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-er")==0) { 
	   len=z_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ey")==0) { 
	   len=z_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-f")==0) { 
	   len=z_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-g")==0) { 
	   len=z_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-hh")==0) { 
	   len=z_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ih")==0) { 
	   len=z_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-iy")==0) { 
	   len=z_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-jh")==0) { 
	   len=z_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-k")==0) { 
	   len=z_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-l")==0) { 
	   len=z_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-m")==0) { 
	   len=z_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-n")==0) { 
	   len=z_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-ow")==0) { 
	   len=z_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-oy")==0) { 
	   len=z_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-p")==0) { 
	   len=z_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-pau")==0) { 
	   len=z_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-r")==0) { 
	   len=z_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-s")==0) { 
	   len=z_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-sh")==0) { 
	   len=z_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-t")==0) { 
	   len=z_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-th")==0) { 
	   len=z_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"z-uh")==0) { 
	   len=z_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-uw")==0) { 
	   len=z_uw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-v")==0) { 
	   len=z_v_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-w")==0) { 
	   len=z_w_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-y")==0) { 
	   len=z_y_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-z")==0) { 
	   len=z_z_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"z-zh")==0) { 
	   len=z_zh_raw_len;
	   
	   }
	   
	   //zh diphones
	   if (g_strcmp0(diphone_str,"zh-aa")==0) { 
	   len=zh_aa_raw_len;
	   
	   }
	   
	   if (g_strcmp0(diphone_str,"zh-ae")==0) { 
	   len=zh_ae_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ah")==0) { 
	   len=zh_ah_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ao")==0) { 
	   len=zh_ao_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-aw")==0) { 
	   len=zh_aw_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ax")==0) { 
	   len=zh_ax_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ay")==0) { 
	   len=zh_ay_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-b")==0) { 
	   len=zh_b_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ch")==0) { 
	   len=zh_ch_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-d")==0) { 
	   len=zh_d_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-dh")==0) { 
	   len=zh_dh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-eh")==0) { 
	   len=zh_eh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-er")==0) { 
	   len=zh_er_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ey")==0) { 
	   len=zh_ey_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-f")==0) { 
	   len=zh_f_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-g")==0) { 
	   len=zh_g_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-hh")==0) { 
	   len=zh_hh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ih")==0) { 
	   len=zh_ih_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-iy")==0) { 
	   len=zh_iy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-jh")==0) { 
	   len=zh_jh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-k")==0) { 
	   len=zh_k_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-l")==0) { 
	   len=zh_l_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-m")==0) { 
	   len=zh_m_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-n")==0) { 
	   len=zh_n_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-ow")==0) { 
	   len=zh_ow_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-oy")==0) { 
	   len=zh_oy_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-p")==0) { 
	   len=zh_p_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-pau")==0) { 
	   len=zh_pau_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-r")==0) { 
	   len=zh_r_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-s")==0) { 
	   len=zh_s_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-sh")==0) { 
	   len=zh_sh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-t")==0) { 
	   len=zh_t_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-th")==0) { 
	   len=zh_th_raw_len;
	   
	   
	   }	
	   if (g_strcmp0(diphone_str,"zh-uh")==0) { 
	   len=zh_uh_raw_len;
	   
	   
	   }
	   if (g_strcmp0(diphone_str,"zh-uw")==0) { 
	   len=zh_uw_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"zh-v")==0) { 
	   len=zh_v_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"zh-w")==0) { 
	   len=zh_w_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"zh-y")==0) { 
	   len=zh_y_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"zh-z")==0) { 
	   len=zh_z_raw_len;
	   }
	   if (g_strcmp0(diphone_str,"zh-zh")==0) { 
	   len=zh_zh_raw_len;	   
	   }
	 
	    	
	return len;
}
