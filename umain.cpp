
#include <iostream>
#include <fcntl.h> 
#include <io.h>    
#include <string>
#include <locale>
#include <codecvt> 
#include <fstream>
#include <windows.h>
using namespace std;
int main()
{
    locale loc(locale(), new codecvt_utf8<wchar_t>);
    _setmode(fileno(stdin), 0x00040000);
    _setmode(fileno(stdout), 0x00040000);

    wcout << L"Chương trình đọc và xuất chuỗi tiếng Việt\n\n";

    // nhập họ tên
    wstring username;
    wcout << L"Nhập họ tên của bạn: ";
    getline(wcin, username);
    wcout << L">> Xin chào, " << username << L"!\n\n";

    // nhập giới tính
    wchar_t gender;
    wcout << L"Bạn là nam hay nữ:\n a. Nam\n b. Nữ\n";
    wcin >> gender;
    wcout << L">> Giới tính: ";
    if      (gender == L'a') wcout << L"Nam\n\n";
    else if (gender == L'b') wcout << L"Nữ\n\n";
    else                     wcout << L"Không xác định\n\n";

    // nhập tuổi
    int age;
    wcout << L"Nhập tuổi của bạn: ";
    wcin >> age;
    wcout << L">> Năm nay bạn được " << age << L" tuổi\n\n";


    // lưu file tiếng Việt (UTF-8 without BOM)  // UTF-8
    wofstream fout(L"..\\database\\account\\vietnamese.txt");
    if (!fout) {
        wcout << L"Không thể tạo file\n";
    } else {
        fout.imbue(loc);
        fout << username << L"\n" << gender << L"\n" << age << L"\n";
        wstring temp = L"Đây là file được lưu...\n";
        fout << temp;
        fout.close();
    }
    
    // đọc file tiếng Việt (định dạng UTF-8 without BOM)
    wifstream fin(L"..\\database\\account\\vietnamese.txt");
    if (!fin) {
        wcout << L"Không thể đọc file \n";
    } else {
        fin.imbue(loc);
        getline(fin, username);
        wstring temp;
        fin >> gender >> age;

        wcout << L"Họ tên: " << username << L"\nGiới tính: " 
        << (gender == L'a' ? L"Nam" : (gender == L'b' ? L"Nữ" : L"Không xác định"))
        << L"\nTuổi: " << age << L"\n\n";

        fin.close();
    }
    wcout << L"Chương trình kết thúc.\n";
}