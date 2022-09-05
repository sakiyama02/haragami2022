/*
*	FileIOクラス
*	作成者：崎山
*/

#pragma once

#include "../system/system.h"

using namespace std;

void my_printf(const char* format, ... );

class FileIO{
	private:
	FILE *fp_Log;

	public:
	char read(vector<char>& destination,char* file_path);
	int getSize(char* file_path);
	int log_open(void);
	void log_close(void);
	int log_set(char* str, int index);
	
	
	static FileIO &getInstance( )
	{
		static FileIO FileIO_;
		return FileIO_;
	}
};