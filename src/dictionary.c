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

//A-words
//a 
{"a","ey-ey ey-ey"}, 
//account
{"accountant","ah-k k-aa aa-uh uh-n n-t t-ah ah-n n-t"},
//activity
{"activity","ae-k k-t t-ih ih-ih ih-v v-ah ah-t t-iy iy-pau"},
//adventure
{"adventure","ae-d d-v v-eh eh-n n-ch ch-uh uh-r"},
//afternoon
{"afternoon","ae-ae ae-ae ae-f f-t t-er er-pau pau-er er-n n-uw uw-uw uw-n"},
//agatha
{"agatha","ae-g g-ah ah-th th-ah"},
//agent
{"agent","eh-iy iy-jh jh-ah ah-n n-t"},
//agree
{"agree","ah-g g-r r-iy"},
//agreement
{"agreement","ah-g g-r r-iy iy-m m-ah ah-n n-t"},
//airport
{"airport","eh-eh eh-r r-p p-ao ao-ao ao-r r-t"},
//alan
{"alan","ae-ae ae-l l-ah ah-n"}, 
//alans
{"alans","ae-ae ae-l l-ah ah-n n-z"},
//alarm
{"alarm","ah-l l-aa aa-r r-m"},
//alec
{"alec","ae-ae ae-l l-ih ih-k"},
//alex
{"alex","ae-ae ae-l l-ah ah-k k-s"},
//alexander
{"alexander","ae-ae ae-l l-ah ah-g g-z z-ae ae-n n-d d-uh uh-r"},
//alexanders
{"alexanders","ae-ae ae-l l-ih ih-g g-z z-ae ae-n n-d d-uh uh-r r-z"},
//alexs
{"alexs","ae-ae ae-l l-ah ah-k k-s s-ih ih-z"},
//alf
{"alf","ae-ae ae-l l-f"},
//alfred
{"alfred","ae-ae ae-l l-f f-r r-ah ah-d"},
//alfreds
{"alfreds","ae-ae ae-l l-f f-r r-ih ih-d d-z"},
//alice
{"alice","ae-ae ae-l l-ih ih-s"},
//alices
{"alices","ae-ae ae-l l-ih ih-s s-ah ah-z"},
//alison and allison
{"alison","ae-ae ae-l l-ih ih-s s-ah ah-n"},
//alisons and allisons
{"alisons","ae-ae ae-l l-ih ih-s s-ah ah-n n-z"},
//alister and allister
{"alister","ae-ae ae-l l-ih ih-s s-t t-uh uh-r"},
//all
{"all","ao-l l-pau"},
//allotment
{"allotment","ah-l l-aa aa-aa aa-t t-m m-ah ah-n n-t"},
//am
{"am","ae-m"}, 
//amazon
{"amazon","ae-ae ae-m m-ah ah-z z-aa aa-aa aa-n"},
//amber
{"amber","ae-ae ae-m m-b b-er er-pau"},
//ambulance
{"ambulance","ae-ae ae-m m-b b-y y-ah ah-l l-ah ah-n n-s"},
//amelia
{"amelia","ah-m m-iy iy-iy iy-l l-y y-ah"},
//amelias
{"amelias","ah-m m-iy iy-iy iy-l l-y y-ah ah-z"},
//amm
{"amm","ey-ey ey-ae ae-m m-m m-m"}, //A.M.
//amy
{"amy","eh-iy iy-m m-iy iy-pau"},
//and
{"and","ah-n n-d"},
//andora
{"andora","ae-ae ae-n d-ao ao-ao ao-r r-ah ah-pau"},
//andre
{"andre","aa-aa aa-n n-d d-r r-ey ey-ey"},
//andrea
{"andrea","ae-ae ae-n n-d d-r r-iy iy-iy iy-ah"},
//andreas
{"andreas","ae-ae aa-n n-d d-r r-eh eh-iy iy-iy iy-ah ah-z"},
//andrew
{"andrew","ae-ae ae-n n-d d-r r-uw uw-pau"},
//andrews
{"andrews","ae-ae ae-n n-d d-r r-uw uw-uw uw-z"},
//andy
{"andy","ae-ae ae-n n-d d-iy iy-pau"},
//andys
{"andys","ae-ae ae-n n-d d-iy iy-pau pau-iy iy-z"},
//angela
{"angela","ae-ae ae-n n-jh jh-ah ah-l l-ah"},
//angelina
{"angelina","ae-n n-jh jh-eh eh-l l-iy iy-n n-ah"},
//animal
{"animal","ae-n n-ah ah-m m-ah ah-l"},
//anna
{"anna","ae-ae ae-n n-ah"},
//annabel
{"annabel","ae-ae ae-n n-ah ah-b b-eh eh-eh eh-l"},
//anne
{"anne","ae-ae ae-n"},
//anniversary
{"anniversary","ae-ae ae-n n-ah ah-v v-er er-er er-s s-er er-iy iy-pau"},
//anthony
{"anthony","ae-ae ae-n n-th th-ao ao-n n-iy iy-iy"},
//{"anthony","ae-ae ae-n n-th th-ao ao-n n-iy iy-iy iy-z"},
//anti
{"anti","ae-n n-t t-iy"},
//appoint
{"appoint","ah-p p-ao ao-iy iy-n n-t"},
//appointment
{"appointment","pau-ah ah-p p-oy oy-oy oy-n n-t t-m m-ah ah-n n-t"},
//april
{"april","ey-ey ey-p p-r r-ah ah-l"},
//archery
{"archery","aa-r r-ch ch-uh uh-r r-iy"},
//archie
{"archie","aa-r r-ch ch-iy"},
//art
{"art","aa-aa aa-aa aa-r r-t"},
//arthur
{"arthur","aa-r r-th th-uh uh-r"},
//assessment
{"assessment","ah-s s-eh eh-eh eh-s s-m m-ah ah-pau pau-ah ah-n n-t"},
//attack
{"attack","ah-t t-ae ae-k"},
//aubrey
{"aubrey","ao-ao ao-b b-r r-iy iy-pau"},
//audrey
{"audrey","ao-ao ao-d d-r r-iy iy-pau"},
//{"audreys","ao-ao ao-uh uh-d d-r r-iy iy-z"},
//august
{"august","aa-aa aa-g g-ah ah-s s-t t-pau"},
//aunt
{"aunt","ae-ae ae-n n-t"},
//auntie and aunty
{"auntie","ae-ae ae-n n-t t-iy iy-pau"},
//aunts
{"aunts","ae-ae ae-n n-t t-s"},
//autumn
{"autumn","ao-t t-ah ah-m m-pau"},

 
//B-words
//baby
{"baby","b-eh eh-iy iy-b b-iy"},
//badminton 
{"badminton","b-ae ae-d d-m m-ih ih-n n-t t-aa aa-n"},
//bakery
{"bakery","b-eh eh-iy iy-k k-uh uh-r r-iy"},
//ball
{"ball","b-ao ao-l"},
//band
{"band","b-ae ae-n n-d"},
//bank
{"bank","b-ae ae-ae ae-ng ng-k"},
//banking
{"banking","b-ae ae-ae ae-ng ng-k k-ih ih-ng"},
//barber
{"barber","b-aa aa-aa aa-r r-b b-er er-pau"},
//barbars
{"barbers","b-aa  aa-aa aa-r r-b b-er er-z z-pau"},
//be
{"be","b-iy"},
//bed
{"bed","b-eh eh-d"},
//begins
{"begins","b-ih ih-g g-ih ih-n n-z"},
//beth
{"beth","b-eh eh-eh eh-th"},
//bethany
{"bethany","b-eh eh-eh eh-th th-ah ah-n n-iy iy-pau"},
//betsy
{"betsy","b-eh eh-eh eh-t t-s s-iy iy-pau"},
//betsys
{"betsys","b-eh eh-eh eh-t t-s s-iy iy-z z-pau"},
//betty
{"betty","b-eh eh-eh eh-t t-iy iy-pau"},
//bettys
{"betty","b-eh eh-eh eh-t t-iy iy-z z-pau"},
//big
//bike
{"bike","b-ay ay-ay ay-k"},
//billy
{"billy","b-ih ih-ih ih-l l-iy iy-pau"},
//bin
{"bin","b-ih ih-ih ih-n"},
//bird
{"bird","b-uh uh-r r-d"},
//birth
{"birth","b-uh uh-r r-th"},
//birthday
{"birthday","b-er er-er er-th th-d d-ey ey-ey ey-pau"},
//boat
{"boat","b-ao ao-uh uh-t"},
//book
{"book","b-uh uh-k"},
//bowls
{"bowls","b-ao ao-uh uh-l l-z"},
//box
{"box","b-aa aa-k k-s"},
//boxing
{"boxing","b-aa aa-aa aa-k k-s s-ih ih-ng"},
//break
{"break","b-r r-eh eh-iy iy-k"},
//breakfast
{"breakfast","b-r r-eh eh-eh eh-k k-f f-ah ah-s s-t t-pau"},
//british
{"british","b-r r-ih ih-t t-ih ih-sh"},
//brother
{"brother","b-r r-ah ah-dh dh-uh uh-r"},
//brothers
{"brothers","b-r r-ah ah-dh dh-uh uh-r r-z"},
//brunch
{"brunch","b-r r-r r-ah ah-n n-n n-ch ch-ch"},
//bus
{"bus","b-ah ah-ah ah-s s-s"},
//business
{"business","b-ih ih-z z-n n-ah ah-s"},
//buy
{"buy","b-aa aa-iy iy-pau"},
//by
{"by","b-aa aa-iy"},
//bye
{"bye","b-aa aa-iy"},

