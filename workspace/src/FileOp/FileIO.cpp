/*
*	FileIOクラス
*	作成者：崎山
*/

#include "../../include/FileOp/FileIO.hpp"

/*
*	ファイル読み込み
*	destinationにファイルデータを格納する
*/

char FileIO::read(vector<char>& destination,char* file_path){
	FILE *fp;

	if (( fp = fopen ( file_path,"r" )) == NULL ){
		printf("file open err\n");
		return -1;
	}

	if ( fread( &destination[0],destination.size(),1,fp ) == 0 ){
		printf("file read err\n");
		return -1;
	}

	fclose(fp);

	return 0;
}

int FileIO::getSize(char* file_path){

	FILE *fp;
	int fsize = 0;

	if (( fp = fopen ( file_path,"r" )) == NULL ){
		printf("file open err\n");
		return -1;
	}

	while (true) {
        if (fgetc(fp) == EOF) {
            if (feof(fp)) {
                break;
            }
            else if (ferror(fp)) {
                fclose(fp);
				break;
            }
		}
		fsize++;
    }

	fclose(fp);

	return fsize;

}

int FileIO::log_open(void){

	#ifndef EV3
	if (( fp_Log = fopen ( "mLog.txt","w" )) == NULL ){
		printf("file open err\n");
		return -1;
	}
	#else
	if (( fp_Log = fopen ( "/ev3rt/res/mLog.txt","a" )) == NULL ){
		printf("file open err\n");
		return -1;
	}
	
	if( bt == NULL && flg == 0){
		bt = ev3_serial_open_file(EV3_SERIAL_BT);
		if(bt!=NULL){
			printf("bt open err\n");
		}
		flg = 1;
	}
	#endif
	return 1;

}

void FileIO::log_close(void){
	fclose(fp_Log);
	if(bt!=NULL){
		fclose(bt);
	}
}

int FileIO::log_set(char* str, int index){
	if ( fwrite( str,index,1,fp_Log ) == 0 ){
		printf("file write err\n");
		return -1;
	}
	if(bt == NULL) return 1;
	if ( fwrite( str,index,1,bt ) == 0 ){
		//printf("bt write err\n");
		return -1;
	}

	return 1;
}

void my_printf(const char* format, ... ) {
	char buf[256];
	va_list ap;
	int index = 0;

	for( index = 0; index < 256; index ++ ) {
		buf[index] = 0;
	}
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);

	for( index = 0; buf[index] != 0; index ++ ) {
		;
	}

	FileIO &tmp = FileIO::getInstance();
	tmp.log_set(&buf[0], index);
	return;
}