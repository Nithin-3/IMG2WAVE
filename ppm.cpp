#include <fstream>
using namespace std;
int main(){
    ofstream nin;
    ifstream rt;
    rt.open("img.wav",ios::binary);
    nin.open("img.ppm",ios_base::binary);
    rt.tellg();
    rt.seekg(44);
    nin << "P3"<<' ';
    while(!rt.eof()){
        int w;
        rt.read(reinterpret_cast<char*>(&w),2);
        nin << w << ' ';
    }
    nin.close();
    rt.close();
    return 0;

}
