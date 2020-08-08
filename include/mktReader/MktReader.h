#pragma once

#include <thirdparty/rapidcsv/rapidcsv.h>
#include <string>
#include <vector>

class MktReader{
public:
	std::vector<char> type;
	std::vector<int> orderId;
	std::vector<char> side;
	std::vector<int> size;
	std::vector<int> px;

	MktReader(const std::string &aMktDataFile){
		readCsv(aMktDataFile);
	}

	~MktReader(){
	}

protected:


	void readCsv(const std::string &aCsvFile) {
		rapidcsv::Document myDoc(aCsvFile, rapidcsv::LabelParams(-1, -1));
		type = myDoc.GetColumn<char>(0);
		orderId = myDoc.GetColumn<int>(1);
		side = myDoc.GetColumn<char>(2);
		size = myDoc.GetColumn<int>(3);
		px = myDoc.GetColumn<int>(4);
		return;
	}
};




