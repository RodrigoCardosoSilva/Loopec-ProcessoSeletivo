// Processo seletivo LoopCE 01/2015
// 2a Etapa
// Rodrigo Cardoso da Silva

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
    char ID_field[3], size_of_BMP[5], Offset_Pixel_Array[5], byte[1];
    int filesize, current_bit, ascii;
    fstream myfile, message_file;
    string message;

    myfile.open ("testImage.bmp", ios::in | ios::binary); //Load image.
    myfile.seekg(0, myfile.end);
    filesize=myfile.tellp(); // Get size of file.
    myfile.seekg(0, myfile.beg); // Set file pointer to begin of file.
    myfile.read(ID_field, 2); // Get ID_field (BM).
    myfile.seekg(10);
    myfile.read(Offset_Pixel_Array, 4); // Get address of the start of the pixel array.
    int pointer_to_bmp_array=(int)Offset_Pixel_Array[0];
    int ascii_pointer=1;
    myfile.seekg(pointer_to_bmp_array); //Now file points to pixel array area.

    while(myfile.tellp()<filesize) //Read each byte separately of the entire file.
    {
            myfile.read(byte, 1);
            current_bit=(uint8_t)byte[0]%2; //Get the LSB of the byte.
            current_bit=current_bit << (ascii_pointer-1); // Shift Left Logical to set bit at the right position.
            ascii=ascii+current_bit;
            if(ascii_pointer==8)
            {
                ascii_pointer=0;
                message.push_back((char)ascii);
                if(ascii==0)
                    break;
                ascii=0;
            }
            ascii_pointer++;
    }
    myfile.close();

    message_file.open("message_extracted.txt", ios::out);
    message_file << message;
    message_file.close();
    return(0);
}