//C-words
//cabbie CABBIE  K AE1 B IY0
{"cabbie","k-ae ae-ae ae-b b-b b-iy iy-pau"},
//cafe
{"cafe","k-ah ah-f f-ey ey-ey"},
//calendar
{"calendar","k-ae ae-ae ae-l l-ah ah-n n-d d-er er-pau"},
//call
{"call","k-ao ao-l"},
//camp
{"camp","k-ae ae-m m-p"},
//camping
{"campsite","k-ae ae-m m-p p-s s-aa aa-iy iy-t t-s"},
//car
{"car","k-aa aa-aa aa-r"},
//card
{"card","k-aa aa-r r-d"},
//care
{"care","k-eh eh-r"},
//carol
{"carol","k-ae ae-r r-ah ah-l"},
//caroline
{"caroline","k-eh eh-r r-ah ah-l l-aa aa-iy iy-n"},
{"carolines","k-eh eh-r r-ah ah-l l-aa aa-iy iy-n n-z"},
//cat
{"cat","k-ae ae-t"},
//cath
{"cath","k-ae ae-ae ae-th th-th"},
//catherine and katherine
{"catherine","k-ae ae-ae ae-th th-er er-ah ah-n"},
//{"katherine","k-ae ae-ae ae-th th-er er-ih ih-n"},
//certificate
{"certificate","s-uh uh-r r-t t-ih ih-f f-ih ih-k k-ah ah-t"},
//charles
{"charles","ch-aa aa-aa aa-r r-l l-z"},
//charlotte
{"charlotte","sh-aa  aa-aa aa-r r-l l-ah ah-t"},
//chauffeur
{"chauffeur","sh-ao ao-uh uh-f f-uh uh-r"},
//check
{"check","ch-eh eh-k"},
//chemist
{"chemist","k-eh eh-m m-ih ih-s s-t t-pau"},
//child
{"child","ch-aa aa-iy iy-l l-d"},
//children
{"children","ch-ih ih-l l-d d-r r-ah ah-n"},
//chips
{"chips","ch-ih ih-ih ih-p p-s s-pau"}, //dog name - walk chips
//choir
{"choir","k-w w-aa aa-iy iy-uh uh-r"},
//chore
{"chore","ch-ao ao-ao ao-r r-pau"},
//christie
{"christie","k-r r-ih ih-s s-t t-iy"},
//christina
{"christina","k-r r-ih ih-s s-t t-iy iy-n n-ah"},
//christine
{"christine","k-r r-ih ih-s s-t t-iy iy-n"},
//christmas
{"christmas","k-r r-ih ih-ih ih-s s-m m-ah ah-s"},
//church
{"church","ch-er er-er er-ch"},
//cinema
{"cinema","s-ih ih-ih ih-n n-ah ah-m m-ah ah-pau"},
//circle
{"circle","s-uh uh-r r-k k-ah ah-l"},
//circus
{"circus","s-uh uh-r r-k k-ah ah-s"},
//city
{"city","s-ih ih-t t-iy"},
//claire
{"claire","k-l l-eh eh-eh eh-r"},
//clara
{"clara","k-l l-ae ae-ae ae-r r-ah"},  //aunt clara
//clarence
{"clarence","k-l l-eh eh-eh eh-r r-ah ah-n n-s"},
//clarissa
{"clarissa","k-l l-er er-ih ih-ih ih-s s-ah"},
//class
{"class","k-l l-ae ae-s"},
//claude
{"claude","k-l l-ao ao-ao ao-d"},
//clean
{"clean","k-l l-iy iy-n"},
//cleaner
{"cleaner","k-l l-iy iy-n n-uh uh-r"},
//climbing
{"climbing","k-l l-aa aa-iy iy-m m-ih ih-ng"},
//clinic
{"clinic","k-l l-ih ih-ih ih-n n-ih ih-k"},
//clock
{"clock","k-l l-aa aa-k"},
//clocks
{"clocks","k-l l-aa aa-k k-s"},
//close
{"close","k-l l-ao ao-uh uh-s"},
//closed
{"closed","k-l l-ao ao-uh uh-z z-d"},
//club
{"club","k-l l-ah ah-b"},
//coach
{"coach","k-ow ow-ow ow-ch ch-ch"},
//coast
{"coast","k-ao ao-uh uh-s s-t"},
//code
{"code","k-ao ao-uh uh-d"},
//coffee
{"coffee","k-aa aa-f f-iy"},
//collection
{"collection","k-ah ah-l l-eh eh-k k-sh sh-ah ah-n"},
//college
{"college","k-aa aa-l l-ih ih-jh"},
//coming
{"coming","k-ah ah-ah ah-m m-ih ih-ng"},
//computer
{"computer","k-ah ah-m m-p p-y y-uw uw-t t-uh uh-r"},
//concert
{"concert","k-aa aa-n n-s s-uh uh-r r-t"},
//contact
{"contact","k-aa aa-n n-t t-ae ae-k k-t"},
//cottage
{"cottage","k-aa  aa-aa aa-t t-ah ah-jh"},
//court
{"court","k-ao ao-r r-t"},
//cousin
{"cousin","k-ah ah-z z-ah ah-n"},

//crispin
{"crispin","k-r  r-ih ih-ih ih-s s-p p-ih ih-n n-n"},
//crispins (saint day)
{"crispins","k-r  r-ih ih-ih ih-s s-p p-ih ih-ih ih-n n-n n-z"},  //saint day
//crook
{"crook","k-r r-uh uh-k"},
//crooks
{"crooks","k-r r-uh uh-k k-s"},
//cyber
{"cyber","s-ay ay-ay ay-b b-er er-pau"},
//cycle
{"cycle","s-aa aa-iy iy-k k-ah ah-l"},

//D-words
//dad
{"dad","d-ae ae-ae ae-d"},
//dads
{"dads","d-ae ae-ae ae-d d-z"},
//daisy
{"daisy","d-ey ey-ey ey-z z-iy iy-pau"},
//dan
{"dan","d-ae ae-n"},
//dance
{"dance","d-ae ae-n n-s"},
//daniel
{"daniel","d-ae ae-ae ae-n n-y y-ah ah-l"},
//danielle
{"danielle","d-ae ae-ae ae-n n-iy iy-eh eh-eh eh-l"},
//danny
{"danny","d-ae ae-ae ae-n n-iy"},
//date
{"date","d-ey ey-ey ey-t"},
//dates
{"dates","d-ey ey-ey ey-t t-s s-pau"},
//daughter
{"daughter","d-ao ao-ao ao-t t-er er-pau"},
//daughters
{"daughter","d-ao ao-ao ao-t t-er er-z"},
//dave
{"dave","d-ey ey-ey ey-v"},
//david
{"david","d-ey ey-ey ey-v v-ih ih-d"},
//davids
{"davids","d-ey ey-ey ey-v v-ih ih-d d-z"},
//day
{"day","d-d d-ey ey-ey ey-pau"},
//days
{"days","d-eh eh-iy iy-z"},
//dead
{"dead","d-eh eh-d"},
//deadline
{"deadline","d-eh eh-eh eh-d d-l l-ay ay-ay ay-n"},
//dealer
{"dealer","d-iy iy-l l-uh uh-r"},
//death
{"death","d-eh eh-th"},
//debbie or debby
{"debbie","d-eh eh-eh eh-b b-iy iy-pau"},
//{"debby","d-eh eh-eh eh-b b-iy iy-pau"},
//deborah
{"deborah","d-eh eh-eh eh-b b-er er-ah ah-pau"},
//debs
{"debs","d-eh eh-b b-z"},
//december
{"december","d-ih ih-s s-eh eh-eh eh-m m-b b-er er-pau"},
//decorate
{"decorate","d-eh eh-k k-uh uh-r r-eh eh-iy iy-t"},
//decorating
{"decorating","d-eh eh-k k-uh uh-r r-eh eh-iy iy-t t-ih ih-ng"},
//delivery
{"delivery","d-ih ih-l l-ih ih-ih ih-v v-er er-iy iy-pau"},
//dentist
{"dentist","d-eh eh-eh eh-n n-t t-ah ah-s s-t"},
//development
{"development","d-ih ih-v v-eh eh-l l-ah ah-p p-m m-ah ah-n n-t"},
//diana
{"diana","d-aa aa-iy iy-ae ae-n n-ah"},
//diary
{"diary","d-aa aa-iy iy-uh uh-r r-iy"},
//dinner
{"dinner","d-ih ih-ih ih-n n-er er-pau"},
//{"diphone","d-ih ih-ih ih-f f-ow ow-ow ow-n n-pau"}, //bad pronouciation
//do
{"do","d-uw"},
//doctor
{"doctor","d-aa aa-aa aa-k k-t t-er er-pau"},
//doctors
{"doctors","d-aa aa-aa aa-k k-t t-er r-z z-pau"},
//dog
{"dog","d-ao ao-g"},
//don
{"don","d-aa aa-aa aa-n"},
//donald
{"donald","d-aa aa-aa aa-n n-ah ah-l l-d"},
//donalds
{"donalds","d-aa aa-aa aa-n n-ah ah-l l-d d-z"},
//donkey
{"donkey","d-aa aa-ng ng-k k-iy"},
//dons
{"dons","d-aa aa-aa aa-n n-z"},
//dora
{"dora","d-ao ao-ao ao-r r-ah ah-pau"},
//down
{"down","d-aa aa-uh uh-n"},
//driver
{"driver","d-r r-ay ay-ay ay-v v-er er-pau"},
//dustbin
{"dustbin","d-ah ah-ah ah-s s-t t-b b-ih ih-n n-pau"},

