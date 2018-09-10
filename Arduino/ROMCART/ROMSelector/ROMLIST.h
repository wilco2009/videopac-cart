#define MAX_NAME_LEN 30
#define MAX_ROMSET_NAME 8

#define MAXLEN 31

static const unsigned long PROGMEM CRCList [] = {
//  0,1,2,3,4,5,6,7,8,9, //Custom Named ROMs
  0x3BFEF56B,
  0x9B5E9356,
  0x7C747245,
  0xD158EEBA,
  0x1EEB88F5,
  0x4103EE95,
  0xD94D4109,
  0x71AE8533,
  0xDDBA0ED2,
  0x4663C4B6,
  0xE129490D,
  0x45EF459C,
  0x2247405E,
  0x5AE57A8C,
  0xA7344D1F,
  0x764894A1,
  0xFC5A7F08,
  0x9D2C45DC,
  0xB07748E7,
  0x9D72D4E9,
  0x4A6963DE,
  0xFB83171E,
  0xD38153F6,
  0xB1109A09,
  0xE5FB4260,
  0xB5FB1416,
  0x82996B1F,
  0x084EE035,
  0xA7E97958,
  0x77066338,
  0x3B9D30C4,
  0x193F3855,
  0xBB6E7135,
  0xA0620082,
  0xA57E1724,
  0xBE4FF48E,
  0x11EDF25B,
  0x6FABCB7E,
  0x7C989567,
  0xFD179F6D,
  0x26517E77,
  0x0F870806,
  0x14B6CC76,
  0x95EFA98B,
  0xB590CF14,
  0x2F6E4B46,
  0xAFC093FD,
  0xA8DBED92,
  0x7A006985,
  0xC049E79E,
  0xF4C2075E,
  0x2A5F0B2B,
  0x0CA8C961,
  0x9BFC3E01,
  0x50AF9D45,
  0x9884EF36,
  0x2DCB77F0,
  0x838A2D1E,
  0xDC30AD3D,
  0x7810BAD5,
  0x89C6DE2C,
  0xCFCA6F39,
  0x32AAC006,
  0x06861A9C,
  0xF9084AA3,
  0x1931F5C5,
  0x54736B74,
  0xD0BC4EE6,
  0xA57D84F3,
  0x65E5A779,
  0xC4134DF8,
  0x39989464,
  0xF00F9DBA,
  0x69D21F8F,
  0xFDF0028F,
  0xAD7A9A11,
  0x17BE749B,
  0xCA8AB259,
  0x1C8368E7,
  0x5F663FFC,
  0x39E31BF0,
  0x7108E058,
  0x4A3E2DC8,
  0x4F73B44C,
  0xA6909A8B,
  0x688FAD11,
  0x85DFCDD7,
  0xB47F3E0B,
  0x877B4109,
  0x4E2CC6D3,
  0xDEE70B33,
  0xB096654E,
  0x9C9DDDF9,
  0x6F66B1F7,
  0x6381E402,
  0xC8F36C28,
  0xB2F0F0B4,
  0x5B6E741A,
  0xCA23F40C,
  0xB932D584,
  0x335481F1,
  0xBBF276A0,
  0xDC5AFAA2,
  0x0C4E4B0A,
  0x655FDF57,
  0x5C8708AC,
  0x19947048,
  0xA5ABFD39,
  0x07685850,
  0xC97268DC,
  0xBE26212B,
  0xA2C6750E,
  0x88D7CE72,
  0x0009965B,
  0xFEE664F3,
  0x2122012C,
  0x510416B7,
  0x91A85E7C,
  0xA767508B,
  0x68560DC7,
  0xAFB23F89,
  0xD03EFA86,
  0x25874B04,
  0xBE11157C,
  0x2038F56C,
  0x569E4249,
  0xECCD03BE,
  0x9E5EE195,
  0xABE9B016,
  0xA030B990,
  0x72674ADB,
  0x7BE6F1EF,
  0x313547EB,
  0x26B0FF5B,
  0xCF2F8E7A,
  0xDAAE02DC,
  0xA75C42F8,
  0xE39500A6,
  0x16C574C8,
  0x798E10BB,
  0x0C2E4811,
  0x874F36A4,
  0xE7B26A56,
  0x6CEBAB74,
  0xEB61888F,
  0x239DF97D,
  0xA69C2C93,
  0xB2FFB353,
  0x81C20196,
  0xD62814A3,
  0x6EF2471A,
  0x6CB1DE16,
  0xA29F0FD4,
  0x3C949A57,
  0x4CEC1404,
  0x24D53E2C,
  0xA674EA27,
  0x245D3533,
  0xC06A3880,
  0x5216771A,
  0x1B188870,
  0x3351FEDA,
  0x40AE062D,
  0x202F2749,
  0x5C4F35D3,
  0x0F46CF66,
  0x4A578DFE,
  0xEF9E9C3B,
  0x7394E82C,
  0xDF36683F,
  0x863D5E2D,
  0x9487C920,
  0xABE368BF,
  0x1B9F2F16,
  0x2391C2FB,
  0x25057C11,
  0x67069924,
  0x44D1A8A5,
  0xEE3EE642,
  0x2DA28C17,
  0x4EDA4917,
  0x3B24E1EE,
  0x96ADC96C,
  0x35ACE4E8,
  0x3E5F71F3,
  0x9585D511,
  0x02743352,
  0x95936B07,
  0xE58AA0AC,
  0x280D08F4,
  0x11FF50AD,
  0xAD89F799,
  0x881CEAE4,
  0xF390BFEC,
  0x825976A9,
  0x61A350E6,
  0x9451BE1E,
  0xA21DA732,
  0x2FCE9245,
  0xAC5C74E6,
  0x0A2F0F58,
  0x2C9D1715,
  0x54BF4750,
  0xE246A812,
  0x0D2D721D,
  0x9E42E766,
  0x1C750349,
  0x0B2DEB61,
  0xCC8BC68C,
  0xB936BD78,
  0x5C02BEE6,
  0xB4735E6B,
  0x2B1E9E19,
  0x395629E1,
  0x45E62222,
  0x69893F7F,
  0xD3B09FEC,
  0x551E38A2,
  0x9BC04EBB,
  0x105231F8,
  0x20E2F7BE,
  0x228842DF,
  0x58FA6766
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
  const char string0[MAXLEN] PROGMEM =  "4 In 1 Row";
  const char string1[MAXLEN] PROGMEM =  "4 In 1 Row (French version)";
  const char string2[MAXLEN] PROGMEM =  "4 In 1 Row (modified - works o";
  const char string3[MAXLEN] PROGMEM =  "A Labyrinth Game / Supermind";
  const char string4[MAXLEN] PROGMEM =  "Air Battle (""Red Baron"" - no P";
  const char string5[MAXLEN] PROGMEM =  "Air Battle (Brazilian version)";
  const char string6[MAXLEN] PROGMEM =  "Air Battle +";
  const char string7[MAXLEN] PROGMEM =  "Alien Invaders - Plus!";
  const char string8[MAXLEN] PROGMEM =  "Alien Invaders - Plus! (hack)";
  const char string9[MAXLEN] PROGMEM =  "Alpine Skiing!";
  const char string10[MAXLEN] PROGMEM =  "Alpine Skiing! (French version";
  const char string11[MAXLEN] PROGMEM =  "Amok";
  const char string12[MAXLEN] PROGMEM =  "Amok (free version)";
  const char string13[MAXLEN] PROGMEM =  "Armored Encounter! / Sub Chase";
  const char string14[MAXLEN] PROGMEM =  "Atlantis";
  const char string15[MAXLEN] PROGMEM =  "Attack of the Timelord +";
  const char string16[MAXLEN] PROGMEM =  "Attack of the Timelord!";
  const char string17[MAXLEN] PROGMEM =  "Backgammon";
  const char string18[MAXLEN] PROGMEM =  "Baseball!";
  const char string19[MAXLEN] PROGMEM =  "Blobbers";
  const char string20[MAXLEN] PROGMEM =  "Blobbers (modified - NTSC vers";
  const char string21[MAXLEN] PROGMEM =  "Blockout! / Breakdown!";
  const char string22[MAXLEN] PROGMEM =  "Blockout! / Breakdown! (French";
  const char string23[MAXLEN] PROGMEM =  "Bombardeio Submarino + Tiro ao";
  const char string24[MAXLEN] PROGMEM =  "Bowling / Basketball +";
  const char string25[MAXLEN] PROGMEM =  "Bowling / Basketball + (Jopac ";
  const char string26[MAXLEN] PROGMEM =  "Bowling / Basketball + (modifi";
  const char string27[MAXLEN] PROGMEM =  "Bowling! / Basketball!";
  const char string28[MAXLEN] PROGMEM =  "Bowling! / Basketball! (French";
  const char string29[MAXLEN] PROGMEM =  "C7010 Video Chess Module (not ";
  const char string30[MAXLEN] PROGMEM =  "Cart 31 (Manual examples inc.)";
  const char string31[MAXLEN] PROGMEM =  "Cart 9 (Manual examples inc.)(";
  const char string32[MAXLEN] PROGMEM =  "Casino Slot Machine!";
  const char string33[MAXLEN] PROGMEM =  "Casino Slot Machine! (French v";
  const char string34[MAXLEN] PROGMEM =  "Catch the Ball / Noughts and C";
  const char string35[MAXLEN] PROGMEM =  "Catch the Ball / Noughts and C";
  const char string36[MAXLEN] PROGMEM =  "Chinese Logic (2K version)";
  const char string37[MAXLEN] PROGMEM =  "Clay Pigeon +";
  const char string38[MAXLEN] PROGMEM =  "Clay Pigeon with Plus backgrou";
  const char string39[MAXLEN] PROGMEM =  "Clay Pigeon!";
  const char string40[MAXLEN] PROGMEM =  "Comando Noturno!";
  const char string41[MAXLEN] PROGMEM =  "Computer Golf!";
  const char string42[MAXLEN] PROGMEM =  "Computer Golf! (European versi";
  const char string43[MAXLEN] PROGMEM =  "Computer Intro!";
  const char string44[MAXLEN] PROGMEM =  "Computer Intro! (European vers";
  const char string45[MAXLEN] PROGMEM =  "Conflict Cosmique (Canada)";
  const char string46[MAXLEN] PROGMEM =  "Conquest of the World!";
  const char string47[MAXLEN] PROGMEM =  "Cosmic Conflict +";
  const char string48[MAXLEN] PROGMEM =  "Cosmic Conflict + (modified - ";
  const char string49[MAXLEN] PROGMEM =  "Cosmic Conflict!";
  const char string50[MAXLEN] PROGMEM =  "Cosmic Conflict! (European alt";
  const char string51[MAXLEN] PROGMEM =  "Cosmic Conflict! (European ver";
  const char string52[MAXLEN] PROGMEM =  "Death Race RC4";
  const char string53[MAXLEN] PROGMEM =  "Demon Attack";
  const char string54[MAXLEN] PROGMEM =  "Demon Attack +";
  const char string55[MAXLEN] PROGMEM =  "Demon Attack + (modified - Plu";
  const char string56[MAXLEN] PROGMEM =  "Depth Charge / Marksman (2K ve";
  const char string57[MAXLEN] PROGMEM =  "Desafio Chines (Brazil)";
  const char string58[MAXLEN] PROGMEM =  "Dynasty!";
  const char string59[MAXLEN] PROGMEM =  "Dynasty! (European version)";
  const char string60[MAXLEN] PROGMEM =  "Electronic Table Soccer!";
  const char string61[MAXLEN] PROGMEM =  "Exojet +";
  const char string62[MAXLEN] PROGMEM =  "Exojet + (modified - NTSC/PAL ";
  const char string63[MAXLEN] PROGMEM =  "Flash Point + (VP+ only)";
  const char string64[MAXLEN] PROGMEM =  "Football!";
  const char string65[MAXLEN] PROGMEM =  "Freedom Fighters +";
  const char string66[MAXLEN] PROGMEM =  "Freedom Fighters!";
  const char string67[MAXLEN] PROGMEM =  "Frogger";
  const char string68[MAXLEN] PROGMEM =  "Frogger (Brazilian version)";
  const char string69[MAXLEN] PROGMEM =  "Helicopter Rescue / Buzzword";
  const char string70[MAXLEN] PROGMEM =  "Helicopter Rescue + (VP+ only ";
  const char string71[MAXLEN] PROGMEM =  "Hockey! / Soccer!";
  const char string72[MAXLEN] PROGMEM =  "Hockey! / Soccer! (French vers";
  const char string73[MAXLEN] PROGMEM =  "Interpol (does not work on O2E";
  const char string74[MAXLEN] PROGMEM =  "interpol (NTSC version)";
  const char string75[MAXLEN] PROGMEM =  "Invaders from Hyperspace!";
  const char string76[MAXLEN] PROGMEM =  "Invaders from Hyperspace! (Eur";
  const char string77[MAXLEN] PROGMEM =  "Invaders from Hyperspace! (Fre";
  const char string78[MAXLEN] PROGMEM =  "I've Got Your Number!";
  const char string79[MAXLEN] PROGMEM =  "J.G. Munchkin!";
  const char string80[MAXLEN] PROGMEM =  "Jake";
  const char string81[MAXLEN] PROGMEM =  "K.C. Munchkin!";
  const char string82[MAXLEN] PROGMEM =  "K.C. Munchkin! (European versi";
  const char string83[MAXLEN] PROGMEM =  "K.C. Munchkin! (Pac-Man hack)";
  const char string84[MAXLEN] PROGMEM =  "K.C.'s Krazy Chase!";
  const char string85[MAXLEN] PROGMEM =  "Keyboard Creations!";
  const char string86[MAXLEN] PROGMEM =  "Keyboard Creations! (European ";
  const char string87[MAXLEN] PROGMEM =  "Kill The Attacking Aliens (1st";
  const char string88[MAXLEN] PROGMEM =  "Kill The Attacking Aliens (2nd";
  const char string89[MAXLEN] PROGMEM =  "Kill The Attacking Aliens (fin";
  const char string90[MAXLEN] PROGMEM =  "Killer Bees +";
  const char string91[MAXLEN] PROGMEM =  "Killer Bees!";
  const char string92[MAXLEN] PROGMEM =  "Kinder Im Verkehr 1";
  const char string93[MAXLEN] PROGMEM =  "Las Vegas Blackjack!";
  const char string94[MAXLEN] PROGMEM =  "Las Vegas Blackjack! (French v";
  const char string95[MAXLEN] PROGMEM =  "Las Vegas Blackjack! (modified";
  const char string96[MAXLEN] PROGMEM =  "Le Tresor Englouti + (VP+ only";
  const char string97[MAXLEN] PROGMEM =  "Looney Ballon (BR)";
  const char string98[MAXLEN] PROGMEM =  "Loony Balloon (no Plus graphic";
  const char string99[MAXLEN] PROGMEM =  "Loony Balloon +";
  const char string100[MAXLEN] PROGMEM =  "Martian Threat (Europe)(Proto)";
  const char string101[MAXLEN] PROGMEM =  "Matchmaker! / Logix! / Buzzwor";
  const char string102[MAXLEN] PROGMEM =  "Math-A-Magic! / Echo!";
  const char string103[MAXLEN] PROGMEM =  "Math-A-Magic! / Echo! (French ";
  const char string104[MAXLEN] PROGMEM =  "Mission Impossible (Brazil)(Pr";
  const char string105[MAXLEN] PROGMEM =  "Mod cart 14";
  const char string106[MAXLEN] PROGMEM =  "Mod cart 21";
  const char string107[MAXLEN] PROGMEM =  "Mod cart 28";
  const char string108[MAXLEN] PROGMEM =  "Mod cart 30";
  const char string109[MAXLEN] PROGMEM =  "Mod cart 31 G7400";
  const char string110[MAXLEN] PROGMEM =  "Mod cart 35";
  const char string111[MAXLEN] PROGMEM =  "Mod cart 36";
  const char string112[MAXLEN] PROGMEM =  "Mod play tag fix";
  const char string113[MAXLEN] PROGMEM =  "Mod Tutankham";
  const char string114[MAXLEN] PROGMEM =  "Monkeyshines!";
  const char string115[MAXLEN] PROGMEM =  "Morse";
  const char string116[MAXLEN] PROGMEM =  "Morse (French version)";
  const char string117[MAXLEN] PROGMEM =  "Moto Crash (modified - non-VP+";
  const char string118[MAXLEN] PROGMEM =  "Moto Crash (modified - non-VP+";
  const char string119[MAXLEN] PROGMEM =  "Moto Crash + (VP+ only)";
  const char string120[MAXLEN] PROGMEM =  "Musician";
  const char string121[MAXLEN] PROGMEM =  "Neutron Star (""Black Hole"" - n";
  const char string122[MAXLEN] PROGMEM =  "Neutron Star (Brazilian versio";
  const char string123[MAXLEN] PROGMEM =  "Neutron Star + (12K version - ";
  const char string124[MAXLEN] PROGMEM =  "Neutron Star + (12K version bu";
  const char string125[MAXLEN] PROGMEM =  "Neutron Star + (modified - 8K ";
  const char string126[MAXLEN] PROGMEM =  "New calculator.bin (Rene van d";
  const char string127[MAXLEN] PROGMEM =  "New kc-pacvid.bin";
  const char string128[MAXLEN] PROGMEM =  "New route66 Rafael Cardoso";
  const char string129[MAXLEN] PROGMEM =  "New_mrroboto.bin Ted (Foolery)";
  const char string130[MAXLEN] PROGMEM =  "New_puzzle-piece-panic Ted (Fo";
  const char string131[MAXLEN] PROGMEM =  "Nightfighter (Europe)(Proto)";
  const char string132[MAXLEN] PROGMEM =  "Nightmare (""Phantom House"" - n";
  const char string133[MAXLEN] PROGMEM =  "Nightmare +";
  const char string134[MAXLEN] PROGMEM =  "Nimble Numbers Ned";
  const char string135[MAXLEN] PROGMEM =  "Nimble Numbers Ned (modified -";
  const char string136[MAXLEN] PROGMEM =  "Norseman + (VP+ only)";
  const char string137[MAXLEN] PROGMEM =  "O Malabarista+Jogo da Velha (B";
  const char string138[MAXLEN] PROGMEM =  "O Segredo do Farao (Brazil)";
  const char string139[MAXLEN] PROGMEM =  "O2em version of Puzzle Piece P";
  const char string140[MAXLEN] PROGMEM =  "Out of this World! / Helicopte";
  const char string141[MAXLEN] PROGMEM =  "P.T. Barnum's Acrobats!";
  const char string142[MAXLEN] PROGMEM =  "P.T. Barnum's Acrobats! (Europ";
  const char string143[MAXLEN] PROGMEM =  "P.T. Barnum's Acrobats! (Europ";
  const char string144[MAXLEN] PROGMEM =  "P.T. Barnum's Acrobats! (modif";
  const char string145[MAXLEN] PROGMEM =  "Pachinko!";
  const char string146[MAXLEN] PROGMEM =  "Pairs / Space Rendezvous / Log";
  const char string147[MAXLEN] PROGMEM =  "Pick Axe Pete +";
  const char string148[MAXLEN] PROGMEM =  "Pick Axe Pete + (modified - Pl";
  const char string149[MAXLEN] PROGMEM =  "Pick Axe Pete!";
  const char string150[MAXLEN] PROGMEM =  "Pinball!";
  const char string151[MAXLEN] PROGMEM =  "Planet Lander!";
  const char string152[MAXLEN] PROGMEM =  "Playtag (Europe)(Proto)";
  const char string153[MAXLEN] PROGMEM =  "Pocket Billiards +";
  const char string154[MAXLEN] PROGMEM =  "Pocket Billiards + (Jopac vers";
  const char string155[MAXLEN] PROGMEM =  "Pocket Billiards!";
  const char string156[MAXLEN] PROGMEM =  "Pocket Billiards! (French vers";
  const char string157[MAXLEN] PROGMEM =  "Pong";
  const char string158[MAXLEN] PROGMEM =  "Pong (with extra features)";
  const char string159[MAXLEN] PROGMEM =  "Popeye";
  const char string160[MAXLEN] PROGMEM =  "Popeye (Brazilian version)";
  const char string161[MAXLEN] PROGMEM =  "Power Lords";
  const char string162[MAXLEN] PROGMEM =  "Power Lords (alternate)";
  const char string163[MAXLEN] PROGMEM =  "Q*bert";
  const char string164[MAXLEN] PROGMEM =  "Red Baron (Europe)(Proto)(Alt ";
  const char string165[MAXLEN] PROGMEM =  "Restaurant";
  const char string166[MAXLEN] PROGMEM =  "Restaurant (modified - NTSC ve";
  const char string167[MAXLEN] PROGMEM =  "Robot City (Europe)(Proto)";
  const char string168[MAXLEN] PROGMEM =  "Secret of the Pharaohs (2K ver";
  const char string169[MAXLEN] PROGMEM =  "Shark Hunter";
  const char string170[MAXLEN] PROGMEM =  "Shark Hunter (modified - NTSC ";
  const char string171[MAXLEN] PROGMEM =  "Showdown in 2100 A.D.";
  const char string172[MAXLEN] PROGMEM =  "Showdown in 2100 A.D. (Europea";
  const char string173[MAXLEN] PROGMEM =  "Sid the Spellbinder";
  const char string174[MAXLEN] PROGMEM =  "Smithereens +";
  const char string175[MAXLEN] PROGMEM =  "Smithereens + (modified 2 - wi";
  const char string176[MAXLEN] PROGMEM =  "Smithereens!";
  const char string177[MAXLEN] PROGMEM =  "Smithereens! (European version";
  const char string178[MAXLEN] PROGMEM =  "Speedway / Spin-Out / Crypto-L";
  const char string179[MAXLEN] PROGMEM =  "Speedway / Spin-Out / Crypto-L";
  const char string180[MAXLEN] PROGMEM =  "Speedway! / Spin-Out! / Crypto";
  const char string181[MAXLEN] PROGMEM =  "Speedway! / Spin-Out! / Crypto";
  const char string182[MAXLEN] PROGMEM =  "Speedway! / Spin-Out! / Crypto";
  const char string183[MAXLEN] PROGMEM =  "Spider-Man (Europe)(Proto)";
  const char string184[MAXLEN] PROGMEM =  "Spider-Man (Europe)(Proto)(Alt";
  const char string185[MAXLEN] PROGMEM =  "Super Bee (4K version)";
  const char string186[MAXLEN] PROGMEM =  "Super Bee (Brazil)";
  const char string187[MAXLEN] PROGMEM =  "Super Cobra";
  const char string188[MAXLEN] PROGMEM =  "Super Cobra (Brazilian version";
  const char string189[MAXLEN] PROGMEM =  "Syracuse";
  const char string190[MAXLEN] PROGMEM =  "Take the Money and Run!";
  const char string191[MAXLEN] PROGMEM =  "Take the Money and Run! (Frenc";
  const char string192[MAXLEN] PROGMEM =  "The Great Wall Street Fortune ";
  const char string193[MAXLEN] PROGMEM =  "The Mousing Cat (4K version)";
  const char string194[MAXLEN] PROGMEM =  "The Mousing Cat (8K version)";
  const char string195[MAXLEN] PROGMEM =  "The Mousing Cat (French versio";
  const char string196[MAXLEN] PROGMEM =  "The Quest for the Rings";
  const char string197[MAXLEN] PROGMEM =  "The Quest for the Rings (Frenc";
  const char string198[MAXLEN] PROGMEM =  "Thunderball +";
  const char string199[MAXLEN] PROGMEM =  "Thunderball + (Jopac version)";
  const char string200[MAXLEN] PROGMEM =  "Thunderball + (modified - Plus";
  const char string201[MAXLEN] PROGMEM =  "Thunderball!";
  const char string202[MAXLEN] PROGMEM =  "Thunderball! (French version)";
  const char string203[MAXLEN] PROGMEM =  "Trans American Rally + (bad du";
  const char string204[MAXLEN] PROGMEM =  "Trans American Rally + (VP+ on";
  const char string205[MAXLEN] PROGMEM =  "Turtles";
  const char string206[MAXLEN] PROGMEM =  "Turtles (European version)";
  const char string207[MAXLEN] PROGMEM =  "Tutankham";
  const char string208[MAXLEN] PROGMEM =  "Tutankham (NTSC version)";
  const char string209[MAXLEN] PROGMEM =  "Type & Tell";
  const char string210[MAXLEN] PROGMEM =  "Type & Tell (modified - PAL ve";
  const char string211[MAXLEN] PROGMEM =  "UFO +";
  const char string212[MAXLEN] PROGMEM =  "UFO!";
  const char string213[MAXLEN] PROGMEM =  "UFO! (European version)";
  const char string214[MAXLEN] PROGMEM =  "Verkehrsspiele 1";
  const char string215[MAXLEN] PROGMEM =  "Verkehrsspiele 2";
  const char string216[MAXLEN] PROGMEM =  "Volleyball!";
  const char string217[MAXLEN] PROGMEM =  "Volleyball! (French version)";
  const char string218[MAXLEN] PROGMEM =  "vp01+_F";
  const char string219[MAXLEN] PROGMEM =  "Vp11+_F";
  const char string220[MAXLEN] PROGMEM =  "Vp52+_F";
  const char string221[MAXLEN] PROGMEM =  "Wall Street (Brazil)";
  const char string222[MAXLEN] PROGMEM =  "War of Nerves!";
  
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
