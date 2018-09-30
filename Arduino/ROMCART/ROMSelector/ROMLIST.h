#define MAX_NAME_LEN 30
#define MAX_ROMSET_NAME 8

#define MAXLEN 31

static const unsigned long PROGMEM CRCList [] = {
//  0,1,2,3,4,5,6,7,8,9, //Custom Named ROMs
  0x9BC04EBB,
  0xEE3EE642,
  0x2DA28C17,
  0x4EDA4917,
  0x3B24E1EE,
  0x96ADC96C,
  0xA69C2C93,
  0xF9084AA3,
  0x5AE57A8C,
  0x6F66B1F7,
  0x6381E402,
  0xC8F36C28,
  0xE5FB4260,
  0xB5FB1416,
  0x82996B1F,
  0x084EE035,
  0xA7E97958,
  0xDC5AFAA2,
  0x0C4E4B0A,
  0xB07748E7,
  0x95EFA98B,
  0xB590CF14,
  0x193F3855,
  0x0F870806,
  0x14B6CC76,
  0x2F6E4B46,
  0xA8DBED92,
  0x7A006985,
  0xC049E79E,
  0xF4C2075E,
  0x2A5F0B2B,
  0x105231F8,
  0x11FF50AD,
  0xAD89F799,
  0x1C8368E7,
  0x9487C920,
  0xABE368BF,
  0x5C8708AC,
  0xDC30AD3D,
  0x7810BAD5,
  0x2DCB77F0,
  0x11EDF25B,
  0x838A2D1E,
  0xAD7A9A11,
  0x17BE749B,
  0xCA8AB259,
  0xA57E1724,
  0xBE4FF48E,
  0xE39500A6,
  0x2391C2FB,
  0x25057C11,
  0x67069924,
  0x44D1A8A5,
  0x16C574C8,
  0x7394E82C,
  0x19947048,
  0xDDBA0ED2,
  0x71AE8533,
  0xBB6E7135,
  0xA0620082,
  0x2C9D1715,
  0x2C9D1715,
  0x2C9D1715,
  0x54BF4750,
  0x2FCE9245,
  0xAC5C74E6,
  0x0A2F0F58,
  0x4663C4B6,
  0xE129490D,
  0x239DF97D,
  0x89C6DE2C,
  0xA5ABFD39,
  0xD3B09FEC,
  0x551E38A2,
  0xD38153F6,
  0xFB83171E,
  0x58FA6766,
  0x07685850,
  0xAFB23F89,
  0x3B9D30C4,
  0xC97268DC,
  0xD158EEBA,
  0xE7B26A56,
  0x6CEBAB74,
  0xEB61888F,
  0x874F36A4,
  0x2B1E9E19,
  0x395629E1,
  0xB4735E6B,
  0xBE26212B,
  0x24D53E2C,
  0x3C949A57,
  0x4CEC1404,
  0xA674EA27,
  0xA2C6750E,
  0x39989464,
  0xF00F9DBA,
  0xFEE664F3,
  0x5F663FFC,
  0x7108E058,
  0x4A3E2DC8,
  0x4F73B44C,
  0x1931F5C5,
  0x54736B74,
  0x3BFEF56B,
  0x9B5E9356,
  0x7C747245,
  0xAFC093FD,
  0x9451BE1E,
  0xA21DA732,
  0xB2FFB353,
  0x81C20196,
  0xD62814A3,
  0xA6909A8B,
  0x2122012C,
  0x510416B7,
  0x881CEAE4,
  0x228842DF,
  0xF390BFEC,
  0x825976A9,
  0x61A350E6,
  0x9D2C45DC,
  0x9E42E766,
  0x1C750349,
  0x9585D511,
  0x02743352,
  0x764894A1,
  0xFC5A7F08,
  0xDEE70B33,
  0xB096654E,
  0x20E2F7BE,
  0x313547EB,
  0x26B0FF5B,
  0x5B6E741A,
  0xCA23F40C,
  0xB932D584,
  0xD03EFA86,
  0x25874B04,
  0xBE11157C,
  0x2038F56C,
  0x569E4249,
  0xA75C42F8,
  0x9D72D4E9,
  0x4A6963DE,
  0x1EEB88F5,
  0x4103EE95,
  0xD94D4109,
  0x65E5A779,
  0xC4134DF8,
  0xE246A812,
  0x0D2D721D,
  0x5216771A,
  0x1B188870,
  0x6FABCB7E,
  0xFD179F6D,
  0x202F2749,
  0x95936B07,
  0xE58AA0AC,
  0x3E5F71F3,
  0x35ACE4E8,
  0x335481F1,
  0x88D7CE72,
  0xA29F0FD4,
  0x77066338,
  0x45EF459C,
  0x2247405E,
  0xA7344D1F,
  0xB1109A09,
  0x7C989567,
  0x26517E77,
  0x0CA8C961,
  0x9BFC3E01,
  0x50AF9D45,
  0x9884EF36,
  0xCFCA6F39,
  0x32AAC006,
  0x06861A9C,
  0xD0BC4EE6,
  0xA57D84F3,
  0x69D21F8F,
  0xFDF0028F,
  0x39E31BF0,
  0x688FAD11,
  0x85DFCDD7,
  0xB47F3E0B,
  0x877B4109,
  0x4E2CC6D3,
  0x9C9DDDF9,
  0xB2F0F0B4,
  0xBBF276A0,
  0x655FDF57,
  0x0009965B,
  0x91A85E7C,
  0xA767508B,
  0x68560DC7,
  0xA030B990,
  0xECCD03BE,
  0x9E5EE195,
  0x7BE6F1EF,
  0xCF2F8E7A,
  0xDAAE02DC,
  0x0C2E4811,
  0x6CB1DE16,
  0x245D3533,
  0xC06A3880,
  0x3351FEDA,
  0x40AE062D,
  0x798E10BB,
  0x72674ADB,
  0x5C4F35D3,
  0x0F46CF66,
  0x4A578DFE,
  0xEF9E9C3B,
  0xABE9B016,
  0xDF36683F,
  0x863D5E2D,
  0x1B9F2F16,
  0x280D08F4,
  0x0B2DEB61,
  0xCC8BC68C,
  0xB936BD78,
  0x5C02BEE6,
  0x45E62222,
  0x69893F7F
};