//E-words
//ear
{"ear","iy-iy iy-r"},
//early
{"early","uh-r r-l l-iy"},
//east
{"east","iy-s s-t"},
//easter
{"easter","iy-iy iy-s s-t t-er er-pau"},
//education
{"education","eh-jh jh-ah ah-k k-eh eh-iy iy-sh sh-ah ah-n"},
//eight
{"eight","ey-ey ey-t"},
//eighteen
{"eighteen","eh-ey ey-t t-iy iy-iy iy-n n-pau"},
//eighteenth
{"eighteenth","ey-ey ey-t t-iy iy-iy iy-n n-th th-pau"},
//eighth
{"eighth","eh-ey ey-t t-th th-pau"},
//eightieth (birthday)
{"eightieth","ey-ey ey-t t-iy iy-ih ih-th"},
//eighty
{"eighty","eh-iy iy-t t-iy"},
//electric
{"electric","ih-l l-eh eh-k k-t t-r r-ih ih-k"},
//electrician
{"electrician","ih-ih ih-l l-eh eh-k k-t t-r r-ih ih-ih ih-sh sh-ah ah-n"},
//electricity
{"electricity","ih-l l-eh eh-k k-t t-r r-ih ih-s s-ah ah-t t-iy"},
//eleven
{"eleven","ih-l l-eh eh-eh eh-v v-ah ah-n"},
//eleventh
{"eleventh","ih-l l-eh eh-eh eh-v v-ah ah-n n-th th-pau"},
//elisha
{"elisha","eh-eh eh-l l-ih ih-sh sh-ah ah-pau"},
//eliza
{"eliza","ih-l l-ay ay-ay ay-z z-ah ah-pau"},
//elizabeth
{"elizabeth","ih-l l-ih ih-ih ih-z z-ah ah-b b-ah ah-th"},
//elizabeths
{"elizabeths","ih-l l-ih ih-ih ih-z z-ah ah-b b-ah ah-th th-s"},
//elizas
{"elizas","ih-l l-ay ay-ay ay-z z-ah ah-z"},
//ella
{"ella","eh-l l-ah"},
//elliot or elliott
{"elliot","eh-eh eh-l l-iy iy-ah ah-t"},
//{"elliott","eh-eh eh-l l-iy iy-ah ah-t"},
//elton
{"elton","eh-l l-t t-ah ah-n"},
//emma
{"emma","eh-eh eh-m m-ah"},
//end
{"end","eh-n n-d"},
//ends
{"ends","eh-n n-d d-z"},
//engage
{"engage","eh-n n-g g-eh eh-iy iy-jh"},
{"engagement","eh-n n-g g-eh eh-iy iy-jh jh-m m-ah ah-n n-t"},
//evan
{"evan","eh-eh eh-v v-ah ah-n"},
//evening
{"evening","iy-iy iy-v v-n n-ih ih-ng ng-pau"},
//event
{"event","ih-v v-eh eh-eh eh-n n-t"},
//events
{"events","ih-v v-eh eh-n n-t t-z z-pau"},
//eye
{"eye","aa-iy"},

//F-words
//family
{"family","f-ae ae-ae ae-m m-ah ah-l l-iy iy-pau"},
//farm
{"farm","f-aa aa-aa aa-r r-m"},
//father
{"father","f-aa aa-aa aa-dh dh-er er-pau"},
//fathers
{"fathers","f-aa aa-aa aa-dh dh-er er-pau pau-er er-z z-pau"},
//fawkes
{"fawkes","f-ao ao-ao ao-k k-s"},
//fear
{"fear","f-ih ih-r"},
//february
{"february","f-eh eh-eh eh-b b-y y-ah ah-w w-eh eh-eh eh-r r-iy iy-pau"},
//feed
{"feed","f-iy iy-d"},
//festival
{"festival","f-eh eh-s s-t t-ah ah-v v-ah ah-l"},
//festive
{"festive","f-eh eh-s s-t t-ih ih-v"},
//fifteen
{"fifteen","f-ih ih-ih ih-f f-t t-iy iy-iy iy-n n-pau"},
//fifteenth
{"fifteenth","f-ih ih-f f-t t-iy iy-iy iy-n n-th th-pau"},
//fifth
{"fifth","f-ih ih-ih ih-f f-th th-pau"},
//fifty
{"fifty","f-ih ih-ih ih-f f-t t-iy iy-pau"},
//film
{"film","f-ih ih-ih ih-l l-m m-pau"},
//fiona
{"fiona","f-iy iy-ow ow-ow ow-n n-ah ah-pau"},
//fire
{"fire","f-aa aa-iy iy-uh uh-r"},
//fireworks
{"fireworks","f-aa aa-iy iy-r r-w w-uh uh-r r-k k-s"},
//first
{"first","f-er er-er er-s s-t t-pau pau-t"},
//fish
{"fish","f-ih ih-ih ih-sh"},
//fishing
{"fishing","f-ih ih-sh sh-ih ih-ng"},
//five
{"five","f-ay ay-ay ay-v"},
//fix
{"fix","f-ih ih-k k-s"},
//food
{"food","f-uw uw-d"},
//fools april
{"fools","f-uw uw-l l-z"},
//football
{"football","f-uh uh-t t-b b-ao ao-l"},
//forty
{"forty","f-ao ao-ao ao-r r-t t-iy iy-pau"},
//forward  -clocks forward
{"forward","f-ao ao-r r-w w-uh uh-r r-d"},
//four
{"four","f-ao ao-ao ao-r"},
//fourteen
{"fourteen","f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-pau"},
//fourteenth
{"fourteenth","f-ao ao-ao ao-r r-t t-iy iy-iy iy-n n-th th-pau pau-th"},
//fourth
{"fourth","f-ao ao-ao ao-r r-th th-pau"},
//frances
{"frances","f-r r-ae ae-ae ae-n n-s s-ih ih-s"},
//francesca
{"francesca","f-r r-ae ae-n n-ch ch-eh eh-eh eh-s s-k k-ah"},
//francis
{"francis","f-r r-ae ae-ae ae-n n-s s-ah ah-s"},
//frank
{"frank","f-r r-ae ae-ae ae-ng ng-k"},
//frankenstein
{"frankenstein","f-r r-ae ae-ng ng-k k-ah ah-n n-s s-t t-aa aa-iy iy-n"},
//fred
{"fred","f-f f-r r-eh eh-eh eh-d d-pau"},
//freddie and freddy
{"freddie","f-r r-eh eh-eh eh-d d-iy iy-pau"},
//{"freddy","f-r r-eh eh-eh eh-d d-iy iy-pau"},
//frederic
{"frederic","f-r r-eh eh-d d-r r-ih ih-k"},
//frederick
{"frederick","f-r r-eh eh-eh eh-d d-er er-ih ih-k"},
//freds
{"freds","f-r r-eh eh-eh eh-d d-z z-pau"},
//freeze (anti)
{"freeze","f-r r-iy iy-z"},
//{"freezer","f-r r-iy iy-z z-uh uh-r"},
//freya
{"freya","f-r r-eh eh-iy iy-ah"},
//friday
{"friday","f-r r-ay ay-ay ay-d d-iy iy-pau"},
//friend
{"friend","f-r r-eh eh-eh eh-n n-d"},
//frost
{"frost","f-r r-ao ao-s s-t"},
//funeral
{"funeral","f-y y-uw uw-uw uw-n n-er er-ah ah-l"},

//G-words

