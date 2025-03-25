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
#include <gtk/gtk.h> 
#include "dictionary.h"

//talk calendar dictionary

//dictionary key value pair
typedef struct pair {
  char *key;
  char *value;
} pair_t;


// Key strings must be in strcmp() sorted order!
pair_t table[] = {

//a-words
{"a","ey-ey ey-ey"}, 
{"accountant","ah-k k-aa aa-uh uh-n n-t t-ah ah-n n-t"},
{"activity","ae-k k-t t-ih ih-ih ih-v v-ah ah-t t-iy iy-pau"},
{"afternoon","ae-ae ae-ae ae-f f-t t-er er-pau pau-er er-n n-uw uw-uw uw-n"},
{"airport","eh-eh eh-r r-p p-ao ao-ao ao-r r-t"},
{"alan","ae-ae ae-l l-ah ah-n"}, 
{"alans","ae-ae ae-l l-ah ah-n n-z"}, 
{"alec","ae-ae ae-l l-ih ih-k"},
{"alex","ae-ae ae-l l-ah ah-k k-s"},
{"alexander","ae-ae ae-l l-ah ah-g g-z z-ae ae-n n-d d-uh uh-r"},
{"alexanders","ae-ae ae-l l-ih ih-g g-z z-ae ae-n n-d d-uh uh-r r-z"},
{"alexs","ae-ae ae-l l-ah ah-k k-s s-ih ih-z"},
{"alf","ae-ae ae-l l-f"},
{"alfred","ae-ae ae-l l-f f-r r-ah ah-d"},
{"alfreds","ae-ae ae-l l-f f-r r-ih ih-d d-z"},
{"alice","ae-ae ae-l l-ih ih-s"},
{"alices","ae-ae ae-l l-ih ih-s s-ah ah-z"},
{"alison","ae-ae ae-l l-ih ih-s s-ah ah-n"},
{"alisons","ae-ae ae-l l-ih ih-s s-ah ah-n n-z"},
{"alister","ae-ae ae-l l-ih ih-s s-t t-uh uh-r"},
{"allan","ae-ae ae-l l-ah ah-n"},
{"allans","ae-ae ae-l l-ah ah-n n-z"},
{"allen","ae-ae ae-l l-ah ah-n"},
{"allison","ae-ae ae-l l-ah ah-s s-ah ah-n"},
{"allisons","ae-ae ae-l l-ih ih-s s-ah ah-n n-z"},
{"allister","ao-ao ao-l l-ih ih-s s-t t-er er-pau"},
{"allotment","ah-l l-aa aa-aa aa-t t-m m-ah ah-n n-t"},
{"amazon","ae-ae ae-m m-ah ah-z z-aa aa-aa aa-n"},
{"amber","ae-ae ae-m m-b b-er er-pau"},
{"ambulance","ae-ae ae-m m-b b-y y-ah ah-l l-ah ah-n n-s"},
{"amelia","ah-m m-iy iy-iy iy-l l-y y-ah"},
{"amelias","ah-m m-iy iy-iy iy-l l-y y-ah ah-z"},
{"amm","ey-ey ey-ae ae-m m-m m-m"}, //a.m.
{"and","ah-n n-d"},
{"andora","ae-ae ae-n d-ao ao-ao ao-r r-ah ah-pau"},
{"andre","aa-aa aa-n n-d d-r r-ey ey-ey"},
{"andrea","ae-ae ae-n n-d d-r r-iy iy-iy iy-ah"},
{"andreas","ae-ae aa-n n-d d-r r-eh eh-iy iy-iy iy-ah ah-z"},
{"andrew","ae-ae ae-n n-d d-r r-uw uw-pau"},
{"andrews","ae-ae ae-n n-d d-r r-uw uw-uw uw-z"},
{"andy","ae-ae ae-n n-d d-iy iy-pau"},
{"andys","ae-ae ae-n n-d d-iy iy-pau pau-iy iy-z"},
{"angela","ae-ae ae-n n-jh jh-ah ah-l l-ah"},
{"angelina","ae-n n-jh jh-eh eh-l l-iy iy-n n-ah"},
{"anna","ae-ae ae-n n-ah"},
{"annabel","ae-ae ae-n n-ah ah-b b-eh eh-eh eh-l"},
{"anne","ae-ae ae-n"},
{"anniversary","ae-ae ae-n n-ah ah-v v-er er-er er-s s-er er-iy iy-pau"},
{"anthony","ae-ae ae-n n-th th-ao ao-n n-iy iy-iy"},
{"anthony","ae-ae ae-n n-th th-ao ao-n n-iy iy-iy iy-z"},
{"appointment","pau-ah ah-p p-oy oy-oy oy-n n-t t-m m-ah ah-n n-t"},
{"april","ey-ey ey-p p-r r-ah ah-l"},
{"art","aa-aa aa-aa aa-r r-t"},
{"assessment","ah-s s-eh eh-eh eh-s s-m m-ah ah-pau pau-ah ah-n n-t"},
{"aubrey","ao-ao ao-b b-r r-iy iy-pau"},
{"audrey","ao-ao ao-d d-r r-iy iy-pau"},
{"audreys","ao-ao ao-uh uh-d d-r r-iy iy-z"},
{"august","aa-aa aa-g g-ah ah-s s-t t-pau"},
{"aunt","ae-ae ae-n n-t"},
{"auntie","ae-ae ae-n n-t t-iy iy-pau"},
{"aunts","ae-ae ae-n n-t t-s"},
{"aunty","ae-ae ae-n n-t t-iy iy-pau"},


//b-words
{"bank","b-ae ae-ae ae-ng ng-k"},
{"banking","b-ae ae-ae ae-ng ng-k k-ih ih-ng"},
{"barber","b-aa aa-aa aa-r r-b b-er er-pau"},
{"barbers","b-aa  aa-aa aa-r r-b b-er er-z z-pau"},
{"beth","b-eh eh-eh eh-th"},
{"bethany","b-eh eh-eh eh-th th-ah ah-n n-iy iy-pau"},
{"betsy","b-eh eh-eh eh-t t-s s-iy iy-pau"},
{"betsys","b-eh eh-eh eh-t t-s s-iy iy-z z-pau"},
{"bike","b-ay ay-ay ay-k"},
{"billy","b-ih ih-ih ih-l l-iy iy-pau"},
{"bin","b-ih ih-ih ih-n"},
{"birthday","b-er er-er er-th th-d d-ey ey-ey ey-pau"},
{"boxing","b-aa aa-aa aa-k k-s s-ih ih-ng"},
{"breakfast","b-r r-eh eh-eh eh-k k-f f-ah ah-s s-t t-pau"},
{"bus","b-ah ah-ah ah-s s-s"},

//c-words
{"cafe","k-ah ah-f f-ey ey-ey"},
{"calendar","k-ae ae-ae ae-l l-ah ah-n n-d d-er er-pau"},
{"car","k-aa aa-aa aa-r"},
{"catherine","k-ae ae-ae ae-th th-er er-ah ah-n"},
{"charles","ch-aa aa-aa aa-r r-l l-z"},
{"charlotte","sh-aa  aa-aa aa-r r-l l-ah ah-t"},
{"chips","ch-ih ih-ih ih-p p-s s-pau"}, //dog name - walk chips
{"chore","ch-ao ao-ao ao-r r-pau"},
{"christmas","k-r r-ih ih-ih ih-s s-m m-ah ah-s"},
{"church","ch-er er-er er-ch"},
{"cinema","s-ih ih-ih ih-n n-ah ah-m m-ah ah-pau"},
{"claire","k-l l-eh eh-eh eh-r"},
{"clara","k-l l-ae ae-ae ae-r r-ah"},  //aunt clara
{"clarence","k-l l-eh eh-eh eh-r r-ah ah-n n-s"},
{"clarissa","k-l l-er er-ih ih-ih ih-s s-ah"},
{"claude","k-l l-ao ao-ao ao-d"},
{"clinic","k-l l-ih ih-ih ih-n n-ih ih-k"},
{"coach","k-ow ow-ow ow-ch ch-ch"},
{"cottage","k-aa  aa-aa aa-t t-ah ah-jh"},
//CRISPIN  K R IH1 S P IH0 N
{"crispin","k-r  r-ih ih-ih ih-s s-p p-ih ih-n n-pau"}, //st crispin day
{"crispins","k-r  r-ih ih-ih ih-s s-p p-ih ih-n n-z z-pau"},

//d-words
{"dad","d-ae ae-ae ae-d"},
{"dads","d-ae ae-ae ae-d d-z"},
{"daisy","d-ey ey-ey ey-z z-iy iy-pau"},
{"daniel","d-ae ae-ae ae-n n-y y-ah ah-l"},
{"danielle","d-ae ae-ae ae-n n-iy iy-eh eh-eh eh-l"},
{"danny","d-ae ae-ae ae-n n-iy"},
{"date","d-ey ey-ey ey-t"},
{"dates","d-ey ey-ey ey-t t-s s-pau"},
{"dave","d-ey ey-ey ey-v"},
{"david","d-ey ey-ey ey-v v-ih ih-d"},
{"day","d-ey ey-ey"},
{"deadline","d-eh eh-eh eh-d d-l l-ay ay-ay ay-n"},
{"debbie","d-eh eh-eh eh-b b-iy iy-pau"},
{"debby","d-eh eh-eh eh-b b-iy iy-pau"},
{"deborah","d-eh eh-eh eh-b b-er er-ah ah-pau"},
{"december","d-ih ih-s s-eh eh-eh eh-m m-b b-er er-pau"},
{"delivery","d-ih ih-l l-ih ih-ih ih-v v-er er-iy iy-pau"},
{"dentist","d-eh eh-eh eh-n n-t t-ah ah-s s-t"},
{"dinner","d-ih ih-ih ih-n n-er er-pau"},
{"diphone","d-ih ih-ih ih-f f-ow ow-ow ow-n n-pau"}, //bad pronouciation
{"doctor","d-aa aa-aa aa-k k-t t-er er-pau"},
{"doctors","d-aa aa-aa aa-k k-t t-er r-z z-pau"},
{"don","d-aa aa-aa aa-n"},
{"donald","d-aa aa-aa aa-n n-ah ah-l l-d"},
{"donalds","d-aa aa-aa aa-n n-ah ah-l l-d d-z"},
{"dons","d-aa aa-aa aa-n n-z"},
{"dora","d-ao ao-ao ao-r r-ah ah-pau"},
{"driver","d-r r-ay ay-ay ay-v v-er er-pau"},

//e-words
{"ear","iy-iy iy-r"},
{"easter","iy-iy iy-s s-t t-er er-pau"},
{"eight","ey-ey ey-t"},
{"eighteen","eh-ey ey-t t-iy iy-iy iy-n n-pau"},
{"eighteenth","ey-ey ey-t t-iy iy-iy iy-n n-th th-pau"},
{"eighth","eh-ey ey-t t-th th-pau"},
{"electrician","ih-ih ih-l l-eh eh-k k-t t-r r-ih ih-ih ih-sh sh-ah ah-n"},
{"eleven","ih-l l-eh eh-eh eh-v v-ah ah-n"},
{"eleventh","ih-l l-eh eh-eh eh-v v-ah ah-n n-th th-pau"},
{"elisha","eh-eh eh-l l-ih ih-sh sh-ah ah-pau"},
{"eliza","ih-l l-ay ay-ay ay-z z-ah ah-pau"},
{"elizabeth","ih-l l-ih ih-ih ih-z z-ah ah-b b-ah ah-th"},
{"elizabeths","ih-l l-ih ih-ih ih-z z-ah ah-b b-ah ah-th th-s"},
{"elizas","ih-l l-ay ay-ay ay-z z-ah ah-z"},
{"elliot","eh-eh eh-l l-iy iy-ah ah-t"},
{"elliott","eh-eh eh-l l-iy iy-ah ah-t"},
{"emma","eh-eh eh-m m-ah"},
{"evan","eh-eh eh-v v-ah ah-n"},
{"evening","iy-iy iy-v v-n n-ih ih-ng ng-pau"},
{"event","ih-v v-eh eh-eh eh-n n-t"},
{"eye","aa-iy"},

//f-words
{"family","f-ae ae-ae ae-m m-ah ah-l l-iy iy-pau"},
{"farm","f-aa aa-aa aa-r r-m"},
{"father","f-aa aa-aa aa-dh dh-er er-pau"},
{"fathers","f-aa aa-aa aa-dh dh-er er-pau pau-er er-z"},
{"february","f-eh eh-eh eh-b b-y y-ah ah-w w-eh eh-eh eh-r r-iy iy-pau"},
{"fifteen","f-ih ih-ih ih-f f-t t-iy iy-iy iy-n n-pau"},
{"fifteenth","f-ih ih-f f-t t-iy iy-iy iy-n n-th th-pau"},
{"fifth","f-ih ih-ih ih-f f-th th-pau"},
{"fifty","f-ih ih-ih ih-f f-t t-iy iy-pau"},
{"film","f-ih ih-ih ih-l l-m m-pau"},
{"fiona","f-iy iy-ow ow-ow ow-n n-ah ah-pau"},
{"first","f-er er-er er-s s-t t-pau pau-t"},
{"fish","f-ih ih-ih ih-sh"},
{"five","f-ay ay-ay ay-v"},
{"forty","f-ao ao-ao ao-r r-t t-iy iy-pau"},
{"four","f-ao ao-ao ao-r"},
{"fourteen","f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-pau"},
{"fourteenth","f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-th th-pau pau-th"},
{"fourth","f-ao ao-ao ao-r r-th th-pau"},
{"frances","f-r r-ae ae-ae ae-n n-s s-ih ih-s"},
{"francesca","f-r r-ae ae-n n-ch ch-eh eh-eh eh-s s-k k-ah"},
{"francis","f-r r-ae ae-ae ae-n n-s s-ah ah-s"},
{"frank","f-r r-ae ae-ae ae-ng ng-k"},
{"fred","f-r r-eh eh-eh eh-d"},
{"freddie","f-r r-eh eh-eh eh-d d-iy iy-pau"},
{"freddy","f-r r-eh eh-eh eh-d d-iy iy-pau"},
{"frederic","f-r r-eh eh-d d-r r-ih ih-k"},
{"frederick","f-r r-eh eh-eh eh-d d-er er-ih ih-k"},
{"freds","f-r r-eh eh-eh eh-d d-z z-pau"},
{"friday","f-r r-ay ay-ay ay-d d-iy iy-pau"},
{"friend","f-r r-eh eh-eh eh-n n-d"},
{"funeral","f-y y-uw uw-uw uw-n n-er er-ah ah-l"},

//g-words
{"gale","g-ey ey-ey ey-l"},
{"gallery","g-ae ae-ae ae-l l-er er-iy iy-pau"},
{"garden","g-aa aa-aa aa-r r-d d-ah ah-n"},
{"gas","g-ae ae-ae ae-s s-s"},
{"geoffrey","jh-eh eh-eh eh-f f-r r-iy iy-pau"},
{"george","jh-ao ao-ao ao-r r-jh"},
{"georges","jh-ao ao-ao ao-r r-jh jh-ah ah-z z-pau"},
{"georgina","jh-ao ao-ao ao-r r-jh jh-iy iy-n n-ah ah-pau"},
{"glasses","g-l l-ae ae-ae ae-s s-ah ah-z"},
{"grandad","g-r r-ae ae-ae ae-n n-d d-ae ae-ae ae-d"},
{"granny","g-r r-ae ae-ae ae-n n-iy iy-pau"},

//h-words
{"hairdressing","hh-eh eh-eh eh-r r-d d-r r-eh eh-eh eh-s s-ih ih-ng"},
{"halloween","hh-ae ae-ae ae-l l-ah ah-w w-iy iy-iy iy-n"},
{"hanna","hh-ae ae-ae ae-n n-ah"},
{"hannah","hh-ae ae-ae ae-n n-ah"},
{"harold","hh-eh eh-eh eh-r r-ah ah-d"},
{"harolds","hh-eh eh-eh eh-r r-ah ah-d d-z"},
{"harry","hh-eh eh-eh eh-r r-iy"},
{"health","hh-eh eh-eh eh-l l-th"},
{"heating","hh-iy iy-iy iy-t t-ih ih-ng"},
{"hector","hh-eh eh-eh eh-k k-t t-er er-pau"},
{"helen","hh-eh eh-eh eh-l l-ah ah-n"},
{"hello","hh-ah ah-l l-ow ow-ow ow-pau"},
{"help","hh-eh eh-eh eh-l l-p"},
{"herbert","hh-er er-er er-b b-t"},
{"herbert","hh-er er-er er-b b-t t-s"},
{"holiday","hh-aa aa-aa aa-l l-ah ah-d d-ey ey-ey"},
{"hospital","hh-aa aa-aa aa-s s-p p-ih ih-ih ih-t t-ah ah-l"},
{"hotel","hh-ow ow-t t-eh eh-eh eh-l"},
{"hour","aw-aw aw-r r-pau"},
{"hours","aw-aw aw-r r-z"},
{"house","hh-hh hh-aw aw-aw aw-s s-s"},
{"humanoid","hh-y y-uw uw-uw uw-m m-ah ah-n n-oy oy-oy oy-d"},
{"humphrey","hh-ah  ah-ah ah-m m-f f-r r-iy iy-pau"},
{"husband","hh-ah  ah-ah ah-z z-b b-ah ah-n n-d"},
{"husbands","hh-ah  ah-ah ah-z z-b b-ah ah-n n-d d-z"},

//i-words
{"i","ay-ay ay-pau"},
{"ian","iy-iy iy-ah ah-n"},
{"irene","ay-r r-iy iy-iy iy-n"},
{"is","pau-ih ih-z"},
{"isaac","ih-ih ih-s s-ah ah-k"},
{"isaacs","ih-ih ih-s s-ah ah-k k-s"},
{"isabel","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l"},
{"isabella","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-ah ah-pau"},
{"isabellas","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-ah ah-z"},
{"isabelle","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l"},
{"isabels","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-z"},
{"ivan","ay-ay ay-v v-ah ah-n"},
{"ivans","ay-ay ay-v v-ah ah-n n-z"},
{"ivy","ay-ay ay-v v-iy iy-pau"},

//j-words
{"jack","jh-ae ae-ae ae-k"},
{"jackie","jh-ae ae-ae ae-k k-iy iy-pau"},
{"jacks","jh-ae ae-ae ae-k k-s"},
{"jacky","jh-ae ae-ae ae-k k-iy"},
{"jacob","jh-eh ey-ey ey-k k-ah ah-b"},
{"jacobs","jh-eh ey-ey ey-k k-ah ah-b b-z"},
{"jacqueline","jh-ae ae-ae ae-k k-w w-ah ah-l l-ih ih-n"},
{"james","jh-ey ey-ey ey-m m-z"},
{"jamie","jh-ey ey-ey ey-m m-iy iy-pau"},
{"january","jh-ae ae-ae ae-n n-y y-uw uw-eh eh-eh eh-r r-iy iy-pau"},
{"jason","jh-ey ey-ey ey-s s-ah ah-n"},
{"jeff","jh-eh eh-eh eh-f"},
{"jeffrey","jh-eh eh-eh eh-f f-r r-iy iy-pau"},
{"job","jh-aa aa-aa aa-b b-b"},
{"john","jh-aa aa-aa aa-n"},
{"johns","jh-aa aa-aa aa-n n-z"},
{"journey","jh-er er-er er-n n-iy iy-pau"},
{"july","jh-uw uw-uw uw-l l-ay ay-ay ay-pau"},
{"june","jh-uw uw-uw uw-n n-pau"},

//k-word
{"karen","k-eh eh-eh eh-r r-ah ah-n"},
{"kate","k-ey ey-ey ey-t"},
{"katherine","k-ae ae-ae ae-th th-er er-ih ih-n"},
{"ken","k-eh eh-eh eh-n"},

//l-words
{"lecture","l-eh eh-eh eh-k k-ch ch-er er-pau"},
{"lift","l-ih ih-ih ih-f f-t"},
{"lilly","l-ih ih-ih ih-l l-iy iy-pau"},
{"linux","l-ih ih-ih ih-n n-ah ah-k k-s"},
{"louisa","l-uw uw-iy iy-iy iy-z z-ah ah-pau"},
{"lunch","l-ah ah-ah ah-n n-ch ch-pau"},

//m-words
{"madeline","m-ae ae-ae ae-d d-ah ah-l l-ih ih-n"},
{"maintenance","m-ey ey-ey ey-n n-t t-ah ah-n n-ah ah-n n-s s-s"},
{"management","m-ae ae-ae ae-n n-ah ah-jh jh-m m-ah ah-n n-t"},
{"march","m-aa aa-aa aa-r r-ch ch-pau"},
{"mary","m-eh eh-eh eh-r r-iy iy-pau"},
{"marys","m-eh eh-eh eh-r r-iy iy-z"},
{"master","m-ae ae-ae ae-s s-t t-er er-pau"},
{"matt","m-ae ae-ae ae-t"},
{"matthew","m-ae ae-ae ae-th th-y y-uw uw-pau"},
{"matthews","m-ae ae-ae ae-th th-y y-uw uw-z"},
{"matthias","m-ah ah-th th-ay ay-ay ay-ah ah-s"},
{"may","m-ey ey-ey ey-pau"},
{"meal","m-iy iy-iy iy-l l-pau"},
{"medical","m-eh eh-eh eh-d d-ah ah-k k-ah ah-l"},
{"meet","m-iy iy-iy iy-t"},
{"meeting","m-iy iy-iy iy-t t-ih ih-ng"},
{"memorandum","m-eh eh-eh eh-m m-er er-ae ae-ae ae-n n-d d-ah ah-m"},
////MINI  M IH1 N IY0
{"mini","m-ih ih-ih ih-n n-iy iy-iy iy-pau"},

{"monday","m-ah ah-ah ah-n n-d d-iy iy-pau"},
{"morning","m-ao ao-ao ao-r r-n n-ih ih-ng"},
{"mother","m-ah ah-ah ah-dh dh-er er-pau"},
{"mothers","m-ah ah-ah ah-dh dh-er er-z"},
{"motorcycle","m-ow ow-ow ow-t t-er er-s s-ay ay-ay ay-k k-ah ah-l"},
{"movie","m-uw uw-uw uw-v v-iy iy-pau"},
{"mum","m-ah ah-ah ah-m"},
{"mums","m-ah ah-ah ah-m m-z"},
{"music","m-y y-uw uw-uw uw-z z-ih ih-k"},
{"my","m-ay ay-ay"},

//n-words
{"naomi","n-ey ey-ow ow-ow ow-m m-iy iy-pau"},
{"netflix","n-eh eh-eh eh-t t-f f-l l-ih ih-ih ih-k k-k"},
{"new","n-uw uw-uw"},
{"nine","n-ay ay-ay ay-n"},
{"nineteen","n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-pau"},
{"nineteenth","n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-th th-pau pau-th"},
{"ninth","n-ay ay-ay ay-n n-th th-pau"},
{"norman","n-ao ao-r r-m m-ah ah-n"},
{"normans","n-ao ao-r r-m m-ah ah-n n-z"},
{"november","n-ow ow-v v-eh eh-eh eh-m m-b b-er er-pau"},
{"now","n-aw aw-aw aw-pau"},
{"nursery","n-er er-er er-s s-er er-iy"},

//o-words
{"o","ao-uh uh-ao ao-uh"},
{"october","aa-k k-t t-ow ow-ow ow-b b-er"},
{"office","ao-ao ao-f f-ah ah-s"},
{"oliver","aa-aa aa-l l-ih ih-v v-er"},
{"olivia","ow-l l-ih ih-ih ih-v v-iy iy-ah ah-pau"},
{"olivias","ow-l l-ih ih-ih ih-v v-iy iy-ah ah-z"},
{"on","aa-aa aa-n n-n"},
{"one","w-ah ah-ah ah-n"},
{"own","ow-ow-ow-ow ow-n n-pau"},

//p-words
{"pam","p-ae ae-ae ae-m"},
{"pamela","p-ae ae-ae ae-m m-ah ah-l l-ah"},
{"pams","p-ae ae-ae ae-m m-z z-pau"},
{"pancake","p-ae ae-ae ae-n n-k k-ey ey-ey ey-k"},
{"party","p-aa aa-aa aa-r r-t t-iy iy-pau"},
{"passport","p-ae ae-ae ae-s s-p p-ao ao-ao ao-r r-t"},
{"pau","pau-pau"},
{"paul","p-ao ao-ao ao-l"},
{"paula","p-ao ao-ao ao-l l-ah ah-pau"},
{"pauline","p-ao ao-l l-iy iy-iy iy-n"},
{"pause","pau-pau"},
{"payment","p-ey ey-ey ey-m m-ah ah-n n-t"},
{"penelope","p-ah ah-n n-eh eh-eh eh-l l-ah ah-p p-iy iy-pau"},
{"penny","p-eh eh-eh eh-n n-iy iy-pau"},
{"pension","p-eh eh-eh eh-n n-sh sh-ah ah-n"},
{"percy","p-er er-er er-s s-iy iy-pau"},
{"perry","p-eh eh-eh eh-r r-iy iy-pau"},
{"peter","p-iy iy-iy iy-t t-er er-pau"},
{"peters","p-iy iy-iy iy-t t-er er-z"},
{"phebe","f-iy iy-iy iy-b b-iy iy-pau"},
{"phoebe","f-iy iy-iy iy-b b-iy iy-pau"},
{"pmm","p-iy iy-iy iy-m m-eh eh-m m-m m-m"},
{"point","p-oy oy-oy oy-n n-t t-pau"},
{"program","p-r r-ow ow-ow ow-g g-r r-ae ae-ae ae-m m-pau"},
{"programme","p-r r-ow ow-ow ow-g g-r r-ae ae-ae ae-m m-pau"},
{"project","p-r r-aa aa-aa aa-jh jh-eh eh-k k-t"},
{"prunella","p-r r-uw uw-n n-eh eh-eh eh-l l-ah"},
{"pub","p-ah ah-ah ah-b b-pau"},
{"public","p-ah ah-ah ah-b b-l l-ih ih-k k-pau"},

//q-words
{"quiz","k-w w-ih ih-ih ih-z z-pau"},
{"quote","k-w w-w w-ow ow-ow ow-t t-pau"},
//r-words
{"radio","r-ey ey-ey ey-d d-iy iy-ow ow-ow ow-pau"},
{"reminder","r-iy iy-m m-ay ay-ay ay-n n-d d-er er-pau"},
{"rest","r-eh eh-eh eh-s s-t"},
{"restaurant","r-eh eh-eh eh-s s-t t-er er-aa aa-aa aa-n n-t"},
{"retirement","r-iy iy-t t-ay ay-er er-m m-ah ah-n n-t"},
{"rose","r-ow ow-ow ow-z"},
{"rosemary","r-ow ow-ow ow-z z-m m-eh eh-eh eh-r r-iy iy-pau"},

//s-words
{"sabrina","s-ah ah-b b-r r-iy iy-iy iy-n n-ah ah-pau"},
{"saint","s-ey ey-ey ey-n n-t t-pau"},
{"saturday","s-ae ae-ae ae-t t-ih ih-ih ih-d d-ey ey-ey"},
{"school","s-k k-uw uw-l"},
{"second","s-eh eh-eh eh-k k-ah ah-n n-d d-pau"},
{"self","s-eh eh-eh eh-l l-f"},
{"seminar","s-eh eh-eh eh-m m-ah ah-n n-aa aa-aa aa-r r-r"},
{"september","s-eh eh-p p-t t-eh eh-eh eh-m m-b b-er er-pau"},
{"service","s-er er-er er-v v-ah ah-s"},
{"seven","s-eh eh-eh eh-v v-ah ah-n"},
{"seventeen","s-eh eh-eh eh-v v-ah ah-n n-t t-iy iy-iy iy-n n-pau"},
{"seventeenth","s-eh eh-eh eh-v v-ah ah-n n-t t-iy iy-iy iy-n n-th th-pau"},
{"seventh","s-eh eh-eh eh-v v-ah ah-n n-th th-pau"},
{"shop","sh-aa aa-aa aa-p"},
{"shopping","sh-aa aa-aa aa-p p-ih ih-ng"},
{"show","sh-ow ow-ow ow-pau"},
{"six","s-ih ih-ih ih-k k-s s-pau"},
{"sixteen","s-ih ih-k k-s s-t t-iy iy-iy iy-n n-pau"},
{"sixteenth","s-ih ih-k k-s s-t t-iy iy-iy iy-n n-th th-pau"},
{"sixth","s-ih ih-ih ih-k k-s s-th th-pau"},
{"society","s-ow ow-s s-ay ay-ay ay-ih ih-t t-iy iy-pau"},
{"speech","s-p p-iy iy-iy iy-ch ch-ch"},
{"sport","s-p p-ao ao-ao ao-r r-t"},
{"spring","s-p p-r r-ih ih-ih ih-ng"},
{"stephen","s-t t-iy iy-iy iy-v v-ah ah-n"},
{"steve","s-t t-iy iy-iy iy-v"},
{"steven","s-t t-iy iy-iy iy-v v-ah ah-n"},
{"sunday","s-ah ah-ah ah-n n-d d-ey ey-ey ey-pau pau-ey"},
{"susan","s-uw uw-uw uw-z z-ah ah-n"},
{"susans","s-uw uw-uw uw-z z-ah ah-n n-z"},
{"synthesizer","s-ih ih-ih ih-n n-th th-ah th-z z-s s-ay ay-ay ay-ay ay-er er-pau"},
//{"synthesizer","s-ih ih-ih ih-n n-th th-ah ah-ah ah-s s-s s-ay ay-er er-er"},


//t-words
{"talk","t-ao ao-ao ao-k"},
{"talking","t-ao ao-ao ao-k k-ih ih-ng"},
{"task","t-ae ae-ae ae-s s-k"},
{"tax","t-ae ae-ae ae-k k-s"},
{"taxi","t-ae ae-ae ae-k k-s s-iy iy-pau"},
{"television","t-eh eh-eh eh-l l-ah ah-v v-ih ih-ih ih-zh zh-ah ah-n"},
{"ten","t-eh eh-eh eh-n"},
{"tenth","t-eh eh-eh eh-n n-th th-pau"},
{"the","dh-ah ah-ah"},
{"theater","th-iy iy-iy iy-ey ey-t t-er er-pau"},
{"third","pau-th th-er er-er er-d d-pau"},
{"thirteen","th-er er-er er-t t-iy iy-iy iy-n n-pau"},
{"thirteenth","th-er er-er er-t t-iy iy-iy iy-n n-th th-pau"},
{"thirtieth","th-er er-er er-t t-iy iy-eh eh-eh eh-th th-pau"},
{"thirty","th-er er-er er-d d-iy iy-iy iy-pau"},
{"thomas","t-aa aa-aa aa-m m-ah ah-s"},
{"thomases","t-aa aa-aa aa-m m-ah ah-s s-ih ih-z"},
{"three","th-r r-iy iy-iy"},
{"thursday","th-er er-er er-z z-d d-iy iy-pau"},
{"tiffany","t-ih ih-f ih-f f-ah ah-n n-iy iy-pau"},
{"tilda","t-ih ih-ih ih-l l-d d-ah"},
{"tim","t-ih ih-ih ih-m"},
{"time","t-ay ay-ay ay-m"},
{"timothy","t-ih ih-ih ih-m m-ah ah-th th-iy iy-pau"},
{"tims","t-ih ih-ih ih-m m-z"},
{"to","t-uw uw-uw"},
{"today","t-ah ah-d d-ey ey-ey"},
{"tom","t-aa aa-aa aa-m"},
{"toms","t-aa aa-aa aa-m m-z"},
{"travel","t-r r-ae ae-ae ae-v v-ah ah-l"},
{"trevor","t-r r-eh eh-eh eh-v v-er er-pau"},
{"trevors","t-r r-eh eh-eh eh-v v-er er-z z-pau pau-z"},
{"trip","t-r r-ih ih-ih ih-p p-p"},
{"tuesday","t-uw uw-uw uw-z z-d d-iy iy-pau"},
{"tunnel","t-ah ah-n n-ah ah-l"},
{"twelfth","t-w w-eh eh-eh eh-l l-f f-th th-pau pau-th"},
{"twelve","t-w w-eh eh-eh eh-l l-v"},
{"twentieth","t-w w-eh eh-eh eh-n n-t t-iy iy-eh eh-eh eh-th th-pau"},
{"twenty","t-w w-eh eh-eh eh-n n-t t-iy iy-pau"},
{"two","t-uw uw-uw uw-pau"},

//u-words
{"uncle","ah-ah ah-ng ng-k k-ah ah-l"},
{"unknown","ah-n n-n n-ow ow-ow ow-n n-n"},
{"upcoming","ah-p p-k k-ah ah-ah ah-m m-ih ih-ng"},
{"use","y-uw uw-uw uw-z z-pau"},
{"user","y-uw uw-uw uw-z z-er er-pau"},
//v-words
{"vacation","v-ey ey-k k-ey ey-ey ey-sh sh-ah ah-n"},
{"valentine","v-ae ae-ae ae-l l-ah ah-n n-t t-ay ay-ay ay-n"},
{"valentines","v-ae ae-ae ae-l l-ah ah-n n-t t-ay ay-ay ay-n n-z"},
{"valerie","v-ae ae-ae ae-l l-er er-iy iy-pau"},
{"vehicle","v-iy iy-iy iy-hh hh-ih ih-k k-ah ah-l"},
{"version","v-er er-er er-zh zh-ah ah-n"},
{"visit","v-ih ih-ih ih-z z-ih ih-t t-pau"},

//w-words
{"walk","w-w w-ao ao-ao ao-k k-k"},
{"web","w-eh eh-eh eh-b b-b"},
{"wedding","w-eh eh-eh eh-d d-ih ih-ng"},
{"wednesday","w-eh eh-eh eh-n n-z z-d d-iy iy-pau"}, //or iy-iy
{"wife","w-ay ay-ay ay-f"},
{"winnie","w-ih ih-ih ih-n n-iy iy-pau"},
{"winnifred","w-ih ih-ih ih-n n-ih ih-f f-r r-ih ih-d"},
{"winston","w-ih ih-ih ih-n n-s s-t t-ah ah-n"},
{"winter","w-ih ih-ih ih-n n-t t-er er-pau"},
{"work","w-uh uh-r r-k k-pau"},
{"world","w-er er-er er-l l-d"},

//x-words

//y-words
{"yacht","y-aa  aa-aa aa-t"},
{"year","y-ih ih-ih ih-r"},
{"yearly","y-ih ih-ih ih-r r-l l-iy iy-pau"},

//z-words
{"zero","z-iy iy-iy iy-r r-ow ow-pau"},
	
};

