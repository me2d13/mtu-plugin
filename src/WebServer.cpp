#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>
#include "WebServer.h"

using namespace std;

// Handler for when a message is received from the client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	// Parse out the client's request string e.g. GET /index.html HTTP/1.1
	istringstream iss(msg);
	vector<string> parsed((istream_iterator<string>(iss)), istream_iterator<string>());

	// Some defaults for output to the client (404 file not found 'page')
	string content = "<h1>404 Not Found</h1>";
	string htmlFile = "/index.html";
	int errorCode = 404;

	// If the GET request is valid, try and get the name
	if (parsed.size() >= 3 && parsed[0] == "GET")
	{
		htmlFile = parsed[1];

		// If the file is just a slash, use index.html. This should really
		// be if it _ends_ in a slash. I'll leave that for you :)
		if (htmlFile == "/")
		{
			htmlFile = "/index.html";
		}
	}

	if (htmlFile == "/log") {
		// build content from log messages
		ostringstream oss;
		oss << "<html><head><title>Log</title></head><body><h1>Log</h1><ul>";
		if (m_logMessages != nullptr) {
			for (auto& msg : *m_logMessages) {
				string line(msg.begin(), msg.end());
				oss << "<li>" << line << "</li>";
			}
		}
		oss << "</ul></body></html>";
		content = oss.str();
		errorCode = 200;
	} else {

		// Open the document in the local file system
		ifstream f(".\\wwwroot" + htmlFile);

		// Check if it opened and if it did, grab the entire contents
		if (f.good())
		{
			string str((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
			content = str;
			errorCode = 200;
		}
		else {
			cerr << "File not found: " << htmlFile << endl;
		}

		f.close();
	}

	// Write the document back to the client
	ostringstream oss;
	oss << "HTTP/1.1 " << errorCode << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	string output = oss.str();
	int size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), size);
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{

}