//gale
{"gale","g-ey ey-ey ey-l"},
//gallery
{"gallery","g-ae ae-ae ae-l l-er er-iy iy-pau"},
//game
{"game","g-eh eh-iy iy-m"},
//garage
{"garage","g-uh uh-r r-aa aa-zh"},
//garbage
{"garden","g-aa aa-aa aa-r r-d d-ah ah-n"},
//garden
{"garden","g-aa aa-r r-d d-ah ah-n"},
//gas
{"gas","g-ae ae-ae ae-s s-s"},
//gate
{"gate","g-eh eh-iy iy-t"},
//geoff
{"geoff","jh-eh eh-eh eh-f f-pau"},
//geoffrey
{"geoffrey","jh-eh eh-eh eh-f f-r r-iy iy-pau"},
//george
{"george","jh-ao ao-ao ao-r r-jh"},
//georges  saint day
{"georges","jh-ao ao-ao ao-r r-jh jh-ah ah-z z-pau"},
//georgina
{"georgina","jh-ao ao-ao ao-r r-jh jh-iy iy-n n-ah ah-pau"},
//glasses
{"glasses","g-l l-ae ae-ae ae-s s-ah ah-z"},
//go
{"go","g-ao ao-uh"},
//golf
{"golf","g-aa aa-l l-f"},
//good
{"good","g-uh uh-d"},
//grand
{"grand","g-r r-ae ae-n n-d"},
{"grandchild","g-r r-ae ae-n n-d d-ch ch-aa aa-iy iy-l l-d"},
{"grandchildren","g-r r-ae ae-n n-ch ch-ih ih-l l-d d-r r-ah ah-n"},
//grandad
{"grandad","g-r r-ae ae-ae ae-n n-d d-ae ae-ae ae-d"},
{"granddaughter","g-r r-ae ae-n n-d d-ao ao-t t-uh uh-r"},
{"grandfather","g-r r-ae ae-n n-d d-f f-aa aa-dh dh-uh uh-r"},
{"grandma","g-r r-ae ae-m m-aa"},
{"grandmother","g-r r-ae ae-n n-d d-m m-ah ah-dh dh-uh uh-r"},
{"grandpa","g-r r-ae ae-n n-d d-p p-aa"},
{"grandparent","g-r r-ae ae-n n-d d-p p-eh eh-r r-ah ah-n n-t"},
{"grandparents","g-r r-ae ae-n n-d d-p p-eh eh-r r-ah ah-n n-t t-s"},
{"grandson","g-r r-ae ae-n n-d d-s s-ah ah-n"},
//granny and grannie
{"granny","g-r r-ae ae-ae ae-n n-iy iy-pau"},
//guy (fawkes day)
{"guy","g-ay ay-ay ay-ay ay-pau"},

//H-words
//hairdresser
{"hairdresser","hh-eh eh-eh eh-r r-d d-r r-eh eh-eh eh-s s-er er-pau"},
//hairdressing
{"hairdressing","hh-eh eh-eh eh-r r-d d-r r-eh eh-eh eh-s s-ih ih-ng"},
//halloween
{"halloween","hh-ae ae-ae ae-l l-ah ah-w w-iy iy-iy iy-n"},
//hannah or hanna
//{"hanna","hh-ae ae-ae ae-n n-ah"},
{"hannah","hh-ae ae-ae ae-n n-ah"},
//harold
{"harold","hh-eh eh-eh eh-r r-ah ah-d"},
//{"harolds","hh-eh eh-eh eh-r r-ah ah-d d-z"},
//harry
{"harry","hh-eh eh-eh eh-r r-iy"},
//have
{"have","hh-ae ae-v"},
//head
{"head","hh-eh eh-d"},
//headache
{"headache","hh-eh eh-d d-eh eh-iy iy-k"},
//health
{"health","hh-eh eh-eh eh-l l-th"},
//hear
{"hear","hh-iy iy-r"},
//heating
{"heating","hh-iy iy-iy iy-t t-ih ih-ng"},
//hector
{"hector","hh-eh eh-eh eh-k k-t t-er er-pau"},
//helen
{"helen","hh-eh eh-eh eh-l l-ah ah-n"},
//hello
{"hello","hh-ah ah-l l-ow ow-ow ow-pau"},
//help
{"help","hh-eh eh-eh eh-l l-p"},
//hen
{"hen","hh-eh eh-n"},
//henry
{"henry","hh-eh eh-n n-r r-iy"},
//herbert
{"herbert","hh-er er-er er-b b-t"},
//{"herbert","hh-er er-er er-b b-t t-s"},
//high
{"high","hh-aa aa-iy"},
//hobby
{"hobby","hh-aa aa-b b-iy"},
//hockey
{"hockey","hh-aa aa-aa aa-k kiy iy-pau"},
//holiday
{"holiday","hh-aa aa-aa aa-l l-ah ah-d d-ey ey-ey"},
//home
{"home","hh-ow ow-ow ow-m m-pau"},
//honor
{"honor","aa-n n-uh uh-r"},
//hospital
{"hospital","hh-aa aa-aa aa-s s-p p-ih ih-ih ih-t t-ah ah-l"},
//hotel
{"hotel","hh-ow ow-t t-eh eh-eh eh-l"},
//hour
{"hour","aw-aw aw-r r-pau"},
//hours
{"hours","aw-aw aw-r r-z"},
//house
{"house","hh-hh hh-aw aw-aw aw-s s-s"},
//humanoid
{"humanoid","hh-y y-uw uw-uw uw-m m-ah ah-n n-oy oy-oy oy-d"},
//humphrey
{"humphrey","hh-ah  ah-ah ah-m m-f f-r r-iy iy-pau"},
//hundred
{"hundred","hh-ah ah-n n-d d-r r-ah ah-d"},
//hundredth
{"hundredth","hh-ah ah-n n-d d-r r-ah ah-d d-th"},
//husband
{"husband","hh-ah  ah-ah ah-z z-b b-ah ah-n n-d"},
//husbands
{"husbands","hh-ah  ah-ah ah-z z-b b-ah ah-n n-d d-z"},

//I-words
//i
{"i","ay-ay ay-pau"},
//ian
{"ian","iy-iy iy-ah ah-n"},
//in
{"in","ih-n"},
//industry
{"industry","ih-n n-d d-ah ah-s s-t t-r r-iy"},
//information
{"information","ih-n n-f f-uh uh-r r-m m-eh eh-iy iy-sh sh-ah ah-n"},
//inn
{"inn","ih-ih ih-ih ih-n n-pau"},
//insurance
{"insurance","ih-n n-sh sh-uh uh-r r-ah ah-n n-s"},
//inter
{"inter","ih-n n-t t-uh uh-r"},
//investment
{"investment","ih-n n-v v-eh eh-s s-t t-m m-ah ah-n n-t"},
//invoice
{"invoice","ih-n n-v v-ao ao-iy iy-s"},
//invoke
{"invoke","ih-n n-v v-ao ao-uh uh-k"},
//irene
{"irene","ay-r r-iy iy-iy iy-n"},
//is
{"is","pau-ih ih-z"},
//isaac
{"isaac","ih-ih ih-s s-ah ah-k"},
//isaacs
{"isaacs","ih-ih ih-s s-ah ah-k k-s"},
//isabel or isabelle
{"isabel","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l"},
//isabella
{"isabella","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-ah ah-pau"},
//issabellas
{"isabellas","ih-ih ih-z z-ah ah-b b-eh eh-eh eh-l l-ah ah-z"},
//island
{"island","aa-iy iy-l l-ah ah-n n-d"},
//ivan
{"ivan","ay-ay ay-v v-ah ah-n"},
//ivans
{"ivans","ay-ay ay-v v-ah ah-n n-z"},
//ivy
{"ivy","ay-ay ay-v v-iy iy-pau"},

//J-words
//jack
{"jack","jh-ae ae-ae ae-k"},
//jackie or jacky
{"jackie","jh-ae ae-ae ae-k k-iy iy-pau"},
//{"jacky","jh-ae ae-ae ae-k k-iy"},
//jacks
{"jacks","jh-ae ae-ae ae-k k-s"},
//jacob
{"jacob","jh-eh ey-ey ey-k k-ah ah-b"},
//jacobs
{"jacobs","jh-eh ey-ey ey-k k-ah ah-b b-z"},
//jacqueline
{"jacqueline","jh-ae ae-ae ae-k k-w w-ah ah-l l-ih ih-n"},
//james
{"james","jh-ey ey-ey ey-m m-z"},
//jamie
{"jamie","jh-ey ey-ey ey-m m-iy iy-pau"},
//january
{"january","jh-ae ae-ae ae-n n-y y-uw uw-eh eh-eh eh-r r-iy iy-pau"},
//jason
{"jason","jh-ey ey-ey ey-s s-ah ah-n"},
//jeff jeffery same as geoff and geoffrey
//{"jeff","jh-eh eh-eh eh-f"},
//{"jeffrey","jh-eh eh-eh eh-f f-r r-iy iy-pau"},
//jet
{"jet","jh-eh eh-t"},
//jethro
{"jethro","jh-eh eh-th th-r r-ao ao-uh"},
//jeweler
{"jeweler","jh-uw uw-ah ah-l l-uh uh-r"},
{"jewelers","jh-uw uw-ah ah-l l-uh uh-r r-z"},
//job
{"job","jh-aa aa-aa aa-b b-b"},
//john
{"john","jh-aa aa-aa aa-n"},
//johns
{"johns","jh-aa aa-aa aa-n n-z"},
//journey
{"journey","jh-er er-er er-n n-iy iy-pau"},
//joy
{"joy","jh-ao ao-iy"},
//july
{"july","jh-uw uw-uw uw-l l-ay ay-ay ay-pau"},
//june
{"june","jh-uw uw-uw uw-n n-pau"},

//K-words
//karen or karren
{"karen","k-eh eh-eh eh-r r-ah ah-n"},
//kate
{"kate","k-ey ey-ey ey-t"},
//ken
{"ken","k-eh eh-eh eh-n"},
//kennel
{"kennel","k-eh eh-n n-ah ah-l"},
{"kennels","k-eh eh-n n-ah ah-l l-z"},
//kenneth
{"kenneth","k-eh eh-n n-ih ih-th"},
//king
{"king","k-ih ih-ng"},
//kingdom
{"kingdom","k-ih ih-ng ng-d d-ah ah-m"},

