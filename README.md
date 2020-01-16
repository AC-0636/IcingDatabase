# IcingDatabase
###############################
This program is created to obtain the icing information from GRIB.
**The database itself is not included since it excess the limited of the upload file size**
###############################

##Data Source / Reference Link / Tool

######1. Aviation Weather Center (AWC) webpage
https://aviationweather.gov/icing/fip
This webpage display a graphical view of the icing condition, this is used to compare and verify the decode data.


######2. Data Source
https://tgftp.nws.noaa.gov/SL.us008001/DC.avspt/DS.cip20/PT.grid_DF.gr1/
notice: 1. check the time stamp for the latest version of the icing data
		2. sometime there will be two files are uploaded within 5 min, need to use BOTH OF THEM to obtain the complete information for the current update
		3. current verison of the program **WILL NOT WORK if** the latest data update is **in the format mentioned in notice 2**

######3. Decoding Tool
The tool used to decode the raw data (**wgrib2**) can be found and download in:
https://www.nco.ncep.noaa.gov/pmb/codes/GRIB2/
For more info about this tool, see:
https://www.cpc.ncep.noaa.gov/products/wesley/wgrib2/
For command line of using this tool, see:
https://www.cpc.ncep.noaa.gov/products/wesley/wgrib2/long_cmd_list.html


##How to use this program
1. Download the raw data **manually**
2. Rename the downloaded file to "**latest**.bin"
3. Copy **latest.bin** to **/IcingDatabase/wgrib2/data/InputData**, if there is older verison of file exist on that folder, replace it with the new one
4. Run the program, it will take a while for the program to run, a database file **Icing.db** will be generated and it is located in **/IcingDatabase/SQliteTest**
