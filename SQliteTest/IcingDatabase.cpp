//
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <fstream>
#include "sqlite3.h"
#include "spatialite.h"
#include "spatialite\gaiageo.h"
////////timer use////
#include <chrono>
////////
using namespace std;

//temp variable for counter
//int i, j, k;

//temp value
double tempLoc;
string tempLocStr;
double tempVal;
string tempValStr;

//read file thing
string LineReader;
int LineCounter;
const int DataSize = 151987;
string ICSEVFileData[DataSize];

int RawAl = 1000; //in ft
string FileAl;
string FileHead;
string FileTail;
string FileName;
string tempstr;

//[][0]:Lat; [][1]Long; [][2]ICSEV; [][3]SIPD; [][4]ICPRB;
double SEVetSLD[DataSize][5] = {NULL};


/////////////////////////////////////////////////////////////////////////////





void ReadICSEVfile(int Altitude) //read file
{
	LineCounter = 0;
	FileAl = to_string(Altitude);
	FileHead = "../wgrib2/data/OutputData/ICSEV/";
	FileTail = "ft.csv";
	FileName = FileHead + FileAl + FileTail;
	ifstream TestDataFile(FileName);
	if (TestDataFile.is_open())
	{
		while (!TestDataFile.eof())
		{
			getline(TestDataFile, LineReader); //read file line by line
			ICSEVFileData[LineCounter] = LineReader; //put read line in ICSEVFileData[], one line one spot 
			LineCounter++;
		}
	}
	TestDataFile.close();
}


void TakeICSEVinfo()
{
	int pos;
	for (int i = 0; i <DataSize; i++)
	{
		tempstr = ICSEVFileData[i];
		//use the "level" from "sea level" that all the file shall the same
		size_t FindL = tempstr.find("level");
		//find "level" and move the pivit to the location before the longitude value
		pos = FindL + 7;
		//reuse tempstr to represent the part of info from "l" to the end of the line
		tempstr = ICSEVFileData[i].substr(pos, sizeof(ICSEVFileData[i]));


		//find "," from the new tempstr -> get Long value
		size_t FindComma1 = tempstr.find(",");
		//find Longitude in string format
		tempLocStr = tempstr.substr(0, FindComma1);
		//convert into double type
		tempLoc = stod(tempLocStr);
		//put obtained longitude value in SEVetSLD[][1]
		SEVetSLD[i][1] = tempLoc;

		//reuse tempstr to represent the part starting from the comma+1 between long and lat to the end of the line
		tempstr = tempstr.substr(FindComma1 + 1, sizeof(tempstr));
		//find "," from the new tempstr -> get Lat value
		size_t FindComma2 = tempstr.find(",");
		//find Latitude in string format
		tempLocStr = tempstr.substr(0, FindComma2);
		//convert into double type
		tempLoc = stod(tempLocStr);
		//put obtained latitude value in SEVetSLD[][0]
		SEVetSLD[i][0] = tempLoc;

		//reuse tempstr to represent the required ICSEV/SIPD value
		//tempstr = tempstr.substr(FindComma2+1, sizeof(tempstr));
		//but actually at this point the new tempstr itself is the required value, so:		
		//find needed value in string format
		tempValStr = tempstr.substr(FindComma2 + 1, sizeof(tempstr));
		tempVal = stoi(tempValStr);
		SEVetSLD[i][2] = tempVal;

	}
}

void ReadSIPDfile(int Altitude) //read file
{
	LineCounter = 0;
	FileAl = to_string(Altitude);
	FileHead = "../wgrib2/data/OutputData/SIPD/";
	FileTail = "ft.csv";
	FileName = FileHead + FileAl + FileTail;
	ifstream TestDataFile(FileName);//("../wgrib2/data/OutputData/ICSEV/xxft.csv");
	if (TestDataFile.is_open())
	{
		while (!TestDataFile.eof())
		{
			getline(TestDataFile, LineReader); //read file line by line
			ICSEVFileData[LineCounter] = LineReader; //put read line in ICSEVFileData[], one line one spot 
			LineCounter++;
		}
	}
	TestDataFile.close();
}

