// MyOCR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dirent.h" 

#include <iostream>
#include <string>


using namespace std;

void get_text_from_png(FILE *fp, char* input_DirName, string fileName)
{
	string result = "";
	string str_cmd = "tesseract " + string(input_DirName) + "/" + fileName + " stdout -l eng";
#ifdef _WIN32
	FILE *ls = _popen(str_cmd.c_str(), "r");
#else
	FILE *ls = popen(str_cmd.c_str(), "r");
#endif
	char buf[256];
	while (fgets(buf, sizeof(buf), ls) != 0) {
		if (buf[0] != '\f')
			result += buf;
		printf("%s", buf);
		/*...*/
	}
#ifdef _WIN32
	_pclose(ls);
#else
	pclose(ls);
#endif

	fprintf(fp, "--------------------------------\n");
	fprintf(fp, fileName.c_str());
	fprintf(fp, "=====>:\n");
	fprintf(fp, "\n");
	fprintf(fp, result.c_str());
	//fputs("This is testing for fputs...\n", fp);
}

int main() {
	//system("tesseract price2.png stdout -l eng");

	char input_DirName[100];
	cin >> input_DirName;

	int i = 0;
	DIR *dir;
	struct dirent *direntry; //could be a file, or a directory
	FILE *fp;

	fp = fopen("result_text.txt", "w+");


	dir = opendir(input_DirName);
	if (!dir) {
		printf("Error: directory did not open!\n");
		return 1;
	}

	while ((direntry = readdir(dir)) != NULL) {
		//printf("%s\n",direntry->d_name);
		if ((strcmp(direntry->d_name, ".") != 0) && (strcmp(direntry->d_name, "..") != 0))
			get_text_from_png(fp, input_DirName, direntry->d_name);
	}

	closedir(dir);
	printf("\n");
	fclose(fp);

	return 0;
}