//  const char stringc0[MAXLEN] =  "Custom name 0";
//  const char stringc1[MAXLEN] =  "Custom name 1";
//  const char stringc2[MAXLEN] =  "Custom name 2";
//  const char stringc3[MAXLEN] =  "Custom name 3";
//  const char stringc4[MAXLEN] =  "Custom name 4";
//  const char stringc5[MAXLEN] =  "Custom name 5";
//  const char stringc6[MAXLEN] =  "Custom name 6";
//  const char stringc7[MAXLEN] =  "Custom name 7";
//  const char stringc8[MAXLEN] =  "Custom name 8";
//  const char stringc9[MAXLEN] =  "Custom name 9";
  const char string0[MAXLEN] PROGMEM =  "01 Race/Spin-out/Cryptogram [1";
  const char string1[MAXLEN] PROGMEM =  "01 Speedway / Spin-Out / Crypt";
  const char string2[MAXLEN] PROGMEM =  "01 Speedway / Spin-Out / Crypt";
  const char string3[MAXLEN] PROGMEM =  "01 Speedway! / Spin-Out! / Cry";
  const char string4[MAXLEN] PROGMEM =  "01 Speedway! / Spin-Out! / Cry";
  const char string5[MAXLEN] PROGMEM =  "01 Speedway! / Spin-Out! / Cry";
  const char string6[MAXLEN] PROGMEM =  "02 Pairs / Space Rendezvous / ";
  const char string7[MAXLEN] PROGMEM =  "03 Football!";
  const char string8[MAXLEN] PROGMEM =  "04 Armored Encounter! / Sub Ch";
  const char string9[MAXLEN] PROGMEM =  "05 Las Vegas Blackjack!";
  const char string10[MAXLEN] PROGMEM =  "05 Las Vegas Blackjack! (Frenc";
  const char string11[MAXLEN] PROGMEM =  "05 Las Vegas Blackjack! (modif";
  const char string12[MAXLEN] PROGMEM =  "06 Bowling / Basketball + [6+]";
  const char string13[MAXLEN] PROGMEM =  "06 Bowling / Basketball + [6+]";
  const char string14[MAXLEN] PROGMEM =  "06 Bowling / Basketball + [6+]";
  const char string15[MAXLEN] PROGMEM =  "06 Bowling! / Basketball! [6]";
  const char string16[MAXLEN] PROGMEM =  "06 Bowling! / Basketball! [6](";
  const char string17[MAXLEN] PROGMEM =  "07 Math-A-Magic! / Echo!";
  const char string18[MAXLEN] PROGMEM =  "07 Math-A-Magic! / Echo! (Fren";
  const char string19[MAXLEN] PROGMEM =  "08 Baseball! [8]";
  const char string20[MAXLEN] PROGMEM =  "09 Computer Intro!";
  const char string21[MAXLEN] PROGMEM =  "09 Computer Intro! (European v";
  const char string22[MAXLEN] PROGMEM =  "09 Computer Programmer [9] (Ma";
  const char string23[MAXLEN] PROGMEM =  "10 Computer Golf!";
  const char string24[MAXLEN] PROGMEM =  "10 Computer Golf! (European ve";
  const char string25[MAXLEN] PROGMEM =  "11 Conflict Cosmique [11](C)";
  const char string26[MAXLEN] PROGMEM =  "11 Cosmic Conflict +";
  const char string27[MAXLEN] PROGMEM =  "11 Cosmic Conflict + (modified";
  const char string28[MAXLEN] PROGMEM =  "11 Cosmic Conflict!";
  const char string29[MAXLEN] PROGMEM =  "11 Cosmic Conflict! (European ";
  const char string30[MAXLEN] PROGMEM =  "11 Cosmic Conflict! (European ";
  const char string31[MAXLEN] PROGMEM =  "11 Cosmic Conflict+ [11+](F)";
  const char string32[MAXLEN] PROGMEM =  "12 Take the Money and Run!";
  const char string33[MAXLEN] PROGMEM =  "12 Take the Money and Run! (Fr";
  const char string34[MAXLEN] PROGMEM =  "13 Playschool Maths";
  const char string35[MAXLEN] PROGMEM =  "14 Gunfighter";
  const char string36[MAXLEN] PROGMEM =  "14 Gunfighter (European versio";
  const char string37[MAXLEN] PROGMEM =  "14 Gunfighter Mod [14]";
  const char string38[MAXLEN] PROGMEM =  "15 Samurai";
  const char string39[MAXLEN] PROGMEM =  "15 Samurai (European version)";
  const char string40[MAXLEN] PROGMEM =  "16 Depth Charge / Marksman (2K";
  const char string41[MAXLEN] PROGMEM =  "17 Chinese Logic (2K version)";
  const char string42[MAXLEN] PROGMEM =  "17 Desafio Chines [17](B)";
  const char string43[MAXLEN] PROGMEM =  "18 Invaders from Hyperspace!";
  const char string44[MAXLEN] PROGMEM =  "18 Invaders from Hyperspace! (";
  const char string45[MAXLEN] PROGMEM =  "18 Invaders from Hyperspace! (";
  const char string46[MAXLEN] PROGMEM =  "19 Catch the Ball / Noughts an";
  const char string47[MAXLEN] PROGMEM =  "19 Catch the Ball / Noughts an";
  const char string48[MAXLEN] PROGMEM =  "19 O Malabarista+Jogo da Velha";
  const char string49[MAXLEN] PROGMEM =  "20 Smithereens +";
  const char string50[MAXLEN] PROGMEM =  "20 Smithereens + (modified 2 -";
  const char string51[MAXLEN] PROGMEM =  "20 Smithereens!";
  const char string52[MAXLEN] PROGMEM =  "20 Smithereens! (European vers";
  const char string53[MAXLEN] PROGMEM =  "21 O Segredo do Farao [21](B)";
  const char string54[MAXLEN] PROGMEM =  "21 Secret of the Pharaohs (2K ";
  const char string55[MAXLEN] PROGMEM =  "21 Secret of the Pharaohs Mod ";
  const char string56[MAXLEN] PROGMEM =  "22 Space Monster - Plus! [22](";
  const char string57[MAXLEN] PROGMEM =  "22 Space Monster - Plus! [22+]";
  const char string58[MAXLEN] PROGMEM =  "23 Las Vegas Gambling";
  const char string59[MAXLEN] PROGMEM =  "23 Las Vegas Gambling (French ";
  const char string60[MAXLEN] PROGMEM =  "24 Flipper Game";
  const char string61[MAXLEN] PROGMEM =  "24 Flipper Game";
  const char string62[MAXLEN] PROGMEM =  "24 Flipper Game";
  const char string63[MAXLEN] PROGMEM =  "24 Flipper Game (French versio";
  const char string64[MAXLEN] PROGMEM =  "24 Flipper Game +";
  const char string65[MAXLEN] PROGMEM =  "24 Flipper Game + (Jopac versi";
  const char string66[MAXLEN] PROGMEM =  "24 Flipper Game + (modified - ";
  const char string67[MAXLEN] PROGMEM =  "25 Alpine Skiing! [25]";
  const char string68[MAXLEN] PROGMEM =  "25 Alpine Skiing! [25](F)";
  const char string69[MAXLEN] PROGMEM =  "26 Basket Game";
  const char string70[MAXLEN] PROGMEM =  "27 Electronic Table Football";
  const char string71[MAXLEN] PROGMEM =  "28 Electronic Volleyball Mod [";
  const char string72[MAXLEN] PROGMEM =  "28 Volleyball";
  const char string73[MAXLEN] PROGMEM =  "28 Volleyball! (French version";
  const char string74[MAXLEN] PROGMEM =  "29 Blockout! / Breakdown! [29]";
  const char string75[MAXLEN] PROGMEM =  "29 Blockout! / Breakdown![29]";
  const char string76[MAXLEN] PROGMEM =  "30 BattleField";
  const char string77[MAXLEN] PROGMEM =  "30 Battlefield Mod [30]";
  const char string78[MAXLEN] PROGMEM =  "31 Musician";
  const char string79[MAXLEN] PROGMEM =  "31 Musician [31] (Manual ex.in";
  const char string80[MAXLEN] PROGMEM =  "31 Musician Mod [31] G7400";
  const char string81[MAXLEN] PROGMEM =  "32 A Labyrinth Game / Supermin";
  const char string82[MAXLEN] PROGMEM =  "33 Acrobats! (European - extra";
  const char string83[MAXLEN] PROGMEM =  "33 Acrobats! (European version";
  const char string84[MAXLEN] PROGMEM =  "33 Acrobats! (modified - PAL v";
  const char string85[MAXLEN] PROGMEM =  "33 Jumping Acrobats!";
  const char string86[MAXLEN] PROGMEM =  "34 Satellite Attack";
  const char string87[MAXLEN] PROGMEM =  "34 Satellite Attack (European ";
  const char string88[MAXLEN] PROGMEM =  "34 Satellite Attack +";
  const char string89[MAXLEN] PROGMEM =  "35 Electronic Billiards Mod [3";
  const char string90[MAXLEN] PROGMEM =  "35 Electronic Billiards!";
  const char string91[MAXLEN] PROGMEM =  "35 Pocket Billiards +";
  const char string92[MAXLEN] PROGMEM =  "35 Pocket Billiards + (Jopac v";
  const char string93[MAXLEN] PROGMEM =  "35 Pocket Billiards! (French v";
  const char string94[MAXLEN] PROGMEM =  "36 Electronic Soccer/Electroni";
  const char string95[MAXLEN] PROGMEM =  "36 Hockey! / Soccer!";
  const char string96[MAXLEN] PROGMEM =  "36 Hockey! / Soccer! (French v";
  const char string97[MAXLEN] PROGMEM =  "37 Monkeyshines!";
  const char string98[MAXLEN] PROGMEM =  "38 J.G. Munchkin!";
  const char string99[MAXLEN] PROGMEM =  "38 K.C. Munchkin!";
  const char string100[MAXLEN] PROGMEM =  "38 K.C. Munchkin! (European ve";
  const char string101[MAXLEN] PROGMEM =  "38 K.C. Munchkin! (Pac-Man hac";
  const char string102[MAXLEN] PROGMEM =  "39 Freedom Fighters +";
  const char string103[MAXLEN] PROGMEM =  "39 Freedom Fighters!";
  const char string104[MAXLEN] PROGMEM =  "40 4 In 1 Row [40]";
  const char string105[MAXLEN] PROGMEM =  "40 4 In 1 Row [40](F)";
  const char string106[MAXLEN] PROGMEM =  "40 4 In 1 Row [40](mod for VP+";
  const char string107[MAXLEN] PROGMEM =  "41 Conquest of the World!";
  const char string108[MAXLEN] PROGMEM =  "42 The Quest for the Rings";
  const char string109[MAXLEN] PROGMEM =  "42 The Quest for the Rings (Fr";
  const char string110[MAXLEN] PROGMEM =  "43 Pick Axe Pete +";
  const char string111[MAXLEN] PROGMEM =  "43 Pick Axe Pete + (modified -";
  const char string112[MAXLEN] PROGMEM =  "43 Pick Axe Pete!";
  const char string113[MAXLEN] PROGMEM =  "44 K.C.'s Krazy Chase!";
  const char string114[MAXLEN] PROGMEM =  "45 Morse";
  const char string115[MAXLEN] PROGMEM =  "45 Morse (French version)";
  const char string116[MAXLEN] PROGMEM =  "46 The Great Wall Street Fortu";
  const char string117[MAXLEN] PROGMEM =  "46 The Great Wall Street Fortu";
  const char string118[MAXLEN] PROGMEM =  "47 The Mousing Cat (4K version";
  const char string119[MAXLEN] PROGMEM =  "47 The Mousing Cat (8K version";
  const char string120[MAXLEN] PROGMEM =  "47 The Mousing Cat (French ver";
  const char string121[MAXLEN] PROGMEM =  "48 Backgammon [48]";
  const char string122[MAXLEN] PROGMEM =  "49 Turtles";
  const char string123[MAXLEN] PROGMEM =  "49 Turtles (European version)";
  const char string124[MAXLEN] PROGMEM =  "50 Super Bee (4K version)";
  const char string125[MAXLEN] PROGMEM =  "50 Super Bee [50](B)";
  const char string126[MAXLEN] PROGMEM =  "51 Attack of the Timelord + [5";
  const char string127[MAXLEN] PROGMEM =  "51 Attack of the Timelord! [51";
  const char string128[MAXLEN] PROGMEM =  "52 Killer Bees +";
  const char string129[MAXLEN] PROGMEM =  "52 Killer Bees!";
  const char string130[MAXLEN] PROGMEM =  "52 Killer Bees+ [52+](F)";
  const char string131[MAXLEN] PROGMEM =  "53 Nightmare (""Phantom House"" ";
  const char string132[MAXLEN] PROGMEM =  "53 Nightmare +";
  const char string133[MAXLEN] PROGMEM =  "54 Looney Ballon [54] (BR)";
  const char string134[MAXLEN] PROGMEM =  "54 Loony Balloon (no Plus grap";
  const char string135[MAXLEN] PROGMEM =  "54 Loony Balloon +";
  const char string136[MAXLEN] PROGMEM =  "55 Neutron Star (""Black Hole"" ";
  const char string137[MAXLEN] PROGMEM =  "55 Neutron Star (Brazilian ver";
  const char string138[MAXLEN] PROGMEM =  "55 Neutron Star + (12K version";
  const char string139[MAXLEN] PROGMEM =  "55 Neutron Star + (12K version";
  const char string140[MAXLEN] PROGMEM =  "55 Neutron Star + (modified - ";
  const char string141[MAXLEN] PROGMEM =  "56 Norseman + (VP+ only)";
  const char string142[MAXLEN] PROGMEM =  "57 Blobbers";
  const char string143[MAXLEN] PROGMEM =  "57 Blobbers [57](mod)(NTSC)";
  const char string144[MAXLEN] PROGMEM =  "58 Air Battle [58]";
  const char string145[MAXLEN] PROGMEM =  "58 Air Battle [58](B)";
  const char string146[MAXLEN] PROGMEM =  "58 Air Battle+ [58+]";
  const char string147[MAXLEN] PROGMEM =  "59 Helicopter Rescue / Buzzwor";
  const char string148[MAXLEN] PROGMEM =  "59 Helicopter Rescue + (VP+ on";
  const char string149[MAXLEN] PROGMEM =  "60 Trans American Rally + (bad";
  const char string150[MAXLEN] PROGMEM =  "60 Trans American Rally + (VP+";
  const char string151[MAXLEN] PROGMEM =  "61 Popeye";
  const char string152[MAXLEN] PROGMEM =  "61 Popeye (Brazilian version)";
  const char string153[MAXLEN] PROGMEM =  "62 Clay Pigeon +";
  const char string154[MAXLEN] PROGMEM =  "62 Clay Pigeon!";
  const char string155[MAXLEN] PROGMEM =  "62 Q*bert";
  const char string156[MAXLEN] PROGMEM =  "63 Super Cobra";
  const char string157[MAXLEN] PROGMEM =  "63 Super Cobra (Brazilian vers";
  const char string158[MAXLEN] PROGMEM =  "65 Spider-Man [65](EU)(Proto)(";
  const char string159[MAXLEN] PROGMEM =  "65 Spider-Man [65])(EU)(Proto)";
  const char string160[MAXLEN] PROGMEM =  "67 Martian Threat [67](EU)(Pro";
  const char string161[MAXLEN] PROGMEM =  "69 Play Tag Mod fix [69]";
  const char string162[MAXLEN] PROGMEM =  "69 Playtag [69](EU)(Proto)";
  const char string163[MAXLEN] PROGMEM =  "C7010 Video Chess Module (not ";
  const char string164[MAXLEN] PROGMEM =  "XX Amok [??]";
  const char string165[MAXLEN] PROGMEM =  "XX Amok [??] (free version)";
  const char string166[MAXLEN] PROGMEM =  "XX Atlantis [??]";
  const char string167[MAXLEN] PROGMEM =  "XX Bombardeio Submarino + Tiro";
  const char string168[MAXLEN] PROGMEM =  "XX Clay Pigeon+ [62+]";
  const char string169[MAXLEN] PROGMEM =  "XX Comando Noturno!";
  const char string170[MAXLEN] PROGMEM =  "XX Death Race RC4";
  const char string171[MAXLEN] PROGMEM =  "XX Demon Attack";
  const char string172[MAXLEN] PROGMEM =  "XX Demon Attack +";
  const char string173[MAXLEN] PROGMEM =  "XX Demon Attack + (modified - ";
  const char string174[MAXLEN] PROGMEM =  "XX Exojet +";
  const char string175[MAXLEN] PROGMEM =  "XX Exojet + (modified - NTSC/P";
  const char string176[MAXLEN] PROGMEM =  "XX Flash Point + (VP+ only)";
  const char string177[MAXLEN] PROGMEM =  "XX Frogger";
  const char string178[MAXLEN] PROGMEM =  "XX Frogger (Brazilian version)";
  const char string179[MAXLEN] PROGMEM =  "XX Interpol (does not work on ";
  const char string180[MAXLEN] PROGMEM =  "XX Interpol (NTSC) [61]";
  const char string181[MAXLEN] PROGMEM =  "XX Jake";
  const char string182[MAXLEN] PROGMEM =  "XX Keyboard Creations!";
  const char string183[MAXLEN] PROGMEM =  "XX Keyboard Creations! (Europe";
  const char string184[MAXLEN] PROGMEM =  "XX Kill The Attacking Aliens (";
  const char string185[MAXLEN] PROGMEM =  "XX Kill The Attacking Aliens (";
  const char string186[MAXLEN] PROGMEM =  "XX Kill The Attacking Aliens (";
  const char string187[MAXLEN] PROGMEM =  "XX Kinder Im Verkehr 1";
  const char string188[MAXLEN] PROGMEM =  "XX Le Tresor Englouti + (VP+ o";
  const char string189[MAXLEN] PROGMEM =  "XX Matchmaker! / Logix! / Buzz";
  const char string190[MAXLEN] PROGMEM =  "XX Mission Impossible [??](B)(";
  const char string191[MAXLEN] PROGMEM =  "XX Mod Tutankham";
  const char string192[MAXLEN] PROGMEM =  "XX Moto Crash (modified - non-";
  const char string193[MAXLEN] PROGMEM =  "XX Moto Crash (modified - non-";
  const char string194[MAXLEN] PROGMEM =  "XX Moto Crash + (VP+ only)";
  const char string195[MAXLEN] PROGMEM =  "XX Mr Roboto Ted (Foolery) Szc";
  const char string196[MAXLEN] PROGMEM =  "XX New calculator (Rene van de";
  const char string197[MAXLEN] PROGMEM =  "XX New kc-pacvid";
  const char string198[MAXLEN] PROGMEM =  "XX Nightfighter [??](EU)(Proto";
  const char string199[MAXLEN] PROGMEM =  "XX Nimble Numbers Ned";
  const char string200[MAXLEN] PROGMEM =  "XX Nimble Numbers Ned (modifie";
  const char string201[MAXLEN] PROGMEM =  "XX Out of this World! / Helico";
  const char string202[MAXLEN] PROGMEM =  "XX Planet Lander!";
  const char string203[MAXLEN] PROGMEM =  "XX Pong";
  const char string204[MAXLEN] PROGMEM =  "XX Pong (with extra features)";
  const char string205[MAXLEN] PROGMEM =  "XX Power Lords";
  const char string206[MAXLEN] PROGMEM =  "XX Power Lords (alternate)";
  const char string207[MAXLEN] PROGMEM =  "XX Puzzle Piece Panic (O2em ve";
  const char string208[MAXLEN] PROGMEM =  "XX Puzzle Piece Panic Ted (Foo";
  const char string209[MAXLEN] PROGMEM =  "XX Red Baron [??](EU)(Proto)(A";
  const char string210[MAXLEN] PROGMEM =  "XX Restaurant";
  const char string211[MAXLEN] PROGMEM =  "XX Restaurant (modified - NTSC";
  const char string212[MAXLEN] PROGMEM =  "XX Robot City [??](EU)(Proto)";
  const char string213[MAXLEN] PROGMEM =  "XX Route66 Rafael Cardoso";
  const char string214[MAXLEN] PROGMEM =  "XX Shark Hunter";
  const char string215[MAXLEN] PROGMEM =  "XX Shark Hunter (modified - NT";
  const char string216[MAXLEN] PROGMEM =  "XX Sid the Spellbinder";
  const char string217[MAXLEN] PROGMEM =  "XX Syracuse";
  const char string218[MAXLEN] PROGMEM =  "XX Tutankham";
  const char string219[MAXLEN] PROGMEM =  "XX Tutankham (NTSC)";
  const char string220[MAXLEN] PROGMEM =  "XX Type & Tell";
  const char string221[MAXLEN] PROGMEM =  "XX Type & Tell (modified - PAL";
  const char string222[MAXLEN] PROGMEM =  "XX Verkehrsspiele 1";
  const char string223[MAXLEN] PROGMEM =  "XX Verkehrsspiele 2";
  