//L-words
//laboratory
{"laboratory","l-ae ae-b b-r r-ah ah-t t-ao ao-r r-iy"},
//large
{"large","l-aa aa-r r-jh"},
//last e.g last day of summer
{"last","l-ae ae-s s-t"},
//laura
{"laura","l-ao ao-r r-ah"},
{"laurel","l-ao ao-r r-ah ah-l"},
{"laurence","l-ao ao-r r-ah ah-n n-s"},
{"lavender","l-ae ae-v v-ah ah-n n-d d-uh uh-r"},
//lawrence
{"lawrence","l-ao ao-r r-ah ah-n n-s"},
//lawyer
{"lawyer","l-ao ao-y y-uh uh-r"},

//leave
{"leave","l-iy iy-v"},
//leaving
{"leaving","l-iy iy-v v-ih ih-ng"},
//lecture
{"lecture","l-eh eh-eh eh-k k-ch ch-er er-pau"},
//leo
{"leo","l-iy iy-ao ao-uh"},
//lesson
{"lesson","l-eh eh-s s-ah ah-n"},
{"lester","l-eh eh-s s-t t-uh uh-r"},
//library book
{"library","l-aa aa-iy iy-b b-r r-eh eh-r r-iy"},
//license tv
{"license","l-aa aa-iy iy-s s-ah ah-n n-s"},
//lift -car lift
{"lift","l-ih ih-ih ih-f f-t"},
//lily or lilliy
{"lily","l-ih ih-ih ih-l l-iy iy-pau"},
//line
{"line","l-aa aa-iy iy-n"},
//linux
{"linux","l-ih ih-ih ih-n n-ah ah-k k-s"},
//location
{"location","l-ao ao-uh uh-k k-eh eh-iy iy-sh sh-ah ah-n"},
//lock
{"lock","l-aa aa-k"},
{"lockup","l-aa aa-k k-ah ah-p"},
{"locomotive","l-ao ao-uh uh-k k-ah ah-m m-ao ao-uh uh-t t-ih ih-v"},

//lodge
{"lodge","l-aa aa-jh"},
//long
{"long","l-ao ao-ng"},

//look
{"look","l-uh uh-k"},
//louisa
{"louisa","l-uw uw-iy iy-iy iy-z z-ah ah-pau"},
//low
{"low","l-ao ao-uh"},
//luca
{"luca","l-uw uw-k k-ah ah-pau"},
{"lucas","l-uw uw-k k-ah ah-s"},
//lunch
{"lunch","l-ah ah-ah ah-n n-ch ch-pau"},

//M-words
//madeline
{"madeline","m-ae ae-ae ae-d d-ah ah-l l-ih ih-n"},
//magazine
{"magazine","m-ae ae-g g-ah ah-z z-iy iy-n"},
{"maggie","m-ae ae-g g-iy"},
{"magic","m-ae ae-jh jh-ih ih-k"},
{"magician","m-ah ah-jh jh-ih ih-sh sh-ah ah-n"},
{"magistrate","m-ae ae-jh jh-ah ah-s s-t t-r r-eh eh-iy iy-t"},
{"magistrates","m-ae ae-jh jh-ih ih-s s-t t-r r-eh eh-iy iy-t t-s"},
//maintenance
{"maintenance","m-ey ey-ey ey-n n-t t-ah ah-n n-ah ah-n n-s s-s"},
//man
{"man","m-ae ae-n"},
//management
{"management","m-ae ae-ae ae-n n-ah ah-jh jh-m m-ah ah-n n-t"},
//many
{"many","m-eh eh-n n-iy"},
//march
{"march","m-aa aa-aa aa-r r-ch ch-pau"},
{"marie","m-uh uh-r r-iy"},
{"marigold","m-eh eh-r r-ah ah-g g-ao ao-uh uh-l l-d"},
{"marina","m-uh uh-r r-iy iy-n n-ah"},
//marine
{"marine","m-uh uh-r r-iy iy-n"},
//marjorie
{"marjorie","m-aa aa-r r-jh jh-uh uh-r r-iy"},
{"mark","m-aa aa-r r-k"},
//market
//mary
{"mary","m-eh eh-eh eh-r r-iy iy-pau"},
//marys
{"marys","m-eh eh-eh eh-r r-iy iy-z"},
//master
{"master","m-ae ae-ae ae-s s-t t-er er-pau"},
//mat
//matt
{"matt","m-ae ae-ae ae-t"},
//matthew
{"matthew","m-ae ae-ae ae-th th-y y-uw uw-pau"},
//matthews
{"matthews","m-ae ae-ae ae-th th-y y-uw uw-z"},
//matthias
{"matthias","m-ah ah-th th-ay ay-ay ay-ah ah-s"},
//maurice
{"maurice","m-ao ao-r r-iy iy-s"},
//may
{"may","m-m m-ey ey-ey ey-pau"},
//me
{"me","m-iy"},
//meal
{"meal","m-iy iy-iy iy-l l-pau"},
//mechanic
{"mechanic","m-ah ah-k k-ae ae-n n-ih ih-k"},
//medical
{"medical","m-eh eh-eh eh-d d-ah ah-k k-ah ah-l"},
//meet
{"meet","m-iy iy-iy iy-t"},
//meeting
{"meeting","m-iy iy-iy iy-t t-ih ih-ng"},
{"member","m-eh eh-m m-b b-uh uh-r"},
{"members","m-eh eh-m m-b b-uh uh-r r-z"},
//memorandum
{"memorandum","m-eh eh-eh eh-m m-er er-ae ae-ae ae-n n-d d-ah ah-m"},
//message
{"message","m-eh eh-s s-ah ah-jh"},
//midnight
{"midnight","m-ih ih-d d-n n-aa aa-iy iy-t"},
//mike
{"mike","m-aa aa-iy iy-k"},
//minder
{"minder","m-aa aa-iy iy-n n-d d-uh uh-r"},
//mini
{"mini","m-ih ih-ih ih-n n-iy iy-iy iy-pau"},
//miriam
{"miriam","m-ih ih-r r-iy iy-ah ah-m"},
//monday
{"monday","m-ah ah-ah ah-n n-d d-iy iy-pau"},
//monster
{"monster","m-aa aa-n n-s s-t t-uh uh-r"},
//month
{"month","m-ah ah-n n-th"},
//morning
{"morning","m-ao ao-ao ao-r r-n n-ih ih-ng"},
//mother
{"mother","m-ah ah-ah ah-dh dh-er er-pau"},
//mothers
{"mothers","m-ah ah-ah ah-dh dh-er er-z"},
//motorcycle
{"motorcycle","m-ow ow-ow ow-t t-er er-s s-ay ay-ay ay-k k-ah ah-l"},
//move
{"move","m-uw uw-v"},
{"moving","m-uw uw-v v-ih ih-ng"},
//movie
{"movie","m-uw uw-uw uw-v v-iy iy-pau"},
//muhammad
{"muhammad","m-uh uh-hh hh-aa aa-m m-ah ah-d"},
//mum
{"mum","m-ah ah-ah ah-m"},
//mums
{"mums","m-ah ah-ah ah-m m-z"},
//music
{"music","m-y y-uw uw-uw uw-z z-ih ih-k"},
//my
{"my","m-ay ay-ay"},

//N-words
//naomi
{"naomi","n-ey ey-ow ow-ow ow-m m-iy iy-pau"},
//nat
{"nat","n-ae ae-t"},
//natalie
{"natalie","n-ae ae-t t-ah ah-l l-iy"},
//natasha
{"natasha","n-ah ah-t t-aa aa-sh sh-ah"},
//nathan
{"nathan","n-eh eh-iy iy-th th-ah ah-n"},
{"nathaniel","n-ah ah-th th-ae ae-n n-y y-ah ah-l"},
{"nation","n-eh eh-iy iy-sh sh-ah ah-n"},
{"national","n-ae ae-sh sh-ah ah-n n-ah ah-l"},

//neighbour
{"neighbour","n-eh eh-iy iy-b b-uh uh-r"},
//nephew
{"nephew","n-eh eh-f f-y y-uw"},
//ness
{"ness","n-eh eh-s"},
//netball 
{"net","n-eh eh-t t-b b-ao ao-l"},
//netflix
{"netflix","n-eh eh-eh eh-t t-f f-l l-ih ih-ih ih-k k-k"},
//new
{"new","n-uw uw-uw"},
//news
{"news","n-uw uw-z"},
//newspaper
{"newspaper","n-uw uw-z z-p p-eh eh-iy iy-p p-uh uh-r"},
//niece
{"niece","n-iy iy-s"},
//night
{"night","n-aa aa-iy iy-t"},
//nine
{"nine","n-ay ay-ay ay-n"},
//nineteen
{"nineteen","n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-pau"},
//nineteenth
{"nineteenth","n-ay ay-ay ay-n n-t t-iy iy-iy iy-n n-th th-pau pau-th"},
//ninetieth
{"ninetieth","n-aa aa-iy iy-n n-t t-iy iy-ih ih-th"},
//ninety
{"ninety","n-aa aa-iy iy-n n-t t-iy"},
//ninth
{"ninth","n-ay ay-ay ay-n n-th th-pau"},
//no
{"no","n-ao ao-uh"},
//noah
{"noah","n-ao ao-uh uh-ah"},
//norman
{"norman","n-ao ao-r r-m m-ah ah-n"},
//normans
{"normans","n-ao ao-r r-m m-ah ah-n n-z"},
//north
{"north","n-ao ao-r r-th th-pau"},
{"northumbria","n-ao ao-r r-th th-ah ah-m m-r r-iy iy-ah"},
//not
{"not","n-aa aa-t"},
//notable
{"notable","n-ao ao-uh uh-t t-ah ah-b b-ah ah-l"},
//november
{"november","n-ow ow-v v-eh eh-eh eh-m m-b b-er er-pau"},
//now
{"now","n-aw aw-aw aw-pau"},
//nurse
{"nurse","n-uh uh-r r-s"},
//nursery
{"nursery","n-er er-er er-s s-er er-iy"},