void TakeSIPDinfo()
{
	int pos;
	for (int i = 0; i <DataSize; i++)
	{
		tempstr = ICSEVFileData[i];
		//use the "level" from "sea level" that all the file shall the same
		size_t FindL = tempstr.find("level");
		//find "level" and move the pivit to the location before the longitude value
		pos = FindL + 7;
		//reuse tempstr to represent the part of info from "l" to the end of the line
		tempstr = ICSEVFileData[i].substr(pos, sizeof(ICSEVFileData[i]));

		//find "," from the new tempstr -> get Long value
		size_t FindComma1 = tempstr.find(",");

		//reuse tempstr to represent the part starting from the comma+1 between long and lat to the end of the line
		tempstr = tempstr.substr(FindComma1 + 1, sizeof(tempstr));
		//find "," from the new tempstr -> get Lat value
		size_t FindComma2 = tempstr.find(",");

		//reuse tempstr to represent the required ICSEV/SIPD value
		//tempstr = tempstr.substr(FindComma2+1, sizeof(tempstr));
		//but actually at this point the new tempstr itself is the required value, so:		
		//find needed value in string format
		tempValStr = tempstr.substr(FindComma2 + 1, sizeof(tempstr));
		tempVal = stod(tempValStr);
		SEVetSLD[i][3] = tempVal;
	}
}

void ReadICPRBfile(int Altitude) //read file
{
	LineCounter = 0;
	FileAl = to_string(Altitude);
	FileHead = "../wgrib2/data/OutputData/ICPRB/";
	FileTail = "ft.csv";
	FileName = FileHead + FileAl + FileTail;
	ifstream TestDataFile(FileName);//("../wgrib2/data/OutputData/ICSEV/XXft.csv");
	if (TestDataFile.is_open())
	{
		while (!TestDataFile.eof())
		{
			getline(TestDataFile, LineReader); //read file line by line
			ICSEVFileData[LineCounter] = LineReader; //put read line in ICSEVFileData[], one line one spot 
			LineCounter++;
		}
	}
	TestDataFile.close();
}

void TakeICPRBinfo()
{
	int pos; 
	double tempLat, tempLong;
	for (int i = 0; i <LineCounter-1; i++)
	{
			tempstr = ICSEVFileData[i];
			//use the "level" from "sea level" that all the file shall the same
			size_t FindL = tempstr.find("level");
			//find "level" and move the pivit to the location before the longitude value
			pos = FindL + 7;
			//reuse tempstr to represent the part of info from "l" to the end of the line
			tempstr = ICSEVFileData[i].substr(pos, sizeof(ICSEVFileData[i]));


			//find "," from the new tempstr -> get Long value
			size_t FindComma1 = tempstr.find(",");
			//find Longitude in string format
			tempLocStr = tempstr.substr(0, FindComma1);
			//convert into double type
			tempLong = stod(tempLocStr);
			//put obtained longitude value in SEVetSLD[][1]
			//IcprbTable[i][1] = tempLong;

			//reuse tempstr to represent the part starting from the comma+1 between long and lat to the end of the line
			tempstr = tempstr.substr(FindComma1 + 1, sizeof(tempstr));
			//find "," from the new tempstr -> get Lat value
			size_t FindComma2 = tempstr.find(",");
			//find Latitude in string format
			tempLocStr = tempstr.substr(0, FindComma2);
			//convert into double type
			tempLat = stod(tempLocStr);
			//put obtained latitude value in SEVetSLD[][0]
			//IcprbTable[i][0] = tempLat;

			//reuse tempstr to represent the required ICSEV/SIPD value
			//tempstr = tempstr.substr(FindComma2+1, sizeof(tempstr));
			//but actually at this point the new tempstr itself is the required value, so:		
			//find needed value in string format
			tempValStr = tempstr.substr(FindComma2 + 1, sizeof(tempstr));
			tempVal = stod(tempValStr);
			//find the point with the same Lat and Long, and insert the 
			for (int k = 0; k < DataSize; k++)
			{
				if (tempLong == SEVetSLD[k][1] && tempLat == SEVetSLD[k][0])
				{
					SEVetSLD[k][4] = tempVal;
				}
			}
	}
}



static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}





