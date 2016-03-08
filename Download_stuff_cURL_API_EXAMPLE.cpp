//http://curl.haxx.se/gknw.net/7.40.0/dist-w32/renamed-curl-7.40.0-devel-mingw32.zip   API LINK
#include <stdio.h> //standard calls provided by vs
#include <curl/curl.h> //Curl API 
#include<iostream> //to print to window 
#include <Windows.h> // to access MS windows exclusive functions. <NOT used>
#include <string> // because I am too lazy to write a string class...
using namespace std; // bad code here  and ill show you why in a coming meeting

//0x10; 	//0x is the prefix for hexidecimal  similar to  0FFh  for assembly programming
static int vabrado = 500; 	// global/ static variable that will hold the value of the frequency for the sound output.

size_t write_data(void*, size_t, size_t, FILE*);
void download_stuff(std::string);

int main(void) {
	cout << "Ramone's - Ultra Convinent - Very Inconspicious- Industry Oriented Programming Club Downloading Service\n";
	system("Color F3"); // set program color
	cout << "\t utility Created with Curl\n";

	//store your links in a string array.
	string dl_links[8] = { "http://imagej.nih.gov/ij/images/cat.jpg",
		"http://cdn.pokki.com/download/Pokki_TweekiSetup.exe",
		"http://freeglut.sourceforge.net/docs/api.php",
		"http://iweb.dl.sourceforge.net/project/freeglut/freeglut/3.0.0/freeglut-3.0.0.tar.gz",
		//"http://www.cycle-planet.com/ot/calculuslarsonedwards.pdf"
		"http://curl.haxx.se/gknw.net/7.40.0/dist-w32/renamed-curl-7.40.0-devel-mingw32.zip",
		"http://www.textfiles.com/art/barney.txt",
		"https://codeload.github.com/greim/jcurl/zip/master/jcurl-master.zip",
		"http://www.portaudio.com/archives/portaudio_v18_1.zip" };


	// I call the download_stuff function with the address in my array
	for (int i = 0; i<8; i++)
		download_stuff(dl_links[i]);

	cout << "\n\n\n\n";
	cout << "Now enter an address: ";
	string yourlink;
	cin >> yourlink;
	download_stuff(yourlink);
	system("pause");
	return 0;
}





size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void download_stuff(std::string dl_link)
{
	using namespace std;
	CURL *curl;
	FILE *fp;
	CURLcode res;
	string dl_data = "";
	curl = curl_easy_init();
	/*Below is my algorithm to simplify the code process  you place the link and it will determine the extention
	further refinement can help prevent errors when trying to download from links from places such as youtube's (that have no ending extention)*/
	/*this code could be exploited to download malicious content/scripts  or helpful for quickly downloading utilities from some server in your office*/
	//PS: this is why most people wish to see the source code before running, there is alot of risk running  unknown 3rd party applications such as the program I just made.
	//PSS: I wont try to get a worm on your pc
	//PSSS: Program should not be able to work on any other operating system besides windows; UNLESS,  you compile for that operating system.

	int fnameplace;
	for (fnameplace = dl_link.length(); dl_link[fnameplace - 1] != '/'; fnameplace--)
	{
		//calculates the portion of the address that contains the file name and extention;
	}
	for (int z = fnameplace; z < dl_link.length(); z++)
	{
		//store the name of the file to feed into the download function.
		dl_data += dl_link[z];
	}
	cout << "Downloading: " + dl_data << endl;
	if (curl) {
		system("Color 0C");
		//high byte in this case (0) determines background color from 0-F hex
		//low byte in this case (C) determines text color from 0-F hex
		//try playing with this if youre board with the standard look of your commandline in windows.

		char *url = (char*)dl_link.c_str();   
		/* The vs string class as a function(c_str()) that can return the string as a constant char array
		    I cannot use constants here so I'll have to cast it to a regular char pointer.*/

		char *outfilename = (char*)dl_data.c_str();
		//cout << url<< endl; //prints the link; FOR DEBUG
		fp = fopen(outfilename, "wb");  //write-binary    // list of modes here <http://www.cplusplus.com/reference/cstdio/fopen/>
		curl_easy_setopt(curl, CURLOPT_URL, url);  //retrieves the data
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); // function pointers used to determine what to do with the data
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // a file will be created on the hard drive  and filled with the data found.
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		//the beep to know its done;
		system("Color F3");
		Beep((DWORD)vabrado, (DWORD)100);

		//does a quick beep sound  (pitch is controlled in the first argument with (vabrado) must be some 32 bit value link an int)
		// second argument determines the sound length (period) must also be some 32 bit value.
		vabrado += 255;  // increases the pitch per downloaded file so you know how close to done you are.

		fclose(fp);
	}
}