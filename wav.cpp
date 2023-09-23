#include <fstream>
using namespace std;
const string CHUCK_ID = "RIFF";
const string CHUCK_SIZE = "----";
const string FORMAT = "WAVE";

const string SUBCHUCK = "fmt ";
const int SUBCHUCK_SIZE = 16;
const int AUDIO_FORMAT = 1;
const int CHANNEL = 1;
const int RATE = 44100;
const int BYTE_RATE = RATE * CHANNEL*(SUBCHUCK_SIZE / 8);
const int BLOCK_ALINE = CHANNEL * (SUBCHUCK_SIZE / 8);
const int BIT_PER_SAMP = 16;

const string SUBCHUCK2 = "data";
const string SUBCHUCK2_SIZE = "----";

const int amplit = 32760;
const double freq = 250;
void write(ofstream &file, int value, int size){
    file.write(reinterpret_cast<const char*>(&value),size);
}

int main(){
    ofstream nin;
    ifstream nit;
    nit.open("portrait_p3_comment_replicated.ppm",ios::binary);
    nin.open("img.wav",ios::binary);
    string dum = "";
    nit >> dum;
    if(nin.is_open()){
        nin << CHUCK_ID;
        nin << CHUCK_SIZE;
        nin << FORMAT;
        nin << SUBCHUCK;
        write(nin,SUBCHUCK_SIZE,4);
        write(nin,AUDIO_FORMAT,2);
        write(nin,CHANNEL,2);
        write(nin,RATE,4);
        write(nin,BYTE_RATE,4);
        write(nin,BLOCK_ALINE,2);
        write(nin,BIT_PER_SAMP,2);
        nin << SUBCHUCK2;
        nin << SUBCHUCK2_SIZE;
        int strt = nin.tellp();
        while (!nit.eof()){
            int i ;
            nit >> i;
            write(nin,i,2);
        }
        
        int end = nin.tellp();
        nin.seekp(strt - 4);
        write(nin,end-strt,4);
        nin.seekp(4,ios::beg);
        write(nin,end-8,4);
    }
    nin.close();
    return 0;
}