//O-words
//o
{"o","ao-uh uh-ao ao-uh"},
//october
{"october","aa-k k-t t-ow ow-ow ow-b b-er"},
//of
{"of","ah-v"},
{"off","ao-f"},
{"offer","ao-f f-uh uh-r"},
//office
{"office","ao-ao ao-f f-ah ah-s"},
//oliver
{"oliver","aa-aa aa-l l-ih ih-v v-er"},
//olivers
{"oliver","aa-aa aa-l l-ih ih-v v-er er-z"},
//olivia
{"olivia","ow-l l-ih ih-ih ih-v v-iy iy-ah ah-pau"},
//olivias
{"olivias","ow-l l-ih ih-ih ih-v v-iy iy-ah ah-z"},
//on
{"on","aa-aa aa-n n-n"},
//one
{"one","w-ah ah-ah ah-n"},
//online
{"online","aa-aa aa-n n-n n-l l-aa aa-iy iy-n"},
//open
{"open","ao-uh uh-p p-ah ah-n"},
//or
{"or","ao-r"},
//orchestra
{"orchestra","ao-r r-k k-ah ah-s s-t t-r r-ah"},
//oscar
{"oscar","ao-s s-k k-uh uh-r"},
{"oscars","ao-s s-k k-uh uh-r r-z"},
//out
{"out","aa-uh uh-t"},
{"outbreak","aa-uh uh-t t-b b-r r-eh eh-iy iy-k"},
{"outcome","aa-uh uh-t t-k k-ah ah-m"},
{"outhouse","aa-uh uh-t t-hh hh-aa aa-uh uh-s"},
{"outing","aa-uh uh-t t-ih ih-ng"},
//over
{"over","ao-uh uh-v v-uh uh-r"},
//own
{"own","ow-ow-ow-ow ow-n n-pau"},

//P-words
//pam
{"pam","p-ae ae-ae ae-m m-pau"},
//pamela
{"pamela","p-ae ae-ae ae-m m-ah ah-l l-ah"},
//pams
{"pams","p-ae ae-ae ae-m m-z z-pau"},
//pancake
{"pancake","p-ae ae-ae ae-n n-k k-ey ey-ey ey-k"},
//paper
{"paper","p-eh eh-iy iy-p p-uh uh-r"},
//parent
{"parent","p-eh eh-r r-ah ah-n n-t"},
{"parents","p-eh eh-r r-ah ah-n n-t t-s"},
//parrot
{"parrot","p-eh eh-r r-ah ah-t"},
//party
{"party","p-aa aa-aa aa-r r-t t-iy iy-pau"},
//passport
{"passport","p-ae ae-ae ae-s s-p p-ao ao-ao ao-r r-t"},
//pat
{"pat","p-ae ae-t"},
//patricia
{"patricia","p-ah ah-t t-r r-ih ih-sh sh-ah"},
//patrick
{"patrick","p-ae ae-ae ae-t t-r r-ih ih-k"},
//patricks (saint name)
{"patricks","p-ae ae-ae ae-t t-r r-ih ih-k k-s"},
//pau
{"pau","pau-pau"},
//paul
{"paul","p-ao ao-ao ao-l"},
//paula
{"paula","p-ao ao-ao ao-l l-ah ah-pau"},
//pauline
{"pauline","p-ao ao-l l-iy iy-iy iy-n"},
//pause
{"pause","pau-pau"},
//pay
{"pay","p-eh eh-iy"},
{"payable","p-eh eh-iy iy-ah ah-b b-ah ah-l"},
{"payed","p-eh eh-iy iy-d"},
//paying
{"paying","p-eh eh-iy iy-ih ih-ng"},
//payment
{"payment","p-ey ey-ey ey-m m-ah ah-n n-t"},
//penelope
{"penelope","p-ah ah-n n-eh eh-eh eh-l l-ah ah-p p-iy iy-pau"},
//penny
{"penny","p-eh eh-eh eh-n n-iy iy-pau"},
//pension
{"pension","p-eh eh-eh eh-n n-sh sh-ah ah-n"},
//percy
{"percy","p-er er-er er-s s-iy iy-pau"},
//perry
{"perry","p-eh eh-eh eh-r r-iy iy-pau"},
//person
{"person","p-uh uh-r r-s s-ah ah-n"},
//personal
{"personal","p-uh uh-r r-s s-ih ih-n n-ih ih-l"},
//pet
{"pet","p-eh eh-t"},
//peter
{"peter","p-iy iy-iy iy-t t-er er-pau"},
//peters
{"peters","p-iy iy-iy iy-t t-er er-z"},
//phoebe or phebe
{"phoebe","f-iy iy-iy iy-b b-iy iy-pau"},
//phone
{"phone","f-ao ao-uh uh-n"},
//piano
{"piano","p-iy iy-ae ae-n n-ao ao-uh"},
//picture
{"picture","p-ih ih-ih ih-k k-ch ch-er er-pau"},
//pictures
{"pictures","p-ih ih-ih ih-k k-ch ch-er er-z z-pau"},
//pilates
{"pilates","p-ih ih-ih ih-l l-aa aa-aa aa-t t-iy iy-iy iy-s s-pau"},
//place
{"place","p-l l-eh eh-iy iy-s"},
//pmm
{"pmm","p-iy iy-iy iy-m m-eh eh-m m-m m-m"},
//point
{"point","p-oy oy-oy oy-n n-t t-pau"},
{"pop","p-aa aa-p"},
{"popcorn","p-aa aa-p p-k k-ao ao-r r-n"},
//pope
{"pope","p-ao ao-uh uh-p"},
//port
{"port","p-ao ao-r r-t"},
//post
{"post","p-ao ao-uh uh-s s-t"},
//postoffice
{"postoffice","p-ao ao-uh uh-s s-t t-ao ao-f f-ah ah-s"},
//{"potato","p-ah ah-t t-eh eh-iy iy-t t-ao ao-uh"},
//{"potatoes","p-ah ah-t t-eh eh-iy iy-t t-ao ao-uh uh-z"},
//practice
{"practice","p-r r-ae ae-k k-t t-ah ah-s"},
//premier
{"premier","p-r r-eh eh-m m-ih ih-ih ih-r r-pau"},
//prescription
{"prescription","p-r r-ah ah-s s-k k-r r-ih ih-p p-sh sh-ah ah-n"},
//present
{"present","p-r r-eh eh-z z-ah ah-n n-t"},
//pressure
{"pressure","p-r r-eh eh-sh sh-uh uh-r"},
//priority
{"priority","p-r r-aa aa-iy iy-ao ao-r r-ah ah-t t-iy"},
{"priscilla","p-r r-ih ih-s s-ih ih-l l-ah"},
{"prism","p-r r-ih ih-z z-ah ah-m"},
{"prison","p-r r-ih ih-z z-ah ah-n"},
{"private","p-r r-aa aa-iy iy-v v-ah ah-t"},
//program
{"program","p-r r-ow ow-ow ow-g g-r r-ae ae-ae ae-m m-pau"},
//programme (duplicate)
{"programme","p-r r-ow ow-ow ow-g g-r r-ae ae-ae ae-m m-pau"},
//project
{"project","p-r r-aa aa-aa aa-jh jh-eh eh-k k-t"},
//pronounce
{"pronounce","p-r r-ah ah-n n-aa aa-uh uh-n n-s"},
//pronounced
{"pronounced","p-r r-ah ah-n n-aa aa-uh uh-n n-s s-t"},
//prunella
{"prunella","p-r r-uw uw-n n-eh eh-eh eh-l l-ah"},
//pub
{"pub","p-ah ah-ah ah-b b-pau"},
//public
{"public","p-ah ah-ah ah-b b-l l-ih ih-k k-pau"},
//purchase
{"purchase","p-uh uh-r r-ch ch-ah ah-s"},

//Q-words
//queen
{"queen","k-w w-iy iy-n"},
//quick
{"quick","k-w w-ih ih-k"},
//quiz
{"quiz","k-w w-ih ih-ih ih-z z-pau"},
//quote
{"quote","k-w w-w w-ow ow-ow ow-t t-pau"},


