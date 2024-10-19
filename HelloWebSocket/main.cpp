#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/ServerApplication.h>

#include <string>
#include <vector>


class PageRequestHandler : public Poco::Net::HTTPRequestHandler
{
	void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
	{
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");
		std::ostream &ostr = response.send();
		ostr << "<html>";
		ostr << "<body>";
		ostr << "  <font color='red'>Hello WebSocket</font>";
		ostr << "</body>";
		ostr << "</html>";
	}
};

class WebSocketFactory : public Poco::Net::HTTPRequestHandlerFactory
{
	Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request)
	{
		/*
		if (request.find("Upgrade") != request.end() && request["Upgrade"] == "websocket")
			return new WebSocketRequestHandler;
		else
			return new PageRequestHandler;
		*/
		return new PageRequestHandler;
	}
};

class WebSocketServer : public Poco::Util::ServerApplication
{
	int main(const std::vector<std::string> &args)
	{
		unsigned short port = 9980;
		Poco::Net::ServerSocket socket(port);

		Poco::Net::HTTPServer srv(new WebSocketFactory, socket, new Poco::Net::HTTPServerParams);

		srv.start();
		waitForTerminationRequest();
		srv.stop();

		return 0;
	}
};

POCO_SERVER_MAIN(WebSocketServer)