//drop table of the old database version
bool ClearOldTable(sqlite3* db)
{
	bool bRet = false;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
	int id = 1000; // data value start from 1000ft
	//sql querry for dropping table: DROP TABLE tablename
	string str= "DROP TABLE Alt";
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	for (int i = 0; i < 30; i++)
	{
		string str1 = to_string(id)+"ft";
		string tempstr = str + str1;
		sql = tempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		id += 1000;
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool CreateTable(sqlite3 *db)
{
	bool bRet = false;
	char *zErrMsg = 0;
	int rc;
	const char *sql;
	int id = 1000; // data value start from 1000ft
	void* cache;
	char addgeom[1024];
	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);

	//sql create table querry: CREATE TABLE IF NOT EXISTS tablename(ColumnOneName ColumnOneType, ColumnTwoName ColumnTwoType, ....)
	string str = "CREATE TABLE IF NOT EXISTS "; 
	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	//Create 30 table for three types of icing data
	for (int i = 0; i < 30; i++)
	{
		string str1 = to_string(id);
		string str2 = "Alt" + str1 + "ft";
		string tempstr = str + str2 + "("\
			"Altitude INT,"\
			"Latitude DOUBLE,"\
			"Longitude DOUBLE,"\
			"ICSEV INT,"\
			"SLD DOUBLE,"\
			"ICPRB DOUBLE);";
		sql = tempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


		rc = sqlite3_exec(db, "SELECT InitSpatialMetaData();", nullptr, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			cout << "CreateSpatialMetaData error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
		}
		string str3 = "SELECT AddGeometryColumn('Alt"+str1+"ft";
		string str4 = "', 'geom', 4326, 'POINTZ', 'XYZ');";
		str2 = str3 + str4;
		sql = str2.c_str();
		rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
		if (rc != SQLITE_OK)
		{
			cout << "CreateSpatialMetaData error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
		}



		id+=1000;
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}

bool FillFullDatabase(sqlite3* db, int Altitude)
{

	bool bRet = false;
	char* zErrMsg = 0;
	const char* sql;
	char sql1[1024];
	char sql2[1024];
	int rc;
	string LatStr, LongStr, IcsevStr, SipdStr, IcprbStr, str1, str2, str3, tempstr;

	rc = sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);

	//[] [0] :Lat; [] [1] Long; [] [2] ICSEV; [] [3] SIPD; [] [4] ICPRB;
	for (int i = 0; i < DataSize; i++)
	{
		sprintf_s(sql1, "INSERT INTO Alt%dft (Altitude, Latitude, Longitude, ICSEV, SLD, ICPRB,geom) VALUES(", Altitude);
		sprintf_s(sql2, "%d,%f,%f,%f,%f,%f,", Altitude, SEVetSLD[i][0], SEVetSLD[i][1], SEVetSLD[i][2], SEVetSLD[i][3], SEVetSLD[i][4]);
		strcat_s(sql1, sql2);
		sprintf_s(sql2, "GeomFromText('POINTZ(%f %f %f)'", SEVetSLD[i][1], SEVetSLD[i][0], Altitude);
		strcat_s(sql1, sql2);
		strcat_s(sql1, ", 4326))");

		rc = sqlite3_exec(db, sql1, NULL, NULL, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "ErrorICI: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}

	}
	rc = sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return bRet;
}




////fill the 30 tables for full icing database
bool FillEastDatabase(sqlite3 *db, int Altitude)
{

	bool bRet = false;
	char *zErrMsg = 0;
	const char *sql;
	char sql1[1024];
	char sql2[1024];
	int rc;
	string LatStr, LongStr, IcsevStr, SipdStr,IcprbStr, str1, str2, str3, tempstr;

	rc = sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);

	//[] [0] :Lat; [] [1] Long; [] [2] ICSEV; [] [3] SIPD; [] [4] ICPRB;
	for (int i = 0; i < DataSize; i++)
	{
		if ( (SEVetSLD[i][0] > 39.5283 && SEVetSLD[i][0]<41.7495) && (SEVetSLD[i][1] > -76.0397 && SEVetSLD[i][1] < -71.9736)) //get only the data in the east coast
		{
			sprintf_s(sql1, "INSERT INTO Alt%dft (Altitude, Latitude, Longitude, ICSEV, SLD, ICPRB,geom) VALUES(", Altitude);
			sprintf_s(sql2, "%d,%f,%f,%f,%f,%f,", Altitude, SEVetSLD[i][0], SEVetSLD[i][1], SEVetSLD[i][2], SEVetSLD[i][3], SEVetSLD[i][4]);
			strcat_s(sql1, sql2);
			sprintf_s(sql2, "GeomFromText('POINTZ(%f %f %f)'", SEVetSLD[i][1], SEVetSLD[i][0], Altitude);
			strcat_s(sql1, sql2);
			strcat_s(sql1, ", 4326))");

			rc = sqlite3_exec(db, sql1, NULL, NULL, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				fprintf(stderr, "ErrorICI: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}

		}

	}
	rc = sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	return bRet;
}





// generate csv file of the icing data (for full)
// Ref:https://stackoverflow.com/questions/25201131/writing-csv-files-from-c
void MakeFullCsv(int Altitude)
{
	string outFileName = to_string(Altitude);
	string outFullPath = "./output/CSVs/" + outFileName + ".csv";
	ofstream outcsv;
	outcsv.open(outFullPath);
	outcsv << "Altitude,Latitude,Longitude,ICSEV,SLD,ICPRB\n";
	for (int i = 0; i < DataSize; i++)
	{
		outcsv << Altitude << "," << SEVetSLD[i][0] << "," << SEVetSLD[i][1] << "," << SEVetSLD[i][2] << "," << SEVetSLD[i][3] << "," << SEVetSLD[i][4] << endl;
	}
	outcsv.close();
}



// generate csv file of the icing data (for the EAST)
// Ref:https://stackoverflow.com/questions/25201131/writing-csv-files-from-c
void MakeEastCsv(int Altitude)
{
	string outFileName = to_string(Altitude);
	string outFullPath = "./east_output/CSVs/" + outFileName + ".csv";
	ofstream outcsv;
	outcsv.open(outFullPath);
	outcsv << "Altitude,Latitude,Longitude,ICSEV,SLD,ICPRB\n";
	for (int i = 0; i < DataSize; i++)
	{
		if ((SEVetSLD[i][0] > 39.5283 && SEVetSLD[i][0] < 41.7495) && (SEVetSLD[i][1] > -76.0397 && SEVetSLD[i][1] < -71.9736))
		{
			outcsv << Altitude << "," << SEVetSLD[i][0] << "," << SEVetSLD[i][1] << "," << SEVetSLD[i][2] << "," << SEVetSLD[i][3] << "," << SEVetSLD[i][4] << endl;
		}
	}
	outcsv.close();
}






int main()
{
	chrono::steady_clock sc;   // create an object of `steady_clock` class
	auto start = sc.now();

	//////////////////////////////////////////////////////
	////Decoding the download .bin file using the wgrib application
	system("Wgrib2Script.bat");
	/////////////////////////////////

	//create full icing database
	sqlite3 *fullDB = NULL;
	int full = sqlite3_open("./output/icing.db", &fullDB);
	cout << "Initializing full icing database..." << endl;
	ClearOldTable(fullDB);
	CreateTable(fullDB);

	//create east icing database
	sqlite3* eastDB = NULL;
	int east = sqlite3_open("./east_output/east_icing.db", &eastDB);
	cout << "Initializing east icing database..." << endl;
	ClearOldTable(eastDB);
	CreateTable(eastDB);



	cout << "Inserting data to database...." << endl;

	//get all 30 tables 
	for (int p = 0; p < 30; p++)
	{
		ReadICSEVfile(RawAl);
		TakeICSEVinfo();
		ReadSIPDfile(RawAl);
		TakeSIPDinfo();
		ReadICPRBfile(RawAl);
		TakeICPRBinfo();
		FillFullDatabase(fullDB, RawAl);
		MakeFullCsv(RawAl);
		FillEastDatabase(eastDB, RawAl);
		MakeEastCsv(RawAl);
		RawAl = RawAl + 1000;
	}






	cout << "Done" << endl;
	//timer for display, can be remove
	auto end = sc.now();       // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
	cout << "Operation took: " << time_span.count() << " seconds !!!";

	system("pause");
	return 0;
}