static int compare_keys(const void *va, const void *vb) {
  const pair_t *a = va, *b = vb;
  return strcmp(a->key, b->key);
}

char* get_value(char *key) {
  pair_t key_pair[1] = {{key}};
  pair_t *pair = bsearch(key_pair, table,
      sizeof table / sizeof table[0], sizeof table[0], compare_keys);  
  
  if (pair ==NULL) return ""; //word not found
  else   return pair->value;
}


GList* word_to_diphones(const char* word_str) {
	
	//g_print("word_to_diphone: word_str =%s\n",word_str);
	
	GList *diphone_list=NULL;	//{"pau","pau-pau"},
	//diphone_list =g_list_concat(diphone_list,"pau-pau");
	char* word = g_ascii_strdown(word_str, -1); //convert to lower case
    //g_print("word_to_diphones: word =%s\n",word);
    char* dp_str ="";
    dp_str=get_value(word); 
	char buf[256];	
	strcpy(buf, dp_str);
	char *tok_str =strtok(buf, " ");	//space delimiter
	while(tok_str != NULL) {
		//g_print("tok_str = %s\n",tok_str);		
		char *copy_str = strdup(tok_str); //duplicate
		diphone_list = g_list_append(diphone_list, copy_str);		
		tok_str =strtok(NULL, " ");	
	}		
	return diphone_list;
}	