//R-words
//radio
{"radio","r-ey ey-ey ey-d d-iy iy-ow ow-ow ow-pau"},
//rail
{"rail","r-eh eh-iy iy-l"},
//railway
{"railway","r-eh eh-iy iy-l l-w w-eh eh-iy"},
{"rain","r-eh eh-iy iy-n"},
{"ralph","r-ae ae-l l-f"},
//ray
{"ray","r-eh eh-iy"},
//reminder
{"reminder","r-iy iy-m m-ay ay-ay ay-n n-d d-er er-pau"},
//rene and renne
{"rene","r-ah ah-n n-eh eh-iy"},
{"renew","r-ih ih-n n-uw"},
{"renewal","r-ih ih-n n-uw uw-ah ah-l"},
//repair
{"repair","r-ih ih-p p-eh eh-r"},
//rest
{"rest","r-eh eh-eh eh-s s-t"},
//restaurant
{"restaurant","r-eh eh-eh eh-s s-t t-er er-aa aa-aa aa-n n-t"},
//retire
{"retire","r-ih ih-t t-aa aa-iy iy-r"},
//retirement
{"retirement","r-iy iy-t t-ay ay-er er-m m-ah ah-n n-t"},
//return
{"return","r-ih ih-t t-uh uh-r r-n"},
//richard
{"richard","r-ih ih-ch ch-uh uh-r r-d"},
//road
{"road","r-ao ao-uh uh-d"},
{"robber","r-aa aa-b b-uh uh-r"},
//robbie
{"robbie","r-aa aa-b b-iy"},
//robert
{"robert","r-aa aa-b b-uh uh-r r-t"},
//robin
{"robin","r-aa aa-b b-ah ah-n"},
//ronald
{"ronald","r-aa aa-n n-ah ah-l l-d"},
//room
{"room","r-uw uw-m"},
//rose
{"rose","r-ow ow-ow ow-z"},
//rosemary
{"rosemary","r-ow ow-ow ow-z z-m m-eh eh-eh eh-r r-iy iy-pau"},
//royal
{"royal","r-ao ao-iy iy-ah ah-l"},
//rugby
{"rugby","r-ah ah-g g-b b-iy"},
//russell and russel
{"russell","r-ah ah-s s-ah ah-l"},

//S-words
//sabrina
{"sabrina","s-ah ah-b b-r r-iy iy-iy iy-n n-ah ah-pau"},
//saint
{"saint","s-ey ey-ey ey-n n-t t-pau"},
{"sam","s-ae ae-m"},
{"samuel","s-ae ae-m m-y y-uw uw-l"},
//sanctuary
{"sanctuary","s-ae ae-ng ng-k k-ch ch-uw uw-eh eh-r r-iy"},
//sarah
{"sarah","s-eh eh-r r-ah"},
//saturday
{"saturday","s-ae ae-ae ae-t t-ih ih-ih ih-d d-ey ey-ey"},
//say
{"say","s-eh eh-iy"},
//says
{"says","s-eh eh-z"},
//school
{"school","s-k k-uw uw-l"},
//sea
{"sea","s-iy iy-iy"},
{"seal","s-iy iy-l"},
{"seaside","s-iy iy-s s-aa aa-iy iy-d"},
{"season","s-iy iy-z z-ah ah-n"},
//second
{"second","s-eh eh-eh eh-k k-ah ah-n n-d d-pau"},
//self
{"self","s-eh eh-eh eh-l l-f"},
//semi
{"semi","s-eh eh-m m-iy"},
{"semicircle","s-eh eh-m m-ih ih-s s-uh uh-r r-k k-ah ah-l"},
//seminar
{"seminar","s-eh eh-eh eh-m m-ah ah-n n-aa aa-aa aa-r r-r"},
//september
{"september","s-eh eh-p p-t t-eh eh-eh eh-m m-b b-er er-pau"},
//series
{"series","s-ih ih-r r-iy iy-z"},
//service
{"service","s-er er-er er-v v-ah ah-s"},
//seven
{"seven","s-eh eh-eh eh-v v-ah ah-n"},
//seventeen
{"seventeen","s-eh eh-eh eh-v v-ah ah-n n-t t-iy iy-iy iy-n n-pau"},
//seventeenth
{"seventeenth","s-eh eh-eh eh-v v-ah ah-n n-t t-iy iy-iy iy-n n-th th-pau"},
//seventh
{"seventh","s-eh eh-eh eh-v v-ah ah-n n-th th-pau"},
//seventieth
{"seventieth","s-eh eh-v v-ah ah-n n-t t-iy iy-ih ih-th"},
//seventy
{"seventy","s-eh eh-v v-ah ah-n n-t t-iy"},
//shoe
{"shoe","sh-uw uw-pau"},
//shop
{"shop","sh-aa aa-aa aa-p"},
//shopping
{"shopping","sh-aa aa-aa aa-p p-ih ih-ng"},
//short
{"short","sh-ao ao-r r-t"},
//show
{"show","sh-ow ow-ow ow-pau"},
//side
{"side","s-aa aa-iy iy-d"},
//sister
{"sister","s-ih ih-s s-t t-uh uh-r"},
//sisters
{"sisters","s-ih ih-s s-t t-uh uh-r r-z"},
//six
{"six","s-ih ih-ih ih-k k-s s-pau"},
//sixteen
{"sixteen","s-ih ih-k k-s s-t t-iy iy-iy iy-n n-pau"},
//sixteenth
{"sixteenth","s-ih ih-k k-s s-t t-iy iy-iy iy-n n-th th-pau"},
//sixth
{"sixth","s-ih ih-ih ih-k k-s s-th th-pau"},
//sixtieth
//sixty
{"sixty","s-ih ih-k k-s s-t t-iy"},
//sky
{"sky","s-k k-aa aa-iy"},
//small
{"small","s-m m-ao ao-l"},
//society
{"society","s-ow ow-s s-ay ay-ay ay-ih ih-t t-iy iy-pau"},
//software
//son
{"son","s-ah ah-ah ah-n"},
//sons
{"sons","s-ah ah-ah ah-n n-z"},
//south
//special
//speech
{"speech","s-p p-iy iy-iy iy-ch ch-ch ch-pau"},
//sport
{"sport","s-p p-ao ao-ao ao-r r-t"},
//spring
{"spring","s-p p-r r-ih ih-ih ih-ng"},
//stag
{"stag","s-t t-ae ae-g"},
//star
{"star","s-t t-aa aa-r"},
//start
{"start","s-t t-aa aa-r r-t"},
//starts
{"starts","s-t t-aa aa-r r-t t-s"},
//station
{"station","s-t t-ey ey-ey ey-sh sh-ah ah-n"},
//stay
{"stay","s-t t-eh eh-iy"},
//steve
{"steve","s-t t-iy iy-iy iy-v"},
//steven or stephen
{"steven","s-t t-iy iy-iy iy-v v-ah ah-n"},
//{"stephen","s-t t-iy iy-iy iy-v v-ah ah-n"},
//stock
{"stock","s-t t-aa aa-k"},
//store
{"store","s-t t-ao ao-r"},
//study
{"study","s-t t-ah ah-d d-iy"},
{"studying","s-t t-ah ah-d d-iy iy-ih ih-ng"},
//sub
{"sub","s-ah ah-b"},
//summer
{"summer","s-ah ah-m m-uh uh-r"},
//summertime
{"summertime","s-ah ah-m m-uh uh-r r-t t-aa aa-iy iy-m"},
//sunday
{"sunday","s-ah ah-ah ah-n n-d d-ey ey-ey ey-pau pau-ey"},
//super
{"super","s-uw uw-p p-uh uh-r"},
//susan
{"susan","s-uw uw-uw uw-z z-ah ah-n"},
//susans
{"susans","s-uw uw-uw uw-z z-ah ah-n n-z"},
//synthesizer bad prounciation
{"synthesizer","s-ih ih-ih ih-n n-th th-ah th-z z-s s-ay ay-ay ay-ay ay-er er-pau"},