const char* const ROMNameList [233] PROGMEM = {
//stringc0, 
//stringc1, 
//stringc2, 
//stringc3, 
//stringc4, 
//stringc5, 
//stringc6, 
//stringc7, 
//stringc8, 
//stringc9, 
string0, 
string1, 
string2, 
string3, 
string4, 
string5, 
string6, 
string7, 
string8, 
string9, 
string10, 
string11, 
string12, 
string13, 
string14, 
string15, 
string16, 
string17, 
string18, 
string19, 
string20, 
string21, 
string22, 
string23, 
string24, 
string25, 
string26, 
string27, 
string28, 
string29, 
string30, 
string31, 
string32, 
string33, 
string34, 
string35, 
string36, 
string37, 
string38, 
string39, 
string40, 
string41, 
string42, 
string43, 
string44, 
string45, 
string46, 
string47, 
string48, 
string49, 
string50, 
string51, 
string52, 
string53, 
string54, 
string55, 
string56, 
string57, 
string58, 
string59, 
string60, 
string61, 
string62, 
string63, 
string64, 
string65, 
string66, 
string67, 
string68, 
string69, 
string70, 
string71, 
string72, 
string73, 
string74, 
string75, 
string76, 
string77, 
string78, 
string79, 
string80, 
string81, 
string82, 
string83, 
string84, 
string85, 
string86, 
string87, 
string88, 
string89, 
string90, 
string91, 
string92, 
string93, 
string94, 
string95, 
string96, 
string97, 
string98, 
string99, 
string100, 
string101, 
string102, 
string103, 
string104, 
string105, 
string106, 
string107, 
string108, 
string109, 
string110, 
string111, 
string112, 
string113, 
string114, 
string115, 
string116, 
string117, 
string118, 
string119, 
string120, 
string121, 
string122, 
string123, 
string124, 
string125, 
string126, 
string127, 
string128, 
string129, 
string130, 
string131, 
string132, 
string133, 
string134, 
string135, 
string136, 
string137, 
string138, 
string139, 
string140, 
string141, 
string142, 
string143, 
string144, 
string145, 
string146, 
string147, 
string148, 
string149, 
string150, 
string151, 
string152, 
string153, 
string154, 
string155, 
string156, 
string157, 
string158, 
string159, 
string160, 
string161, 
string162, 
string163, 
string164, 
string165, 
string166, 
string167, 
string168, 
string169, 
string170, 
string171, 
string172, 
string173, 
string174, 
string175, 
string176, 
string177, 
string178, 
string179, 
string180, 
string181, 
string182, 
string183, 
string184, 
string185, 
string186, 
string187, 
string188, 
string189, 
string190, 
string191, 
string192, 
string193, 
string194, 
string195, 
string196, 
string197, 
string198, 
string199, 
string200, 
string201, 
string202, 
string203, 
string204, 
string205, 
string206, 
string207, 
string208, 
string209, 
string210, 
string211, 
string212, 
string213, 
string214, 
string215, 
string216, 
string217, 
string218, 
string219, 
string220, 
string221, 
string222};
