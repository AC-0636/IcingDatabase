# IcingDatabase
###############################
This program is created to obtain the icing information from GRIB.
**The database itself is not included since it excess the limited of the upload file size**
###############################

##Data Source / Reference Link / Tool##

######1. Aviation Weather Center (AWC) webpage##
https://aviationweather.gov/icing/fip
This webpage display a graphical view of the icing condition, this is used to compare and verify the decode data.


######2. Data Source######
https://tgftp.nws.noaa.gov/SL.us008001/DC.avspt/DS.cip20/PT.grid_DF.gr1/
notice: 1. check the time stamp for the latest version of the icing data
		2. sometime there will be two files are uploaded within 5 min, need to use BOTH OF THEM to obtain the complete information for the current update
		3. current verison of the program **WILL NOT WORK if** the latest data update is **in the format mentioned in notice 2**

######3. Decoding Tool : wgrib2######
The tool used to decode the raw data (**wgrib2**) can be found and download in:
https://www.nco.ncep.noaa.gov/pmb/codes/GRIB2/
For more info about this tool, see:
https://www.cpc.ncep.noaa.gov/products/wesley/wgrib2/
For command line of using this tool, see:
https://www.cpc.ncep.noaa.gov/products/wesley/wgrib2/long_cmd_list.html

##Other useful software: degrib##
https://www.weather.gov/mdl/degrib_download
download and install the GUI, can be used to open the grib file, and convert to other datatype 



##How to use this program######
1. Download the raw data **manually**  https://tgftp.nws.noaa.gov/SL.us008001/DC.avspt/DS.cip20/PT.grid_DF.gr1/
2. Rename the downloaded file to *8latest.bin**
3. Copy **latest.bin** to **/IcingDatabase/wgrib2/data/InputData**, if there is older verison of file exist on that folder, replace it with the new one
4. Run the program, it will take a while for the program to run, database and CSV files will be generare and can be found in folder **output** and **east_output** in this location **IcingDatabase\SQliteTest**



##How this work##
1. Run "Wgrib2Script.bat" (done in main()) to run the wgrib2 decoding tool and pass the preset command to the decoder to obtain decoded data in csv format. The output csv files can be found in "IcingDatabase\wgrib2\data\OutputData"

2. Load csv files, read data and put them in database