//T-words
//take
{"take","t-eh eh-iy iy-k"},
//talk
{"talk","t-ao ao-ao ao-k"},
//talking
{"talking","t-ao ao-ao ao-k k-ih ih-ng"},
//task
{"task","t-ae ae-ae ae-s s-k"},
//tax
{"tax","t-ae ae-ae ae-k k-s"},
//taxi
{"taxi","t-ae ae-ae ae-k k-s s-iy iy-pau"},
//tea
{"tea","t-t t-iy iy-iy"},
{"tearoom","t-r r-uh uh-r r-uw uw-m"},
//team
{"team","t-iy iy-m"},
//television
{"television","t-eh eh-eh eh-l l-ah ah-v v-ih ih-ih ih-zh zh-ah ah-n"},
//temperature
{"temperature","t-eh eh-m m-p p-r r-ah ah-ch ch-uh uh-r"},
//ten
{"ten","t-eh eh-eh eh-n"},
//tennis
{"tennis","t-eh eh-n n-ah ah-s"},
//tenth
{"tenth","t-eh eh-eh eh-n n-th th-pau"},
//test
{"test","t-eh eh-s s-t"},
//thank
{"thank","th-ae ae-ng ng-k"},
//that
{"that","dh-ae ae-t"},
//the
{"the","dh-ah ah-ah"},
//theatre
{"theater","th-iy iy-iy iy-ey ey-t t-er er-pau"},
//then
{"then","dh-eh eh-eh eh-n n-pau"},
//theo
{"theo","th-iy iy-ao ao-uh"},
//theodore
{"theodore","th-iy iy-ah ah-d d-ao ao-r"},
//third
{"third","pau-th th-er er-er er-d d-pau"},
//thirteen
{"thirteen","th-er er-er er-t t-iy iy-iy iy-n n-pau"},
//thirteenth
{"thirteenth","th-er er-er er-t t-iy iy-iy iy-n n-th th-pau"},
//thirtieth
{"thirtieth","th-er er-er er-t t-iy iy-eh eh-eh eh-th th-pau"},
//thirty
{"thirty","th-er er-er er-d d-iy iy-iy iy-pau"},
//thomas
{"thomas","t-aa aa-aa aa-m m-ah ah-s"},
//{"thomases","t-aa aa-aa aa-m m-ah ah-s s-ih ih-z"},
//three
{"three","th-r r-iy iy-iy"},
//thursday
{"thursday","th-er er-er er-z z-d d-iy iy-pau"},
//ticket
{"ticket","t-ih ih-k k-ah ah-t"},
//tiffany
{"tiffany","t-ih ih-f ih-f f-ah ah-n n-iy iy-pau"},
//tilda
{"tilda","t-ih ih-ih ih-l l-d d-ah"},
//tim
{"tim","t-ih ih-ih ih-m"},
//time
{"time","t-ay ay-ay ay-m"},
//times
{"times","t-aa aa-iy iy-m m-z"},
//timothy
{"timothy","t-ih ih-ih ih-m m-ah ah-th th-iy iy-pau"},
//tims
{"tims","t-ih ih-ih ih-m m-z"},
//tiny
{"tiny","t-aa aa-iy iy-n n-iy"},
//to
{"to","t-uw uw-uw"},
//today
{"today","t-ah ah-d d-ey ey-ey"},
//toll
{"toll","t-ao ao-uh uh-l"},
//tom
{"tom","t-aa aa-aa aa-m"},
//tomorrow
{"tomorrow","t-ah ah-m m-aa aa-r r-ao ao-uh"},
//toms
{"toms","t-aa aa-aa aa-m m-z"},
//train
{"train","t-r r-eh eh-iy iy-n"},
//trans
{"trans","t-r r-ae ae-n n-z"},
{"transport","t-r r-ae ae-n n-s s-p p-ao ao-r r-t"},
//travel
{"travel","t-r r-ae ae-ae ae-v v-ah ah-l"},
//traveling or travelling
{"traveling","t-r r-ae ae-ae ae-v v-ah ah-l l-ih ih-ng"},
//travelodge
{"travelodge","t-r r-ae ae-ae ae-v v-ah ah-l l-aa aa-aa aa-jh jh-pau"},
//trevor
{"trevor","t-r r-eh eh-eh eh-v v-er er-pau"},
//trevors
{"trevors","t-r r-eh eh-eh eh-v v-er er-z z-pau pau-z"},
//trip
{"trip","t-r r-ih ih-ih ih-p p-p"},
//tuesday
{"tuesday","t-uw uw-uw uw-z z-d d-iy iy-pau"},
//tunnel
{"tunnel","t-ah ah-n n-ah ah-l"},
//turn
{"turn","t-uh uh-r r-n"},
//tv
{"tv","t-iy iy-iy iy-v v-iy iy-iy iy-pau"},
//twelfth
{"twelfth","t-w w-eh eh-eh eh-l l-f f-th th-pau pau-th"},
//twelve
{"twelve","t-w w-eh eh-eh eh-l l-v"},
//twentieth
{"twentieth","t-w w-eh eh-eh eh-n n-t t-iy iy-eh eh-eh eh-th th-pau"},
//twenty
{"twenty","t-w w-eh eh-eh eh-n n-t t-iy iy-pau"},
//two
{"two","t-uw uw-uw uw-pau"},

//U-words
//uncle
{"uncle","ah-ah ah-ng ng-k k-ah ah-l l-pau"},
//under
{"under","ah-n n-d d-uh uh-r"},
//university
{"university","y-uw uw-n n-ah ah-v v-uh uh-r r-s s-ah ah-t t-iy"},
//unknown
{"unknown","ah-n n-n n-ow ow-ow ow-n n-n"},
//up
{"up","ah-p p-p"},
//upcoming
{"upcoming","ah-p p-k k-ah ah-ah ah-m m-ih ih-ng"},
//ursula
{"ursula","uh-r r-s s-ah ah-l l-ah"},
//use
{"use","y-uw uw-uw uw-z z-pau"},
//user
{"user","y-uw uw-uw uw-z z-er er-pau"},

//V-words
//vacation
{"vacation","v-ey ey-k k-ey ey-ey ey-sh sh-ah ah-n"},
//val
{"val","v-ae ae-ae ae-l l-pau"},
//valentine
{"valentine","v-ae ae-ae ae-l l-ah ah-n n-t t-ay ay-ay ay-n"},
//valentines
{"valentines","v-ae ae-ae ae-l l-ah ah-n n-t t-ay ay-ay ay-n n-z"},
//valerie
{"valerie","v-ae ae-ae ae-l l-er er-iy iy-pau"},
//vehicle
{"vehicle","v-iy iy-iy iy-hh hh-ih ih-k k-ah ah-l"},
//venue
{"venue","v-eh eh-n n-y y-uw"},
//version
{"version","v-er er-er er-zh zh-ah ah-n"},
//veronica
{"veronica","v-uh uh-r r-aa aa-n n-ih ih-k k-ah"},
{"vicar","v-ih ih-k k-uh uh-r"},
{"vicarage","v-ih ih-k k-uh uh-r r-r r-aa aa-jh"},
//victor
{"victor","v-ih ih-k k-t t-uh uh-r"},
{"victoria","v-ih ih-k k-t t-ao ao-r r-iy iy-ah"},
//visit
{"visit","v-ih ih-ih ih-z z-ih ih-t t-pau"},

//w-words
//walk
{"walk","w-w w-ao ao-ao ao-k k-k"},
//warm
{"warm","w-ao ao-r r-m"},
//warming
{"warming","w-ao ao-r r-m m-ih ih-ng"},
{"warn","w-ao ao-r r-n"},
{"warning","w-ao ao-r r-n n-ih ih-ng"},
//wash
{"wash","w-aa aa-sh"},
//washing
{"washing","w-aa aa-sh sh-ih ih-ng"},
//water
//{"water","w-ao ao-t t-uh uh-r"},
{"water","w-ao ao-ao ao-t t-er er-pau"},
//way
{"way","w-ey ey-iy"},
//weather warning (to do)
{"weather","w-eh eh-dh dh-uh uh-r"},
//web
{"web","w-eh eh-eh eh-b b-b"},
//wedding
{"wedding","w-eh eh-eh eh-d d-ih ih-ng"},
//wednesday
{"wednesday","w-eh eh-eh eh-n n-z z-d d-iy iy-pau"}, //or iy-iy
//week
{"week","w-iy iy-k"},
//west
{"west","w-eh eh-s s-t"},
//wife
{"wife","w-ay ay-ay ay-f"},
//wifes
{"wifes","w-aa aa-iy iy-f f-s"},
//willow
{"willow","w-ih ih-l l-ao ao-uh"},
{"wills","w-ih ih-l l-z"},
{"willy","w-ih ih-l l-iy"},
{"willyum","w-ih ih-l l-y y-ah ah-m"},
{"wilma","w-ih ih-l l-m m-ah"},
{"wilson","w-ih ih-l l-s s-ah ah-n"},
//window
{"window","w-ih ih-n n-d d-ao ao-uh"},
//winnie
{"winnie","w-ih ih-ih ih-n n-iy iy-pau"},
//winnifred
{"winnifred","w-ih ih-ih ih-n n-ih ih-f f-r r-ih ih-d"},
//winston
{"winston","w-ih ih-ih ih-n n-s s-t t-ah ah-n"},
//winter
{"winter","w-ih ih-ih ih-n n-t t-er er-pau"},
//witch
{"witch","w-ih ih-ch"},
//woman
{"woman","w-uh uh-m m-ah ah-n"},
//word
{"word","w-uh uh-r r-d"},
//work
{"work","w-uh uh-r r-k k-pau"},
//working
{"working","w-uh uh-r r-k k-ih ih-ng"},
{"workman","w-uh uh-r r-k k-m m-ah ah-n"},
//workshop
{"workshop","w-uh uh-r r-k k-sh sh-aa aa-p"},
//world
{"world","w-er er-er er-l l-d"},

//X-words
//xavier
//xena

//Y-words
//yacht
{"yacht","y-aa  aa-aa aa-t"},
//year
{"year","y-ih ih-ih ih-r"},
//yearly
{"yearly","y-ih ih-ih ih-r r-l l-iy iy-pau"},
{"yodel","y-ao ao-uh uh-d d-ah ah-l"},
//you
{"you","y-uw uw-uw"},
{"youth","y-uw uw-th"},

//Z-words
//zach
{"zach","z-ae ae-k"},
//zachary
{"zachary","z-ae ae-k k-uh uh-r r-iy"},
//zara
{"zarahemla","z-ae ae-r r-ah ah-hh hh-iy iy-m m-l l-ah"},
{"zeppelin","z-eh eh-p p-ih ih-l l-ih ih-n"},
//zero
{"zero","z-iy iy-iy iy-r r-ow ow-pau"},
//zoe
{"zoe","z-ao ao-uh uh-iy"},
//zone
{"zone","z-ao ao-uh uh-n"},
//zoo
{"zoo","z-uw"},

	
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
