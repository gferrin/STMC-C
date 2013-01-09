/*  Author: Gabriel Ferrin , Date: 10-20-2012
	
	This function takes in an array and the array size as well as an optional
	third parameter which is used to index the plots if more then one is being 
	generated by the same routine. If the third param is passed it must be called 
	in assending order or it will lead to an inacurate qdf.plt file
*/

#ifndef QDF_GNU_H
#define QDF_GNU_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int qdf_gnu(double array[], int arraySize, int timesCalled = 0);

int qdf_gnu(double array[], int arraySize, int timesCalled)
{
	//string plotNumber = timesCalled;
	

	int ICNT = timesCalled + 1;
	const double extraZero = 0.0000000;
	const double extraOne = 1.0000000;
	const int precision = 7;

	//cout<<setiosflags(ios::fixed)<<setprecision(precision);

	// if this has been run on the same dataset more then 99 times
	// exit the program and print error
	if( ICNT > 99 ) {
		cout << "DF_GNU: INCT=99 Exhausted!" << endl;
		return 0; 
	}

	// need to create a string of the file name
	stringstream plotFilenameStream,dataFilenameStream;
	if( ICNT <= 9 ){
		plotFilenameStream << "qdf" << extraZero << ICNT << ".plt";	
		dataFilenameStream << "qdf" << extraZero << ICNT << ".d"; 
	} else {
		plotFilenameStream << "qdf" << ICNT <<  ".plt";
		dataFilenameStream << "qdf" << ICNT << ".d"; 
	}
	// convert the file names to strings
	string dataFilename = dataFilenameStream.str(),plotFilename = plotFilenameStream.str(),
						  totalPlotFilename	= "qdf.plt"; 
	// open the new data file
	ofstream outstream((plotFilename).c_str());;
	// write to the file the needed information 
	outstream << "set noyzeroaxis\n" << "set yrange [0:0.525]\n" << "plot \""
			  << dataFilename << "\" using 1:3 with line lt 1\n" << "pause -1\n";
	// close file
	outstream.close();
	// open new file
	ofstream outstreamTotalPlot; 
	if(ICNT >= 2 ){ // this assumes that this function is always called in order
					// consider changing 
		outstreamTotalPlot.open((totalPlotFilename).c_str());
		outstreamTotalPlot << "set noyzeroaxis\n" << "set yrange [0:0.525]\n" 
			  			   << "plot \"qdf01.d\" using 1:3 with line lt 1,\\\n";
		
		// now add filenames to list making sure not to give the last one a backslash
		for(int j = 2; j <= ICNT; j++){
			if(j != ICNT){
				if( ICNT <= 9 ){
					outstreamTotalPlot << "\t \"qdf" << extraZero << j << ".d\""
					 					<< " using 1:3 with line lt " << j <<",\\\n";
				} else {
					outstreamTotalPlot << "\t \"qdf" << j << ".d\""
					 					<< " using 1:3 with line lt " << j <<",\\\n";
				}
			} else {
				if( ICNT <= 9 ){
					outstreamTotalPlot << "\t \"qdf" << extraZero << j << ".d\""
					 					<< " using 1:3 with line lt " << j <<"\n" << "pause -1\n";
				} else {
					outstreamTotalPlot << "\t \"qdf" << j << ".d\""
					 					<< " using 1:3 with line lt " << j << "\n" << "pause -1\n";
				}
			}
		}
	} 
	
	// close the file
	outstreamTotalPlot.close();
	// open stream for data file
	ofstream dataOutStream((dataFilename).c_str());
	// write the first element of the array followed by two zeros
	dataOutStream.precision(precision);

	dataOutStream.setf(ios::left);
	
	dataOutStream << fixed << array[0] << '\t' << extraZero << '\t' << extraZero << endl;
	
	for (int i = 0; i < (arraySize - 1); ++i)
	{	
		if(array[i+1] < array[i]){
			cout << "QDF_GNU: Data not sorted." << endl;
			break;
		}
		double F = ((i*extraOne)/(arraySize * extraOne)); //  this may need to be arraySize-1  
		double Fq;
		if(F < (extraOne - F)){
			Fq = F;
		} else {
			Fq = (extraOne - F);
		}
	 	dataOutStream << array[i] << '\t' << F  << '\t' << Fq << endl;

	 	dataOutStream << array[i+1] << '\t' << F << '\t' << Fq << endl;
	}
	// this is different then < arraysize -1
	dataOutStream << array[arraySize-1] << '\t' << extraOne << '\t' << extraZero << endl;
	// close the data file;
	dataOutStream.close();

	return 0;
}

#endif /* QDF_GNU_H */