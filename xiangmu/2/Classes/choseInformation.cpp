#include "choseInformation.h"
choseInformation *choseInformation::instence = nullptr;
choseInformation *choseInformation::getInstence(){
	if(instence == nullptr){
		instence = new choseInformation();
	}
	return instence;
}
void choseInformation::setFileNameXml(std::string name){
	this->fileNameXml = name;
}
std::string choseInformation::getFileNameXml(){
	return this->fileNameXml;
	
}
void choseInformation::setImageName(std::string name){
	this->imageName = name;
}
std::string choseInformation::getImageName(){
	return this->imageName;
}