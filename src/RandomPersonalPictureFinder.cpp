#include "RandomPersonalPictureFinder.h"

static int types = 26;
static std::string cams[] = {
"dcp0", // Kodak
"dsc0", // Nikon
"dscn", // Nikon
"mvc-", //Sony Mavica 1
"mvc0", //Sony Mavica
"P101", // Olympus?  First 3 are dates, work on this...
"P",    //PMDD where M is hex
"IMG_", // Canon
"imag", // RCA and Samsung
"1",     // Canon 1TH-TH##  thousands, hundreds
"dscf",// Fuji Finepix
"pdrm", // Toshiba PDR
"IM00", // HP Photosmart
"EX00", // HP Photosmart timelapse?
"dc", // Kodak dc-40,50,120 dc####(l|m|s)
"pict", // Minolta Dimage pict####.jpg
"P00", //Kodak DC290 p#######.jpg
"", // Casio QV3000 mmdd####.jpg
"", // Casio QV-7000: YYMDD###.JPG
"imgp", // pentax optio S: imgp####.jpg
"pana", // Panasonic video camera still PANA####.jpg
"1",     // Canon 1TH-TH##  thousands, hundreds, with _IMG tacked on
"HPIM", // HP Photosmart HPIM####.jpg
"PCDV", // Cheap camera pcdv####.jpg
"_MG_", // Canon Raw conversion
"IMG_"}; // Android? IMG_YYYYMMDD_HHMMSS



//site="http://images.google.com/images?q=";
//site="http://www.bing.com/images/search?q=";
static std::string site="http://images.google.com/images?q=";

int getRandomIndex(int max) {
	return ofRandom(max);
}


std::string RandomPersonalPictureFinder::generateFileName() {
	//var size = document.menufrm.imgsz.value;
	std::string size = "";

	int range = 4000;
	int width = 4;
	int choice = getRandomIndex(types);
	//choice = 25;
	std::string str = cams[choice];
	if (choice == 3) {
		range = 400; //Mavica doesn't have many pictures
		width = 3;
	}
	if (choice == 4) {
		range = 500; //Mavica doesn't have many pictures
		width = 4;
	}
	if (choice == 6) {
		range = 50; // PMDD
		width = 4;
		std::string strmonth = ofToString(getRandomIndex(13));
		if (strmonth == "10") strmonth = "a";
		if (strmonth == "11") strmonth = "b";
		if (strmonth == "12") strmonth = "c";
		std::string strdate = ofToString(getRandomIndex(31), 2, '0');
		str += strmonth;
		str += strdate;
	}
	if (choice == 8) {
		range = 130; //Not a lot of RCA pics
		width = 4;
	}
	if (choice == 9) {
		range = 100; // 1TH-TH##
		width = 2;
		std::string strthou = ofToString(getRandomIndex(3), 2, '0');
		str += strthou;
		str += "-";
		str += strthou;
	}
	if (choice == 11) {
		range = 600; //Not a lot of Toshiba pics
		width = 4;
	}
	if (choice == 12) {
		range = 850; //Not a lot of HP pics
		width = 4;
	}
	if (choice == 13) {
		range = 100; //Not a lot of HP pics
		width = 4;
	}

	if (choice == 15) {
		range = 600;
		width = 4;
	}

	if (choice == 16) {
		range = 12000;
		width = 5;
	}

	if (choice == 17) {
		range = 30; // PMDD
		width = 4;
		std::string strmonth = ofToString(getRandomIndex(13), 2, '0');

		std::string strdate = ofToString(getRandomIndex(31), 2, '0');
		str += strmonth;
		str += strdate;
	}

	if (choice == 18) {
		range = 50; // PMDD
		width = 3;
		std::string stryear = ofToString(getRandomIndex(3), 2, '0');
		std::string strmonth = ofToString(getRandomIndex(13));
		if (strmonth == "10") strmonth = "a";
		if (strmonth == "11") strmonth = "b";
		if (strmonth == "12") strmonth = "c";
		std::string strdate = ofToString(getRandomIndex(31), 2, '0');
		str += stryear;
		str += strmonth;
		str += strdate;
	}

	if (choice == 19) {
		range = 2000;
		width = 4;
	}

	if (choice == 20) {
		range = 200;
		width = 4;
	}

	if (choice == 22) {
		range = 3700;
		width = 4;
	}
	if (choice == 23) {
		range = 300;
		width = 4;
	}

	std::string strfoo = ofToString(getRandomIndex(range), width, '0');
	str += strfoo;

	if (choice == 14) {
		std::string strsize = ofToString(getRandomIndex(3));
		if (strsize == "0") strsize = "s";
		if (strsize == "1") strsize = "m";
		if (strsize == "2") strsize = "l";
		std::string strnumber= ofToString(getRandomIndex(190), 4, '0');
		str = cams[choice];
		str += strnumber;
		str += strsize;
	}

	if (choice == 21) {
		range = 100; // 1TH-TH##
		width = 2;
		std::string strthou = ofToString(getRandomIndex(90), 2, '0');
		str = "1";
		str += strthou;
		str += "-";
		str += strthou;
		strfoo = ofToString(getRandomIndex(range), width, '0');
		str += strfoo;
		str += "_IMG";
	}

	if (choice == 25) {
		std::string stryear = ofToString(getRandomIndex(3)+7, 2, '0');
		std::string strmonth = ofToString(getRandomIndex(11)+1, 2, '0');
		std::string strdate = ofToString(getRandomIndex(30)+1, 2, '0');
		str = cams[choice];
		str += "20";
		str += stryear;
		str += strmonth;
		str += strdate;
		str += "_*";
	}

	std::string url = site + str + ".jpg" + size;
	if (choice == 30) {
		std::string strnumber= ofToString(getRandomIndex(99), 2, '0');
		str = cams[choice];
		str += strnumber;
		url = site + str + "+site%3Apbase.com&hl=en&imgsz=" + size + "&imgsafe=off";
	}

	return url + "&adlt=off";
}
