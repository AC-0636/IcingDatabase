//
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <fstream>
#include <spatialite/gaiageo.h>
#include <spatialite.h>
#include <spatialite\sqlite3.h>
////////timer use////
#include <chrono>
////////
using namespace std;

//general temp variable
int i, j, k;

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
	for (i = 0; i <DataSize; i++)
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
	for (i = 0; i <DataSize; i++)
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
	for (i = 0; i <LineCounter-1; i++)
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
			for (k = 0; k < DataSize; k++)
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

void CreateDB(int argc, char* argv[])
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char *sql;

	rc = sqlite3_open("Icing.db", &db);
	/*sql = "CREATE TABLE IF NOT EXISTS AltitudeID("\
		"TableID INT PRIMARY KEY NOT NULL,"\
		"Altitude INT NOT NULL );";
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);*/
	/*if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit;
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}*/
	sqlite3_close(db);
}



//AltitudeID table set up
//Table ID = Identical id
//Altitude = corresponding altitude
bool AltitudeIDTableSetup(sqlite3 *db)
{
	bool bRet = false;
	char *zErrMsg = 0;
	int rc;
	const char *sql;
	string str1 = "INSERT INTO AltitudeID(TableID,Altitude) VALUES('";
	int id = 1;
	int al = 1000;

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);



	for (int i = 0; i < 30; i++)
	{
		string str2 = to_string(id);
		string str3 = to_string(al);
		string tempstr = str1 + str2 + "','" + str3 + "');";
		sql = tempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		id++;
		al = al + 1000;
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);

	return bRet;
}

bool CreateICSEVTable(sqlite3 *db)
{
	bool bRet = false;
	char *zErrMsg = 0;
	int rc;
	const char *sql;
	string str = "CREATE TABLE IF NOT EXISTS ";
	int id = 1;
	void* cache;
	char addgeom[1024];

	cache = spatialite_alloc_connection();
	spatialite_init_ex(db, cache, 0);

	sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &zErrMsg);
	//Create 30 table for both icing severity and sipd
	for (int i = 0; i < 30; i++)
	{
		string str1 = to_string(id);
		string str2 = "IcingInfo" + str1;
		string tempstr = str + str2 + "("\
			"Altitude INT,"\
			"Latitude DOUBLE,"\
			"Longitude DOUBLE,"\
			"ICSEV INT,"\
			"SLD DOUBLE,"\
			"ICPRB DOUBLE);";
		sql = tempstr.c_str();
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		/*if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		}
		else {
		fprintf(stdout, "Table created\n");
		}*/

		rc = sqlite3_exec(db, "SELECT InitSpatialMetaData();", nullptr, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			cout << "CreateSpatialMetaData error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
		}
		string str3 = "SELECT AddGeometryColumn('IcingInfo"+str1;
		string str4 = "', 'geom', 4326, 'POINTZ', 'XYZ');";
		str2 = str3 + str4;
		sql = str2.c_str();
		rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg); //"SELECT InitSpatialMetaData();"
		if (rc != SQLITE_OK)
		{
			cout << "CreateSpatialMetaData error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
		}



		id++;
	}
	sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &zErrMsg);
	return bRet;
}


//fill the 30 tables
bool FillTable(sqlite3 *db, int Altitude)
{
	bool bRet = false;
	char *zErrMsg = 0;
	const char *sql;
	char sql1[1024];
	char sql2[1024];
	int rc;
	string LatStr, LongStr, IcsevStr, SipdStr,IcprbStr, str1, str2, str3, tempstr;
	string IDnumber = to_string(Altitude / 1000);

	rc = sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);


	for (i = 0; i < DataSize; i++)
	{
		sprintf_s(sql1, "INSERT INTO IcingInfo%d (Altitude, Latitude, Longitude, ICSEV, SLD, ICPRB,geom) VALUES(",Altitude/1000);
		sprintf_s(sql2, "%d,%f,%f,%f,%f,%f,",Altitude,SEVetSLD[i][0],SEVetSLD[i][1],SEVetSLD[i][2],SEVetSLD[i][3],SEVetSLD[i][4]);
		strcat_s(sql1, sql2);
		sprintf_s(sql2, "GeomFromText('POINTZ(%f %f %f)'", SEVetSLD[i][0], SEVetSLD[i][1], Altitude);
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




int main()
{
	chrono::steady_clock sc;   // create an object of `steady_clock` class
	auto start = sc.now();

	//////////////////////////////////////////////////////
	//Decoding the download .bin file using the wgrib application
	system("Wgrib2Script.bat");
	/////////////////////////////////

	CreateDB(NULL, NULL);
	cout << "Database Icing.db created" << endl;
	sqlite3 *DB = NULL;
	int path = sqlite3_open("Icing.db", &DB);
	//AltitudeIDTableSetup(DB);
	cout << "Set up AltitudeID Table" << endl;
	CreateICSEVTable(DB);
	cout << "IcingInfo tables created" << endl;
	cout << "Inserting data to IcingInfo tables...." << endl;

	//use for testing
	/*ReadICSEVfile(20000);
	TakeICSEVinfo();
	ReadSIPDfile(20000);
	TakeSIPDinfo();
	ReadICPRBfile(20000);
	TakeICPRBinfo();
	FillTable(DB, 20000);*/

	//get all 30 tables 
	for (int p = 0; p < 30; p++)
	{
		ReadICSEVfile(RawAl);
		TakeICSEVinfo();
		ReadSIPDfile(RawAl);
		TakeSIPDinfo();
		ReadICPRBfile(RawAl);
		TakeICPRBinfo();
		FillTable(DB, RawAl);
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