/**
 * XML Serialization
 * Simple and lightweight xml serialization class
 * 
 * Original code by Lothar Perr
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely
 */

#include <iostream>
#include <sstream>
#include "xmlserialization.h"

using namespace xmls;

class LastUsedDocument: public Serializable
{
public:
	LastUsedDocument();
	xString Name;
	xString Path;
	xInt Size;
};

class DatabaseLogin: public Serializable
{
public:
	DatabaseLogin();
	xString HostName;
	xInt Port;
	xString User;
	xString Password;
};

class ApplicationSettings: public Serializable
{
public:
	ApplicationSettings();
	xString Setting1;
	xString Setting2;
	xString Setting3;
	xInt Setting4;
	xInt Setting5;
	xBool Setting6;
	xBool Setting7;
	DatabaseLogin Login;
	Collection<LastUsedDocument> LastUsedDocuments;
};

LastUsedDocument::LastUsedDocument()
{
	setClassName("LastUsedDocument"); 
	Register("Name", &Name); 
	Register("Path", &Path);
	Register("Size", &Size);
};

DatabaseLogin::DatabaseLogin()
{
	setClassName("DatabaseLogin");
	Register("HostName", &HostName);
	Register("Port", &Port);
	Register("User", &User);
	Register("Password", &Password);
};

ApplicationSettings::ApplicationSettings()
{
	setClassName("ApplicationSettings");
	Register("Setting1", &Setting1);
	Register("Setting2", &Setting2);
	Register("Setting3", &Setting3);
	Register("Setting4", &Setting4);
	Register("Setting5", &Setting5);
	Register("Setting6", &Setting6);
	Register("Setting7", &Setting7);
	Register("Login", &Login);
	Register("LastUsedDocuments", &LastUsedDocuments);
	setVersion("2.1");
};

int main()
{
	// Creating the settings object 
	cout << "Creating object..." << endl;
	ApplicationSettings *settings=new ApplicationSettings;
	settings->Setting1="Settings string 1";
	settings->Setting2="Settings string 2";
	settings->Setting3="Settings string 3";
	settings->Setting4=1234;
	settings->Setting5=5678;
	settings->Setting6=false;
	settings->Setting7=true;
	settings->Login.HostName="my.db.Settings.server.local";
	settings->Login.Port=2000;
	settings->Login.User="john.smith";
	settings->Login.Password="JohnSmithPassword";

	for (int docNum=1; docNum<=10; docNum++)
	{
		LastUsedDocument *doc = settings->LastUsedDocuments.newElement();
		std::stringstream docName;
		docName << "Document #" << docNum;
		doc->Name = docName.str();
		doc->Path = "{FILEPATH}"; // Set Placeholder for search/replace
		doc->setVersion("1.1");
	}

	cout << "OK" << endl;

	// Serialize the Settings object
	cout << "Serializing object... " << endl;
	string xmlData = settings->toXML();
	cout << "OK" << endl << endl;
	cout << "Result:" << endl;
	cout << xmlData << endl << endl;

	cout << "Login, URL:" << endl;
	cout << "Hostname: " << settings->Login.HostName.value();
	cout << ":" << settings->Login.Port.toString() << endl << endl;
	cout << "Show all collection items" << endl;
	for (size_t i=0; i<settings->LastUsedDocuments.size(); i++)
	{
		LastUsedDocument* doc = settings->LastUsedDocuments.getItem(i);
		cout << "Item " << i << ": " << doc->Name.value() << endl;
	}
	cout << endl;

	cout << "Deserialization:" << endl;
	cout << "Class version: " << Serializable::IdentifyClassVersion(xmlData) << endl;
	cout << "Performing deserialization..." << endl;

	// Deserialize the XML text
	ApplicationSettings* dser_Settings=new ApplicationSettings;
	if (Serializable::fromXML(xmlData, dser_Settings))
	{
		cout << "OK" << endl << endl;

		// compare both objects
		cout << "Compareing objects: ";
		if (dser_Settings->Compare(settings))
			cout << "equal" << endl << endl; else
			cout << "net equal" << endl << endl; 
		
		// now set value
		cout << "Set new value for field >password<..." << endl;
		dser_Settings->Login.Password = "newPassword";
		cout << "OK" << endl << endl;

		cout << "compare objects again: ";
		if (dser_Settings->Compare(settings))
			cout << "equal" << endl << endl; else
			cout << "net equal" << endl << endl; 


		cout << "search and replace placeholders: ";
		dser_Settings->Replace("{FILEPATH}", "c:\\temp\\");
		cout << "OK" << endl << endl;

		//output xml-data
		cout << "Serialize and output xml data: " << endl;
		cout << dser_Settings->toXML() << endl << endl;

		cout << "Clone object:" << endl;
		ApplicationSettings *clone1(new ApplicationSettings);
		Serializable::Clone(dser_Settings, clone1);
		cout << "Serialize and output clone: " << endl;
		cout << clone1->toXML() << endl << endl;
		delete (clone1);
	}
	delete(settings);
	delete(dser_Settings);
	getchar();
	return 0;
}
