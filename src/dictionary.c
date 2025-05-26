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
//may 2025 -change dictionary to join words on a pause (pau)

//dictionary key value pair
typedef struct pair {
  char *key;
  char *value;
} pair_t;


// Key strings must be in strcmp() sorted order!
pair_t table[] = {


//A-words
//a 
{"a","pau-ey ey-ey ey-ey ey-pau"}, 
//account
{"accountant","pau-ah ah-k k-aa aa-uh uh-n n-t t-ah ah-n n-t t-pau"},
//activity
{"activity","pau-ae ae-k k-t t-ih ih-ih ih-v v-ah ah-t t-iy iy-pau"},
//adventure
{"adventure","pau ae ae-d d-v v-eh eh-n n-ch ch-uh uh-r r-pau"},
//afternoon
{"afternoon","pau-ae ae-ae ae-ae ae-f f-t t-er er-pau pau-er er-n n-uw uw-uw uw-n n-pau"},
//agatha
{"agatha","pau-ae ae-g g-ah ah-th th-ah ah-pau"},
//agent
{"agent","pau-eh eh-iy iy-jh jh-ah ah-n n-t t-pau"},
//agree
{"agree","pau-ah ah-g g-r r-iy iy-pau"},
//agreement
{"agreement","pau-ah ah-g g-r r-iy iy-m m-ah ah-n n-t t-pau"},
//airport
{"airport","pau-eh eh-eh eh-r r-p p-ao ao-ao ao-r r-t t-pau"},
//alan
{"alan","pau-ae ae-ae ae-l l-ah ah-n n-pau"}, 
//alans
{"alans","pau-ae ae-ae ae-l l-ah ah-n n-z z-pau"},
//alarm
{"alarm","pau-ah ah-l l-aa aa-r r-m m-pau"},
//alec
{"alec","pau-ae ae-ae ae-l l-ih ih-k k-pau"},
//alex
{"alex","pau-ae ae-ae ae-l l-ah ah-k k-s s-pau"},
//alexander
{"alexander","pau-ae ae-ae ae-l l-ah ah-g g-z z-ae ae-n n-d d-uh uh-r r-pau"},
//alexanders
{"alexanders","pau-ae ae-ae ae-l l-ih ih-g g-z z-ae ae-n n-d d-uh uh-r r-z z-pau"},
//alexs
{"alexs","pau-ae ae-ae ae-l l-ah ah-k k-s s-ih ih-z z-pau"},
//alf
{"alf","pau-ae ae-ae ae-l l-f f-pau"},
//alfred
{"alfred","pau-ae ae-ae ae-l l-f f-r r-ah ah-d d-pau"},
//alfreds
{"alfreds","pau-ae ae-ae ae-l l-f f-r r-ih ih-d d-z z-pau"},
//alice
{"alice","pau-ae ae-ae ae-l l-ih ih-s s-pau"},
//alices
{"alices","pau-ae ae-ae ae-l l-ih ih-s s-ah ah-z z-pau"},
//alison and allison
{"alison","pau-ae ae-ae ae-l l-ih ih-s s-ah ah-n n-pau"},
//alisons and allisons
{"alisons","pau-ae ae-ae ae-l l-ih ih-s s-ah ah-n n-z z-pau"},
//alister and allister
{"alister","pau-ae ae-ae ae-l l-ih ih-s s-t t-uh uh-r r-pau"},
//all
{"all","pau-al ao-l l-pau"},
//allotment
{"allotment","pau-ah ah-l l-aa aa-aa aa-t t-m m-ah ah-n n-t t-pau"},
//am
{"am","pau-ae ae-m m-pau"}, 
//amazon
{"amazon","pau-ae ae-ae ae-m m-ah ah-z z-aa aa-aa aa-n n-pau"},
//amber
{"amber","pau-ae ae-ae ae-m m-b b-er er-pau"},
//ambulance
{"ambulance","pau-ae ae-ae ae-m m-b b-y y-ah ah-l l-ah ah-n n-s s-pau"},
//amelia
{"amelia","pau-ah ah-m m-iy iy-iy iy-l l-y y-ah ah-pau"},
//amelias
{"amelias","pau-ah ah-m m-iy iy-iy iy-l l-y y-ah ah-z z-pau"},
//amm
{"amm","pau-ey ey-ey ey-ae ae-m m-m m-m m-pau"}, //A.M.
//amy
{"amy","pau-eh eh-iy iy-m m-iy iy-pau"},
//and
{"and","pau-ah ah-n n-d d-pau"},
//andora
{"andora","pau-ae ae-ae ae-n d-ao ao-ao ao-r r-ah ah-pau"},
//andoras
{"andoras","pau-ae ae-ae ae-n d-ao ao-ao ao-r r-ah ah-z z-pau"},
//andre
{"andre","pau-aa aa-aa aa-n n-d d-r r-ey ey-ey ey-pau"},
//andrea
{"andrea","pau-ae ae-ae ae-n n-d d-r r-iy iy-iy iy-ah ah-pau"},
//andreas
{"andreas","pau-ae ae-ae aa-n n-d d-r r-eh eh-iy iy-iy iy-ah ah-z z-pau"},
//andrew
{"andrew","pau-ae ae-ae ae-n n-d d-r r-uw uw-pau"},
//andrews
{"andrews","pau-ae ae-ae ae-n n-d d-r r-uw uw-uw uw-z z-pau"},
//andy
{"andy","pau-ae ae-ae ae-n n-d d-iy iy-pau"},
//andys
{"andys","pau-ae ae-ae ae-n n-d d-iy iy-pau pau-iy iy-z z-pau"},
//angela
{"angela","pau-ae ae-ae ae-n n-jh jh-ah ah-l l-ah ah-pau"},
//angelina
{"angelina","pau-ae ae-n n-jh jh-eh eh-l l-iy iy-n n-ah ah-pau"},
//animal
{"animal","pau-ae ae-n n-ah ah-m m-ah ah-l l-pau"},
//anna
{"anna","pau-ae ae-ae ae-n n-ah ah-pau"},
//annabel
{"annabel","pau-ae ae-ae ae-n n-ah ah-b b-eh eh-eh eh-l l-pau"},
//anne
{"anne","pau-ae ae-ae ae-n n-pau"},
//anniversary
//{"anniversary","ae-ae ae-n n-ah ah-v v-er er-er er-s s-er er-iy iy-pau"},
{"anniversary","pau-ae ae-ae ae-n n-ah ah-v v-er er-er er-s s-er er-iy iy-pau"},
//anthony
{"anthony","pau-ae ae-ae ae-n n-th th-ao ao-n n-iy iy-iy iy-pau"},
//antifreeze  
{"antifreeze","pau-ae ae-ae ae-n n-t t-iy iy-f f-r r-iy iy-iy iy-z z-pau"},
//appoint
{"appoint","pau-ah ah-p p-ao ao-iy iy-n n-t t-pau"},
//appointment
{"appointment","pau-ah ah-p p-oy oy-oy oy-n n-t t-m m-ah ah-n n-t t-pau"},
//april
{"april","pau-ey ey-ey ey-p p-r r-ah ah-l l-pau"},
//archery
{"archery","pau-aa aa-r r-ch ch-uh uh-r r-iy iy-pau"},
//archie
{"archie","pau-aa aa-r r-ch ch-iy iy-pau"},
//art
{"art","pau-aa aa-aa aa-aa aa-r r-t t-pau"},
//arthur
{"arthur","pau-aa aa-r r-th th-uh uh-r r-pau"},
//assessment
{"assessment","pau-ah ah-s s-eh eh-eh eh-s s-m m-ah ah-pau pau-ah ah-n n-t t-pau"},
//attack
{"attack","pau-ah ah-t t-ae ae-k k-pau"},
//aubrey
{"aubrey","pau-ao ao-ao ao-b b-r r-iy iy-pau"},
//audrey
{"audrey","pau-ao ao-ao ao-d d-r r-iy iy-pau"},
//{"audreys","ao-ao ao-uh uh-d d-r r-iy iy-z"},
//august
{"august","pau-aa aa-aa aa-g g-ah ah-s s-t t-pau"},
//aunt
{"aunt","pau-ae ae-ae ae-n n-t t-pau"},
//auntie and aunty
{"auntie","pau-ae ae-ae ae-n n-t t-iy iy-pau"},
//aunts
{"aunts","pau-ae ae-ae ae-n n-t t-s s-pau"},
//autumn
{"autumn","pau-ao ao-t t-ah ah-m m-pau"},

 
//B-words
//baby
{"baby","pau-b b-eh eh-iy iy-b b-iy iy-pau"},
//badminton 
{"badminton","pau-b b-ae ae-d d-m m-ih ih-n n-t t-aa aa-n n-pau"},
//bakery
{"bakery","pau-b b-eh eh-iy iy-k k-uh uh-r r-iy iy-pau"},
//ball
{"ball","pau-b b-ao ao-l l-pau"},
//band
{"band","pau-b b-ae ae-n n-d d-pau"},
//bank
{"bank","pau-b b-ae ae-ae ae-ng ng-k k-pau"},
//banking
{"banking","pau-b b-ae ae-ae ae-ng ng-k k-ih ih-ng ng-pau"},
//barber
{"barber","pau-b b-aa aa-aa aa-r r-b b-er er-pau"},
//barbars
{"barbers","pau-b b-aa aa-aa aa-r r-b b-er er-z z-pau"},
//be
{"be","pau-b b-iy iy-pau"},
//bed
{"bed","pau-b b-eh eh-d d-pau"},
//begins
{"begins","pau-b b-ih ih-g g-ih ih-n n-z z-pau"},
//beth
{"beth","pau-b b-eh eh-eh eh-th th-pau"},
//bethany
{"bethany","pau-b b-eh eh-eh eh-th th-ah ah-n n-iy iy-pau"},
//betsy
{"betsy","pau-b b-eh eh-eh eh-t t-s s-iy iy-pau"},
//betsys
{"betsys","pau-b b-eh eh-eh eh-t t-s s-iy iy-z z-pau"},
//betty
{"betty","pau-b b-eh eh-eh eh-t t-iy iy-pau"},
//bettys
{"betty","pau-b b-eh eh-eh eh-t t-iy iy-z z-pau"},
//big
//bike
{"bike","pau-b b-ay ay-ay ay-k k-pau"},
//billy
{"billy","pau-b b-ih ih-ih ih-l l-iy iy-pau"},
//bin
{"bin","pau-b b-ih ih-ih ih-n n-pau"},
//bird
{"bird","pau-b b-uh uh-r r-d d-pau"},
//birth
{"birth","pau-b b-uh uh-r r-th th-pau"},
//birthday
//{"birthday","pau-b b-er er-er er-th th-d d-ey ey-pau"},
{"birthday","pau-b b-er er-er er-th th-d d-ey ey-ey ey-pau"},
//boat
{"boat","pau-b b-ao ao-uh uh-t t-pau"},
//book
{"book","pau-b b-uh uh-k k-pau"},
//bowls
{"bowls","pau-b b-ao ao-uh uh-l l-z z-pau"},
//box
{"box","pau-b b-aa aa-k k-s s-pau"},
//boxing
{"boxing","pau-b b-aa aa-aa aa-k k-s s-ih ih-ng ng-pau"},
//break
{"break","pau-b b-r r-eh eh-iy iy-k k-pau"},
//breakfast
{"breakfast","pau-b b--r r-eh eh-eh eh-k k-f f-ah ah-s s-t t-pau"},
//british
{"british","pau-b b-r r-ih ih-t t-ih ih-sh sh-pau"},
//brother
{"brother","pau-b b-r r-ah ah-dh dh-uh uh-r r-pau"},
//brothers
{"brothers","pau-b b-r r-ah ah-dh dh-uh uh-r r-z z-pau"},
//brunch
{"brunch","pau-b b-r r-r r-ah ah-n n-n n-ch ch-ch ch-pau"},
//bus
{"bus","pau-b b-ah ah-ah ah-s s-s s-pau"},
//business
{"business","b-ih ih-z z-n n-ah ah-s s-pau"},
//buy
{"buy","pau-b b-aa aa-iy iy-pau"},
//by
{"by","pau-b b-aa aa-iy iy-pau"},
//bye
{"bye","pau-b b-aa aa-iy iy-pau"},

//C-words
//cabbie 
{"cabbie","pau-k k-ae ae-ae ae-b b-b b-iy iy-pau"},
//cafe
{"cafe","pau-k k-ah ah-f f-ey ey-ey"},
//calendar
{"calendar","pau-k k-ae ae-ae ae-l l-ah ah-n n-d d-er er-pau"},
//call
{"call","pau-k k-ao ao-l l-pau"},
//camp
{"camp","pau-k k-ae ae-m m-p p-pau"},
//camping
{"campsite","pau-k k-ae ae-m m-p p-s s-aa aa-iy iy-t t-s s-pau"},
//car
{"car","pau-k k-aa aa-aa aa-r r-pau"},
//card
{"card","pau-k k-aa aa-r r-d d-pau"},
//care
{"care","pau-k k-eh eh-r r-pau"},
//carol
{"carol","pau-k k-ae ae-r r-ah ah-l l-pau"},
//caroline
{"caroline","pau-k k-eh eh-r r-ah ah-l l-aa aa-iy iy-n n-pau"},
{"carolines","pau-k k-eh eh-r r-ah ah-l l-aa aa-iy iy-n n-z z-pau"},
//cat
{"cat","pau-k k-ae ae-t t-pau"},
//cath
{"cath","pau-k k-ae ae-ae ae-th th-th th-pau"},
//catherine and katherine
{"catherine","pau-k k-ae ae-ae ae-th th-er er-ah ah-n n-pau"},
{"catherines","pau-k k-ae ae-ae ae-th th-er er-ah ah-n n-z z-pau"},
//certificate
{"certificate","pau-s s-uh uh-r r-t t-ih ih-f f-ih ih-k k-ah ah-t t-pau"},
//charles
{"charles","pau-ch ch-aa aa-aa aa-r r-l l-z z-pau"},
//charlotte
{"charlotte","pau-sh sh-aa  aa-aa aa-r r-l l-ah ah-t t-pau"},
//chauffeur
{"chauffeur","pau-sh sh-ao ao-uh uh-f f-f f-uh uh-r r-pau"},
//check
{"check","pau-ch ch-eh eh-k k-pau"},
//chemist
{"chemist","pau-k k-eh eh-m m-ih ih-s s-t t-pau"},
//child
{"child","pau-ch ch-aa aa-iy iy-l l-d d-pau"},
//children
{"children","pau-ch ch-ih ih-l l-d d-r r-ah ah-n n-pau"},
//chips
{"chips","pau-ch ch-ih ih-ih ih-p p-s s-pau"}, //dog name - walk chips
//choir
{"choir","pau-k k-w w-aa aa-iy iy-uh uh-r r-pau"},
//chore
{"chore","pau-ch ch-ao ao-ao ao-r r-pau"},
//christie
{"christie","pau-k k-r r-ih ih-s s-t t-iy iy-pau"},
//christina
{"christina","pau-k k-r r-ih ih-s s-t t-iy iy-n n-ah ah-pau"},
//christine
{"christine","pau-k k-r r-ih ih-s s-t t-iy iy-n n-pau"},
//christmas
{"christmas","pau-k k-r r-ih ih-ih ih-s s-m m-ah ah-s s-pau"},
//church
{"church","pau-ch ch-er er-er er-ch ch-pau"},
//cinema
{"cinema","s-ih ih-ih ih-n n-ah ah-m m-ah ah-pau"},
//circle
{"circle","pau-s s-uh uh-r r-k k-ah ah-l l-pau"},
//circus
{"circus","pau-s s-uh uh-r r-k k-ah ah-s s-pau"},
//city
{"city","pau-s s-ih ih-t t-iy iy-pau"},
//claire
{"claire","pau-k k-l l-eh eh-eh eh-r r-pau"},
//clara
{"clara","pau-k k-l l-ae ae-ae ae-r r-ah ah-pau"},  //aunt clara
//clarence
{"clarence","pau-k k-l l-eh eh-eh eh-r r-ah ah-n n-s s-pau"},
//clarissa
{"clarissa","pau-k k-l l-er er-ih ih-ih ih-s s-ah ah-pau"},
//class
{"class","pau-k k-l l-ae ae-s s-pau"},
//claude
{"claude","pau-k k-l l-ao ao-ao ao-d d-pau"},
//clean
{"clean","pau-k k-l l-iy iy-n n-pau"},
//cleaner
{"cleaner","pau-k k-l l-iy iy-n n-uh uh-r r-pau"},
//climbing
{"climbing","pau-k k-l l-aa aa-iy iy-m m-ih ih-ng ng-pau"},
//clinic
{"clinic","pau-k k-l l-ih ih-ih ih-n n-ih ih-k k-pau"},
//clock
{"clock","pau-k k-l l-aa aa-k k-pau"},
//clocks
{"clocks","pau-k k-l l-aa aa-k k-s s-pau"},
//close
{"close","pau-k k-l l-ao ao-uh uh-s s-pau"},
//closed
{"closed","pau-k k-l l-ao ao-uh uh-z z-d d-pau"},
//club
{"club","pau-k k-l l-ah ah-b b-pau"},
//coach
{"coach","pau-k k-ow ow-ow ow-ch ch-ch ch-pau"},
//coast
{"coast","pau-k k-ao ao-uh uh-s s-t t-pau"},
//cobbler 
{"cobbler","pau-k k-aa aa-aa aa-b b-b b--l l-er er-pau"},
//code
{"code","pau-k k-ao ao-uh uh-d d-pau"},
//coffee
{"coffee","pau-k k-aa aa-f f-iy iy-pau"},
//collection
{"collection","pau-k k-ah ah-l l-eh eh-k k-sh sh-ah ah-n n-pau"},
//college
{"college","pau-k k-aa aa-l l-ih ih-jh jh-pau"},
//coming
{"coming","pau-k k-ah ah-ah ah-m m-ih ih-ng ng-pau"},
//computer
{"computer","pau-k k-ah ah-m m-p p-y y-uw uw-t t-uh uh-r r-pau"},
//concert
{"concert","pau-k k-aa aa-n n-s s-uh uh-r r-t t-pau"},
//contact
{"contact","pau-k k-aa aa-n n-t t-ae ae-k k-t t-pau"},
//cottage
{"cottage","pau-k k-aa  aa-aa aa-t t-ah ah-jh jh-pau"},
//court
{"court","pau-k k-ao ao-r r-t t-pau"},
//cousin
{"cousin","pau-k k-ah ah-z z-ah ah-n n-pau"},

//crispin
{"crispin","pau-k k-r  r-ih ih-ih ih-s s-p p-ih ih-n n-n n-pau"},
//crispins (saint day)
{"crispins","pau-k k-r  r-ih ih-ih ih-s s-p p-ih ih-ih ih-n n-n n-z z-pau"},  //saint day
//crook
{"crook","pau-k k-r r-uh uh-k k-pau"},
//crooks
{"crooks","pau-k k-r r-uh uh-k k-s s-pau"},
//cyber
{"cyber","pau-s s-ay ay-ay ay-b b-er er-pau"},
//cycle
{"cycle","pau-s s-aa aa-iy iy-k k-ah ah-l l-pau"},

//D-words
//dad
{"dad","pau-d d-ae ae-ae ae-d d-pau"},
//dads
{"dads","pau-d d-ae ae-ae ae-d d-z z-pau"},
//daisy
{"daisy","pau-d d-ey ey-ey ey-z z-iy iy-pau"},
//dan
{"dan","pau-d d-ae ae-n n-pau"},
//dance
{"dance","pau-d d-ae ae-n n-s s-pau"},
//daniel
{"daniel","pau-d d-ae ae-ae ae-n n-y y-ah ah-l l-pau"},
//danielle
{"danielle","pau-d d-ae ae-ae ae-n n-iy iy-eh eh-eh eh-l l-pau"},
{"danielle","pau-d d-ae ae-ae ae-n n-iy iy-eh eh-eh eh-l l-z z-pau"},
//danny
{"danny","pau-d d-ae ae-ae ae-n n-iy iy-pau"},
//date
{"date","pau-d d-ey ey-ey ey-t t-pau"},
//dates
{"dates","pau-d d-ey ey-ey ey-t t-s s-pau"},
//daughter
{"daughter","pau-d d-ao ao-ao ao-t t-er er-pau"},
//daughters
{"daughter","pau-d d-ao ao-ao ao-t t-er er-z z-pau"},
//dave
{"dave","pau-d d-ey ey-ey ey-v v-pau"},
//david
{"david","pau-d d-ey ey-ey ey-v v-ih ih-d d-pau"},
//davids
{"davids","pau-d d-ey ey-ey ey-v v-ih ih-d d-z z-pau"},
//day
{"day","pau-d d-d d-ey ey-ey ey-pau"},
//days
{"days","pau-d d-eh eh-iy iy-z z-pau"},
//dead
{"dead","pau-d d-eh eh-d d-pau"},
//deadline
{"deadline","pau-d d-eh eh-eh eh-d d-l l-ay ay-ay ay-n n-pau"},
//dealer
{"dealer","pau-d d-iy iy-l l-uh uh-r r-pau"},
//death
{"death","pau-d d-eh eh-th th-pau"},
//debbie or debby
{"debbie","pau-d d-eh eh-eh eh-b b-iy iy-pau"},
//deborah
{"deborah","pau-d d-eh eh-eh eh-b b-er er-ah ah-pau"},
//debs
{"debs","pau-d d-eh eh-b b-z z-pau"},
//december
{"december","pau-d d-ih ih-s s-eh eh-eh eh-m m-b b-er er-pau"},
//decorate
{"decorate","pau-d d-eh eh-k k-uh uh-r r-eh eh-iy iy-t t-pau"},
//decorating
{"decorating","pau-d d-eh eh-k k-uh uh-r r-eh eh-iy iy-t t-ih ih-ng ng-pau"},
//delivery
{"delivery","pau-d d-ih ih-l l-ih ih-ih ih-v v-er er-iy iy-pau"},
//dentist
{"dentist","pau-d d-eh eh-eh eh-n n-t t-ah ah-s s-t t-pau"},
//development
{"development","pau-d d-ih ih-v v-eh eh-l l-ah ah-p p-m m-ah ah-n n-t t-pau"},
//diana
{"diana","pau-d d-aa aa-iy iy-ae ae-n n-ah ah-pau"},
//diary
{"diary","pau-d d-aa aa-iy iy-uh uh-r r-iy iy-pau"},
//dinner
{"dinner","pau-d d-ih ih-ih ih-n n-er er-pau"},
//{"diphone","d-ih ih-ih ih-f f-ow ow-ow ow-n n-pau"}, //bad pronouciation
//do
{"do","pau-d d-uw uw-pau"},
//doctor
{"doctor","pau-d d-aa aa-aa aa-k k-t t-er er-pau"},
//doctors
{"doctors","pau-d d-aa aa-aa aa-k k-t t-er r-z z-pau"},
//dog
{"dog","pau-d d-ao ao-g g-pau"},
//don
{"don","pau-d d-aa aa-aa aa-n n-pau"},
//donald
{"donald","pau-d d-aa aa-aa aa-n n-ah ah-l l-d d-pau"},
//donalds
{"donalds","pau-d d-aa aa-aa aa-n n-ah ah-l l-d d-z z-pau"},
//donkey
{"donkey","pau-d d-aa aa-ng ng-k k-iy iy-pau"},
//dons
{"dons","pau-d d-aa aa-aa aa-n n-z z-pau"},
//dora
{"dora","pau-d d-ao ao-ao ao-r r-ah ah-pau"},
//down
{"down","pau-d d-aa aa-uh uh-n n-pau"},
//driver
{"driver","pau-d d-r r-ay ay-ay ay-v v-er er-pau"},
//dustbin
{"dustbin","pau-d d-ah ah-ah ah-s s-t t-b b-ih ih-n n-pau"},

//E-words
//ear
{"ear","pau-iy iy-iy iy-r r-pau"},
//early
{"early","pau-uh uh-r r-l l-iy iy-pau"},
//east
{"east","pau-iy iy-s s-t t-pau"},
//easter
{"easter","pau-iy iy-iy iy-s s-t t-er er-pau"},
//education
{"education","pau-eh eh-jh jh-ah ah-k k-eh eh-iy iy-sh sh-ah ah-n n-pau"},
//eight
{"eight","pau-ey ey-ey ey-t t-pau"},
//eighteen
{"eighteen","pau-ey ey-ey ey-t t-iy iy-iy iy-n n-pau"},
//eighteenth
{"eighteenth","pau-ey ey-ey ey-t t-iy iy-iy iy-n n-th th-pau"},
//eighth
{"eighth","pau-eh eh-ey ey-ey ey-t t-th th-pau"},
//eightieth (birthday)
{"eightieth","pau-eh ey-ey ey-t t-iy iy-ih ih-th th-pau"},
//eighty
{"eighty","pau-eh eh-iy iy-t t-iy iy-pau"},
//electric
{"electric","pau-ih ih-l l-eh eh-k k-t t-r r-ih ih-k k-pau"},
//electrician
{"electrician","pau-ih ih-ih ih-l l-eh eh-k k-t t-r r-ih ih-ih ih-sh sh-ah ah-n n-pau"},
//electricity
{"electricity","pau-ih ih-l l-eh eh-k k-t t-r r-ih ih-s s-ah ah-t t-iy iy-pau"},
//eleven
{"eleven","pau-ih ih-l l-eh eh-eh eh-v v-ah ah-n n-pau"},
//eleventh
{"eleventh","pau-ih ih-l l-eh eh-eh eh-v v-ah ah-n n-th th-pau"},
//elisha
{"elisha","pau-eh eh-eh eh-l l-ih ih-sh sh-ah ah-pau"},
//eliza
{"eliza","pau-ih ih-l l-ay ay-ay ay-z z-ah ah-pau"},
//elizabeth
{"elizabeth","pau-ih ih-l l-ih ih-ih ih-z z-ah ah-b b-ah ah-th th-pau"},
//elizabeths
{"elizabeths","pau-ih ih-l l-ih ih-ih ih-z z-ah ah-b b-ah ah-th th-s s-pau"},
//elizas
{"elizas","pau-ih ih-l l-ay ay-ay ay-z z-ah ah-z z-pau"},
//ella
{"ella","pau-eh eh-l l-l l-ah ah-pau"},
//elliot or elliott
{"elliot","pau-eh eh-eh eh-l l-iy iy-ah ah-t t-pau"},
//{"elliott","eh-eh eh-l l-iy iy-ah ah-t"},
//elton
{"elton","pau-eh eh-l l-t t-ah ah-n n-pau"},
//emma
{"emma","pau-eh eh-eh eh-m m-ah ah-pau"},
//end
{"end","pau-eh eh-n n-d d-pau"},
//ends
{"ends","pau-eh eh-n n-d d-z z-pau"},
//engage
{"engage","pau-eh eh-n n-g g-eh eh-iy iy-jh jh-pau"},
{"engagement","pau-eh eh-n n-g g-eh eh-iy iy-jh jh-m m-ah ah-n n-t t-pau"},
//evan
{"evan","pau-eh eh-eh eh-v v-ah ah-n n-pau"},
//evening
{"evening","pau-iy iy-iy iy-v v-n n-ih ih-ng ng-pau"},
//event
{"event","pau-ih ih-v v-eh eh-eh eh-n n-t t-pau"},
//events
{"events","pau-ih ih-v v-eh eh-n n-t t-z z-pau"},
//eye
{"eye","pau-aa aa-iy iy-pau"},

//F-words
//family
{"family","pau-f f-ae ae-ae ae-m m-ah ah-l l-iy iy-pau"},
//farm
{"farm","pau-f f-aa aa-aa aa-r r-m m-pau"},
//father
{"father","pau-f f-aa aa-aa aa-dh dh-er er-pau"},
//fathers
//{"fathers","pau-f f-aa aa-aa aa-dh dh-er er-pau pau-er er-z z-pau"},
{"fathers","pau-f f-aa aa-aa aa-dh dh-er er-er er-z z-z z-pau"},
//fawkes
{"fawkes","pau-f f-ao ao-ao ao-k k-s s-pau"},
//fear
{"fear","pau-f f-ih ih-r r-pau"},
//february
//{"february","f-eh eh-eh eh-b b-y y-ah ah-w w-eh eh-eh eh-r r-iy iy-pau"},
{"february","pau-f f-eh eh-eh eh-b b--y y-ah ah-w w-eh eh-eh eh-r r-iy iy-pau"},
//feed
{"feed","pau-f f-iy iy-d d-pau"},
//festival
{"festival","pau-f f-eh eh-s s-t t-ah ah-v v-ah ah-l l-pau"},
//festive
{"festive","pau-f f-eh eh-s s-t t-ih ih-v v-pau"},
//fifteen
{"fifteen","pau-f f-ih ih-ih ih-f f-t t-iy iy-iy iy-n n-pau"},
//fifteenth
{"fifteenth","pau-f f-ih ih-f f-t t-iy iy-iy iy-n n-th th-pau"},
//fifth
{"fifth","pau-f f-ih ih-ih ih-f f-th th-pau"},
//fifty
{"fifty","pau-f f-ih ih-ih ih-f f-t t-iy iy-pau"},
//film
{"film","pau-f f-ih ih-ih ih-l l-m m-pau"},
//fiona
{"fiona","pau-f f-iy iy-ow ow-ow ow-n n-ah ah-pau"},
//fire
{"fire","pau-f f-aa aa-iy iy-uh uh-r r-pau"},
//fireworks
{"fireworks","pau-f f-aa aa-iy iy-r r-w w-uh uh-r r-k k-s s-pau"},
//first
{"first","pau-f f-er er-er er-s s-t t-pau pau-t"},
//fish
{"fish","pau-f f-ih ih-ih ih-sh sh-pau"},
//fishing
{"fishing","pau-f f-ih ih-sh sh-ih ih-ng ng-pau"},
//five
{"five","pau-f f-ay ay-ay ay-v v-pau"},
//fix
{"fix","pau-f f-ih ih-k k-s s-pau"},
//food
{"food","pau-f f-uw uw-d d-pau"},
//fools april
{"fools","pau-f f-uw uw-l l-z z-pau"},
//football
{"football","pau-f f-uh uh-t t-b b-ao ao-l l-pau"},
//forty
{"forty","pau-f f-ao ao-ao ao-r r-t t-iy iy-pau"},
//forward  -clocks forward
{"forward","pau-f f-ao ao-r r-w w-uh uh-r r-d d-pau"},
//four
{"four","pau-f f-ao ao-ao ao-r r-pau"},
//fourteen
{"fourteen","pau-f f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-pau"},
//fourteenth
//{"fourteenth","pau-f f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-th th-pau pau-th th-pau"},
{"fourteenth","pau-f f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-th th-th th-pau"},
//fourth
{"fourth","pau-f f-ao ao-ao ao-r r-th th-pau"},
//frances
{"frances","pau-f f-r r-ae ae-ae ae-n n-s s-ih ih-s s-pau"},
//francesca
{"francesca","pau-f f-r r-ae ae-n n-ch ch-eh eh-eh eh-s s-k k-ah ah-pau"},
//francis
{"francis","pau-f f-r r-ae ae-ae ae-n n-s s-ah ah-s s-pau"},
//frank
{"frank","pau-f f-r r-ae ae-ae ae-ng ng-k k-pau"},
//frankenstein
{"frankenstein","pau-f f-r r-ae ae-ng ng-k k-ah ah-n n-s s-t t-aa aa-iy iy-n n-pau"},
//fred
{"fred","pau-f f-f f-r r-eh eh-eh eh-d d-pau"},
//freddie and freddy
{"freddie","pau-f f-r r-eh eh-eh eh-d d-iy iy-pau"},
//{"freddy","f-r r-eh eh-eh eh-d d-iy iy-pau"},
//frederic
{"frederic","pau-f f-r r-eh eh-d d-r r-ih ih-k k-pau"},
//frederick
{"frederick","pau-f f-r r-eh eh-eh eh-d d-er er-ih ih-k k-pau"},
//freds
{"freds","pau-f f-r r-eh eh-eh eh-d d-z z-pau"},
//freeze (anti)
{"freeze","pau-f f-r r-iy iy-z z-pau"},
//{"freezer","f-r r-iy iy-z z-uh uh-r"},
//freya
{"freya","pau-f f-r r-eh eh-iy iy-ah ah-pau"},
//friday
{"friday","pau-f f-r r-ay ay-ay ay-d d-iy iy-pau"},
//friend
{"friend","pau-f f-r r-eh eh-eh eh-n n-d d-pau"},
//frost
{"frost","pau-f f-r r-ao ao-s s-t t-pau"},
//funeral
{"funeral","pau-f f-y y-uw uw-uw uw-n n-er er-ah ah-l l-pau"},

//G-words

//gale
{"gale","pau-g g-ey ey-ey ey-l l-pau"},
{"gales","pau-g g-ey ey-ey ey-l l-z z-pau"},
//gallery
{"gallery","pau-g g-ae ae-ae ae-l l-er er-iy iy-pau"},
//game
{"game","pau-g g-eh eh-iy iy-m m-pau"},
//garage
{"garage","pau-g g-uh uh-r r-aa aa-zh zh-pau"},
//garbage 
{"garbage","pau-g g-aa aa-aa aa-r r-b b-ih ih-jh jh-pau"},
//garden
{"garden","pau-g g-aa aa-r r-d d-ah ah-n n-pau"},
//gas
{"gas","pau-g g-ae ae-ae ae-s s-s s-pau"},
//gate
{"gate","pau-g g-eh eh-iy iy-t t-pau"},
//geoff
{"geoff","pau-jh jh-eh eh-eh eh-f f-pau"},
//geoffrey
{"geoffrey","pau-jh jh-eh eh-eh eh-f f-r r-iy iy-pau"},
{"geoffreys","pau-jh jh-eh eh-eh eh-f f-r r-iy iy-z z-pau"},
//geoffs
{"geoffs","pau-jh jh-eh eh-eh eh-f f-z z-pau"},
//george
{"george","pau-jh jh-ao ao-ao ao-r r-jh jh-pau"},
//georges  saint day
{"georges","pau-jh jh-ao ao-ao ao-r r-jh jh-ah ah-z z-pau"},
//georgina
{"georgina","pau-jh jh-ao ao-ao ao-r r-jh jh-iy iy-n n-ah ah-pau"},
//glasses
{"glasses","pau-g g-l l-ae ae-ae ae-s s-ah ah-z z-pau"},
//go
{"go","pau-g g-ao ao-uh uh-pau"},
//golf
{"golf","pau-g g-aa aa-l l-f f-pau"},
//good
{"good","pau-g g-uh uh-d d-pau"},
//grand
{"grand","pau-g g-r r-ae ae-n n-d d-pau"},
{"grandchild","pau-g g-r r-ae ae-n n-d d-ch ch-aa aa-iy iy-l l-d d-pau"},
{"grandchildren","pau-g g-r r-ae ae-n n-ch ch-ih ih-l l-d d-r r-ah ah-n n-pau"},
//grandad
{"grandad","pau-g g-r r-ae ae-ae ae-n n-d d-ae ae-ae ae-d d-pau"},
{"granddaughter","pau-g g-r r-ae ae-n n-d d-ao ao-t t-uh uh-r r-pau"},
{"grandfather","pau-g g-r r-ae ae-n n-d d-f f-aa aa-dh dh-uh uh-r r-pau"},
{"grandma","pau-g g-r r-ae ae-m m-aa aa-pau"},
{"grandmother","pau-g g-r r-ae ae-n n-d d-m m-ah ah-dh dh-uh uh-r r-pau"},
{"grandpa","pau-g g-r r-ae ae-n n-d d-p p-aa aa-pau"},
{"grandparent","pau-g g-r r-ae ae-n n-d d-p p-eh eh-r r-ah ah-n n-t t-pau"},
{"grandparents","pau-g g-r r-ae ae-n n-d d-p p-eh eh-r r-ah ah-n n-t t-s s-pau"},
{"grandson","pau-g g-r r-ae ae-n n-d d-s s-ah ah-n n-pau"},
//granny and grannie
{"granny","pau-g g-r r-ae ae-ae ae-n n-iy iy-pau"},
//guy (fawkes day)
{"guy","pau-g g-ay ay-ay ay-ay ay-pau"},

//H-words
//hairdresser
{"hairdresser","pau-hh hh-eh eh-eh eh-r r-d d-r r-eh eh-eh eh-s s-er er-pau"},
//hairdressing
{"hairdressing","pau-hh hh-eh eh-eh eh-r r-d d-r r-eh eh-eh eh-s s-ih ih-ng ng-pau"},
//halloween
{"halloween","pau-hh hh-ae ae-ae ae-l l-ah ah-w w-iy iy-iy iy-n n-pau"},
//hannah or hanna
//{"hanna","hh-ae ae-ae ae-n n-ah"},
{"hannah","pau-hh hh-ae ae-ae ae-n n-ah ah-pau"},
{"hannahs","pau-hh hh-ae ae-ae ae-n n-ah ah-z z-pau"},
//happy (birthday)
{"happy","pau-hh hh-ae ae-ae ae-p p-iy iy-pau"},
//harold
{"harold","pau-hh hh-eh eh-eh eh-r r-ah ah-d d-pau"},
{"harolds","pau-hh hh-eh eh-eh eh-r r-ah ah-d d-z z-pau"},
//harry
{"harry","pau-hh hh-eh eh-eh eh-r r-iy iy-pau"},
//have
{"have","pau-hh hh-ae ae-v v-pau"},
//head
{"head","pau-hh hh-eh eh-d d-pau"},
//headache
{"headache","pau-hh hh-eh eh-d d-eh eh-iy iy-k k-pau"},
//health
{"health","pau-hh hh-eh eh-eh eh-l l-th th-pau"},
//hear
{"hear","pau-hh hh-iy iy-r r-pau"},
//heating
{"heating","pau-hh hh-iy iy-iy iy-t t-ih ih-ng ng-pau"},
//hector
{"hector","hh-eh eh-eh eh-k k-t t-er er-pau"},
//helen
{"helen","pau-hh hh-eh eh-eh eh-l l-ah ah-n n-pau"},
//hello
{"hello","pau-hh hh-ah ah-l l-ow ow-ow ow-pau"},
//help
{"help","pau-hh hh-eh eh-eh eh-l l-p p-pau"},
//hen
{"hen","pau-hh hh-eh eh-n n-pau"},
//henry
{"henry","pau-hh hh-eh eh-n n-r r-iy iy-pau"},
//herbert
{"herbert","pau-hh hh-er er-er er-b b-t t-pau"},
//{"herbert","hh-er er-er er-b b-t t-s"},
//high
{"high","pau-hh hh-aa aa-iy iy-pau"},
//hobby
{"hobby","pau-hh hh-aa aa-b b-iy iy-pau"},
//hockey
{"hockey","pau-hh hh-aa aa-aa aa-k kiy iy-pau"},
//holiday
{"holiday","pau-hh hh-aa aa-aa aa-l l-ah ah-d d-ey ey-ey ey-pau"},
//home
{"home","pau-hh hh-ow ow-ow ow-m m-pau"},
//honor
{"honor","pau-hh aa-n n-uh uh-r r-pau"},
//hospital
{"hospital","pau-hh hh-aa aa-aa aa-s s-p p-ih ih-ih ih-t t-ah ah-l l-pau"},
//hotel
{"hotel","pau-hh hh-ow ow-t t-eh eh-eh eh-l l-pau"},
//hour
{"hour","pau-aw aw-aw aw-r r-pau"},
//hours
{"hours","pau-aw aw-aw aw-r r-z z-pau"},
//house
{"house","pau-hh hh-hh hh-aw aw-aw aw-s s-s s-pau"},
//humanoid
{"humanoid","pau-hh hh-y y-uw uw-uw uw-m m-ah ah-n n-oy oy-oy oy-d d-pau"},
//humphrey
{"humphrey","pau-hh hh-ah ah-ah ah-m m-f f-r r-iy iy-pau"},
//hundred
{"hundred","pau-hh hh-ah ah-n n-d d-r r-ah ah-d d-pau"},
//hundredth
{"hundredth","pau-hh hh-ah ah-n n-d d-r r-ah ah-d d-th th-pau"},
//husband
{"husband","pau-hh hh-ah  ah-ah ah-z z-b b-ah ah-n n-d d-pau"},
//husbands
{"husbands","pau-hh hh-ah  ah-ah ah-z z-b b-ah ah-n n-d d-z z-pau"},

//I-words
//i
{"i","pau-ay ay-ay ay-pau"},
//ian
{"ian","pau-iy iy-iy iy-ah ah-n n-pau"},
//in
{"in","pau-ih ih-n n-pau"},
//industry
{"industry","pau-ih ih-n n-d d-ah ah-s s-t t-r r-iy iy-pau"},
//information
{"information","pau-ih ih-n n-f f-uh uh-r r-m m-eh eh-iy iy-sh sh-ah ah-n n-pau"},
//inn
{"inn","pau-ih ih-ih ih-ih ih-n n-pau"},
//insurance
{"insurance","pau-ih ih-n n-sh sh-uh uh-r r-ah ah-n n-s s-pau"},
//investment
{"investment","pau-ih ih-n n-v v-eh eh-s s-t t-m m-ah ah-n n-t t-pau"},
//invoice
{"invoice","pau-ih ih-n n-v v-ao ao-iy iy-s s-pau"},
//invoke
{"invoke","pau-ih ih-n n-v v-ao ao-uh uh-k k-pau"},
//irene
{"irene","pau-ay ay-r r-iy iy-iy iy-n n-pau"},
//is
{"is","pau-ih ih-z z-z z-pau"},
//isaac
{"isaac","pau-ih ih-ih ih-s s-ah ah-k k-pau"},
//isaacs
{"isaacs","pau-ih ih-ih ih-s s-ah ah-k k-s s-pau"},
//isabel or isabelle
{"isabel","pau-ih ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-pau"},
//isabella
{"isabella","pau-ih ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-ah ah-pau"},
//issabellas
{"isabellas","pau-ih ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-ah ah-z z-pau"},
//island
{"island","pau-aa aa-iy iy-l l-ah ah-n n-d d-pau"},
//ivan
{"ivan","pau-ay ay-ay ay-v v-ah ah-n n-pau"},
//ivans
{"ivans","pau-ay ay-ay ay-v v-ah ah-n n-z z-pau"},
//ivy
{"ivy","pau-ay ay-ay ay-v v-iy iy-pau"},

//J-words
//jack
{"jack","pau-jh jh-ae ae-ae ae-k k-pau"},
//jackie or jacky
{"jackie","pau-jh jh-ae ae-ae ae-k k-iy iy-pau"},
//{"jacky","jh-ae ae-ae ae-k k-iy"},
//jacks
{"jacks","pau-jh jh-ae ae-ae ae-k k-s s-pau"},
//jacob
{"jacob","pau-jh jh-eh ey-ey ey-k k-ah ah-b b-pau"},
//jacobs
{"jacobs","pau-jh jh-eh ey-ey ey-k k-ah ah-b b-z z-pau"},
//jacqueline
{"jacqueline","pau-jh jh-ae ae-ae ae-k k-w w-ah ah-l l-ih ih-n n-pau"},
//james
{"james","pau-jh jh-ey ey-ey ey-m m-z z-pau"},
//jamie
{"jamie","pau-jh jh-ey ey-ey ey-m m-iy iy-pau"},
//january
{"january","pau-jh jh-ae ae-ae ae-n n-y y-uw uw-eh eh-eh eh-r r-iy iy-pau"},
//jason
{"jason","pau-jh jh-ey ey-ey ey-s s-ah ah-n n-pau"},
//jeff jeffery same as geoff and geoffrey
//jet
{"jet","pau-jh jh-eh eh-t t-pau"},
//jethro
{"jethro","pau-jh jh-eh eh-th th-r r-ao ao-uh uh-pau"},
//jeweler
{"jeweler","pau-jh jh-uw uw-ah ah-l l-uh uh-r r-pau"},
{"jewelers","pau-jh jh-uw uw-ah ah-l l-uh uh-r r-z z-pau"},
//job
{"job","pau-jh jh-aa aa-aa aa-b b-b b-pau"},
//john
{"john","pau-jh jh-aa aa-aa aa-n n-pau"},
//johns
{"johns","pau-jh jh-aa aa-aa aa-n n-z z-pau"},
//journey
{"journey","pau-jh jh-er er-er er-n n-iy iy-pau"},
//joy
{"joy","pau-jh jh-ao ao-iy iy-pau"},
//july
{"july","pau-jh jh-uw uw-uw uw-l l-ay ay-ay ay-pau"},
//june
{"june","pau-jh jh-uw uw-uw uw-n n-pau"},

//K-words
//karen or karren
{"karen","pau-k k-eh eh-eh eh-r r-ah ah-n n-pau"},
{"karens","pau-k k-eh eh-eh eh-r r-ah ah-n n-z z-pau"},
//kate
{"kate","pau-k k-ey ey-ey ey-t t-pau"},
//ken
{"ken","pau-k k-eh eh-eh eh-n n-pau"},
//kennel
{"kennel","pau-k k-eh eh-n n-ah ah-l l-pau"},
{"kennels","pau-k k-eh eh-n n-ah ah-l l-z z-pau"},
//kenneth
{"kenneth","pau-k k-eh eh-n n-ih ih-th th-pau"},
//king
{"king","pau-k k-ih ih-ng ng-pau"},
//kingdom
{"kingdom","pau-k k-ih ih-ng ng-d d-ah ah-m m-pau"},
//kings
{"kings","pau-k k-ih ih-ng ng-z z-pau"},

//L-words
//laboratory
{"laboratory","pau-l l-ae ae-b b-r r-ah ah-t t-ao ao-r r-iy iy-pau"},
//large
{"large","pau-l l-aa aa-r r-jh jh-pau"},
//last e.g. last day of summer
{"last","pau-l l-ae ae-s s-t t-pau"},
//laura
{"laura","pau-l l-ao ao-r r-ah ah-pau"},
{"laurel","pau-l l-ao ao-r r-ah ah-l l-pau"},
{"laurence","pau-l l-ao ao-r r-ah ah-n n-s s-pau"},
{"lavender","pau-l l-ae ae-v v-ah ah-n n-d d-uh uh-r r-pau"},
//lawrence
{"lawrence","pau-l l-ao ao-r r-ah ah-n n-s s-pau"},
//lawyer
{"lawyer","pau-l l-ao ao-y y-uh uh-r r-pau"},

//leave
{"leave","pau-l l-iy iy-v v-pau"},
//leaving
{"leaving","pau-l l-iy iy-v v-ih ih-ng ng-pau"},
//lecture
{"lecture","pau-l l-eh eh-eh eh-k k-ch ch-er er-pau"},
//leo
{"leo","pau-l l-iy iy-ao ao-uh uh-pau"},
//lesson
{"lesson","pau-l l-eh eh-s s-ah ah-n n-pau"},
{"lester","pau-l l-eh eh-s s-t t-uh uh-r r-pau"},
//library book
{"library","pau-l l-aa aa-iy iy-b b-r r-eh eh-r r-iy iy-pau"},
//license tv
{"license","pau-l l-aa aa-iy iy-s s-ah ah-n n-s s-pau"},
//lift -car lift
{"lift","pau-l l-ih ih-ih ih-f f-t t-pau"},
//lily or lilly
{"lily","pau-l l-ih ih-ih ih-l l-iy iy-pau"},
//line
{"line","pau-l l-aa aa-iy iy-n n-pau"},
//linux
{"linux","pau-l l-ih ih-ih ih-n n-ah ah-k k-s s-pau"},
//location
{"location","pau-l l-ao ao-uh uh-k k-eh eh-iy iy-sh sh-ah ah-n n-pau"},
//lock
{"lock","pau-l l-aa aa-k pau"},
{"lockup","pau-l l-aa aa-k k-ah ah-p p-pau"},
{"locomotive","pau-l l-ao ao-uh uh-k k-ah ah-m m-ao ao-uh uh-t t-ih ih-v v-pau"},
//lodge
{"lodge","pau-l l-aa aa-jh"},
//long
{"long","pau-l l-ao ao-ng"},
//look
{"look","pau-l l-uh uh-k"},
//louisa
{"louisa","pau-l l-uw uw-iy iy-iy iy-z z-ah ah-pau"},
//low
{"low","pau-l l-ao ao-uh"},
//luca
{"luca","pau-l l-uw uw-k k-ah ah-pau"},
{"lucas","pau-l l-uw uw-k k-ah ah-s"},
//lunch
{"lunch","pau-l l-ah ah-ah ah-n n-ch ch-pau"},

//M-words
//madeline
{"madeline","pau-m m-ae ae-ae ae-d d-ah ah-l l-ih ih-n n-pau"},
//magazine
{"magazine","pau-m m-ae ae-g g-ah ah-z z-iy iy-n n-pau"},
{"maggie","pau-m m-ae ae-g g-iy iy-pau"},
{"magic","pau-m m-ae ae-jh jh-ih ih-k k-pau"},
{"magician","pau-m m-ah ah-jh jh-ih ih-sh sh-ah ah-n n-pau"},
{"magistrate","pau-m m-ae ae-jh jh-ah ah-s s-t t-r r-eh eh-iy iy-t t-pau"},
{"magistrates","pau-m m-ae ae-jh jh-ih ih-s s-t t-r r-eh eh-iy iy-t t-s s-pau"},
//maintenance
{"maintenance","pau-m m-ey ey-ey ey-n n-t t-ah ah-n n-ah ah-n n-s s-s s-pau"},
//man
{"man","pau-m m-ae ae-n n-pau"},
//management
{"management","pau-m m-ae ae-ae ae-n n-ah ah-jh jh-m m-ah ah-n n-t t-pau"},
//many
{"many","pau-m m-eh eh-n n-iy iy-pau"},
//march
{"march","pau-m m-aa aa-aa aa-r r-ch ch-pau"},
{"marie","pau-m m-uh uh-r r-iy iy-pau"},
{"marigold","pau-m m-eh eh-r r-ah ah-g g-ao ao-uh uh-l l-d d-pau"},
{"marina","pau-m m-uh uh-r r-iy iy-n n-ah ah-pau"},
//marine
{"marine","pau-m m-uh uh-r r-iy iy-n n-pau"},
//marjorie
{"marjorie","pau-m m-aa aa-r r-jh jh-uh uh-r r-iy iy-pau"},
{"mark","pau-m m-aa aa-r r-k k-pau"},
//market
//mary
{"mary","pau-m m-eh eh-eh eh-r r-iy iy-pau"},
//marys
{"marys","pau-m m-eh eh-eh eh-r r-iy iy-z z-pau"},
//master
{"master","pau-m m-ae ae-ae ae-s s-t t-er er-pau"},
//mat
//matt
{"matt","pau-m m-ae ae-ae ae-t t-pau"},
//matthew
{"matthew","pau-m m-ae ae-ae ae-th th-y y-uw uw-pau"},
//matthews
{"matthews","pau-m m-ae ae-ae ae-th th-y y-uw uw-z z-pau"},
//matthias
{"matthias","pau-m m-ah ah-th th-ay ay-ay ay-ah ah-s s-pau"},
//maurice
{"maurice","pau-m m-ao ao-r r-iy iy-s s-pau"},
//may
{"may","pau-m m-m m-ey ey-ey ey-pau"},
//me
{"me","pau-m m-iy iy-pau"},
//meal
{"meal","pau-m m-iy iy-iy iy-l l-pau"},
//mechanic
{"mechanic","pau-m m-ah ah-k k-ae ae-n n-ih ih-k k-pau"},
//medical
{"medical","pau-m m-eh eh-eh eh-d d-ah ah-k k-ah ah-l l-pau"},
//meet
{"meet","pau-m m-iy iy-iy iy-t t-pau"},
//meeting
{"meeting","pau-m m-iy iy-iy iy-t t-ih ih-ng ng-pau"},
{"member","pau-m m-eh eh-m m-b b-uh uh-r r-pau"},
{"members","pau-m m-eh eh-m m-b b-uh uh-r r-z z-pau"},
//memo
{"memo","pau-m m-eh eh-eh eh-m m-ao ao-uh uh-pau"},
//memorandum
{"memorandum","pau-m m-eh eh-eh eh-m m-er er-ae ae-ae ae-n n-d d-ah ah-m m-pau"},
//message
{"message","pau-m m-eh eh-s s-ah ah-jh jh-pau"},
//midnight
{"midnight","pau-m m-ih ih-d d-n n-aa aa-iy iy-t t-pau"},
//mike
{"mike","pau-m m-aa aa-iy iy-k k-pau"},
//minder
{"minder","pau-m m-aa aa-iy iy-n n-d d-uh uh-r r-pau"},
//mini
{"mini","pau-m m-ih ih-ih ih-n n-iy iy-iy iy-pau"},
//miriam
{"miriam","pau-m m-ih ih-r r-iy iy-ah ah-m m-pau"},
//monday
{"monday","pau-m m-ah ah-ah ah-n n-n n-d d-iy iy-pau"},
//monster
{"monster","pau-m m-aa aa-n n-s s-t t-uh uh-r r-pau"},
//month
{"month","pau-m m-ah ah-n n-th th-pau"},
//morning
{"morning","pau-m m-ao ao-ao ao-r r-n n-ih ih-ng ng-pau"},
//mother
{"mother","pau-m m-ah ah-ah ah-dh dh-er er-pau"},
//mothers
{"mothers","pau-m m-ah ah-ah ah-dh dh-er er-z z-pau"},
//motorcycle
{"motorcycle","pau-m m-ow ow-ow ow-t t-er er-s s-ay ay-ay ay-k k-ah ah-l l-pau"},
//move
{"move","pau-m m-uw uw-v v-pau"},
{"moving","pau-m m-uw uw-v v-ih ih-ng ng-pau"},
//movie
{"movie","pau-m m-uw uw-uw uw-v v-iy iy-pau"},
//muhammad
{"muhammad","pau-m m-uh uh-hh hh-aa aa-m m-ah ah-d d-pau"},
{"muhammads","pau-m m-uh uh-hh hh-aa aa-m m-ah ah-d d-z z-pau"},
//mum
{"mum","pau-m m-ah ah-ah ah-m m-pau"},
//mums
{"mums","pau-m m-ah ah-ah ah-m m-z z-pau"},
//music
{"music","pau-m m-y y-uw uw-uw uw-z z-ih ih-k k-pau"},
//my
{"my","pau-m m-ay ay-ay ay-pau"},

//N-words
//naomi
{"naomi","pau-n n-ey ey-ow ow-ow ow-m m-iy iy-pau"},
//nat
{"nat","pau-n n-ae ae-t t-pau"},
//natalie
{"natalie","pau-n n-ae ae-t t-ah ah-l l-iy iy-pau"},
//natasha
{"natasha","pau-n n-ah ah-t t-aa aa-sh sh-ah ah-pau"},
//nathan
{"nathan","pau-n n-eh eh-iy iy-th th-ah ah-n n-pau"},
{"nathaniel","pau-n n-ah ah-th th-ae ae-n n-y y-ah ah-l l-pau"},
{"nation","pau-n n-eh eh-iy iy-sh sh-ah ah-n n-pau"},
{"national","pau-n n-ae ae-sh sh-ah ah-n n-ah ah-l l-pau"},

//neighbour
{"neighbour","pau-n n-eh eh-iy iy-b b-uh uh-r r-pau"},
//nephew
{"nephew","pau-n n-eh eh-f f-y y-uw uw-pau"},
//netball 
{"net","pau-n n-eh eh-t t-b b-ao ao-l l-pau"},
//netflix
{"netflix","pau-n n-eh eh-eh eh-t t-f f-l l-ih ih-ih ih-k k-k k-pau"},
//new
{"new","pau-n n-uw uw-uw uw-pau"},
//news
{"news","pau-n n-uw uw-z z-pau"},
//newspaper
{"newspaper","pau-n n-uw uw-z z-p p-eh eh-iy iy-p p-uh uh-r r-pau"},
//niece
{"niece","pau-n n-iy iy-s s-pau"},
//night
{"night","pau-n n-aa aa-iy iy-t t-pau"},
//nine
{"nine","pau-n n-ay ay-ay ay-n n-pau"},
//nineteen
{"nineteen","pau-n n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-pau"},
//nineteenth
//{"nineteenth","pau-n n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-th th-pau pau-th th-pau"},
{"nineteenth","pau-n n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-th th-th th-pau"},
//ninetieth
{"ninetieth","pau-n n-aa aa-iy iy-n n-t t-iy iy-ih ih-th th-pau"},
//ninety
{"ninety","pau-n n-aa aa-iy iy-n n-t t-iy iy-pau"},
//ninth
{"ninth","pau-n n-ay ay-ay ay-n n-th th-pau"},
//no
{"no","pau-n n-ao ao-uh uh-pau"},
//noah
{"noah","pau-n n-ao ao-uh uh-ah ah-pau"},
//norman
{"norman","pau-n n-ao ao-r r-m m-ah ah-n n-pau"},
//normans
{"normans","pau-n n-ao ao-r r-m m-ah ah-n n-z z-pau"},
//north
{"north","pau-n n-ao ao-r r-th th-pau"},
{"northumbria","pau-n n-ao ao-r r-th th-ah ah-m m-r r-iy iy-ah ah-pau"},
//not
{"not","pau-n n-aa aa-t t-pau"},
//notable
{"notable","pau-n n-ao ao-uh uh-t t-ah ah-b b-ah ah-l l-pau"},
//november
{"november","pau-n n-ow ow-v v-eh eh-eh eh-m m-b b-er er-pau"},
//now
{"now","pau-n n-aw aw-aw aw-pau"},
//nurse
{"nurse","pau-n n-uh uh-r r-s s-pau"},
//nursery
{"nursery","pau-n n-er er-er er-s s-er er-iy iy-pau"},

//O-words
//o
{"o","pau-ao ao-uh uh-ao ao-uh uh-pau"},
//october
{"october","pau-aa aa-k k-t t-ow ow-ow ow-b b-er er-pau"},
//of
{"of","pau-ah ah-v v-pau"},
{"off","pau-ao ao-f f-pau"},
{"offer","pau-ao ao-f f-uh uh-r r-pau"},
//office
{"office","pau-ao ao-ao ao-f f-ah ah-s s-pau"},
//oliver
{"oliver","pau-aa aa-aa aa-l l-ih ih-v v-er er-pau"},
//olivers
{"oliver","pau-aa aa-aa aa-l l-ih ih-v v-er er-z z-pau"},
//olivia
{"olivia","pau-ow ow-l l-ih ih-ih ih-v v-iy iy-ah ah-pau"},
//olivias
{"olivias","pau-ow ow-l l-ih ih-ih ih-v v-iy iy-ah ah-z z-pau"},
//on
{"on","pau-aa aa-aa aa-n n-n n-pau"},
//one
{"one","w-ah ah-ah ah-n n-pau"},
//online
{"online","pau-aa aa-aa aa-n n-n n-l l-aa aa-iy iy-n n-pau"},
//open
{"open","pau-ao ao-uh uh-p p-ah ah-n n-pau"},
//or
{"or","pau-ao ao-r r-pau"},
//orchestra
{"orchestra","pau-ao ao-r r-k k-ah ah-s s-t t-r r-ah ah-pau"},
//oscar
{"oscar","pau-ao ao-s s-k k-uh uh-r r-pau"},
{"oscars","pau-ao ao-s s-k k-uh uh-r r-z z-pau"},
//out
{"out","pau-aa aa-uh uh-t t-pau"},
{"outbreak","pau-aa aa-uh uh-t t-b b-r r-eh eh-iy iy-k k-pau"},
{"outcome","pau-aa aa-uh uh-t t-k k-ah ah-m m-pau"},
{"outhouse","pau-aa aa-uh uh-t t-hh hh-aa aa-uh uh-s s-pau"},
{"outing","pau-aa aa-uh uh-t t-ih ih-ng ng-pau"},
//over
{"over","pau-ao ao-uh uh-v v-uh uh-r r-pau"},
//own
{"own","pau-ow ow-ow-ow-ow ow-n n-pau"},

//P-words
//pam
{"pam","pau-p p-ae ae-ae ae-m m-pau"},
//pamela
{"pamela","pau-p p-ae ae-ae ae-m m-ah ah-l l-ah ah-pau"},
//pams
{"pams","pau-p p-ae ae-ae ae-m m-z z-pau"},
//pancake
{"pancake","pau-p p-ae ae-ae ae-n n-k k-ey ey-ey ey-k k-pau"},
//paper
{"paper","pau-p p-eh eh-iy iy-p p-uh uh-r r-pau"},
//parent
{"parent","pau-p p-eh eh-r r-ah ah-n n-t t-pau"},
{"parents","pau-p p-eh eh-r r-ah ah-n n-t t-s s-pau"},
//parrot
{"parrot","pau-p p-eh eh-r r-ah ah-t t-pau"},
//party
{"party","pau-p p-aa aa-aa aa-r r-t t-iy iy-pau"},
//passport
{"passport","pau-p p-ae ae-ae ae-s s-p p-ao ao-ao ao-r r-t t-pau"},
//pat
{"pat","pau-p p-ae ae-t t-pau"},
//patricia
{"patricia","pau-p p-ah ah-t t-r r-ih ih-sh sh-ah ah-pau"},
//patrick
{"patrick","pau-p p-ae ae-ae ae-t t-r r-ih ih-k k-pau"},
//patricks (saint name)
{"patricks","pau-p p-ae ae-ae ae-t t-r r-ih ih-k k-s s-pau"},
//pau
//{"pau","pau-pau"},
//paul
{"paul","pau-p p-ao ao-ao ao-l l-pau"},
//paula
{"paula","pau-p p-ao ao-ao ao-l l-ah ah-pau"},
//pauline
{"pauline","pau-p p-ao ao-l l-iy iy-iy iy-n n-pau"},
//pauses
{"pause1","pau-pau"},
{"pause2","pau-pau pau-pau"},
//pay
{"pay","pau-p p-eh eh-iy iy-pau"},
{"payable","pau-p p-eh eh-iy iy-ah ah-b b-ah ah-l l-pau"},
{"payed","pau-p p-eh eh-iy iy-d d-pau"},
//paying
{"paying","pau-p p-eh eh-iy iy-ih ih-ng ng-pau"},
//payment
{"payment","pau-p p-ey ey-ey ey-m m-ah ah-n n-t t-pau"},
//penelope
{"penelope","pau-p p-ah ah-n n-eh eh-eh eh-l l-ah ah-p p-iy iy-pau"},
//penny
{"penny","pau-p p-eh eh-eh eh-n n-iy iy-pau"},
//pension
{"pension","pau-p p-eh eh-eh eh-n n-sh sh-ah ah-n n-pau"},
//percy
{"percy","pau-p p-er er-er er-s s-iy iy-pau"},
//perry
{"perry","pau-p p-eh eh-eh eh-r r-iy iy-pau"},
//person
{"person","pau-p p-uh uh-r r-s s-ah ah-n n-pau"},
//personal
{"personal","pau-p p-uh uh-r r-s s-ih ih-n n-ih ih-l l-pau"},
//pet
{"pet","pau-p p-eh eh-t t-pau"},
//peter
{"peter","pau-p p-iy iy-iy iy-t t-er er-pau"},
//peters
{"peters","pau-p p-iy iy-iy iy-t t-er er-z z-pau"},
//phoebe or phebe
{"phoebe","pau-f f-iy iy-iy iy-b b-iy iy-pau"},
//phone
{"phone","pau-f f-ao ao-uh uh-n n-pau"},
//piano
{"piano","pau-p p-iy iy-ae ae-n n-ao ao-uh uh-pau"},
//picture
{"picture","pau-p p-ih ih-ih ih-k k-ch ch-er er-pau"},
//pictures
{"pictures","pau-p p-ih ih-ih ih-k k-ch ch-er er-z z-pau"},
//pilates
{"pilates","pau-p p-ih ih-ih ih-l l-aa aa-aa aa-t t-iy iy-iy iy-s s-pau"},
//place
{"place","pau-p p-l l-eh eh-iy iy-s s-pau"},
//pmm
{"pmm","pau-p p-iy iy-iy iy-m m-eh eh-m m-m m-m m-pau"},
//point
{"point","pau-p p-oy oy-oy oy-n n-t t-pau"},
{"pop","pau-p p-aa aa-p p-pau"},
{"popcorn","pau-p p-aa aa-p p-k k-ao ao-r r-n n-pau"},
//pope
{"pope","pau-p p-ao ao-uh uh-p p-pau"},
//port
{"port","pau-p p-ao ao-r r-t t-pau"},
//post
{"post","pau-p p-ao ao-uh uh-s s-t t-pau"},
//postoffice
{"postoffice","pau-p p-ao ao-uh uh-s s-t t-ao ao-f f-ah ah-s s-pau"},
//{"potato","p-ah ah-t t-eh eh-iy iy-t t-ao ao-uh"},
//{"potatoes","p-ah ah-t t-eh eh-iy iy-t t-ao ao-uh uh-z"},
//practice
{"practice","pau-p p-r r-ae ae-k k-t t-ah ah-s s-pau"},
//premier
{"premier","pau-p p-r r-eh eh-m m-ih ih-ih ih-r r-pau"},
//prescription
{"prescription","pau-p p-r r-ah ah-s s-k k-r r-ih ih-p p-sh sh-ah ah-n n-pau"},
//present
{"present","pau-p p-r r-eh eh-z z-ah ah-n n-t t-pau"},
//pressure
{"pressure","pau-p p-r r-eh eh-sh sh-uh uh-r r-pau"},
//priority
{"priority","pau-p p-r r-aa aa-iy iy-ao ao-r r-ah ah-t t-iy iy-pau"},
{"priscilla","pau-p p-r r-ih ih-s s-ih ih-l l-ah ah-pau"},
{"prism","pau-p p-r r-ih ih-z z-ah ah-m m-pau"},
{"prison","pau-p p-r r-ih ih-z z-ah ah-n n-pau"},
{"private","pau-p p-r r-aa aa-iy iy-v v-ah ah-t t-pau"},
{"professional","pau-p p-r ah-ah ah-f f-eh eh-eh eh-sh sh-ah ah-n n-ah ah-l l-pau "},
//professor or prof
{"professor","pau-p p-r ah-ah ah-f f-eh eh-eh eh-s s-er er-pau"},
//program
{"program","pau-p p-r r-ow ow-ow ow-g g-r r-ae ae-ae ae-m m-pau"},
//programme (duplicate)
{"programme","pau-p p-r r-ow ow-ow ow-g g-r r-ae ae-ae ae-m m-pau"},
//project
{"project","pau-p p-r r-aa aa-aa aa-jh jh-eh eh-k k-t t-pau"},
//pronounce
{"pronounce","pau-p p-r r-ah ah-n n-aa aa-uh uh-n n-s s-pau"},
//pronounced
{"pronounced","pau-p p-r r-ah ah-n n-aa aa-uh uh-n n-s s-t t-pau"},
//prunella
{"prunella","pau-p p-r r-uw uw-n n-eh eh-eh eh-l l-ah ah-pau"},
//pub
{"pub","pau-p p-ah ah-ah ah-b b-pau"},
//public
{"public","pau-p p-ah ah-ah ah-b b-l l-ih ih-k k-pau"},
//purchase
{"purchase","pau-p p-uh uh-r r-ch ch-ah ah-s s-pau"},

//Q-words
//queen
{"queen","pau-k k-w w-iy iy-n n-pau"},
//quick
{"quick","pau-k k-w w-ih ih-k k-pau"},
//quiz
{"quiz","pau-k k-w w-ih ih-ih ih-z z-pau"},
//quote
{"quote","pau-k k-w w-w w-ow ow-ow ow-t t-pau"},


//R-words
//radio
{"radio","pau-r r-ey ey-ey ey-d d-iy iy-ow ow-ow ow-pau"},
//rail
{"rail","pau-r r-eh eh-iy iy-l l-pau"},
//railway
{"railway","pau-r r-eh eh-iy iy-l l-w w-eh eh-iy iy-pau"},
{"rain","pau-r r-eh eh-iy iy-n n-pau"},
{"ralph","pau-r r-ae ae-l l-f f-pau"},
//ray
{"ray","pau-r r-eh eh-iy iy-pau"},
//reminder
{"reminder","pau-r r-iy iy-m m-ay ay-ay ay-n n-d d-er er-pau"},
//rene and renne
{"rene","pau-r r-ah ah-n n-eh eh-iy iy-pau"},
{"renew","pau-r r-ih ih-n n-uw uw-pau"},
{"renewal","pau-r r-ih ih-n n-uw uw-ah ah-l l-pau"},
//repair
{"repair","pau-r r-ih ih-p p-eh eh-r r-pau"},
//rest
{"rest","pau-r r-eh eh-eh eh-s s-t t-pau"},
//restaurant
{"restaurant","pau-r r-eh eh-eh eh-s s-t t-er er-aa aa-aa aa-n n-t t-pau"},
//retire
{"retire","pau-r r-ih ih-t t-aa aa-iy iy-r r-pau"},
//retirement
{"retirement","pau-r r-iy iy-t t-ay ay-er er-m m-ah ah-n n-t t-pau"},
//return
{"return","pau-r r-ih ih-t t-uh uh-r r-n n-pau"},
//richard
{"richard","pau-r r-ih ih-ch ch-uh uh-r r-d d-pau"},
//road
{"road","pau-r r-ao ao-uh uh-d d-pau"},
{"robber","pau-r r-aa aa-b b-uh uh-r r-pau"},
//robbie
{"robbie","pau-r r-aa aa-b b-iy iy-pau"},
//robert
{"robert","pau-r r-aa aa-b b-uh uh-r r-t t-pau"},
//robin
{"robin","pau-r r-aa aa-b b-ah ah-n n-pau"},
//ronald
{"ronald","pau-r r-aa aa-n n-ah ah-l l-d d-pau"},
//room
{"room","pau-r r-uw uw-m m-pau"},
//rose
{"rose","pau-r r-ow ow-ow ow-z z-pau"},
//rosemary
{"rosemary","pau-r r-ow ow-ow ow-z z-m m-eh eh-eh eh-r r-iy iy-pau"},
//royal
{"royal","pau-r r-ao ao-iy iy-ah ah-l l-pau"},
//rugby
{"rugby","pau-r r-ah ah-g g-b b-iy iy-pau"},
//russell and russel
{"russell","pau-r r-ah ah-s s-ah ah-l l-pau"},

//S-words
//sabrina
{"sabrina","pau-s s-ah ah-b b-r r-iy iy-iy iy-n n-ah ah-pau"},
//saint
{"saint","pau-s s-ey ey-ey ey-n n-t t-pau"},
//sam
{"sam","pau-s s-ae ae-m m-pau"},
//samuel
{"samuel","pau-s s-ae ae-m m-y y-uw uw-l l-pau"},
//sanctuary
{"sanctuary","pau-s s-ae ae-ng ng-k k-ch ch-uw uw-eh eh-r r-iy iy-pau"},
//sarah
{"sarah","pau-s s-eh eh-r r-ah ah-pau"},
//saturday
{"saturday","pau-s s-ae ae-ae ae-t t-ih ih-ih ih-d d-ey ey-ey ey-pau"},
//say
{"say","pau-s s-eh eh-iy iy-pau"},
//says
{"says","pau-s s-eh eh-z z-pau"},
//school
{"school","pau-s s-k k-uw uw-l l-pau"},
//sea
{"sea","pau-s s-iy iy-iy iy-pau"},
{"seal","pau-s s-iy iy-l l-pau"},
{"seaside","pau-s s-iy iy-s s-aa aa-iy iy-d d-pau"},
{"season","pau-s s-iy iy-z z-ah ah-n n-pau"},
//second
{"second","pau-s s-eh eh-eh eh-k k-ah ah-n n-d d-pau"},
//self
{"self","pau-s s-eh eh-eh eh-l l-f f-pau"},
{"semicircle","pau-s s-eh eh-m m-ih ih-s s-uh uh-r r-k k-ah ah-l l-pau"},
//seminar
{"seminar","pau-s s-eh eh-eh eh-m m-ah ah-n n-aa aa-aa aa-r r-r r-pau"},
//september
{"september","pau-s s-eh eh-p p-t t-eh eh-eh eh-m m-b b-er er-pau"},
//series
{"series","pau-s s-ih ih-r r-iy iy-z z-pau"},
//service
{"service","pau-s s-er er-er er-v v-ah ah-s s-pau"},
//seven
{"seven","pau-s s-eh eh-eh eh-v v-ah ah-n n-pau"},
//seventeen
{"seventeen","pau-s s-eh eh-eh eh-v v-ah ah-n n-t t-iy iy-iy iy-n n-pau"},
//seventeenth
{"seventeenth","pau-s s-eh eh-eh eh-v v-ah ah-n n-t t-iy iy-iy iy-n n-th th-pau"},
//seventh
{"seventh","pau-s s-eh eh-eh eh-v v-ah ah-n n-th th-pau"},
//seventieth
{"seventieth","pau-s s-eh eh-v v-ah ah-n n-t t-iy iy-ih ih-th th-pau"},
//seventy
{"seventy","pau-s s-eh eh-v v-ah ah-n n-t t-iy iy-pau"},
//shoe
{"shoe","pau-sh sh-uw uw-pau"},
//shop
{"shop","pau-sh sh-aa aa-aa aa-p p-pau"},
//shopping
{"shopping","pau-sh sh-aa aa-aa aa-p p-ih ih-ng n-pau"},
//short
{"short","pau-sh sh-ao ao-r r-t t-pau"},
//show
{"show","pau-sh sh-ow ow-ow ow-pau"},
//sister
{"sister","pau-s s-ih ih-s s-t t-uh uh-r r-pau"},
//sisters
{"sisters","pau-s s-ih ih-s s-t t-uh uh-r r-z z-pau"},
//six
{"six","pau-s s-ih ih-ih ih-k k-s s-pau"},
//sixteen
{"sixteen","pau-s s-ih ih-k k-s s-t t-iy iy-iy iy-n n-pau"},
//sixteenth
{"sixteenth","pau-s s-ih ih-k k-s s-t t-iy iy-iy iy-n n-th th-pau"},
//sixth
{"sixth","pau-s s-ih ih-ih ih-k k-s s-th th-pau"},
//sixtieth
//sixty
{"sixty","pau-s s-ih ih-k k-s s-t t-iy iy-pau"},
//sky
{"sky","pau-s s-k k-aa aa-iy iy-pau"},
//small
{"small","pau-s s-m m-ao ao-l l-pau"},
//society
{"society","pau-s s-ow ow-s s-ay ay-ay ay-ih ih-t t-iy iy-pau"},
//software
//son
{"son","pau-s s-ah ah-ah ah-n n-pau"},
//sons
{"sons","pau-s s-ah ah-ah ah-n n-z z-pau"},
//south
//special
{"special","pau-s s-p p-eh eh-eh eh-sh sh-ah ah-l l-pau"},
//speech
{"speech","pau-s s-p p-iy iy-iy iy-ch ch-ch ch-pau"},
//sport
{"sport","pau-s s-p p-ao ao-ao ao-r r-t t-pau"},
//spring
{"spring","pau-s s-p p-r r-ih ih-ih ih-ng ng-pau"},
//stag
{"stag","pau-s s-t t-ae ae-g g-pau"},
//star
{"star","pau-s s-t t-aa aa-r r-pau"},
//start
{"start","pau-s s-t t-aa aa-r r-t t-pau"},
//starts
{"starts","pau-s s-t t-aa aa-r r-t t-s s-pau"},
//station
{"station","pau-s s-t t-ey ey-ey ey-sh sh-ah ah-n n-pau"},
//stay
{"stay","pau-s s-t t-eh eh-iy iy-pau"},
//steve
{"steve","pau-s s-t t-iy iy-iy iy-v v-pau"},
//steven or stephen
{"steven","pau-s s-t t-iy iy-iy iy-v v-ah ah-n n-pau"},
//{"stephen","s-t t-iy iy-iy iy-v v-ah ah-n"},
//stock
{"stock","pau-s s-t t-aa aa-k k-pau"},
//store
{"store","pau-s s-t t-ao ao-r r-pau"},
//study
{"study","pau-s s-t t-ah ah-d d-iy iy-pau"},
{"studying","pau-s s-t t-ah ah-d d-iy iy-ih ih-ng ng-pau"},
//summer
{"summer","pau-s s-ah ah-m m-uh uh-r r-pau"},
//summertime
{"summertime","pau-s s-ah ah-m m-uh uh-r r-t t-aa aa-iy iy-m m-pau"},
//sunday 
//{"sunday","pau-s s-ah ah-ah ah-n n-n n-d d-ey ey-ey ey-pau"},
{"sunday","pau-s s-ah ah-ah ah-n n-d d-ey ey-ey ey-pau"},
//super
{"super","pau-s s-uw uw-p p-uh uh-r r-pau"},//prefix
//susan
{"susan","pau-s s-uw uw-uw uw-z z-ah ah-n n-pau"},
//susans
{"susans","pau-s s-uw uw-uw uw-z z-ah ah-n n-z z-pau"},
//synthesizer bad prounciation
{"synthesizer","pau-s s-ih ih-ih ih-n n-th th-ah ah-ah ah-th th-z z-s s-ay ay-ay ay-ay ay-er er-pau"},

//T-words
//take
{"take","pau-t t-eh eh-iy iy-k k-pau"},
//talk
{"talk","pau-t t-ao ao-ao ao-k k-pau"},
//talking
{"talking","pau-t t-ao ao-ao ao-k k-ih ih-ng ng-pau"},
//task
{"task","pau-t t-ae ae-ae ae-s s-k k-pau"},
//tax
{"tax","pau-t t-ae ae-ae ae-k k-s s-pau"},
//taxi
{"taxi","pau-t t-ae ae-ae ae-k k-s s-iy iy-pau"},
//tea
{"tea","pau-t t-t t-iy iy-iy iy-pau"},
{"tearoom","pau-t t-r r-uh uh-r r-uw uw-m m-pau"},
//team
{"team","pau-t t-iy iy-m m-pau"},
//telephone
{"telephone","pau-t t-eh eh-eh eh-l l-ah ah-f f-f f-ow ow-ow ow-ow ow-n n-pau"},
//television
{"television","pau-t t-eh eh-eh eh-l l-ah ah-v v-ih ih-ih ih-zh zh-ah ah-n n-pau"},
//temperature
{"temperature","pau-t t-eh eh-m m-p p-r r-ah ah-ch ch-uh uh-r r-pau"},
//ten
{"ten","pau-t t-eh eh-eh eh-n n-pau"},
//tennis
{"tennis","pau-t t-eh eh-n n-ah ah-s s-pau"},
//tenth
{"tenth","pau-t t-eh eh-eh eh-n n-th th-pau"},
//test
{"test","pau-t t-eh eh-eh eh-s s-t t-pau"},
//thank
{"thank","pau-th th-ae ae-ng ng-k k-pau"},
//that
{"that","pau-dh dh-ae ae-t t-pau"},
//the
{"the","pau-dh dh-ah ah-ah ah-pau"},
//theatre
{"theater","pau-th th-iy iy-iy iy-ey ey-t t-er er-pau"},
//then
{"then","pau-dh dh-eh eh-eh eh-n n-pau"},
//theo
{"theo","pau-th th-iy iy-ao ao-uh uh-pau"},
//theodore
{"theodore","pau-th th-iy iy-ah ah-d d-ao ao-r r-pau"},
//third
{"third","pau-th th-er er-er er-d d-pau"},
//thirteen
{"thirteen","pau-th th-er er-er er-t t-iy iy-iy iy-n n-pau"},
//thirteenth
{"thirteenth","pau-th th-er er-er er-t t-iy iy-iy iy-n n-th th-pau"},
//thirtieth
{"thirtieth","pau-th th-er er-er er-t t-iy iy-eh eh-eh eh-th th-pau"},
//thirty
{"thirty","pau-th th-er er-er er-d d-iy iy-iy iy-pau"},
//thomas
{"thomas","pau-t t-aa aa-aa aa-m m-ah ah-s s-pau"},
//{"thomases","t-aa aa-aa aa-m m-ah ah-s s-ih ih-z"},
//three
{"three","pau-t th-r r-iy iy-iy iy-pau"},
//thursday
{"thursday","pau-th th-er er-er er-z z-d d-iy iy-pau"},
//ticket
{"ticket","pau-t t-ih ih-k k-ah ah-t t-pau"},
//tiffany
{"tiffany","pau-t t-ih ih-f ih-f f-ah ah-n n-iy iy-pau"},
//tilda
{"tilda","pau-t t-ih ih-ih ih-l l-d d-ah ah-pau"},
//tim
{"tim","pau-t t-ih ih-ih ih-m m-pau"},
//time
{"time","pau-t t-ay ay-ay ay-m -pau"},
//times
{"times","pau-t t-aa aa-iy iy-m m-z z-pau"},
//timothy
{"timothy","pau-t t-ih ih-ih ih-m m-ah ah-th th-iy iy-pau"},
//tims
{"tims","pau-t t-ih ih-ih ih-m m-z z-pau"},
//tiny
{"tiny","pau-t t-aa aa-iy iy-n n-iy iy-pau"},
//to
{"to","pau-t t-uw uw-uw uw-pau"},
//today
{"today","pau-t t-ah ah-d d-ey ey-ey ey-pau"},
//toll
{"toll","pau-t t-ao ao-uh uh-l l-pau"},
//tom
{"tom","pau-t t-aa aa-aa aa-m m-pau"},
//tomorrow
{"tomorrow","pau-t t-ah ah-m m-aa aa-r r-ao ao-uh uh-pau"},
//toms
{"toms","pau-t t-aa aa-aa aa-m m-z z-pau"},
//train
{"train","pau-t t-r r-eh eh-iy iy-n n-pau"},
//trans
{"trans","pau-t t-r r-ae ae-n n-z"},//prefix
//transport
{"transport","pau-t t-r r-ae ae-n n-s s-p p-ao ao-r r-t t-pau"},
//travel
{"travel","pau-t t-r r-ae ae-ae ae-v v-ah ah-l l-pau"},
//traveling or travelling
{"traveling","pau-t t-r r-ae ae-ae ae-v v-ah ah-l l-ih ih-ng ng-pau"},
//travelodge
{"travelodge","pau-t t-r r-ae ae-ae ae-v v-ah ah-l l-aa aa-aa aa-jh jh-pau"},
//trevor
{"trevor","pau-t t-r r-eh eh-eh eh-v v-er er-pau"},
//trevors
//{"trevors","pau-t t-r r-eh eh-eh eh-v v-er er-z z-pau pau-z z-pau"},
{"trevors","pau-t t-r r-eh eh-eh eh-v v-er er-z z-z z-pau"},
//trip
{"trip","pau-t t-r r-ih ih-ih ih-p p-p p-pau"},
//tuesday
{"tuesday","pau-t t-uw uw-uw uw-z z-d d-iy iy-pau"},
//tunnel
{"tunnel","pau-t t-ah ah-n n-ah ah-l l-pau"},
//turn
{"turn","pau-t t-uh uh-r r-n n-pau"},
//tv
{"tv","pau-t t-iy iy-iy iy-v v-iy iy-iy iy-pau"},
//twelfth
//{"twelfth","pau-t t-w w-eh eh-eh eh-l l-f f-th th-pau pau-th th-pau"},
{"twelfth","pau-t t-w w-eh eh-eh eh-l l-f f-th th-th th-pau"},
//twelve
{"twelve","pau-t t-w w-eh eh-eh eh-l l-v v-pau"},
//twentieth
{"twentieth","pau-t t-w w-eh eh-eh eh-n n-t t-iy iy-eh eh-eh eh-th th-pau"},
//twenty
{"twenty","pau-t t-w w-eh eh-eh eh-n n-t t-iy iy-pau"},
//two
{"two","pau-t t-uw uw-uw uw-pau"},

//U-words
//uncle
{"uncle","pau-ah ah-ah ah-ng ng-k k-ah ah-l l-pau"},
//uncles
{"uncles","pau-ah ah-ah ah-ng ng-k k-ah ah-l l-z z-pau"},

//university
{"university","pau-y y-uw uw-n n-ah ah-v v-uh uh-r r-s s-ah ah-t t-iy iy-pau"},
//unknown
{"unknown","pau-ah ah-n n-n n-ow ow-ow ow-n n-n n-pau"},

//upcoming
{"upcoming","pau-ah ah-p p-k k-ah ah-ah ah-m m-ih ih-ng ng-pau"},
//ursula
{"ursula","pau-uh uh-r r-s s-ah ah-l l-ah ah-pau"},
//use
{"use","pau-y y-uw uw-uw uw-z z-pau"},
//user
{"user","pau-y y-uw uw-uw uw-z z-er er-pau"},

//V-words
//vacation
{"vacation","pau-v v-ey ey-k k-ey ey-ey ey-sh sh-ah ah-n n-pau"},
//val
{"val","pau-v v-ae ae-ae ae-l l-pau"},
//valentine
{"valentine","pau-v v-ae ae-ae ae-l l-ah ah-n n-t t-ay ay-ay ay-n n-pau"},
//valentines
{"valentines","pau-v v-ae ae-ae ae-l l-ah ah-n n-t t-ay ay-ay ay-n n-z z-pau"},
//valerie
{"valerie","pau-v v-ae ae-ae ae-l l-er er-iy iy-pau"},
//vehicle
{"vehicle","pau-v v-iy iy-iy iy-hh hh-ih ih-k k-ah ah-l l-pau"},
//venue
{"venue","pau-v v-eh eh-n n-y y-uw uw-pau"},
//version
{"version","pau-v v-er er-er er-zh zh-ah ah-n n-pau"},
//veronica
{"veronica","pau-v v-uh uh-r r-aa aa-n n-ih ih-k k-ah ah-pau"},
{"vicar","pau-v v-ih ih-k k-uh uh-r r-pau"},
{"vicarage","pau-v v-ih ih-k k-uh uh-r r-r r-aa aa-jh jh-pau"},
//victor
{"victor","pau-v v-ih ih-k k-t t-uh uh-r r-pau"},
{"victoria","pau-v v-ih ih-k k-t t-ao ao-r r-iy iy-ah ah-pau"},
//visit
{"visit","pau-v v-ih ih-ih ih-z z-ih ih-t t-pau"},

//w-words
//walk
{"walk","pau-w w-w w-ao ao-ao ao-k k-k k-pau"},
//warm
{"warm","pau-w w-ao ao-r r-m m-pau"},
//warming
{"warming","pau-w w-ao ao-r r-m m-ih ih-ng ng-pau"},
{"warn","pau-w w-ao ao-r r-n n-pau"},
{"warning","pau-w w-ao ao-r r-n n-ih ih-ng ng-pau"},
//wash
{"wash","pau-w w-aa aa-sh sh-pau"},
//washing
{"washing","pau-w w-aa aa-sh sh-ih ih-ng ng-pau"},
//water
//{"water","w-ao ao-t t-uh uh-r"},
{"water","pau-w w-ao ao-ao ao-t t-er er-pau"},
//way
{"way","pau-w w-ey ey-iy iy-pau"},
//weather warning (to do)
{"weather","pau-w w-eh eh-dh dh-uh uh-r r-pau"},
//web
{"web","pau-w w-eh eh-eh eh-b b-b b-pau"},
//wedding
{"wedding","pau-w w-eh eh-eh eh-d d-ih ih-ng ng-pau"},
//wednesday
{"wednesday","pau-w w-eh eh-eh eh-n n-z z-d d-iy iy-pau"}, //or iy-iy
//week
{"week","pau-w w-iy iy-k k-pau"},
//west
{"west","pau-w w-eh eh-s s-t t-pau"},
//wife
{"wife","pau-w w-ay ay-ay ay-f f-pau"},
//wifes
{"wifes","pau-w w-aa aa-iy iy-f f-s s-pau"},
//willow
{"willow","pau-w w-ih ih-l l-ao ao-uh uh-pau"},
{"wills","pau-w w-ih ih-l l-z z-pau"},
{"willy","pau-w w-ih ih-l l-iy iy-pau"},
{"willyum","pau-w w-ih ih-l l-y y-ah ah-m m-pau"},
{"wilma","pau-w w-ih ih-l l-m m-ah ah-pau"},
{"wilson","pau-w w-ih ih-l l-s s-ah ah-n n-pau"},
//window
{"window","pau-w w-ih ih-n n-d d-ao ao-uh uh-pau"},
//winnie
{"winnie","pau-w w-ih ih-ih ih-n n-iy iy-pau"},
//winnifred
{"winnifred","pau-w w-ih ih-ih ih-n n-ih ih-f f-r r-ih ih-d d-pau"},
//winston
{"winston","pau-w w-ih ih-ih ih-n n-s s-t t-ah ah-n n-pau"},
//winter
{"winter","pau-w w-ih ih-ih ih-n n-t t-er er-pau"},
//witch
{"witch","pau-w w-ih ih-ch ch-pau"},
//woman
{"woman","pau-w w-uh uh-m m-ah ah-n n-pau"},
//word
{"word","pau-w w-uh uh-r r-d d-pau"},
//work
{"work","pau-w w-uh uh-r r-k k-pau"},
//working
{"working","pau-w w-uh uh-r r-k k-ih ih-ng ng-pau"},
{"workman","pau-w w-uh uh-r r-k k-m m-ah ah-n n-pau"},
//workshop
{"workshop","pau-w w-uh uh-r r-k k-sh sh-aa aa-p p-pau"},
//world
{"world","pau-w w-er er-er er-l l-d d-d d-pau"},

//X-words
//xavier
//xena

//Y-words
//yacht
{"yacht","pau-y y-aa aa-aa aa-t t-pau"},
//year
{"year","pau-y y-ih ih-ih ih-r r-pau"},
//yearly
{"yearly","pau-y y-ih ih-ih ih-r r-l l-iy iy-pau"},
{"yodel","pau-y y-ao ao-uh uh-d d-ah ah-l l-pau"},
//you
{"you","pau-y y-uw uw-uw uw-pau"},
{"youth","pau-y y-uw uw-th th-pau"},

//Z-words
//zach
{"zach","pau-z z-ae ae-k k-pau"},
//zachary
{"zachary","pau-z z-ae ae-k k-uh uh-r r-iy iy-pau"},
//zara
{"zarahemla","pau-z z-ae ae-r r-ah ah-hh hh-iy iy-m m-l l-ah ah-pau"},
{"zeppelin","pau-z z-eh eh-p p-ih ih-l l-ih ih-n n-pau"},
//zero
{"zero","pau-z z-iy iy-iy iy-r r-ow ow-pau"},
//zoe
{"zoe","pau-z z-ao ao-uh uh-iy iy-pau"},
//zone
{"zone","pau-z z-ao ao-uh uh-n n-pau"},
//zoo
{"zoo","pau-z z-uw uw-pau"},

	
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
