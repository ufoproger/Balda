#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Exception.h"

#include <iostream>
#include <vector>
#include <glibmm.h>

#include "Poco/String.h"

#include "cmdictionary.h"
#include "cbalda.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::NameValueCollection;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerParams;
using Poco::Net::ServerSocket;
using Poco::Net::HTTPServer;
using Poco::Net::HTMLForm;
using Poco::cat;

CMDictionary *dictionary;

class FormRequestHandler: public HTTPRequestHandler
{
public:
	FormRequestHandler() 
	{
	}
	
	void handleRequest (HTTPServerRequest &request, HTTPServerResponse &response)
	{
		Application& app = Application::instance();
		app.logger().information("Запрос от " + request.clientAddress().toString());
		
		
//		std::cout << request.getURI() << std::endl;
		
//		std::string filename(request.getURI().substr(0, request.getURI().find("?")));
//		app.logger().information("Файл: " + filename);
		
		/*
		if (opendir(std::string("www" + filename).c_str()) != NULL)
		{
			response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
			return;
		}
		
		if (filename != "balda.json")
		{
			ifstream fin(filename.c_str());
			
			if (fin.is_open())
			{
			
			}
			
			return;
		}
	*/	
		response.setChunkedTransferEncoding(true);
		std::ostream &ostr = response.send();

	//	try
	//	{
//			response.sendFile("/media/hdisk0/programming/project/anbal/2001/www" + filename, "text/plain");
//		}
	//	catch (...)
	//	{
//			ostr << "BAD" << std::endl;
	//	}
		
//		return;
	
		response.setContentType("text/javascript; charset=UTF-8");
		HTMLForm form(request, request.stream());
				
		if (!form.empty())
		{
			std::map < std::string , Glib::ustring > params;

			for (NameValueCollection::ConstIterator it = form.begin(); it != form.end(); ++it)
				params[it->first] = Glib::ustring(it->second);
			
			if (params["map"].length() != 25)
				return;
			
			std::vector < std::vector < SMyGUniChar > > char_map(5, std::vector < SMyGUniChar >(5));
			Glib::ustring u_map = params["map"];
			
			for (int i = 0, len = u_map.length(); i < len; ++i)
				char_map[i / 5][i % 5] = SMyGUniChar(u_map[i], i / 5, i % 5, u_map[i] == Glib::ustring(".")[0]);
			
			CBalda balda(*dictionary);
			std::vector < Glib::ustring > words = balda.calc(char_map);
			
			ostr << params["callback"] << "({\"word\": [\"" << cat(std::string("\", \""), words.begin(), words.end()) << "\"]})";
		}
	}
};

class FormRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
	FormRequestHandlerFactory ()
	{
	}

	HTTPRequestHandler* createRequestHandler (const HTTPServerRequest &request)
	{
		return new FormRequestHandler;
	}
};


class HTTPMainServer: public Poco::Util::ServerApplication
{
public:

	HTTPMainServer ()
	{
	}
	
	~HTTPMainServer ()
	{
	}

protected:
	void initialize (Application &self)
	{
		loadConfiguration();
		
		Application &app = Application::instance();
		
		dictionary = new CMDictionary("output.txt");
		logger().information("Словарь загружен");
		
		ServerApplication::initialize(self);
	}

	int main (const std::vector<std::string> &args)
	{
		ServerSocket socket(9980);
		HTTPServer server(new FormRequestHandlerFactory, socket, new HTTPServerParams);

		server.start();

		logger().information("Сервер запущен");
		waitForTerminationRequest();
		server.stop();
		logger().information("Сервер остановлен");

		return Application::EXIT_OK;
	}
};

int main(int argc, char *argv[])
{	
	HTTPMainServer app;
	return app.run(argc, argv);
}

