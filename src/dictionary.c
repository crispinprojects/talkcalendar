/* dictionary.c
 *
 * Copyright 2025 Alan Crispin <crispinalan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "dictionary.h"

/**
 * @brief A static array of WordEntry structs containing words and 
 * their phonetic transcriptions.
 * @param word The word string.
 * @param transcription The phonetic transcription of the word.
 */
static WordEntry word_table[] = {
//A-words
//a 
{"a","pau_ey ey_ey ey_ey ey_pau"}, 
//account
{"accountant","pau_ah ah_k k_aa aa_uh uh_n n_t t_ah ah_n n_t t_pau"},
//activity
{"activity","pau_ae ae_k k_t t_ih ih_ih ih_v v_ah ah_t t_iy iy_pau"},
//adventure
{"adventure","pau ae ae_d d_v v_eh eh_n n_ch ch_uh uh_r r_pau"},
//afternoon
{"afternoon","pau_ae ae_ae ae_ae ae_f f_t t_er er_pau pau_er er_n n_uw uw_uw uw_n n_pau"},
//agatha
{"agatha","pau_ae ae_g g_ah ah_th th_ah ah_pau"},
//agent
{"agent","pau_eh eh_iy iy_jh jh_ah ah_n n_t t_pau"},
//agree
{"agree","pau_ah ah_g g_r r_iy iy_pau"},
//agreement
{"agreement","pau_ah ah_g g_r r_iy iy_m m_ah ah_n n_t t_pau"},
//airport
{"airport","pau_eh eh_eh eh_r r_p p_ao ao_ao ao_r r_t t_pau"},
//alan
{"alan","pau_ae ae_ae ae_l l_ah ah_n n_pau"}, 
//alans
{"alans","pau_ae ae_ae ae_l l_ah ah_n n_z z_pau"},
//alarm
{"alarm","pau_ah ah_l l_aa aa_r r_m m_pau"},
//alec
{"alec","pau_ae ae_ae ae_l l_ih ih_k k_pau"},
//alert
{"alert","pau_ah ah_l l_er er_er er_t t_pau"},
//alex
{"alex","pau_ae ae_ae ae_l l_ah ah_k k_s s_pau"},
//alexander
{"alexander","pau_ae ae_ae ae_l l_ah ah_g g_z z_ae ae_n n_d d_uh uh_r r_pau"},
//alexanders
{"alexanders","pau_ae ae_ae ae_l l_ih ih_g g_z z_ae ae_n n_d d_uh uh_r r_z z_pau"},
//alexs
{"alexs","pau_ae ae_ae ae_l l_ah ah_k k_s s_ih ih_z z_pau"},
//alf
{"alf","pau_ae ae_ae ae_l l_f f_pau"},
//alfred
{"alfred","pau_ae ae_ae ae_l l_f f_r r_ah ah_d d_pau"},
//alfreds
{"alfreds","pau_ae ae_ae ae_l l_f f_r r_ih ih_d d_z z_pau"},
//alice
{"alice","pau_ae ae_ae ae_l l_ih ih_s s_pau"},
//alices
{"alices","pau_ae ae_ae ae_l l_ih ih_s s_ah ah_z z_pau"},
//alison and allison
{"alison","pau_ae ae_ae ae_l l_ih ih_s s_ah ah_n n_pau"},
//alisons and allisons
{"alisons","pau_ae ae_ae ae_l l_ih ih_s s_ah ah_n n_z z_pau"},
//alister and allister
{"alister","pau_ae ae_ae ae_l l_ih ih_s s_t t_uh uh_r r_pau"},
//all
{"all","pau_al ao_l l_pau"},
//allotment
{"allotment","pau_ah ah_l l_aa aa_aa aa_t t_m m_ah ah_n n_t t_pau"},
//am
{"am","pau_ae ae_m m_pau"}, 
//amazon
{"amazon","pau_ae ae_ae ae_m m_ah ah_z z_aa aa_aa aa_n n_pau"},
//amber
{"amber","pau_ae ae_ae ae_m m_b b_er er_pau"},
//ambulance
{"ambulance","pau_ae ae_ae ae_m m_b b_y y_ah ah_l l_ah ah_n n_s s_pau"},
//amelia
{"amelia","pau_ah ah_m m_iy iy_iy iy_l l_y y_ah ah_pau"},
//amelias
{"amelias","pau_ah ah_m m_iy iy_iy iy_l l_y y_ah ah_z z_pau"},
//amm
{"amm","pau_ey ey_ey ey_ae ae_m m_m m_m m_pau"}, //A.M.
//amy
{"amy","pau_eh eh_iy iy_m m_iy iy_pau"},
//and
{"and","pau_ah ah_n n_d d_pau"},
//andora
{"andora","pau_ae ae_ae ae_n d_ao ao_ao ao_r r_ah ah_pau"},
//andoras
{"andoras","pau_ae ae_ae ae_n d_ao ao_ao ao_r r_ah ah_z z_pau"},
//andre
{"andre","pau_aa aa_aa aa_n n_d d_r r_ey ey_ey ey_pau"},
//andrea
{"andrea","pau_ae ae_ae ae_n n_d d_r r_iy iy_iy iy_ah ah_pau"},
//andreas
{"andreas","pau_ae ae_ae aa_n n_d d_r r_eh eh_iy iy_iy iy_ah ah_z z_pau"},
//andrew
{"andrew","pau_ae ae_ae ae_n n_d d_r r_uw uw_pau"},
//andrews
{"andrews","pau_ae ae_ae ae_n n_d d_r r_uw uw_uw uw_z z_pau"},
//andy
{"andy","pau_ae ae_ae ae_n n_d d_iy iy_pau"},
//andys
{"andys","pau_ae ae_ae ae_n n_d d_iy iy_pau pau_iy iy_z z_pau"},
//angela
{"angela","pau_ae ae_ae ae_n n_jh jh_ah ah_l l_ah ah_pau"},
//angelina
{"angelina","pau_ae ae_n n_jh jh_eh eh_l l_iy iy_n n_ah ah_pau"},
//animal
{"animal","pau_ae ae_n n_ah ah_m m_ah ah_l l_pau"},
//anna
{"anna","pau_ae ae_ae ae_n n_ah ah_pau"},
//annabel
{"annabel","pau_ae ae_ae ae_n n_ah ah_b b_eh eh_eh eh_l l_pau"},
//anne
{"anne","pau_ae ae_ae ae_n n_pau"},
//anniversary
//{"anniversary","ae_ae ae_n n_ah ah_v v_er er_er er_s s_er er_iy iy_pau"},
{"anniversary","pau_ae ae_ae ae_n n_ah ah_v v_er er_er er_s s_er er_iy iy_pau"},
//anthony
{"anthony","pau_ae ae_ae ae_n n_th th_ao ao_n n_iy iy_iy iy_pau"},
//antifreeze  
{"antifreeze","pau_ae ae_ae ae_n n_t t_iy iy_f f_r r_iy iy_iy iy_z z_pau"},
//appoint
{"appoint","pau_ah ah_p p_ao ao_iy iy_n n_t t_pau"},
//appointment
{"appointment","pau_ah ah_p p_oy oy_oy oy_n n_t t_m m_ah ah_n n_t t_pau"},
//april
{"april","pau_ey ey_ey ey_p p_r r_ah ah_l l_pau"},
//archery
{"archery","pau_aa aa_r r_ch ch_uh uh_r r_iy iy_pau"},
//archie
{"archie","pau_aa aa_r r_ch ch_iy iy_pau"},
//art
{"art","pau_aa aa_aa aa_aa aa_r r_t t_pau"},
//arthur
{"arthur","pau_aa aa_r r_th th_uh uh_r r_pau"},
//assessment
{"assessment","pau_ah ah_s s_eh eh_eh eh_s s_m m_ah ah_pau pau_ah ah_n n_t t_pau"},
//attack
{"attack","pau_ah ah_t t_ae ae_k k_pau"},
//aubrey
{"aubrey","pau_ao ao_ao ao_b b_r r_iy iy_pau"},
//audrey
{"audrey","pau_ao ao_ao ao_d d_r r_iy iy_pau"},
//{"audreys","ao_ao ao_uh uh_d d_r r_iy iy_z"},
//august
{"august","pau_aa aa_aa aa_g g_ah ah_s s_t t_pau"},
//aunt
{"aunt","pau_ae ae_ae ae_n n_t t_pau"},
//auntie and aunty
{"auntie","pau_ae ae_ae ae_n n_t t_iy iy_pau"},
//aunts
{"aunts","pau_ae ae_ae ae_n n_t t_s s_pau"},
//autumn
{"autumn","pau_ao ao_t t_ah ah_m m_pau"},

 
//B_words
//baby
{"baby","pau_b b_eh eh_iy iy_b b_iy iy_pau"},
//badminton 
{"badminton","pau_b b_ae ae_d d_m m_ih ih_n n_t t_aa aa_n n_pau"},
//bakery
{"bakery","pau_b b_eh eh_iy iy_k k_uh uh_r r_iy iy_pau"},
//ball
{"ball","pau_b b_ao ao_l l_pau"},
//band
{"band","pau_b b_ae ae_n n_d d_pau"},
//bank
{"bank","pau_b b_ae ae_ae ae_ng ng_k k_pau"},
//banking
{"banking","pau_b b_ae ae_ae ae_ng ng_k k_ih ih_ng ng_pau"},
//barber
{"barber","pau_b b_aa aa_aa aa_r r_b b_er er_pau"},
//barbars
{"barbers","pau_b b_aa aa_aa aa_r r_b b_er er_z z_pau"},
//be
{"be","pau_b b_iy iy_pau"},
//bed
{"bed","pau_b b_eh eh_d d_pau"},
//begins
{"begins","pau_b b_ih ih_g g_ih ih_n n_z z_pau"},
//beth
{"beth","pau_b b_eh eh_eh eh_th th_pau"},
//bethany
{"bethany","pau_b b_eh eh_eh eh_th th_ah ah_n n_iy iy_pau"},
//betsy
{"betsy","pau_b b_eh eh_eh eh_t t_s s_iy iy_pau"},
//betsys
{"betsys","pau_b b_eh eh_eh eh_t t_s s_iy iy_z z_pau"},
//betty
{"betty","pau_b b_eh eh_eh eh_t t_iy iy_pau"},
//bettys
{"betty","pau_b b_eh eh_eh eh_t t_iy iy_z z_pau"},
//big
//bike
{"bike","pau_b b_ay ay_ay ay_k k_pau"},
//billy
{"billy","pau_b b_ih ih_ih ih_l l_iy iy_pau"},
//bin
{"bin","pau_b b_ih ih_ih ih_n n_pau"},
//bird
{"bird","pau_b b_uh uh_r r_d d_pau"},
//birth
{"birth","pau_b b_uh uh_r r_th th_pau"},
//birthday 
//{"birthday","pau_b b_er er_er er_th th_d d_pau pau_d d_ey ey_ey ey_pau"},
{"birthday","pau_b b_er er_er er_th th_d d_ey ey_pau"},
//boat
{"boat","pau_b b_ao ao_uh uh_t t_pau"},
//book
{"book","pau_b b_uh uh_k k_pau"},
//bowls
{"bowls","pau_b b_ao ao_uh uh_l l_z z_pau"},
//box
{"box","pau_b b_aa aa_k k_s s_pau"},
//boxing
{"boxing","pau_b b_aa aa_aa aa_k k_s s_ih ih_ng ng_pau"},
//break
{"break","pau_b b_r r_eh eh_iy iy_k k_pau"},
//breakfast
{"breakfast","pau_b b__r r_eh eh_eh eh_k k_f f_ah ah_s s_t t_pau"},
//british
{"british","pau_b b_r r_ih ih_t t_ih ih_sh sh_pau"},
//brother
{"brother","pau_b b_r r_ah ah_dh dh_uh uh_r r_pau"},
//brothers
{"brothers","pau_b b_r r_ah ah_dh dh_uh uh_r r_z z_pau"},
//brunch
{"brunch","pau_b b_r r_r r_ah ah_n n_n n_ch ch_ch ch_pau"},
//bus
{"bus","pau_b b_ah ah_ah ah_s s_s s_pau"},
//business
{"business","b_ih ih_z z_n n_ah ah_s s_pau"},
//buy
{"buy","pau_b b_aa aa_iy iy_pau"},
//by
{"by","pau_b b_aa aa_iy iy_pau"},
//bye
{"bye","pau_b b_aa aa_iy iy_pau"},

//C_words
//cabbie 
{"cabbie","pau_k k_ae ae_ae ae_b b_b b_iy iy_pau"},
//cafe
{"cafe","pau_k k_ah ah_f f_ey ey_ey"},
//calendar
{"calendar","pau_k k_ae ae_ae ae_l l_ah ah_n n_d d_er er_pau"},
//call
{"call","pau_k k_ao ao_l l_pau"},
//camp
{"camp","pau_k k_ae ae_m m_p p_pau"},
//camping
{"campsite","pau_k k_ae ae_m m_p p_s s_aa aa_iy iy_t t_s s_pau"},
//car
{"car","pau_k k_aa aa_aa aa_r r_pau"},
//card
{"card","pau_k k_aa aa_r r_d d_pau"},
//care
{"care","pau_k k_eh eh_r r_pau"},
//carol
{"carol","pau_k k_ae ae_r r_ah ah_l l_pau"},
//caroline
{"caroline","pau_k k_eh eh_r r_ah ah_l l_aa aa_iy iy_n n_pau"},
{"carolines","pau_k k_eh eh_r r_ah ah_l l_aa aa_iy iy_n n_z z_pau"},
//cat
{"cat","pau_k k_ae ae_t t_pau"},
//cath
{"cath","pau_k k_ae ae_ae ae_th th_th th_pau"},
//catherine and katherine
{"catherine","pau_k k_ae ae_ae ae_th th_er er_ah ah_n n_pau"},
{"catherines","pau_k k_ae ae_ae ae_th th_er er_ah ah_n n_z z_pau"},
//certificate
{"certificate","pau_s s_uh uh_r r_t t_ih ih_f f_ih ih_k k_ah ah_t t_pau"},
//charles
{"charles","pau_ch ch_aa aa_aa aa_r r_l l_z z_pau"},
//charlotte
{"charlotte","pau_sh sh_aa  aa_aa aa_r r_l l_ah ah_t t_pau"},
//chauffeur
{"chauffeur","pau_sh sh_ao ao_uh uh_f f_f f_uh uh_r r_pau"},
//check
{"check","pau_ch ch_eh eh_k k_pau"},
//chemist
{"chemist","pau_k k_eh eh_m m_ih ih_s s_t t_pau"},
//child
{"child","pau_ch ch_aa aa_iy iy_l l_d d_pau"},
//children
{"children","pau_ch ch_ih ih_l l_d d_r r_ah ah_n n_pau"},
//chips
{"chips","pau_ch ch_ih ih_ih ih_p p_s s_pau"}, //dog name _ walk chips
//choir
{"choir","pau_k k_w w_aa aa_iy iy_uh uh_r r_pau"},
//chore
{"chore","pau_ch ch_ao ao_ao ao_r r_pau"},
//christie
{"christie","pau_k k_r r_ih ih_s s_t t_iy iy_pau"},
//christina
{"christina","pau_k k_r r_ih ih_s s_t t_iy iy_n n_ah ah_pau"},
//christine
{"christine","pau_k k_r r_ih ih_s s_t t_iy iy_n n_pau"},
//christmas
{"christmas","pau_k k_r r_ih ih_ih ih_s s_m m_ah ah_s s_pau"},
//church
{"church","pau_ch ch_er er_er er_ch ch_pau"},
//cinema
{"cinema","s_ih ih_ih ih_n n_ah ah_m m_ah ah_pau"},
//circle
{"circle","pau_s s_uh uh_r r_k k_ah ah_l l_pau"},
//circus
{"circus","pau_s s_uh uh_r r_k k_ah ah_s s_pau"},
//city
{"city","pau_s s_ih ih_t t_iy iy_pau"},
//claire
{"claire","pau_k k_l l_eh eh_eh eh_r r_pau"},
//clara
{"clara","pau_k k_l l_ae ae_ae ae_r r_ah ah_pau"},  //aunt clara
//clarence
{"clarence","pau_k k_l l_eh eh_eh eh_r r_ah ah_n n_s s_pau"},
//clarissa
{"clarissa","pau_k k_l l_er er_ih ih_ih ih_s s_ah ah_pau"},
//class
{"class","pau_k k_l l_ae ae_s s_pau"},
//claude
{"claude","pau_k k_l l_ao ao_ao ao_d d_pau"},
//clean
{"clean","pau_k k_l l_iy iy_n n_pau"},
//cleaner
{"cleaner","pau_k k_l l_iy iy_n n_uh uh_r r_pau"},
//climbing
{"climbing","pau_k k_l l_aa aa_iy iy_m m_ih ih_ng ng_pau"},
//clinic
{"clinic","pau_k k_l l_ih ih_ih ih_n n_ih ih_k k_pau"},
//clock
{"clock","pau_k k_l l_aa aa_k k_pau"},
//clocks
{"clocks","pau_k k_l l_aa aa_k k_s s_pau"},
//close
{"close","pau_k k_l l_ao ao_uh uh_s s_pau"},
//closed
{"closed","pau_k k_l l_ao ao_uh uh_z z_d d_pau"},
//club
{"club","pau_k k_l l_ah ah_b b_pau"},
//coach
{"coach","pau_k k_ow ow_ow ow_ch ch_ch ch_pau"},
//coast
{"coast","pau_k k_ao ao_uh uh_s s_t t_pau"},
//cobbler 
{"cobbler","pau_k k_aa aa_aa aa_b b_b b__l l_er er_pau"},
//code
{"code","pau_k k_ao ao_uh uh_d d_pau"},
//coffee
{"coffee","pau_k k_aa aa_f f_iy iy_pau"},
//collection
{"collection","pau_k k_ah ah_l l_eh eh_k k_sh sh_ah ah_n n_pau"},
//college
{"college","pau_k k_aa aa_l l_ih ih_jh jh_pau"},
//coming
{"coming","pau_k k_ah ah_ah ah_m m_ih ih_ng ng_pau"},
//computer
{"computer","pau_k k_ah ah_m m_p p_y y_uw uw_t t_uh uh_r r_pau"},
//concert
{"concert","pau_k k_aa aa_n n_s s_uh uh_r r_t t_pau"},
//contact
{"contact","pau_k k_aa aa_n n_t t_ae ae_k k_t t_pau"},
//cottage
{"cottage","pau_k k_aa  aa_aa aa_t t_ah ah_jh jh_pau"},
//court
{"court","pau_k k_ao ao_r r_t t_pau"},
//cousin
{"cousin","pau_k k_ah ah_z z_ah ah_n n_pau"},

//crispin
{"crispin","pau_k k_r  r_ih ih_ih ih_s s_p p_ih ih_n n_n n_pau"},
//crispins (saint day)
{"crispins","pau_k k_r  r_ih ih_ih ih_s s_p p_ih ih_ih ih_n n_n n_z z_pau"},  //saint day
//crook
{"crook","pau_k k_r r_uh uh_k k_pau"},
//crooks
{"crooks","pau_k k_r r_uh uh_k k_s s_pau"},
//cyber
{"cyber","pau_s s_ay ay_ay ay_b b_er er_pau"},
//cycle
{"cycle","pau_s s_aa aa_iy iy_k k_ah ah_l l_pau"},

//D_words
//dad
{"dad","pau_d d_ae ae_ae ae_d d_pau"},
//dads
{"dads","pau_d d_ae ae_ae ae_d d_z z_pau"},
//daisy
{"daisy","pau_d d_ey ey_ey ey_z z_iy iy_pau"},
//dan
{"dan","pau_d d_ae ae_n n_pau"},
//dance
{"dance","pau_d d_ae ae_n n_s s_pau"},
//daniel
{"daniel","pau_d d_ae ae_ae ae_n n_y y_ah ah_l l_pau"},
//danielle
{"danielle","pau_d d_ae ae_ae ae_n n_iy iy_eh eh_eh eh_l l_pau"},
{"danielle","pau_d d_ae ae_ae ae_n n_iy iy_eh eh_eh eh_l l_z z_pau"},
//danny
{"danny","pau_d d_ae ae_ae ae_n n_iy iy_pau"},
//date
{"date","pau_d d_ey ey_ey ey_t t_pau"},
//dates
{"dates","pau_d d_ey ey_ey ey_t t_s s_pau"},
//daughter
{"daughter","pau_d d_ao ao_ao ao_t t_er er_pau"},
//daughters
{"daughter","pau_d d_ao ao_ao ao_t t_er er_z z_pau"},
//dave
{"dave","pau_d d_ey ey_ey ey_v v_pau"},
//david
{"david","pau_d d_ey ey_ey ey_v v_ih ih_d d_pau"},
//davids
{"davids","pau_d d_ey ey_ey ey_v v_ih ih_d d_z z_pau"},
//day
{"day","pau_d d_d d_ey ey_ey ey_pau"},
//days
{"days","pau_d d_eh eh_iy iy_z z_pau"},
//dead
{"dead","pau_d d_eh eh_d d_pau"},
//deadline
{"deadline","pau_d d_eh eh_eh eh_d d_l l_ay ay_ay ay_n n_pau"},
//dealer
{"dealer","pau_d d_iy iy_l l_uh uh_r r_pau"},
//death
{"death","pau_d d_eh eh_th th_pau"},
//debbie or debby
{"debbie","pau_d d_eh eh_eh eh_b b_iy iy_pau"},
//deborah
{"deborah","pau_d d_eh eh_eh eh_b b_er er_ah ah_pau"},
//debs
{"debs","pau_d d_eh eh_b b_z z_pau"},
//december
{"december","pau_d d_ih ih_s s_eh eh_eh eh_m m_b b_er er_pau"},
//decorate
{"decorate","pau_d d_eh eh_k k_uh uh_r r_eh eh_iy iy_t t_pau"},
//decorating
{"decorating","pau_d d_eh eh_k k_uh uh_r r_eh eh_iy iy_t t_ih ih_ng ng_pau"},
//delivery
{"delivery","pau_d d_ih ih_l l_ih ih_ih ih_v v_er er_iy iy_pau"},
//dentist
{"dentist","pau_d d_eh eh_eh eh_n n_t t_ah ah_s s_t t_pau"},
//development
{"development","pau_d d_ih ih_v v_eh eh_l l_ah ah_p p_m m_ah ah_n n_t t_pau"},
//diana
{"diana","pau_d d_aa aa_iy iy_ae ae_n n_ah ah_pau"},
//diary
{"diary","pau_d d_aa aa_iy iy_uh uh_r r_iy iy_pau"},
//dinner
{"dinner","pau_d d_ih ih_ih ih_n n_er er_pau"},
//{"diphone","d_ih ih_ih ih_f f_ow ow_ow ow_n n_pau"}, //bad pronouciation
//do
{"do","pau_d d_uw uw_pau"},
//doctor
{"doctor","pau_d d_aa aa_aa aa_k k_t t_er er_pau"},
//doctors
{"doctors","pau_d d_aa aa_aa aa_k k_t t_er r_z z_pau"},
//dog
{"dog","pau_d d_ao ao_g g_pau"},
//don
{"don","pau_d d_aa aa_aa aa_n n_pau"},
//donald
{"donald","pau_d d_aa aa_aa aa_n n_ah ah_l l_d d_pau"},
//donalds
{"donalds","pau_d d_aa aa_aa aa_n n_ah ah_l l_d d_z z_pau"},
//donkey
{"donkey","pau_d d_aa aa_ng ng_k k_iy iy_pau"},
//dons
{"dons","pau_d d_aa aa_aa aa_n n_z z_pau"},
//dora
{"dora","pau_d d_ao ao_ao ao_r r_ah ah_pau"},
//down
{"down","pau_d d_aa aa_uh uh_n n_pau"},
//driver
{"driver","pau_d d_r r_ay ay_ay ay_v v_er er_pau"},
//dustbin
{"dustbin","pau_d d_ah ah_ah ah_s s_t t_b b_ih ih_n n_pau"},

//E_words
//ear
{"ear","pau_iy iy_iy iy_r r_pau"},
//early
{"early","pau_uh uh_r r_l l_iy iy_pau"},
//east
{"east","pau_iy iy_s s_t t_pau"},
//easter
{"easter","pau_iy iy_iy iy_s s_t t_er er_pau"},
//education
{"education","pau_eh eh_jh jh_ah ah_k k_eh eh_iy iy_sh sh_ah ah_n n_pau"},
//eight
{"eight","pau_ey ey_ey ey_t t_pau"},
//eighteen
{"eighteen","pau_ey ey_ey ey_t t_iy iy_iy iy_n n_pau"},
//eighteenth
{"eighteenth","pau_ey ey_ey ey_t t_iy iy_iy iy_n n_th th_pau"},
//eighth
{"eighth","pau_eh eh_ey ey_ey ey_t t_th th_pau"},
//eightieth (birthday)
{"eightieth","pau_eh ey_ey ey_t t_iy iy_ih ih_th th_pau"},
//eighty
{"eighty","pau_eh eh_iy iy_t t_iy iy_pau"},
//electric
{"electric","pau_ih ih_l l_eh eh_k k_t t_r r_ih ih_k k_pau"},
//electrician
{"electrician","pau_ih ih_ih ih_l l_eh eh_k k_t t_r r_ih ih_ih ih_sh sh_ah ah_n n_pau"},
//electricity
{"electricity","pau_ih ih_l l_eh eh_k k_t t_r r_ih ih_s s_ah ah_t t_iy iy_pau"},
//eleven
{"eleven","pau_ih ih_l l_eh eh_eh eh_v v_ah ah_n n_pau"},
//eleventh
{"eleventh","pau_ih ih_l l_eh eh_eh eh_v v_ah ah_n n_th th_pau"},
//elisha
{"elisha","pau_eh eh_eh eh_l l_ih ih_sh sh_ah ah_pau"},
//eliza
{"eliza","pau_ih ih_l l_ay ay_ay ay_z z_ah ah_pau"},
//elizabeth
{"elizabeth","pau_ih ih_l l_ih ih_ih ih_z z_ah ah_b b_ah ah_th th_pau"},
//elizabeths
{"elizabeths","pau_ih ih_l l_ih ih_ih ih_z z_ah ah_b b_ah ah_th th_s s_pau"},
//elizas
{"elizas","pau_ih ih_l l_ay ay_ay ay_z z_ah ah_z z_pau"},
//ella
{"ella","pau_eh eh_l l_l l_ah ah_pau"},
//elliot or elliott
{"elliot","pau_eh eh_eh eh_l l_iy iy_ah ah_t t_pau"},
//{"elliott","eh_eh eh_l l_iy iy_ah ah_t"},
//elton
{"elton","pau_eh eh_l l_t t_ah ah_n n_pau"},
//emma
{"emma","pau_eh eh_eh eh_m m_ah ah_pau"},
//end
{"end","pau_eh eh_n n_d d_pau"},
//ends
{"ends","pau_eh eh_n n_d d_z z_pau"},
//engage
{"engage","pau_eh eh_n n_g g_eh eh_iy iy_jh jh_pau"},
{"engagement","pau_eh eh_n n_g g_eh eh_iy iy_jh jh_m m_ah ah_n n_t t_pau"},
//evan
{"evan","pau_eh eh_eh eh_v v_ah ah_n n_pau"},
//evening
{"evening","pau_iy iy_iy iy_v v_n n_ih ih_ng ng_pau"},
//event
{"event","pau_ih ih_v v_eh eh_eh eh_n n_t t_pau"},
//events
{"events","pau_ih ih_v v_eh eh_n n_t t_z z_pau"},
//eye
{"eye","pau_aa aa_iy iy_pau"},

//F_words
//family
{"family","pau_f f_ae ae_ae ae_m m_ah ah_l l_iy iy_pau"},
//farm
{"farm","pau_f f_aa aa_aa aa_r r_m m_pau"},
//father
{"father","pau_f f_aa aa_aa aa_dh dh_er er_pau"},
//fathers
//{"fathers","pau_f f_aa aa_aa aa_dh dh_er er_pau pau_er er_z z_pau"},
{"fathers","pau_f f_aa aa_aa aa_dh dh_er er_er er_z z_z z_pau"},
//fawkes
{"fawkes","pau_f f_ao ao_ao ao_k k_s s_pau"},
//fear
{"fear","pau_f f_ih ih_r r_pau"},
//february
//{"february","f_eh eh_eh eh_b b_y y_ah ah_w w_eh eh_eh eh_r r_iy iy_pau"},
{"february","pau_f f_eh eh_eh eh_b b__y y_ah ah_w w_eh eh_eh eh_r r_iy iy_pau"},
//feed
{"feed","pau_f f_iy iy_d d_pau"},
//festival
{"festival","pau_f f_eh eh_s s_t t_ah ah_v v_ah ah_l l_pau"},
//festive
{"festive","pau_f f_eh eh_s s_t t_ih ih_v v_pau"},
//fifteen
{"fifteen","pau_f f_ih ih_ih ih_f f_t t_iy iy_iy iy_n n_pau"},
//fifteenth
{"fifteenth","pau_f f_ih ih_f f_t t_iy iy_iy iy_n n_th th_pau"},
//fifth
{"fifth","pau_f f_ih ih_ih ih_f f_th th_pau"},
//fifty
{"fifty","pau_f f_ih ih_ih ih_f f_t t_iy iy_pau"},
//film
{"film","pau_f f_ih ih_ih ih_l l_m m_pau"},
//fiona
{"fiona","pau_f f_iy iy_ow ow_ow ow_n n_ah ah_pau"},
//fire
{"fire","pau_f f_aa aa_iy iy_uh uh_r r_pau"},
//fireworks
{"fireworks","pau_f f_aa aa_iy iy_r r_w w_uh uh_r r_k k_s s_pau"},
//first
{"first","pau_f f_er er_er er_s s_t t_pau pau_t"},
//fish
{"fish","pau_f f_ih ih_ih ih_sh sh_pau"},
//fishing
{"fishing","pau_f f_ih ih_sh sh_ih ih_ng ng_pau"},
//five
{"five","pau_f f_ay ay_ay ay_v v_pau"},
//fix
{"fix","pau_f f_ih ih_k k_s s_pau"},
//food
{"food","pau_f f_uw uw_d d_pau"},
//fools april
{"fools","pau_f f_uw uw_l l_z z_pau"},
//football
{"football","pau_f f_uh uh_t t_b b_ao ao_l l_pau"},
//forty
{"forty","pau_f f_ao ao_ao ao_r r_t t_iy iy_pau"},
//forward  _clocks forward (todo)
{"forward","pau_f f_ao ao_r r_w w_uh uh_r r_d d_pau"},
//four
{"four","pau_f f_ao ao_ao ao_r r_pau"},
//fourteen
{"fourteen","pau_f f_ao ao_ao ao_r r_t t_iy iy_iy iy_n n_pau"},
//fourteenth
//{"fourteenth","pau_f f_ao ao_ao ao_r r_t t_iy iy_iy iy_n n_th th_pau pau_th th_pau"},
{"fourteenth","pau_f f_ao ao_ao ao_r r_t t_iy iy_iy iy_n n_th th_th th_pau"},
//fourth
{"fourth","pau_f f_ao ao_ao ao_r r_th th_pau"},
//frances
{"frances","pau_f f_r r_ae ae_ae ae_n n_s s_ih ih_s s_pau"},
//francesca
{"francesca","pau_f f_r r_ae ae_n n_ch ch_eh eh_eh eh_s s_k k_ah ah_pau"},
//francis
{"francis","pau_f f_r r_ae ae_ae ae_n n_s s_ah ah_s s_pau"},
//frank
{"frank","pau_f f_r r_ae ae_ae ae_ng ng_k k_pau"},
//frankenstein
{"frankenstein","pau_f f_r r_ae ae_ng ng_k k_ah ah_n n_s s_t t_aa aa_iy iy_n n_pau"},
//fred
{"fred","pau_f f_f f_r r_eh eh_eh eh_d d_pau"},
//freddie and freddy
{"freddie","pau_f f_r r_eh eh_eh eh_d d_iy iy_pau"},
//{"freddy","f_r r_eh eh_eh eh_d d_iy iy_pau"},
//frederic
{"frederic","pau_f f_r r_eh eh_d d_r r_ih ih_k k_pau"},
//frederick
{"frederick","pau_f f_r r_eh eh_eh eh_d d_er er_ih ih_k k_pau"},
//freds
{"freds","pau_f f_r r_eh eh_eh eh_d d_z z_pau"},
//freeze (anti)
{"freeze","pau_f f_r r_iy iy_z z_pau"},
//{"freezer","f_r r_iy iy_z z_uh uh_r"},
//freya
{"freya","pau_f f_r r_eh eh_iy iy_ah ah_pau"},
//friday
{"friday","pau_f f_r r_ay ay_ay ay_d d_iy iy_pau"},
//friend
{"friend","pau_f f_r r_eh eh_eh eh_n n_d d_pau"},
//frost
{"frost","pau_f f_r r_ao ao_s s_t t_pau"},
//funeral
{"funeral","pau_f f_y y_uw uw_uw uw_n n_er er_ah ah_l l_pau"},

//G_words

//gale
{"gale","pau_g g_ey ey_ey ey_l l_pau"},
{"gales","pau_g g_ey ey_ey ey_l l_z z_pau"},
//gallery
{"gallery","pau_g g_ae ae_ae ae_l l_er er_iy iy_pau"},
//game
{"game","pau_g g_eh eh_iy iy_m m_pau"},
//garage
{"garage","pau_g g_uh uh_r r_aa aa_zh zh_pau"},
//garbage 
{"garbage","pau_g g_aa aa_aa aa_r r_b b_ih ih_jh jh_pau"},
//garden
{"garden","pau_g g_aa aa_r r_d d_ah ah_n n_pau"},
//gas
{"gas","pau_g g_ae ae_ae ae_s s_s s_pau"},
//gate
{"gate","pau_g g_eh eh_iy iy_t t_pau"},
//geoff
{"geoff","pau_jh jh_eh eh_eh eh_f f_pau"},
//geoffrey
{"geoffrey","pau_jh jh_eh eh_eh eh_f f_r r_iy iy_pau"},
{"geoffreys","pau_jh jh_eh eh_eh eh_f f_r r_iy iy_z z_pau"},
//geoffs
{"geoffs","pau_jh jh_eh eh_eh eh_f f_z z_pau"},
//george
{"george","pau_jh jh_ao ao_ao ao_r r_jh jh_pau"},
//georges  saint day
{"georges","pau_jh jh_ao ao_ao ao_r r_jh jh_ah ah_z z_pau"},
//georgina
{"georgina","pau_jh jh_ao ao_ao ao_r r_jh jh_iy iy_n n_ah ah_pau"},
//glasses
{"glasses","pau_g g_l l_ae ae_ae ae_s s_ah ah_z z_pau"},
//go
{"go","pau_g g_ao ao_uh uh_pau"},
//golf
{"golf","pau_g g_aa aa_l l_f f_pau"},
//good
{"good","pau_g g_uh uh_d d_pau"},
//grand
{"grand","pau_g g_r r_ae ae_n n_d d_pau"},
{"grandchild","pau_g g_r r_ae ae_n n_d d_ch ch_aa aa_iy iy_l l_d d_pau"},
{"grandchildren","pau_g g_r r_ae ae_n n_ch ch_ih ih_l l_d d_r r_ah ah_n n_pau"},
//grandad
{"grandad","pau_g g_r r_ae ae_ae ae_n n_d d_ae ae_ae ae_d d_pau"},
{"granddaughter","pau_g g_r r_ae ae_n n_d d_ao ao_t t_uh uh_r r_pau"},
{"grandfather","pau_g g_r r_ae ae_n n_d d_f f_aa aa_dh dh_uh uh_r r_pau"},
{"grandma","pau_g g_r r_ae ae_m m_aa aa_pau"},
{"grandmother","pau_g g_r r_ae ae_n n_d d_m m_ah ah_dh dh_uh uh_r r_pau"},
{"grandpa","pau_g g_r r_ae ae_n n_d d_p p_aa aa_pau"},
{"grandparent","pau_g g_r r_ae ae_n n_d d_p p_eh eh_r r_ah ah_n n_t t_pau"},
{"grandparents","pau_g g_r r_ae ae_n n_d d_p p_eh eh_r r_ah ah_n n_t t_s s_pau"},
{"grandson","pau_g g_r r_ae ae_n n_d d_s s_ah ah_n n_pau"},
//granny and grannie
{"granny","pau_g g_r r_ae ae_ae ae_n n_iy iy_pau"},
//guy (fawkes day)
{"guy","pau_g g_ay ay_ay ay_ay ay_pau"},

//H_words
//hairdresser
{"hairdresser","pau_hh hh_eh eh_eh eh_r r_d d_r r_eh eh_eh eh_s s_er er_pau"},
//hairdressing
{"hairdressing","pau_hh hh_eh eh_eh eh_r r_d d_r r_eh eh_eh eh_s s_ih ih_ng ng_pau"},
//halloween
{"halloween","pau_hh hh_ae ae_ae ae_l l_ah ah_w w_iy iy_iy iy_n n_pau"},
//hannah or hanna
//{"hanna","hh_ae ae_ae ae_n n_ah"},
{"hannah","pau_hh hh_ae ae_ae ae_n n_ah ah_pau"},
{"hannahs","pau_hh hh_ae ae_ae ae_n n_ah ah_z z_pau"},
//happy (birthday)
{"happy","pau_hh hh_ae ae_ae ae_p p_iy iy_pau"},
//harold
{"harold","pau_hh hh_eh eh_eh eh_r r_ah ah_d d_pau"},
{"harolds","pau_hh hh_eh eh_eh eh_r r_ah ah_d d_z z_pau"},
//harry
{"harry","pau_hh hh_eh eh_eh eh_r r_iy iy_pau"},
//have
{"have","pau_hh hh_ae ae_v v_pau"},
//head
{"head","pau_hh hh_eh eh_d d_pau"},
//headache
{"headache","pau_hh hh_eh eh_d d_eh eh_iy iy_k k_pau"},
//health
{"health","pau_hh hh_eh eh_eh eh_l l_th th_pau"},
//hear
{"hear","pau_hh hh_iy iy_r r_pau"},
//heating
{"heating","pau_hh hh_iy iy_iy iy_t t_ih ih_ng ng_pau"},
//hector
{"hector","hh_eh eh_eh eh_k k_t t_er er_pau"},
//helen
{"helen","pau_hh hh_eh eh_eh eh_l l_ah ah_n n_pau"},
//hello
{"hello","pau_hh hh_ah ah_l l_ow ow_ow ow_pau"},
//help
{"help","pau_hh hh_eh eh_eh eh_l l_p p_pau"},
//hen
{"hen","pau_hh hh_eh eh_n n_pau"},
//henry
{"henry","pau_hh hh_eh eh_n n_r r_iy iy_pau"},
//herbert
{"herbert","pau_hh hh_er er_er er_b b_t t_pau"},
//{"herbert","hh_er er_er er_b b_t t_s"},
//high
{"high","pau_hh hh_aa aa_iy iy_pau"},
//hobby
{"hobby","pau_hh hh_aa aa_b b_iy iy_pau"},
//hockey
{"hockey","pau_hh hh_aa aa_aa aa_k kiy iy_pau"},
//holiday
{"holiday","pau_hh hh_aa aa_aa aa_l l_ah ah_d d_ey ey_ey ey_pau"},
//home
{"home","pau_hh hh_ow ow_ow ow_m m_pau"},
//honor
{"honor","pau_hh aa_n n_uh uh_r r_pau"},
//hospital
{"hospital","pau_hh hh_aa aa_aa aa_s s_p p_ih ih_ih ih_t t_ah ah_l l_pau"},
//hotel
{"hotel","pau_hh hh_ow ow_t t_eh eh_eh eh_l l_pau"},
//hour
{"hour","pau_aw aw_aw aw_r r_pau"},
//hours
{"hours","pau_aw aw_aw aw_r r_z z_pau"},
//house
{"house","pau_hh hh_hh hh_aw aw_aw aw_s s_s s_pau"},
//humanoid
{"humanoid","pau_hh hh_y y_uw uw_uw uw_m m_ah ah_n n_oy oy_oy oy_d d_pau"},
//humphrey
{"humphrey","pau_hh hh_ah ah_ah ah_m m_f f_r r_iy iy_pau"},
//hundred
{"hundred","pau_hh hh_ah ah_n n_d d_r r_ah ah_d d_pau"},
//hundredth
{"hundredth","pau_hh hh_ah ah_n n_d d_r r_ah ah_d d_th th_pau"},
//husband
{"husband","pau_hh hh_ah  ah_ah ah_z z_b b_ah ah_n n_d d_pau"},
//husbands
{"husbands","pau_hh hh_ah  ah_ah ah_z z_b b_ah ah_n n_d d_z z_pau"},

//I_words
//i
{"i","pau_ay ay_ay ay_pau"},
//ian
{"ian","pau_iy iy_iy iy_ah ah_n n_pau"},
//in
{"in","pau_ih ih_n n_pau"},
//industry
{"industry","pau_ih ih_n n_d d_ah ah_s s_t t_r r_iy iy_pau"},
//information
{"information","pau_ih ih_n n_f f_uh uh_r r_m m_eh eh_iy iy_sh sh_ah ah_n n_pau"},
//inn
{"inn","pau_ih ih_ih ih_ih ih_n n_pau"},
//insurance
{"insurance","pau_ih ih_n n_sh sh_uh uh_r r_ah ah_n n_s s_pau"},
//investment
{"investment","pau_ih ih_n n_v v_eh eh_s s_t t_m m_ah ah_n n_t t_pau"},
//invoice
{"invoice","pau_ih ih_n n_v v_ao ao_iy iy_s s_pau"},
//invoke
{"invoke","pau_ih ih_n n_v v_ao ao_uh uh_k k_pau"},
//irene
{"irene","pau_ay ay_r r_iy iy_iy iy_n n_pau"},
//is
{"is","pau_ih ih_z z_z z_pau"},
//isaac
{"isaac","pau_ih ih_ih ih_s s_ah ah_k k_pau"},
//isaacs
{"isaacs","pau_ih ih_ih ih_s s_ah ah_k k_s s_pau"},
//isabel or isabelle
{"isabel","pau_ih ih_ih ih_z z_ah ah_b b_eh eh_eh eh_l l_pau"},
//isabella
{"isabella","pau_ih ih_ih ih_z z_ah ah_b b_eh eh_eh eh_l l_ah ah_pau"},
//issabellas
{"isabellas","pau_ih ih_ih ih_z z_ah ah_b b_eh eh_eh eh_l l_ah ah_z z_pau"},
//island
{"island","pau_aa aa_iy iy_l l_ah ah_n n_d d_pau"},
//ivan
{"ivan","pau_ay ay_ay ay_v v_ah ah_n n_pau"},
//ivans
{"ivans","pau_ay ay_ay ay_v v_ah ah_n n_z z_pau"},
//ivy
{"ivy","pau_ay ay_ay ay_v v_iy iy_pau"},

//J_words
//jack
{"jack","pau_jh jh_ae ae_ae ae_k k_pau"},
//jackie or jacky
{"jackie","pau_jh jh_ae ae_ae ae_k k_iy iy_pau"},
//{"jacky","jh_ae ae_ae ae_k k_iy"},
//jacks
{"jacks","pau_jh jh_ae ae_ae ae_k k_s s_pau"},
//jacob
{"jacob","pau_jh jh_eh ey_ey ey_k k_ah ah_b b_pau"},
//jacobs
{"jacobs","pau_jh jh_eh ey_ey ey_k k_ah ah_b b_z z_pau"},
//jacqueline
{"jacqueline","pau_jh jh_ae ae_ae ae_k k_w w_ah ah_l l_ih ih_n n_pau"},
//james
{"james","pau_jh jh_ey ey_ey ey_m m_z z_pau"},
//jamie
{"jamie","pau_jh jh_ey ey_ey ey_m m_iy iy_pau"},
//january
{"january","pau_jh jh_ae ae_ae ae_n n_y y_uw uw_eh eh_eh eh_r r_iy iy_pau"},
//jason
{"jason","pau_jh jh_ey ey_ey ey_s s_ah ah_n n_pau"},
//jeff jeffery same as geoff and geoffrey
//jet
{"jet","pau_jh jh_eh eh_t t_pau"},
//jethro
{"jethro","pau_jh jh_eh eh_th th_r r_ao ao_uh uh_pau"},
//jeweler
{"jeweler","pau_jh jh_uw uw_ah ah_l l_uh uh_r r_pau"},
{"jewelers","pau_jh jh_uw uw_ah ah_l l_uh uh_r r_z z_pau"},
//job
{"job","pau_jh jh_aa aa_aa aa_b b_b b_pau"},
//john
{"john","pau_jh jh_aa aa_aa aa_n n_pau"},
//johns
{"johns","pau_jh jh_aa aa_aa aa_n n_z z_pau"},
//journey
{"journey","pau_jh jh_er er_er er_n n_iy iy_pau"},
//joy
{"joy","pau_jh jh_ao ao_iy iy_pau"},
//july
{"july","pau_jh jh_uw uw_uw uw_l l_ay ay_ay ay_pau"},
//june
{"june","pau_jh jh_uw uw_uw uw_n n_pau"},

//K_words
//karen or karren
{"karen","pau_k k_eh eh_eh eh_r r_ah ah_n n_pau"},
{"karens","pau_k k_eh eh_eh eh_r r_ah ah_n n_z z_pau"},
//kate
{"kate","pau_k k_ey ey_ey ey_t t_pau"},
//ken
{"ken","pau_k k_eh eh_eh eh_n n_pau"},
//kennel
{"kennel","pau_k k_eh eh_n n_ah ah_l l_pau"},
{"kennels","pau_k k_eh eh_n n_ah ah_l l_z z_pau"},
//kenneth
{"kenneth","pau_k k_eh eh_n n_ih ih_th th_pau"},
//king
{"king","pau_k k_ih ih_ng ng_pau"},
//kingdom
{"kingdom","pau_k k_ih ih_ng ng_d d_ah ah_m m_pau"},
//kings
{"kings","pau_k k_ih ih_ng ng_z z_pau"},

//L_words
//laboratory
{"laboratory","pau_l l_ae ae_b b_r r_ah ah_t t_ao ao_r r_iy iy_pau"},
//large
{"large","pau_l l_aa aa_r r_jh jh_pau"},
//last e.g. last day of summer
{"last","pau_l l_ae ae_s s_t t_pau"},
//laura
{"laura","pau_l l_ao ao_r r_ah ah_pau"},
{"laurel","pau_l l_ao ao_r r_ah ah_l l_pau"},
{"laurence","pau_l l_ao ao_r r_ah ah_n n_s s_pau"},
{"lavender","pau_l l_ae ae_v v_ah ah_n n_d d_uh uh_r r_pau"},
//lawrence
{"lawrence","pau_l l_ao ao_r r_ah ah_n n_s s_pau"},
//lawyer
{"lawyer","pau_l l_ao ao_y y_uh uh_r r_pau"},

//leave
{"leave","pau_l l_iy iy_v v_pau"},
//leaving
{"leaving","pau_l l_iy iy_v v_ih ih_ng ng_pau"},
//lecture
{"lecture","pau_l l_eh eh_eh eh_k k_ch ch_er er_pau"},
//leo
{"leo","pau_l l_iy iy_ao ao_uh uh_pau"},
//lesson
{"lesson","pau_l l_eh eh_s s_ah ah_n n_pau"},
{"lester","pau_l l_eh eh_s s_t t_uh uh_r r_pau"},
//library book
{"library","pau_l l_aa aa_iy iy_b b_r r_eh eh_r r_iy iy_pau"},
//license tv
{"license","pau_l l_aa aa_iy iy_s s_ah ah_n n_s s_pau"},
//lift _car lift
{"lift","pau_l l_ih ih_ih ih_f f_t t_pau"},
//lily or lilly
{"lily","pau_l l_ih ih_ih ih_l l_iy iy_pau"},
//line
{"line","pau_l l_aa aa_iy iy_n n_pau"},
//linux
{"linux","pau_l l_ih ih_ih ih_n n_ah ah_k k_s s_pau"},
//location
{"location","pau_l l_ao ao_uh uh_k k_eh eh_iy iy_sh sh_ah ah_n n_pau"},
//lock
{"lock","pau_l l_aa aa_k pau"},
{"lockup","pau_l l_aa aa_k k_ah ah_p p_pau"},
{"locomotive","pau_l l_ao ao_uh uh_k k_ah ah_m m_ao ao_uh uh_t t_ih ih_v v_pau"},
//lodge
{"lodge","pau_l l_aa aa_jh"},
//long
{"long","pau_l l_ao ao_ng"},
//look
{"look","pau_l l_uh uh_k"},
//louisa
{"louisa","pau_l l_uw uw_iy iy_iy iy_z z_ah ah_pau"},
//low
{"low","pau_l l_ao ao_uh"},
//luca
{"luca","pau_l l_uw uw_k k_ah ah_pau"},
{"lucas","pau_l l_uw uw_k k_ah ah_s"},
//lunch
{"lunch","pau_l l_ah ah_ah ah_n n_ch ch_pau"},

//M_words
//madeline
{"madeline","pau_m m_ae ae_ae ae_d d_ah ah_l l_ih ih_n n_pau"},
//magazine
{"magazine","pau_m m_ae ae_g g_ah ah_z z_iy iy_n n_pau"},
{"maggie","pau_m m_ae ae_g g_iy iy_pau"},
{"magic","pau_m m_ae ae_jh jh_ih ih_k k_pau"},
{"magician","pau_m m_ah ah_jh jh_ih ih_sh sh_ah ah_n n_pau"},
{"magistrate","pau_m m_ae ae_jh jh_ah ah_s s_t t_r r_eh eh_iy iy_t t_pau"},
{"magistrates","pau_m m_ae ae_jh jh_ih ih_s s_t t_r r_eh eh_iy iy_t t_s s_pau"},
//maintenance
{"maintenance","pau_m m_ey ey_ey ey_n n_t t_ah ah_n n_ah ah_n n_s s_s s_pau"},
//man
{"man","pau_m m_ae ae_n n_pau"},
//management
{"management","pau_m m_ae ae_ae ae_n n_ah ah_jh jh_m m_ah ah_n n_t t_pau"},
//many
{"many","pau_m m_eh eh_n n_iy iy_pau"},
//march
{"march","pau_m m_aa aa_aa aa_r r_ch ch_pau"},
{"marie","pau_m m_uh uh_r r_iy iy_pau"},
{"marigold","pau_m m_eh eh_r r_ah ah_g g_ao ao_uh uh_l l_d d_pau"},
{"marina","pau_m m_uh uh_r r_iy iy_n n_ah ah_pau"},
//marine
{"marine","pau_m m_uh uh_r r_iy iy_n n_pau"},
//marjorie
{"marjorie","pau_m m_aa aa_r r_jh jh_uh uh_r r_iy iy_pau"},
{"mark","pau_m m_aa aa_r r_k k_pau"},
//market
//mary
{"mary","pau_m m_eh eh_eh eh_r r_iy iy_pau"},
//marys
{"marys","pau_m m_eh eh_eh eh_r r_iy iy_z z_pau"},
//master
{"master","pau_m m_ae ae_ae ae_s s_t t_er er_pau"},
//mat
//matt
{"matt","pau_m m_ae ae_ae ae_t t_pau"},
//matthew
{"matthew","pau_m m_ae ae_ae ae_th th_y y_uw uw_pau"},
//matthews
{"matthews","pau_m m_ae ae_ae ae_th th_y y_uw uw_z z_pau"},
//matthias
{"matthias","pau_m m_ah ah_th th_ay ay_ay ay_ah ah_s s_pau"},
//maurice
{"maurice","pau_m m_ao ao_r r_iy iy_s s_pau"},
//may
{"may","pau_m m_m m_ey ey_ey ey_pau"},
//me
{"me","pau_m m_iy iy_pau"},
//meal
{"meal","pau_m m_iy iy_iy iy_l l_pau"},
//mechanic
{"mechanic","pau_m m_ah ah_k k_ae ae_n n_ih ih_k k_pau"},
//medical
{"medical","pau_m m_eh eh_eh eh_d d_ah ah_k k_ah ah_l l_pau"},
//meet
{"meet","pau_m m_iy iy_iy iy_t t_pau"},
//meeting
{"meeting","pau_m m_iy iy_iy iy_t t_ih ih_ng ng_pau"},
{"member","pau_m m_eh eh_m m_b b_uh uh_r r_pau"},
{"members","pau_m m_eh eh_m m_b b_uh uh_r r_z z_pau"},
//memo
{"memo","pau_m m_eh eh_eh eh_m m_ao ao_uh uh_pau"},
//memorandum
{"memorandum","pau_m m_eh eh_eh eh_m m_er er_ae ae_ae ae_n n_d d_ah ah_m m_pau"},
//message
{"message","pau_m m_eh eh_s s_ah ah_jh jh_pau"},
//midnight
{"midnight","pau_m m_ih ih_d d_n n_aa aa_iy iy_t t_pau"},
//mike
{"mike","pau_m m_aa aa_iy iy_k k_pau"},
//minder
{"minder","pau_m m_aa aa_iy iy_n n_d d_uh uh_r r_pau"},
//mini
{"mini","pau_m m_ih ih_ih ih_n n_iy iy_iy iy_pau"},
//miriam
{"miriam","pau_m m_ih ih_r r_iy iy_ah ah_m m_pau"},
//monday
{"monday","pau_m m_ah ah_ah ah_n n_n n_d d_iy iy_pau"},
//monster
{"monster","pau_m m_aa aa_n n_s s_t t_uh uh_r r_pau"},
//month
{"month","pau_m m_ah ah_n n_th th_pau"},
//morning
{"morning","pau_m m_ao ao_ao ao_r r_n n_ih ih_ng ng_pau"},
//mother
{"mother","pau_m m_ah ah_ah ah_dh dh_er er_pau"},
//mothers
{"mothers","pau_m m_ah ah_ah ah_dh dh_er er_z z_pau"},
//motorcycle
{"motorcycle","pau_m m_ow ow_ow ow_t t_er er_s s_ay ay_ay ay_k k_ah ah_l l_pau"},
//move
{"move","pau_m m_uw uw_v v_pau"},
{"moving","pau_m m_uw uw_v v_ih ih_ng ng_pau"},
//movie
{"movie","pau_m m_uw uw_uw uw_v v_iy iy_pau"},
//muhammad
{"muhammad","pau_m m_uh uh_hh hh_aa aa_m m_ah ah_d d_pau"},
{"muhammads","pau_m m_uh uh_hh hh_aa aa_m m_ah ah_d d_z z_pau"},
//mum
{"mum","pau_m m_ah ah_ah ah_m m_pau"},
//mums
{"mums","pau_m m_ah ah_ah ah_m m_z z_pau"},
//music
{"music","pau_m m_y y_uw uw_uw uw_z z_ih ih_k k_pau"},
//my
{"my","pau_m m_ay ay_ay ay_pau"},

//N_words
//naomi
{"naomi","pau_n n_ey ey_ow ow_ow ow_m m_iy iy_pau"},
//nat
{"nat","pau_n n_ae ae_t t_pau"},
//natalie
{"natalie","pau_n n_ae ae_t t_ah ah_l l_iy iy_pau"},
//natasha
{"natasha","pau_n n_ah ah_t t_aa aa_sh sh_ah ah_pau"},
//nathan
{"nathan","pau_n n_eh eh_iy iy_th th_ah ah_n n_pau"},
{"nathaniel","pau_n n_ah ah_th th_ae ae_n n_y y_ah ah_l l_pau"},
{"nation","pau_n n_eh eh_iy iy_sh sh_ah ah_n n_pau"},
{"national","pau_n n_ae ae_sh sh_ah ah_n n_ah ah_l l_pau"},

//neighbour
{"neighbour","pau_n n_eh eh_iy iy_b b_uh uh_r r_pau"},
//nephew
{"nephew","pau_n n_eh eh_f f_y y_uw uw_pau"},
//netball 
{"net","pau_n n_eh eh_t t_b b_ao ao_l l_pau"},
//netflix
{"netflix","pau_n n_eh eh_eh eh_t t_f f_l l_ih ih_ih ih_k k_k k_pau"},
//new
{"new","pau_n n_uw uw_uw uw_pau"},
//news
{"news","pau_n n_uw uw_z z_pau"},
//newspaper
{"newspaper","pau_n n_uw uw_z z_p p_eh eh_iy iy_p p_uh uh_r r_pau"},
//niece
{"niece","pau_n n_iy iy_s s_pau"},
//night
{"night","pau_n n_aa aa_iy iy_t t_pau"},
//nine
{"nine","pau_n n_ay ay_ay ay_n n_pau"},
//nineteen
{"nineteen","pau_n n_ay ay_ay ay_n n_t t_iy iy_iy iy_n n_pau"},
//nineteenth
//{"nineteenth","pau_n n_ay ay_ay ay_n n_t t_iy iy_iy iy_n n_th th_pau pau_th th_pau"},
{"nineteenth","pau_n n_ay ay_ay ay_n n_t t_iy iy_iy iy_n n_th th_th th_pau"},
//ninetieth
{"ninetieth","pau_n n_aa aa_iy iy_n n_t t_iy iy_ih ih_th th_pau"},
//ninety
{"ninety","pau_n n_aa aa_iy iy_n n_t t_iy iy_pau"},
//ninth
{"ninth","pau_n n_ay ay_ay ay_n n_th th_pau"},
//no
{"no","pau_n n_ao ao_uh uh_pau"},
//noah
{"noah","pau_n n_ao ao_uh uh_ah ah_pau"},
//norman
{"norman","pau_n n_ao ao_r r_m m_ah ah_n n_pau"},
//normans
{"normans","pau_n n_ao ao_r r_m m_ah ah_n n_z z_pau"},
//north
{"north","pau_n n_ao ao_r r_th th_pau"},
{"northumbria","pau_n n_ao ao_r r_th th_ah ah_m m_r r_iy iy_ah ah_pau"},
//not
{"not","pau_n n_aa aa_t t_pau"},
//notable
{"notable","pau_n n_ao ao_uh uh_t t_ah ah_b b_ah ah_l l_pau"},
//notification
{"notification","pau_n n_ow ow_ow ow_t t_ah ah_f f_ah ah_k k_ey ey_ey ey_sh sh_ah ah_n n_pau"},
//november
{"november","pau_n n_ow ow_v v_eh eh_eh eh_m m_b b_er er_pau"},
//now
{"now","pau_n n_aw aw_aw aw_pau"},
//nurse
{"nurse","pau_n n_uh uh_r r_s s_pau"},
//nursery
{"nursery","pau_n n_er er_er er_s s_er er_iy iy_pau"},

//O_words
//o
{"o","pau_ao ao_uh uh_ao ao_uh uh_pau"},
//october
{"october","pau_aa aa_k k_t t_ow ow_ow ow_b b_er er_pau"},
//of
{"of","pau_ah ah_v v_pau"},
{"off","pau_ao ao_f f_pau"},
{"offer","pau_ao ao_f f_uh uh_r r_pau"},
//office
{"office","pau_ao ao_ao ao_f f_ah ah_s s_pau"},
//oliver
{"oliver","pau_aa aa_aa aa_l l_ih ih_v v_er er_pau"},
//olivers
{"oliver","pau_aa aa_aa aa_l l_ih ih_v v_er er_z z_pau"},
//olivia
{"olivia","pau_ow ow_l l_ih ih_ih ih_v v_iy iy_ah ah_pau"},
//olivias
{"olivias","pau_ow ow_l l_ih ih_ih ih_v v_iy iy_ah ah_z z_pau"},
//on
{"on","pau_aa aa_aa aa_n n_n n_pau"},
//one
{"one","w_ah ah_ah ah_n n_pau"},
//online
{"online","pau_aa aa_aa aa_n n_n n_l l_aa aa_iy iy_n n_pau"},
//open
{"open","pau_ao ao_uh uh_p p_ah ah_n n_pau"},
//or
{"or","pau_ao ao_r r_pau"},
//orchestra
{"orchestra","pau_ao ao_r r_k k_ah ah_s s_t t_r r_ah ah_pau"},
//oscar
{"oscar","pau_ao ao_s s_k k_uh uh_r r_pau"},
{"oscars","pau_ao ao_s s_k k_uh uh_r r_z z_pau"},
//out
{"out","pau_aa aa_uh uh_t t_pau"},
{"outbreak","pau_aa aa_uh uh_t t_b b_r r_eh eh_iy iy_k k_pau"},
{"outcome","pau_aa aa_uh uh_t t_k k_ah ah_m m_pau"},
{"outhouse","pau_aa aa_uh uh_t t_hh hh_aa aa_uh uh_s s_pau"},
{"outing","pau_aa aa_uh uh_t t_ih ih_ng ng_pau"},
//over
{"over","pau_ao ao_uh uh_v v_uh uh_r r_pau"},
//own
{"own","pau_ow ow_ow_ow_ow ow_n n_pau"},

//P_words
//pam
{"pam","pau_p p_ae ae_ae ae_m m_pau"},
//pamela
{"pamela","pau_p p_ae ae_ae ae_m m_ah ah_l l_ah ah_pau"},
//pams
{"pams","pau_p p_ae ae_ae ae_m m_z z_pau"},
//pancake
{"pancake","pau_p p_ae ae_ae ae_n n_k k_ey ey_ey ey_k k_pau"},
//paper
{"paper","pau_p p_eh eh_iy iy_p p_uh uh_r r_pau"},
//parent
{"parent","pau_p p_eh eh_r r_ah ah_n n_t t_pau"},
{"parents","pau_p p_eh eh_r r_ah ah_n n_t t_s s_pau"},
//parrot
{"parrot","pau_p p_eh eh_r r_ah ah_t t_pau"},
//party
{"party","pau_p p_aa aa_aa aa_r r_t t_iy iy_pau"},
//passport
{"passport","pau_p p_ae ae_ae ae_s s_p p_ao ao_ao ao_r r_t t_pau"},
//pat
{"pat","pau_p p_ae ae_t t_pau"},
//patricia
{"patricia","pau_p p_ah ah_t t_r r_ih ih_sh sh_ah ah_pau"},
//patrick
{"patrick","pau_p p_ae ae_ae ae_t t_r r_ih ih_k k_pau"},
//patricks (saint name)
{"patricks","pau_p p_ae ae_ae ae_t t_r r_ih ih_k k_s s_pau"},
//pau
{"pau","pau_pau"},
//paul
{"paul","pau_p p_ao ao_ao ao_l l_pau"},
//paula
{"paula","pau_p p_ao ao_ao ao_l l_ah ah_pau"},
//pauline
{"pauline","pau_p p_ao ao_l l_iy iy_iy iy_n n_pau"},
//pauses
{"pause1","pau_pau"},
{"pause2","pau_pau pau_pau"},
//pay
{"pay","pau_p p_eh eh_iy iy_pau"},
{"payable","pau_p p_eh eh_iy iy_ah ah_b b_ah ah_l l_pau"},
{"payed","pau_p p_eh eh_iy iy_d d_pau"},
//paying
{"paying","pau_p p_eh eh_iy iy_ih ih_ng ng_pau"},
//payment
{"payment","pau_p p_ey ey_ey ey_m m_ah ah_n n_t t_pau"},
//penelope
{"penelope","pau_p p_ah ah_n n_eh eh_eh eh_l l_ah ah_p p_iy iy_pau"},
//penny
{"penny","pau_p p_eh eh_eh eh_n n_iy iy_pau"},
//pension
{"pension","pau_p p_eh eh_eh eh_n n_sh sh_ah ah_n n_pau"},
//percy
{"percy","pau_p p_er er_er er_s s_iy iy_pau"},
//perry
{"perry","pau_p p_eh eh_eh eh_r r_iy iy_pau"},
//person
{"person","pau_p p_uh uh_r r_s s_ah ah_n n_pau"},
//personal
{"personal","pau_p p_uh uh_r r_s s_ih ih_n n_ih ih_l l_pau"},
//pet
{"pet","pau_p p_eh eh_t t_pau"},
//peter
{"peter","pau_p p_iy iy_iy iy_t t_er er_pau"},
//peters
{"peters","pau_p p_iy iy_iy iy_t t_er er_z z_pau"},
//phoebe or phebe
{"phoebe","pau_f f_iy iy_iy iy_b b_iy iy_pau"},
//phone
{"phone","pau_f f_ao ao_uh uh_n n_pau"},
//piano
{"piano","pau_p p_iy iy_ae ae_n n_ao ao_uh uh_pau"},
//picture
{"picture","pau_p p_ih ih_ih ih_k k_ch ch_er er_pau"},
//pictures
{"pictures","pau_p p_ih ih_ih ih_k k_ch ch_er er_z z_pau"},
//pilates
{"pilates","pau_p p_ih ih_ih ih_l l_aa aa_aa aa_t t_iy iy_iy iy_s s_pau"},
//place
{"place","pau_p p_l l_eh eh_iy iy_s s_pau"},
//pmm
{"pmm","pau_p p_iy iy_iy iy_m m_eh eh_m m_m m_m m_pau"},
//point
{"point","pau_p p_oy oy_oy oy_n n_t t_pau"},
{"pop","pau_p p_aa aa_p p_pau"},
{"popcorn","pau_p p_aa aa_p p_k k_ao ao_r r_n n_pau"},
//pope
{"pope","pau_p p_ao ao_uh uh_p p_pau"},
//port
{"port","pau_p p_ao ao_r r_t t_pau"},
//post
{"post","pau_p p_ao ao_uh uh_s s_t t_pau"},
//postoffice
{"postoffice","pau_p p_ao ao_uh uh_s s_t t_ao ao_f f_ah ah_s s_pau"},
//{"potato","p_ah ah_t t_eh eh_iy iy_t t_ao ao_uh"},
//{"potatoes","p_ah ah_t t_eh eh_iy iy_t t_ao ao_uh uh_z"},
//practice
{"practice","pau_p p_r r_ae ae_k k_t t_ah ah_s s_pau"},
//premier
{"premier","pau_p p_r r_eh eh_m m_ih ih_ih ih_r r_pau"},
//prescription
{"prescription","pau_p p_r r_ah ah_s s_k k_r r_ih ih_p p_sh sh_ah ah_n n_pau"},
//present
{"present","pau_p p_r r_eh eh_z z_ah ah_n n_t t_pau"},
//pressure
{"pressure","pau_p p_r r_eh eh_sh sh_uh uh_r r_pau"},
//priority
{"priority","pau_p p_r r_aa aa_iy iy_ao ao_r r_ah ah_t t_iy iy_pau"},
{"priscilla","pau_p p_r r_ih ih_s s_ih ih_l l_ah ah_pau"},
{"prism","pau_p p_r r_ih ih_z z_ah ah_m m_pau"},
{"prison","pau_p p_r r_ih ih_z z_ah ah_n n_pau"},
{"private","pau_p p_r r_aa aa_iy iy_v v_ah ah_t t_pau"},
{"professional","pau_p p_r ah_ah ah_f f_eh eh_eh eh_sh sh_ah ah_n n_ah ah_l l_pau "},
//professor 
{"professor","pau_p p_r ah_ah ah_f f_eh eh_eh eh_s s_er er_pau"},
//program
{"program","pau_p p_r r_ow ow_ow ow_g g_r r_ae ae_ae ae_m m_pau"},
//programme (duplicate)
{"programme","pau_p p_r r_ow ow_ow ow_g g_r r_ae ae_ae ae_m m_pau"},
//project
{"project","pau_p p_r r_aa aa_aa aa_jh jh_eh eh_k k_t t_pau"},
//pronounce
{"pronounce","pau_p p_r r_ah ah_n n_aa aa_uh uh_n n_s s_pau"},
//pronounced
{"pronounced","pau_p p_r r_ah ah_n n_aa aa_uh uh_n n_s s_t t_pau"},
//prunella
{"prunella","pau_p p_r r_uw uw_n n_eh eh_eh eh_l l_ah ah_pau"},
//pub
{"pub","pau_p p_ah ah_ah ah_b b_pau"},
//public
{"public","pau_p p_ah ah_ah ah_b b_l l_ih ih_k k_pau"},
//purchase
{"purchase","pau_p p_uh uh_r r_ch ch_ah ah_s s_pau"},

//Q_words
//queen
{"queen","pau_k k_w w_iy iy_n n_pau"},
//quick
{"quick","pau_k k_w w_ih ih_k k_pau"},
//quiz
{"quiz","pau_k k_w w_ih ih_ih ih_z z_pau"},
//quote
{"quote","pau_k k_w w_w w_ow ow_ow ow_t t_pau"},


//R_words
//radio
{"radio","pau_r r_ey ey_ey ey_d d_iy iy_ow ow_ow ow_pau"},
//rail
{"rail","pau_r r_eh eh_iy iy_l l_pau"},
//railway
{"railway","pau_r r_eh eh_iy iy_l l_w w_eh eh_iy iy_pau"},
{"rain","pau_r r_eh eh_iy iy_n n_pau"},
{"ralph","pau_r r_ae ae_l l_f f_pau"},
//ray
{"ray","pau_r r_eh eh_iy iy_pau"},
//reminder
{"reminder","pau_r r_iy iy_m m_ay ay_ay ay_n n_d d_er er_pau"},
//rene and renne
{"rene","pau_r r_ah ah_n n_eh eh_iy iy_pau"},
{"renew","pau_r r_ih ih_n n_uw uw_pau"},
{"renewal","pau_r r_ih ih_n n_uw uw_ah ah_l l_pau"},
//repair
{"repair","pau_r r_ih ih_p p_eh eh_r r_pau"},
//rest
{"rest","pau_r r_eh eh_eh eh_s s_t t_pau"},
//restaurant
{"restaurant","pau_r r_eh eh_eh eh_s s_t t_er er_aa aa_aa aa_n n_t t_pau"},
//retire
{"retire","pau_r r_ih ih_t t_aa aa_iy iy_r r_pau"},
//retirement
{"retirement","pau_r r_iy iy_t t_ay ay_er er_m m_ah ah_n n_t t_pau"},
//return
{"return","pau_r r_ih ih_t t_uh uh_r r_n n_pau"},
//richard
{"richard","pau_r r_ih ih_ch ch_uh uh_r r_d d_pau"},
//road
{"road","pau_r r_ao ao_uh uh_d d_pau"},
{"robber","pau_r r_aa aa_b b_uh uh_r r_pau"},
//robbie
{"robbie","pau_r r_aa aa_b b_iy iy_pau"},
//robert
{"robert","pau_r r_aa aa_b b_uh uh_r r_t t_pau"},
//robin
{"robin","pau_r r_aa aa_b b_ah ah_n n_pau"},
//ronald
{"ronald","pau_r r_aa aa_n n_ah ah_l l_d d_pau"},
//room
{"room","pau_r r_uw uw_m m_pau"},
//rose
{"rose","pau_r r_ow ow_ow ow_z z_pau"},
//rosemary
{"rosemary","pau_r r_ow ow_ow ow_z z_m m_eh eh_eh eh_r r_iy iy_pau"},
//royal
{"royal","pau_r r_ao ao_iy iy_ah ah_l l_pau"},
//rugby
{"rugby","pau_r r_ah ah_g g_b b_iy iy_pau"},
//russell and russel
{"russell","pau_r r_ah ah_s s_ah ah_l l_pau"},

//S_words
//sabrina
{"sabrina","pau_s s_ah ah_b b_r r_iy iy_iy iy_n n_ah ah_pau"},
//saint
{"saint","pau_s s_ey ey_ey ey_n n_t t_pau"},
//sam
{"sam","pau_s s_ae ae_m m_pau"},
//samuel
{"samuel","pau_s s_ae ae_m m_y y_uw uw_l l_pau"},
//sanctuary
{"sanctuary","pau_s s_ae ae_ng ng_k k_ch ch_uw uw_eh eh_r r_iy iy_pau"},
//sarah
{"sarah","pau_s s_eh eh_r r_ah ah_pau"},
//saturday
{"saturday","pau_s s_ae ae_ae ae_t t_ih ih_ih ih_d d_ey ey_ey ey_pau"},
//say
{"say","pau_s s_eh eh_iy iy_pau"},
//says
{"says","pau_s s_eh eh_z z_pau"},
//school
{"school","pau_s s_k k_uw uw_l l_pau"},
//sea
{"sea","pau_s s_iy iy_iy iy_pau"},
{"seal","pau_s s_iy iy_l l_pau"},
{"seaside","pau_s s_iy iy_s s_aa aa_iy iy_d d_pau"},
{"season","pau_s s_iy iy_z z_ah ah_n n_pau"},
//second
{"second","pau_s s_eh eh_eh eh_k k_ah ah_n n_d d_pau"},
//self
{"self","pau_s s_eh eh_eh eh_l l_f f_pau"},
{"semicircle","pau_s s_eh eh_m m_ih ih_s s_uh uh_r r_k k_ah ah_l l_pau"},
//seminar
{"seminar","pau_s s_eh eh_eh eh_m m_ah ah_n n_aa aa_aa aa_r r_r r_pau"},
//september
{"september","pau_s s_eh eh_p p_t t_eh eh_eh eh_m m_b b_er er_pau"},
//series
{"series","pau_s s_ih ih_r r_iy iy_z z_pau"},
//service
{"service","pau_s s_er er_er er_v v_ah ah_s s_pau"},
//seven
{"seven","pau_s s_eh eh_eh eh_v v_ah ah_n n_pau"},
//seventeen
{"seventeen","pau_s s_eh eh_eh eh_v v_ah ah_n n_t t_iy iy_iy iy_n n_pau"},
//seventeenth
{"seventeenth","pau_s s_eh eh_eh eh_v v_ah ah_n n_t t_iy iy_iy iy_n n_th th_pau"},
//seventh
{"seventh","pau_s s_eh eh_eh eh_v v_ah ah_n n_th th_pau"},
//seventieth
{"seventieth","pau_s s_eh eh_v v_ah ah_n n_t t_iy iy_ih ih_th th_pau"},
//seventy
{"seventy","pau_s s_eh eh_v v_ah ah_n n_t t_iy iy_pau"},
//shoe
{"shoe","pau_sh sh_uw uw_pau"},
//shop
{"shop","pau_sh sh_aa aa_aa aa_p p_pau"},
//shopping
{"shopping","pau_sh sh_aa aa_aa aa_p p_ih ih_ng n_pau"},
//short
{"short","pau_sh sh_ao ao_r r_t t_pau"},
//show
{"show","pau_sh sh_ow ow_ow ow_pau"},
//sister
{"sister","pau_s s_ih ih_s s_t t_uh uh_r r_pau"},
//sisters
{"sisters","pau_s s_ih ih_s s_t t_uh uh_r r_z z_pau"},
//six
{"six","pau_s s_ih ih_ih ih_k k_s s_pau"},
//sixteen
{"sixteen","pau_s s_ih ih_k k_s s_t t_iy iy_iy iy_n n_pau"},
//sixteenth
{"sixteenth","pau_s s_ih ih_k k_s s_t t_iy iy_iy iy_n n_th th_pau"},
//sixth
{"sixth","pau_s s_ih ih_ih ih_k k_s s_th th_pau"},
//sixtieth
//sixty
{"sixty","pau_s s_ih ih_k k_s s_t t_iy iy_pau"},
//sky
{"sky","pau_s s_k k_aa aa_iy iy_pau"},
//small
{"small","pau_s s_m m_ao ao_l l_pau"},
//society
{"society","pau_s s_ow ow_s s_ay ay_ay ay_ih ih_t t_iy iy_pau"},
//software
//son
{"son","pau_s s_ah ah_ah ah_n n_pau"},
//sons
{"sons","pau_s s_ah ah_ah ah_n n_z z_pau"},
//south
//special
{"special","pau_s s_p p_eh eh_eh eh_sh sh_ah ah_l l_pau"},
//speech
{"speech","pau_s s_p p_iy iy_iy iy_ch ch_ch ch_pau"},
//sport
{"sport","pau_s s_p p_ao ao_ao ao_r r_t t_pau"},
//spring
{"spring","pau_s s_p p_r r_ih ih_ih ih_ng ng_pau"},
//stag
{"stag","pau_s s_t t_ae ae_g g_pau"},
//star
{"star","pau_s s_t t_aa aa_r r_pau"},
//start
{"start","pau_s s_t t_aa aa_r r_t t_pau"},
//starts
{"starts","pau_s s_t t_aa aa_r r_t t_s s_pau"},
//station
{"station","pau_s s_t t_ey ey_ey ey_sh sh_ah ah_n n_pau"},
//stay
{"stay","pau_s s_t t_eh eh_iy iy_pau"},
//steve
{"steve","pau_s s_t t_iy iy_iy iy_v v_pau"},
//steven or stephen
{"steven","pau_s s_t t_iy iy_iy iy_v v_ah ah_n n_pau"},
//{"stephen","s_t t_iy iy_iy iy_v v_ah ah_n"},
//stock
{"stock","pau_s s_t t_aa aa_k k_pau"},
//store
{"store","pau_s s_t t_ao ao_r r_pau"},
//study
{"study","pau_s s_t t_ah ah_d d_iy iy_pau"},
{"studying","pau_s s_t t_ah ah_d d_iy iy_ih ih_ng ng_pau"},
//summer
{"summer","pau_s s_ah ah_m m_uh uh_r r_pau"},
//summertime
{"summertime","pau_s s_ah ah_m m_uh uh_r r_t t_aa aa_iy iy_m m_pau"},
//sunday 
//{"sunday","pau_s s_ah ah_ah ah_n n_n n_d d_ey ey_ey ey_pau"},
{"sunday","pau_s s_ah ah_ah ah_n n_d d_ey ey_ey ey_pau"},
//super
{"super","pau_s s_uw uw_p p_uh uh_r r_pau"},//prefix
//susan
{"susan","pau_s s_uw uw_uw uw_z z_ah ah_n n_pau"},
//susans
{"susans","pau_s s_uw uw_uw uw_z z_ah ah_n n_z z_pau"},
//synthesizer bad prounciation
{"synthesizer","pau_s s_ih ih_ih ih_n n_th th_ah ah_ah ah_th th_z z_s s_ay ay_ay ay_ay ay_er er_pau"},
//system
{"system","pau_s s_ih ih_s s_t t_ah ah_m m_pau"},


//T_words
//take
{"take","pau_t t_eh eh_iy iy_k k_pau"},
//talk
{"talk","pau_t t_ao ao_ao ao_k k_pau"},
//talking
{"talking","pau_t t_ao ao_ao ao_k k_ih ih_ng ng_pau"},
//task
{"task","pau_t t_ae ae_ae ae_s s_k k_pau"},
//tax
{"tax","pau_t t_ae ae_ae ae_k k_s s_pau"},
//taxi
{"taxi","pau_t t_ae ae_ae ae_k k_s s_iy iy_pau"},
//tea
{"tea","pau_t t_t t_iy iy_iy iy_pau"},
{"tearoom","pau_t t_r r_uh uh_r r_uw uw_m m_pau"},
//team
{"team","pau_t t_iy iy_m m_pau"},
//telephone
{"telephone","pau_t t_eh eh_eh eh_l l_ah ah_f f_f f_ow ow_ow ow_ow ow_n n_pau"},
//television
{"television","pau_t t_eh eh_eh eh_l l_ah ah_v v_ih ih_ih ih_zh zh_ah ah_n n_pau"},
//temperature
{"temperature","pau_t t_eh eh_m m_p p_r r_ah ah_ch ch_uh uh_r r_pau"},
//ten
{"ten","pau_t t_eh eh_eh eh_n n_pau"},
//tennis
{"tennis","pau_t t_eh eh_n n_ah ah_s s_pau"},
//tenth
{"tenth","pau_t t_eh eh_eh eh_n n_th th_pau"},
//test
{"test","pau_t t_eh eh_eh eh_s s_t t_pau"},
//thank
{"thank","pau_th th_ae ae_ng ng_k k_pau"},
//that
{"that","pau_dh dh_ae ae_t t_pau"},
//the
{"the","pau_dh dh_ah ah_ah ah_pau"},
//theatre
{"theater","pau_th th_iy iy_iy iy_ey ey_t t_er er_pau"},
//then
{"then","pau_dh dh_eh eh_eh eh_n n_pau"},
//theo
{"theo","pau_th th_iy iy_ao ao_uh uh_pau"},
//theodore
{"theodore","pau_th th_iy iy_ah ah_d d_ao ao_r r_pau"},
//third
{"third","pau_th th_er er_er er_d d_pau"},
//thirteen
{"thirteen","pau_th th_er er_er er_t t_iy iy_iy iy_n n_pau"},
//thirteenth
{"thirteenth","pau_th th_er er_er er_t t_iy iy_iy iy_n n_th th_pau"},
//thirtieth
{"thirtieth","pau_th th_er er_er er_t t_iy iy_eh eh_eh eh_th th_pau"},
//thirty
{"thirty","pau_th th_er er_er er_d d_iy iy_iy iy_pau"},
//thirty
{"thirtyfirst","pau_th th_er er_er er_d d_iy iy_iy iy_pau pau_f f_er er_er er_s s_t t_pau pau_t"},
//this
{"this","pau_dh dh_ih ih_s s_pau"},

//thomas
{"thomas","pau_t t_aa aa_aa aa_m m_ah ah_s s_pau"},
//{"thomases","t_aa aa_aa aa_m m_ah ah_s s_ih ih_z"},
//three
{"three","pau_t th_r r_iy iy_iy iy_pau"},
//thursday
{"thursday","pau_th th_er er_er er_z z_d d_iy iy_pau"},
//ticket
{"ticket","pau_t t_ih ih_k k_ah ah_t t_pau"},
//tiffany
{"tiffany","pau_t t_ih ih_f ih_f f_ah ah_n n_iy iy_pau"},
//tilda
{"tilda","pau_t t_ih ih_ih ih_l l_d d_ah ah_pau"},
//tim
{"tim","pau_t t_ih ih_ih ih_m m_pau"},
//time
{"time","pau_t t_ay ay_ay ay_m _pau"},
//times
{"times","pau_t t_aa aa_iy iy_m m_z z_pau"},
//timothy
{"timothy","pau_t t_ih ih_ih ih_m m_ah ah_th th_iy iy_pau"},
//tims
{"tims","pau_t t_ih ih_ih ih_m m_z z_pau"},
//tiny
{"tiny","pau_t t_aa aa_iy iy_n n_iy iy_pau"},
//to
{"to","pau_t t_uw uw_uw uw_pau"},
//today
{"today","pau_t t_ah ah_d d_ey ey_ey ey_pau"},
//toll
{"toll","pau_t t_ao ao_uh uh_l l_pau"},
//tom
{"tom","pau_t t_aa aa_aa aa_m m_pau"},
//tomorrow
{"tomorrow","pau_t t_ah ah_m m_aa aa_r r_ao ao_uh uh_pau"},
//toms
{"toms","pau_t t_aa aa_aa aa_m m_z z_pau"},
//train
{"train","pau_t t_r r_eh eh_iy iy_n n_pau"},
//trans
{"trans","pau_t t_r r_ae ae_n n_z"},//prefix
//transport
{"transport","pau_t t_r r_ae ae_n n_s s_p p_ao ao_r r_t t_pau"},
//travel
{"travel","pau_t t_r r_ae ae_ae ae_v v_ah ah_l l_pau"},
//traveling or travelling
{"traveling","pau_t t_r r_ae ae_ae ae_v v_ah ah_l l_ih ih_ng ng_pau"},
//travelodge
{"travelodge","pau_t t_r r_ae ae_ae ae_v v_ah ah_l l_aa aa_aa aa_jh jh_pau"},
//trevor
{"trevor","pau_t t_r r_eh eh_eh eh_v v_er er_pau"},
//trevors
//{"trevors","pau_t t_r r_eh eh_eh eh_v v_er er_z z_pau pau_z z_pau"},
{"trevors","pau_t t_r r_eh eh_eh eh_v v_er er_z z_z z_pau"},
//trip
{"trip","pau_t t_r r_ih ih_ih ih_p p_p p_pau"},
//tuesday
{"tuesday","pau_t t_uw uw_uw uw_z z_d d_iy iy_pau"},
//tunnel
{"tunnel","pau_t t_ah ah_n n_ah ah_l l_pau"},
//turn
{"turn","pau_t t_uh uh_r r_n n_pau"},
//tv
{"tv","pau_t t_iy iy_iy iy_v v_iy iy_iy iy_pau"},
//twelfth
//{"twelfth","pau_t t_w w_eh eh_eh eh_l l_f f_th th_pau pau_th th_pau"},
{"twelfth","pau_t t_w w_eh eh_eh eh_l l_f f_th th_th th_pau"},
//twelve
{"twelve","pau_t t_w w_eh eh_eh eh_l l_v v_pau"},
//twentieth
{"twentieth","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_eh eh_eh eh_th th_pau"},

//twenty
{"twenty","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau"},
//21st
{"twentyfirst","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_f f_er er_er er_s s_t t_pau pau_t"},
//22nd
{"twentysecond","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_s s_eh eh_eh eh_k k_ah ah_n n_d d_pau"},
//23rd
{"twentythird","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau  pau_th th_er er_er er_d d_pau"},
//24th
{"twentyfourth","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_f f_ao ao_ao ao_r r_th th_pau"},
//25th
{"twentyfifth","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_f f_ih ih_ih ih_f f_th th_pau"},
//26th
{"twentysixth","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_s s_ih ih_ih ih_k k_s s_th th_pau"},
//27th
{"twentyseventh","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_s s_eh eh_eh eh_v v_ah ah_n n_th th_pau"},
//28th
{"twentyeighth","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_eh eh_ey ey_ey ey_t t_th th_pau"},
//29th
{"twentyninth","pau_t t_w w_eh eh_eh eh_n n_t t_iy iy_pau pau_n n_ay ay_ay ay_n n_th th_pau"},

//two
{"two","pau_t t_uw uw_uw uw_pau"},

//U_words
//uncle
{"uncle","pau_ah ah_ah ah_ng ng_k k_ah ah_l l_pau"},
//uncles
{"uncles","pau_ah ah_ah ah_ng ng_k k_ah ah_l l_z z_pau"},

//university
{"university","pau_y y_uw uw_n n_ah ah_v v_uh uh_r r_s s_ah ah_t t_iy iy_pau"},
//unknown
{"unknown","pau_ah ah_n n_n n_ow ow_ow ow_n n_n n_pau"},

//upcoming
{"upcoming","pau_ah ah_p p_k k_ah ah_ah ah_m m_ih ih_ng ng_pau"},
//ursula
{"ursula","pau_uh uh_r r_s s_ah ah_l l_ah ah_pau"},
//use
{"use","pau_y y_uw uw_uw uw_z z_pau"},
//user
{"user","pau_y y_uw uw_uw uw_z z_er er_pau"},

//V_words
//vacation
{"vacation","pau_v v_ey ey_k k_ey ey_ey ey_sh sh_ah ah_n n_pau"},
//val
{"val","pau_v v_ae ae_ae ae_l l_pau"},
//valentine
{"valentine","pau_v v_ae ae_ae ae_l l_ah ah_n n_t t_ay ay_ay ay_n n_pau"},
//valentines
{"valentines","pau_v v_ae ae_ae ae_l l_ah ah_n n_t t_ay ay_ay ay_n n_z z_pau"},
//valerie
{"valerie","pau_v v_ae ae_ae ae_l l_er er_iy iy_pau"},
//vehicle
{"vehicle","pau_v v_iy iy_iy iy_hh hh_ih ih_k k_ah ah_l l_pau"},
//venue
{"venue","pau_v v_eh eh_n n_y y_uw uw_pau"},
//version
{"version","pau_v v_er er_er er_zh zh_ah ah_n n_pau"},
//veronica
{"veronica","pau_v v_uh uh_r r_aa aa_n n_ih ih_k k_ah ah_pau"},
{"vicar","pau_v v_ih ih_k k_uh uh_r r_pau"},
{"vicarage","pau_v v_ih ih_k k_uh uh_r r_r r_aa aa_jh jh_pau"},
//victor
{"victor","pau_v v_ih ih_k k_t t_uh uh_r r_pau"},
{"victoria","pau_v v_ih ih_k k_t t_ao ao_r r_iy iy_ah ah_pau"},
//visit
{"visit","pau_v v_ih ih_ih ih_z z_ih ih_t t_pau"},

//w_words
//walk
{"walk","pau_w w_w w_ao ao_ao ao_k k_k k_pau"},
//warm
{"warm","pau_w w_ao ao_r r_m m_pau"},
//warming
{"warming","pau_w w_ao ao_r r_m m_ih ih_ng ng_pau"},
{"warn","pau_w w_ao ao_r r_n n_pau"},
{"warning","pau_w w_ao ao_r r_n n_ih ih_ng ng_pau"},
//wash
{"wash","pau_w w_aa aa_sh sh_pau"},
//washing
{"washing","pau_w w_aa aa_sh sh_ih ih_ng ng_pau"},
//water
//{"water","w_ao ao_t t_uh uh_r"},
{"water","pau_w w_ao ao_ao ao_t t_er er_pau"},
//way
{"way","pau_w w_ey ey_iy iy_pau"},
//weather warning (to do)
{"weather","pau_w w_eh eh_dh dh_uh uh_r r_pau"},
//web
{"web","pau_w w_eh eh_eh eh_b b_b b_pau"},
//wedding
{"wedding","pau_w w_eh eh_eh eh_d d_ih ih_ng ng_pau"},
//wednesday
{"wednesday","pau_w w_eh eh_eh eh_n n_z z_d d_iy iy_pau"}, //or iy_iy
//week
{"week","pau_w w_iy iy_k k_pau"},
//weekend
{"weekend","pau_w w_iy iy_k k_eh eh_n n_d d_pau"},
//west
{"west","pau_w w_eh eh_s s_t t_pau"},
//wife
{"wife","pau_w w_ay ay_ay ay_f f_pau"},
//wifes
{"wifes","pau_w w_aa aa_iy iy_f f_s s_pau"},
//willow
{"willow","pau_w w_ih ih_l l_ao ao_uh uh_pau"},
{"wills","pau_w w_ih ih_l l_z z_pau"},
{"willy","pau_w w_ih ih_l l_iy iy_pau"},
{"willyum","pau_w w_ih ih_l l_y y_ah ah_m m_pau"},
{"wilma","pau_w w_ih ih_l l_m m_ah ah_pau"},
{"wilson","pau_w w_ih ih_l l_s s_ah ah_n n_pau"},
//window
{"window","pau_w w_ih ih_n n_d d_ao ao_uh uh_pau"},
//winnie
{"winnie","pau_w w_ih ih_ih ih_n n_iy iy_pau"},
//winnifred
{"winnifred","pau_w w_ih ih_ih ih_n n_ih ih_f f_r r_ih ih_d d_pau"},
//winston
{"winston","pau_w w_ih ih_ih ih_n n_s s_t t_ah ah_n n_pau"},
//winter
{"winter","pau_w w_ih ih_ih ih_n n_t t_er er_pau"},
//witch
{"witch","pau_w w_ih ih_ch ch_pau"},
//woman
{"woman","pau_w w_uh uh_m m_ah ah_n n_pau"},
//word
{"word","pau_w w_uh uh_r r_d d_pau"},
//work
{"work","pau_w w_uh uh_r r_k k_pau"},
//working
{"working","pau_w w_uh uh_r r_k k_ih ih_ng ng_pau"},
{"workman","pau_w w_uh uh_r r_k k_m m_ah ah_n n_pau"},
//workshop
{"workshop","pau_w w_uh uh_r r_k k_sh sh_aa aa_p p_pau"},
//world
{"world","pau_w w_er er_er er_l l_d d_d d_pau"},

//X_words
//xavier
//xena

//Y_words
//yacht
{"yacht","pau_y y_aa aa_aa aa_t t_pau"},
//year
{"year","pau_y y_ih ih_ih ih_r r_pau"},
//yearly
{"yearly","pau_y y_ih ih_ih ih_r r_l l_iy iy_pau"},
//yesterday
{"yesterday","pau_y y_eh eh_s s_t t_er er_d d_ey ey_pau"},
{"yodel","pau_y y_ao ao_uh uh_d d_ah ah_l l_pau"},
//you
{"you","pau_y y_uw uw_uw uw_pau"},
{"youth","pau_y y_uw uw_th th_pau"},

//Z_words
//zach
{"zach","pau_z z_ae ae_k k_pau"},
//zachary
{"zachary","pau_z z_ae ae_k k_uh uh_r r_iy iy_pau"},
//zara
{"zarahemla","pau_z z_ae ae_r r_ah ah_hh hh_iy iy_m m_l l_ah ah_pau"},
{"zeppelin","pau_z z_eh eh_p p_ih ih_l l_ih ih_n n_pau"},
//zero
{"zero","pau_z z_iy iy_iy iy_r r_ow ow_pau"},
//zoe
{"zoe","pau_z z_ao ao_uh uh_iy iy_pau"},
//zone
{"zone","pau_z z_ao ao_uh uh_n n_pau"},
//zoo
{"zoo","pau_z z_uw uw_pau"},

	
};

// Number of entries in the lookup table
const unsigned int word_table_size = sizeof(word_table) / sizeof(word_table[0]);

/**
 * @brief get the diphone sequence for a word
 * @param word to find
 */
WordEntry* find_word_entry(const char* word) {
    for (unsigned int i = 0; i < sizeof(word_table) / sizeof(word_table[0]); i++) {
        if (strcmp(word_table[i].word, word) == 0) {
            return &word_table[i];
        }
    }
    return NULL;
}

