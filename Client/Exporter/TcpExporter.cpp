#include "TcpExporter.h"
#include <chrono>

using namespace std::chrono_literals;
TcpExporter::TcpExporter(TcpExporterSettings settings, std::unique_ptr<IDetectionResultSerializer>&& pSerializer) :
	_settings{ std::move(settings) },
	_endpoint{ asio::ip::tcp::endpoint(asio::ip::address::from_string(_settings.tcpServerIp), static_cast<asio::ip::port_type>(_settings.serverPort)) },
	_pSocket{ std::make_unique<asio::ip::tcp::socket>(_ioService,_endpoint.protocol()) },
	_pSerializer{ std::move(pSerializer) }
{
	_pSocket->connect(_endpoint);
}

void TcpExporter::ExportData(const MoveDetectionResult& dataToExport)
{
	std::ignore = dataToExport;
	std::string message{ "Hello server!\r" };
	try
	{
		_pSocket->send((asio::buffer(message.data(), message.size())));
	}
	catch (const std::exception& ex)
	{
		auto what = ex.what();
		int x = 1;
		int y = 2;
		int z = x + y;
	}
}
